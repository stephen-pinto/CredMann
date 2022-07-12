using CredMann.Lib.Crypto.BlockCipher;
using Org.BouncyCastle.Crypto;

namespace CredMann.Lib.Crypto.CipherChain
{
    interface IBlockProcessorNode
    {
        IBlockProcessorNode Then(IBlockProcessorNode node);

        //IBlockCipherChainNode Then(IBlockCipherAdapter blockCipherAdapter, ICipherParameters cipherParameters);

        byte[] ApplyProcessing(byte[] data);

        byte[] UndoProcessing(byte[] data);
    }
}
