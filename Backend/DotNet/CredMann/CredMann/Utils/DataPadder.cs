using System;
using System.Linq;

namespace CredMann.Utils
{
    public class DataPadder
    {
        private const string padIdentifier = "#$CMPAD#";
        private static Random random;

        public DataPadder()
        {
            if (random == null)
                random = new Random();
        }

        public string Pad(string data, int newSize)
        {
            //Check if there is enough space for padding
            if ((data.Length + padIdentifier.Length) < newSize)
            {
                //Before adding random string add pad indentifier for unpadding simplicity
                data += padIdentifier;

                //If there is still room for more padding add random bytes
                if (data.Length < newSize)
                {
                    //Append random string after identifier
                    data += UtilFactory.Instance.GetRandomDataGenerator().GenerateRandomString(newSize - data.Length);
                }
            }
            else
            {
                //FIXME:
                data = data.PadRight(newSize, '0');
            }

            return data;
        }

        public string UnPad(string data, int originalLength = 0)
        {
            //If padded then search for our pad identifier else return original
            if (data.Contains(padIdentifier))
                return data.Substring(0, data.IndexOf(padIdentifier));
            else if (originalLength > 0)
                return data.Substring(0, originalLength);
            else
                return data;
        }
    }
}
