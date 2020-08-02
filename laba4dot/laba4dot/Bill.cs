using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba4dot
{
    class Bill
    {
        private string nameOfClient;
        private DateTime dateOfBill;
        private string nameOfBill;
        private double balance;

        public Bill(string nameOfClient, DateTime dateOfBill, string nameOfBill, double balance)
        {
            NameOfClient = nameOfClient;
            DateOfBill = dateOfBill;
            NameOfBill = nameOfBill;
            Balance = balance;
        }

        public string NameOfClient { get =>nameOfClient; set => nameOfClient = value; }
        public DateTime DateOfBill { get => dateOfBill; set => dateOfBill = value; }
        public string NameOfBill { get => nameOfBill; set => nameOfBill = value; }
        public double Balance
        {
            get => balance; set => balance = value;
        }
    }
}
