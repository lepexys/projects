using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba4dot
{
    interface IRepository
    {
        IEnumerable<Bill> GetBills();
        IEnumerable<PayDoc> GetPayDocs();
        void SetPayDocs(IEnumerable<Payment> payments);
    }
}
