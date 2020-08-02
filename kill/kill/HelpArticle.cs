using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
    class HelpArticle : IComparer<Article>
    {
        public int Compare(Article x, Article y)
        {
            if (x.Rat > y.Rat)
                return 1;
            if (x.Rat < y.Rat)
                return -1;
            else
                return 0;
        }
    }
}