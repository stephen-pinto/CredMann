using CredMann.Lib.Types;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Parameters;

namespace CredMann.Lib.Crypto.BlockCipher
{
    public class BlockCipherAdapter : IBlockCipherAdapter
    {
        protected BufferedBlockCipher bufferedBlockCipher;
        protected BlockCipherEngine cipherEngine;

        public BlockCipherEngine CipherEngine
        {
            get
            {
                if (bufferedBlockCipher != null)
                    return CipherEnumMapper.GetEngineType(bufferedBlockCipher.AlgorithmName);
                else
                    return BlockCipherEngine.None;
            }
        }

        public BlockCipherAdapter(BufferedBlockCipher blockCipher)
        {
            bufferedBlockCipher = blockCipher;            
        }

        public byte[] Encrypt(ParametersWithIV key, byte[] data)
        {
            bufferedBlockCipher.Init(true, key);
            byte[] cipherText = Process(data);
            return cipherText;
        }

        public byte[] Decrypt(ParametersWithIV key, byte[] data)
        {
            bufferedBlockCipher.Init(false, key);
            byte[] plainText = Process(data);
            return plainText;
        }

        private byte[] Process(byte[] data)
        {
            //Prepare output buffer
            byte[] output = new byte[bufferedBlockCipher.GetOutputSize(data.Length)];

            //Process these bytes
            int bytesProcessed = bufferedBlockCipher.ProcessBytes(
                    data,
                    0,
                    data.Length,
                    output,
                    0
            );

            //Finalize
            bufferedBlockCipher.DoFinal(output, bytesProcessed);
            return output;
        }
    }
}
