using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba4dot
{
    class Payment
    {
        private string nameOfClient;
        private DateTime dateOfPayment;
        private string nameOfPayment;
        private DateTime dateOfBill;
        private string nameOfBill;
        private double sumOfPayment;

        public Payment(string nameOfClient, DateTime dateOfPayment, string nameOfPayment, DateTime dateOfBill, string nameOfBill, double sumOfPayment)
        {
            NameOfClient = nameOfClient;
            DateOfPayment = dateOfPayment;
            NameOfPayment = nameOfPayment;
            DateOfBill = dateOfBill;
            NameOfBill = nameOfBill;
            SumOfPayment = sumOfPayment;
        }

        public string NameOfClient { get => nameOfClient; set => nameOfClient = value; }
        public DateTime DateOfPayment { get => dateOfPayment; set => dateOfPayment = value; }
        public string NameOfPayment { get => nameOfPayment; set => nameOfPayment = value; }
        public DateTime DateOfBill { get => dateOfBill; set => dateOfBill = value; }
        public string NameOfBill { get => nameOfBill; set => nameOfBill = value; }
        public double SumOfPayment { get => sumOfPayment; set => sumOfPayment = value; }
    }
}
