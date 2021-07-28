using CredMann.Lib.Crypto.BlockCipher;
using CredMann.Lib.Types;
using Org.BouncyCastle.Crypto.Parameters;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CredMann.Lib.Crypto.CipherChain
{
    public class CipherChainStack : Stack<KeyValuePair<BlockCipherEngine, ParametersWithIV>>
    {
        protected BlockCipherAdapterFactory factory;
        protected IBlockCipherAdapter[] adapterChain;
        protected bool isModified;
        private object syncObj = new object();

        public CipherChainStack(BlockCipherAdapterFactory adptrFactory)
        {
            factory = adptrFactory;
            isModified = true;
        }

        public void Push(BlockCipherEngine engine, ParametersWithIV iv)
        {
            lock (syncObj)
            {
                isModified = true;
                base.Push(new KeyValuePair<BlockCipherEngine, ParametersWithIV>(engine, iv));
            }
        }

        public new void Push(KeyValuePair<BlockCipherEngine, ParametersWithIV> item)
        {
            lock (syncObj)
            {
                isModified = true;
                base.Push(item);
            }
        }

        public new KeyValuePair<BlockCipherEngine, ParametersWithIV> Pop()
        {
            lock (syncObj)
            {
                isModified = true;
                return base.Pop();
            }
        }

        public new void Clear()
        {
            lock (syncObj)
            {
                isModified = true;
            }
        }

        protected void UpdateChanges()
        {
            lock (syncObj)
            {
                isModified = false;
                adapterChain = null;

                if (Count == 0)
                    return;

                //Initialize a new array
                adapterChain = new IBlockCipherAdapter[Count];

                //The last cipher algorithm will need padding so collect the rest without padding first
                int i = 0;
                for (; i < (Count - 1); i++)
                    adapterChain[i] = factory.GetAdapter(this.ElementAt(i).Key);

                //Get the last alogorithm with padding
                adapterChain[i] = factory.GetAdapter(this.ElementAt(i).Key, true);
            }
        }
    }
}
