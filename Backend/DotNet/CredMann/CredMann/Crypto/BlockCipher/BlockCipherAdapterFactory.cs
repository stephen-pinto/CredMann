using CredMann.Types;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Modes;
using Org.BouncyCastle.Crypto.Paddings;
using System;

namespace CredMann.Crypto.BlockCipher
{
    public class BlockCipherAdapterFactory
    {
        public BlockCipherAdapter GetAdapter(BlockCipherEngine engine, bool enablePadding = false)
        {
            var type = CipherEnumMapper.GetEngine(engine);
            var instance = GetEngineInstance(type);
            BlockCipherAdapter adapter = PrepareAdapter(instance, enablePadding);
            return adapter;
        }

        public IBlockCipher GetEngineInstance(Type type)
        {
            return (IBlockCipher)Activator.CreateInstance(type);
        }

        private BlockCipherAdapter PrepareAdapter(IBlockCipher engine, bool padding = false)
        {
            BufferedBlockCipher buffBlockCipher;
            SicBlockCipher sicBlockCipher = new SicBlockCipher(engine);

            if (padding)
                buffBlockCipher = new PaddedBufferedBlockCipher(sicBlockCipher, new Pkcs7Padding());
            else
                buffBlockCipher = new BufferedBlockCipher(sicBlockCipher);

            return new BlockCipherAdapter(buffBlockCipher);
        }
    }
}
