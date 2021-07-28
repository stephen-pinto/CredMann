using CredMann.Types;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Engines;
using System;

namespace CredMann.Crypto.BlockCipher
{
    public static class CipherEnumMapper
    {
        public static Type GetEngine(BlockCipherEngine cipherEngineType)
        {
            switch(cipherEngineType)
            {
                case BlockCipherEngine.Rijndael:
                    return typeof(RijndaelEngine);
                case BlockCipherEngine.Serpent:
                    return typeof(SerpentEngine);
                case BlockCipherEngine.Twofish:
                    return typeof(TwofishEngine);
                case BlockCipherEngine.Blowfish:
                    return typeof(BlowfishEngine);
                case BlockCipherEngine.Aes:
                case BlockCipherEngine.Default:
                default:
                    return typeof(AesEngine);
             }
        }

        public static BlockCipherEngine GetEngineType(Type engineType)
        {
            if(typeof(RijndaelEngine).Equals(engineType))
            {
                return BlockCipherEngine.Rijndael;
            }
            else if (typeof(SerpentEngine).Equals(engineType))
            {
                return BlockCipherEngine.Serpent;
            }
            else if (typeof(TwofishEngine).Equals(engineType))
            {
                return BlockCipherEngine.Twofish;
            }
            else if (typeof(BlowfishEngine).Equals(engineType))
            {
                return BlockCipherEngine.Blowfish;
            }
            else  //if (typeof(AesEngine).Equals(engineType))
            {
                return BlockCipherEngine.Aes;
            }
        }

        public static BlockCipherEngine GetEngineType(string name)
        {
            foreach (var item in Enum.GetNames(typeof(BlockCipherEngine)))
            {
                if (item.ToString().Equals(name, StringComparison.OrdinalIgnoreCase))
                    return (BlockCipherEngine)Enum.Parse(typeof(BlockCipherEngine), item.ToString());
            }

            throw new NotSupportedException(name + " is spelled wrong or the engine is not supported.");
        }
    }
}
