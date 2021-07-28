using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CredMann.Lib.Extensions
{
    public static class ArrayExtensions
    {
        public static bool IsNullOrEmtpy<T>(this T[] array)
        {
            return array == null || array.Length == 0;
        }
    }
}
