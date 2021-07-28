using Org.BouncyCastle.Crypto.Parameters;

namespace CredMann.Lib.Crypto.BlockCipher
{
    public interface IBlockCipherAdapter
    {
        byte[] Encrypt(ParametersWithIV key, byte[] data);
        
        byte[] Decrypt(ParametersWithIV key, byte[] data);
    }
}
