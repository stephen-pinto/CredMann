using System;
using System.Text;

namespace CredMann.Lib.Common
{
    /// <summary>
    /// This class provides the default configurations/options for the services
    /// </summary>
    public class DefaultConfig : AppConfig
    {
        private static Lazy<DefaultConfig> defaultInstance = new Lazy<DefaultConfig>(() => new DefaultConfig());

        protected DefaultConfig()
        {

        }

        public override Encoding Encoding
        {
            get => Encoding.UTF8;
            protected set => base.Encoding = value;
        }

        public override short KeySize { get => 128; set => base.KeySize = value; }

        public static DefaultConfig Default { get => defaultInstance.Value; }
    }
}
