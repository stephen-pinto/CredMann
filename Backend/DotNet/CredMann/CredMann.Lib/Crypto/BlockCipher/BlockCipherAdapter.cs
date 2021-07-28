using CredMann.Lib.Types;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Parameters;

namespace CredMann.Lib.Crypto.BlockCipher
{
    public class BlockCipherAdapter : IBlockCipherAdapter
    {
        protected BufferedBlockCipher _bufferedBlockCipher;
        protected BlockCipherEngine _cipherEngine;

        public BlockCipherEngine CipherEngine
        {
            get
            {
                if (_bufferedBlockCipher != null)
                    return CipherEnumMapper.GetEngineType(_bufferedBlockCipher.AlgorithmName);
                else
                    return BlockCipherEngine.None;
            }
        }

        public BlockCipherAdapter(BufferedBlockCipher blockCipher)
        {
            _bufferedBlockCipher = blockCipher;            
        }

        public byte[] Encrypt(ParametersWithIV key, byte[] data)
        {
            _bufferedBlockCipher.Init(true, key);
            byte[] cipherText = Process(data);
            return cipherText;
        }

        public byte[] Decrypt(ParametersWithIV key, byte[] data)
        {
            _bufferedBlockCipher.Init(false, key);
            byte[] plainText = Process(data);
            return plainText;
        }

        private byte[] Process(byte[] data)
        {
            //Prepare output buffer
            byte[] output = new byte[_bufferedBlockCipher.GetOutputSize(data.Length)];

            //Process these bytes
            int bytesProcessed = _bufferedBlockCipher.ProcessBytes(
                    data,
                    0,
                    data.Length,
                    output,
                    0
            );

            //Finalize
            _bufferedBlockCipher.DoFinal(output, bytesProcessed);
            return output;
        }
    }
}
