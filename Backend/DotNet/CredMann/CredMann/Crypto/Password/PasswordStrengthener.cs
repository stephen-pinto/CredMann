using CredMann.Common;
using CredMann.Utils;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Crypto.Prng;
using System;

namespace CredMann.Crypto.Password
{
    public class PasswordStrengthener
    {
        private PbeParametersGenerator parametersGenerator;
        private DigestRandomGenerator digestRandomGenerator;

        public PasswordStrengthener(DigestRandomGenerator digestGenerator, PbeParametersGenerator paramGenerator)
        {
            parametersGenerator = paramGenerator;
            digestRandomGenerator = digestGenerator;
        }

        #region Salt generators

        public byte[] GenerateSalt(int size = 16)
        {
            byte[] newSalt = new byte[size];
            digestRandomGenerator.NextBytes(newSalt);
            return newSalt;
        }

        #endregion

        #region Key generators
        public byte[] GenerateKey()
        {
            //Fixme pick from configuration
            return UtilFactory.Instance.GetRandomDataGenerator().GenerateKey(DefaultConfig.Default.KeySize);
        }

        public byte[] GenerateKey(ref string password, byte[] salt, int iterationCount = CommonConstants.DefaultIterationCount)
        {
            KeyParameter keyParam;
            char[] pass = null;

            try
            {
                if (string.IsNullOrWhiteSpace(password))
                    throw new ArgumentNullException(nameof(password));

                //Convert from securestring to regular char array
                pass = password.ToCharArray();

                keyParam = (KeyParameter)GenerateKeyParam(ref pass, ref salt, iterationCount);
            }
            finally
            {
                //Make sure the copies dont preserve any copy of the user's password
                if (pass != null)
                {
                    for (int i = 0; i < pass.Length; i++)
                        pass[0] = '0';
                }
            }

            return keyParam.GetKey();
        }

        public ParametersWithIV GenerateParametersWithIV(ref string password, byte[] salt, int iterationCount = CommonConstants.DefaultIterationCount)
        {
            ParametersWithIV paramWithIV;
            char[] pass = null;

            try
            {
                if (string.IsNullOrWhiteSpace(password))
                    throw new ArgumentNullException(nameof(password));

                //Convert from securestring to regular char array
                pass = password.ToCharArray();

                var keyParam = GenerateKeyParam(ref pass, ref salt, iterationCount);
                paramWithIV = new ParametersWithIV(keyParam, salt);
            }
            finally
            {
                //Make sure the copies dont preserve any copy of the user's password
                if (pass != null)
                {
                    for (int i = 0; i < pass.Length; i++)
                        pass[0] = '0';
                }
            }

            return paramWithIV;
        }

        public ParametersWithIV GenerateParametersWithIV(ref byte[] password, byte[] salt, int iterationCount = CommonConstants.DefaultIterationCount)
        {
            ParametersWithIV paramWithIV;
            char[] pass = null;

            try
            {
                if (password == null || password.Length == 0)
                    throw new ArgumentNullException(nameof(password));

                pass = DefaultConfig.Default.Encoding.GetString(password).ToCharArray();

                var keyParam = GenerateKeyParam(ref pass, ref salt, iterationCount);
                paramWithIV = new ParametersWithIV(keyParam, salt);
            }
            finally
            {
                //Make sure the copies dont preserve any copy of the user's password
                if (pass != null)
                {
                    for (int i = 0; i < pass.Length; i++)
                        pass[0] = '0';
                }
            }

            return paramWithIV;
        }

        #endregion

        #region Private members

        private ICipherParameters GenerateKeyParam(ref char[] password, ref byte[] salt, int iterationCount = CommonConstants.DefaultIterationCount)
        {
            //Initialize the generator
            parametersGenerator.Init(
                PbeParametersGenerator.Pkcs5PasswordToUtf8Bytes(password),
                salt,
                iterationCount);

            //Set algorithm and key size
            //RC4, AES            
            return parametersGenerator.GenerateDerivedParameters(CommonConstants.DerrivedParamsAlgorithm, DefaultConfig.Default.KeySize);
        }

        #endregion
    }
}
