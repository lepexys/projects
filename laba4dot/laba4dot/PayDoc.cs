using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba4dot
{
    class PayDoc
    {
        private string nameOfClient;
        private DateTime dateOfPayment;
        private string nameOfPayment;
        private double sumOfPayment;

        public PayDoc(string nameOfClient, DateTime dateOfPayment, string nameOfPayment, double sumOfPayment)
        {
            NameOfClient = nameOfClient;
            DateOfPayment = dateOfPayment;
            NameOfPayment = nameOfPayment;
            SumOfPayment = sumOfPayment;
        }

        public string NameOfClient { get => nameOfClient; set => nameOfClient = value; }
        public DateTime DateOfPayment { get => dateOfPayment; set => dateOfPayment = value; }
        public string NameOfPayment { get => nameOfPayment; set => nameOfPayment = value; }
        public double SumOfPayment { get => sumOfPayment; set => sumOfPayment = value; }
    }
}
