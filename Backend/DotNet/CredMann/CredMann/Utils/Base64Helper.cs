using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CredMann.Utils
{
    public class Base64Helper
    {
        public byte[] FromBase64(byte[] data)
        {
            var base64Str = Encoding.UTF8.GetString(data);
            var regularData = Convert.FromBase64String(base64Str);
            return regularData;
        }

        public byte[] ToBase64(byte[] data)
        {
            var base64Str = Convert.ToBase64String(data);
            var base64Data = Encoding.UTF8.GetBytes(base64Str);
            return base64Data;
        }
    }
}
