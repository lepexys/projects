using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
    class HelpEdition : IComparer<Edition>
    {
        public int Compare(Edition x, Edition y)
        {
                if (x.Tire > y.Tire)
                    return 1;
                if (x.Tire < y.Tire)
                    return -1;
                else
                    return 0;
        }
    }
}
