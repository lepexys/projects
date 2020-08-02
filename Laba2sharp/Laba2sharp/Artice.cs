using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba2sharp
{

    class Artice : IComparer<Article>
    {
        public int Compare(Article x, Article y)
        {
            if (x.Rating > y.Rating)
                return 1;
            else if (x.Rating < y.Rating)
                return -1;
            else
                return 0;
        }
    }

}