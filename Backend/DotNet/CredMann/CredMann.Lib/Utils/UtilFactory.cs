using System;

namespace CredMann.Lib.Utils
{
    public class UtilFactory
    {
        private static Lazy<UtilFactory> defaultInstance = new Lazy<UtilFactory>();
        private Lazy<RandomDataGenerator> randomDataGenerator = new Lazy<RandomDataGenerator>();
        private Lazy<Base64Helper> base64Helper = new Lazy<Base64Helper>();
        private Lazy<DataPadder> dataPadder = new Lazy<DataPadder>();

        public static UtilFactory Instance { get => defaultInstance.Value; }

        public RandomDataGenerator GetRandomDataGenerator()
        {
            return randomDataGenerator.Value;
        }

        public Base64Helper GetBase64Helper()
        {
            return base64Helper.Value;
        }

        public DataPadder GetDataPadder()
        {
            return dataPadder.Value;
        }
    }
}
