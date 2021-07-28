using CredMann.Lib.Common;
using System;
using System.Linq;
using System.Security.Cryptography;

namespace CredMann.Lib.Utils
{
    public class RandomDataGenerator
    {
        private Random random;
        private RNGCryptoServiceProvider randomKeyProvider;

        public RandomDataGenerator()
        {
            if (random == null)
                random = new Random();

            if (randomKeyProvider == null)
                randomKeyProvider = new RNGCryptoServiceProvider();
        }

        public byte[] GenerateKey(int length)
        {
            RNGCryptoServiceProvider randomKeyProvider = new RNGCryptoServiceProvider();
            byte[] newKey = new byte[length];
            randomKeyProvider.GetNonZeroBytes(newKey);
            return newKey;
        }

        public string GenerateRandomString(int length)
        {
            //This generate a random unsecure string from the reference char pool
            const string referenceCharPool = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
            return new string(Enumerable.Repeat(referenceCharPool, length)
              .Select(s => s[random.Next(s.Length)]).ToArray());
        }

        public string GenerateRandomStrongString(int length) => DefaultConfig.Default.Encoding.GetString(GenerateKey(length));
    }
}
