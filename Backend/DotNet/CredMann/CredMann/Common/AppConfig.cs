using System.Text;

namespace CredMann.Common
{
    public class AppConfig
    {
        public virtual Encoding Encoding { get; protected set; }
        
        public virtual short KeySize { get; set; }
    }
}
