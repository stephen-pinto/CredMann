using CredMann.Common;
using CredMann.Crypto.BlockCipher;
using CredMann.Types;
using CredMann.Utils;
using Org.BouncyCastle.Crypto.Parameters;
using System;
using System.Collections.Generic;
using System.Linq;

namespace CredMann.Crypto.CipherChain
{
    public class BlockCipherChainAdapter : Stack<KeyValuePair<BlockCipherEngine, ParametersWithIV>>
    {
        private BlockCipherAdapterFactory factory;
        private IBlockCipherAdapter[] adapterChain;
        private bool isModified = true;

        public BlockCipherChainAdapter(BlockCipherAdapterFactory adptrFactory)
        {
            factory = adptrFactory;
        }

        #region Overrides to be aware of changes

        public void Push(BlockCipherEngine engine, ParametersWithIV iv)
        {
            isModified = true;
            base.Push(new KeyValuePair<BlockCipherEngine, ParametersWithIV>(engine, iv));
        }

        public new void Push(KeyValuePair<BlockCipherEngine, ParametersWithIV> item)
        {
            isModified = true;
            base.Push(item);
        }

        public new KeyValuePair<BlockCipherEngine, ParametersWithIV> Pop()
        {
            isModified = true;
            return base.Pop();
        }

        public new void Clear()
        {
            isModified = true;
        }

        #endregion

        public byte[] Encrypt(byte[] data)
        {
            if (isModified)
                UpdateChanges();

            if (Count == 0)
                throw new InvalidOperationException("No engines added!!!");

            byte[] output = PrependBlockSize(data);

            for (int i = 0; i < Count; i++)
            {
                var item = this.ElementAt(i);
                output = adapterChain.ElementAt(i).Encrypt(item.Value, output);
            }

            return output;
        }

        public byte[] Decrypt(byte[] cipherData)
        {
            if (isModified)
                UpdateChanges();

            if (Count == 0)
                throw new InvalidOperationException("No engines added!!!");

            byte[] output = cipherData; 

            for (int i = Count - 1; i >= 0; i--)
            {
                var item = this.ElementAt(i);
                var engine = adapterChain.ElementAt(i);
                output = adapterChain.ElementAt(i).Decrypt(item.Value, output);
            }

            return StripBlockSize(output);
        }

        #region Private members

        private byte[] PrependBlockSize(byte[] originalData)
        {
            byte[] dataLenTag = DefaultConfig.Default.Encoding.GetBytes("[" + originalData.Length + "]");
            byte[] newData = new byte[originalData.Length + dataLenTag.Length];
            Array.Copy(dataLenTag, 0, newData, 0, dataLenTag.Length);
            Array.Copy(originalData, 0, newData, dataLenTag.Length, originalData.Length);
            return newData;
        }

        private byte[] StripBlockSize(byte[] data)
        {
            string numStr = "";

            if ((char)data[0] != '[')
                return null;

            int i = 1;
            for (; i < data.Length; i++)
            {
                if ((char)data[i] == ']')
                    break;

                numStr += (char)data[i];
            }

            if (i == data.Length)
                return null;

            int size = int.Parse(numStr);
            int index = i + 1;
            byte[] originalData = new byte[size];
            Array.Copy(data, index, originalData, 0, size);
            return originalData;
        }

        private void UpdateChanges()
        {
            isModified = false;
            adapterChain = null;

            if (Count == 0)
                return;

            adapterChain = new IBlockCipherAdapter[Count];

            int i = 0;

            //The last cipher algorithm will need padding so collect the rest without padding first
            for (; i < (this.Count - 1); i++)
                adapterChain[i] = factory.GetAdapter(this.ElementAt(i).Key);

            //Get the last alogorithm with padding
            adapterChain[i] = factory.GetAdapter(this.ElementAt(i).Key, true);
        }

        #endregion
    }
}
