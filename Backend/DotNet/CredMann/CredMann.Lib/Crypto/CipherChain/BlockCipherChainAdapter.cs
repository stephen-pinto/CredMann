using CredMann.Lib.Common;
using CredMann.Lib.Crypto.BlockCipher;
using CredMann.Lib.Extensions;
using CredMann.Lib.Types;
using Org.BouncyCastle.Crypto.Parameters;
using System;
using System.Collections.Generic;
using System.Linq;

namespace CredMann.Lib.Crypto.CipherChain
{
    public class BlockCipherChainAdapter : CipherChainStack
    {
        public BlockCipherChainAdapter(BlockCipherAdapterFactory adptrFactory) : base(adptrFactory)
        { }

        public byte[] Encrypt(byte[] data)
        {
            if (data.IsNullOrEmtpy())
                throw new ArgumentException("Data is null or empty");

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
            if (cipherData.IsNullOrEmtpy())
                throw new ArgumentException("Data is null or empty");

            if (isModified)
                UpdateChanges();

            if (Count == 0)
                throw new InvalidOperationException("No engines added!!!");

            byte[] output = cipherData;

            for (int i = Count - 1; i >= 0; i--)
            {
                var item = this.ElementAt(i);
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

            if (data.IsNullOrEmtpy())
                throw new ArgumentException("Data is null or empty");

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

        #endregion
    }
}
