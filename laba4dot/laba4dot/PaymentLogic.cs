using Microsoft.VisualBasic.FileIO;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace laba4dot
{
    class PaymentLogic
    {
        private string nameOfBillFile;
        private string nameOfPayDocFile;
        private IEnumerable<Bill> listOfBills;
        private IEnumerable<PayDoc> listOfPayDoc;
        private List<Payment> listOfPayments = new List<Payment>();
        public PaymentLogic(string nameOfBillFile, string nameOfPayDocFile)
        {
            this.nameOfBillFile = nameOfBillFile;
            this.nameOfPayDocFile = nameOfPayDocFile;
        }

        internal List<Payment> ListOfPayments { get => listOfPayments; set => listOfPayments = value; }

        public void CalculatePayments()
        {
            IRepository logic = RepositoryFactory.GetRepository(nameOfBillFile, nameOfPayDocFile);
            listOfBills = logic.GetBills();
            listOfPayDoc = logic.GetPayDocs();
            foreach(Bill bill in listOfBills)
            {
                foreach (PayDoc doc in listOfPayDoc)
                { 
                    if (bill.NameOfClient == doc.NameOfClient && bill.Balance > 0 && doc.SumOfPayment != 0)
                    {
                        if (bill.Balance >= doc.SumOfPayment)
                        {
                            bill.Balance -= doc.SumOfPayment;
                            listOfPayments.Add(new Payment(bill.NameOfClient, doc.DateOfPayment, doc.NameOfPayment, bill.DateOfBill, bill.NameOfBill, doc.SumOfPayment));
                            doc.SumOfPayment = 0;
                        }
                        else
                        {
                            doc.SumOfPayment -= bill.Balance;
                            listOfPayments.Add(new Payment(bill.NameOfClient, doc.DateOfPayment, doc.NameOfPayment, bill.DateOfBill, bill.NameOfBill, bill.Balance));
                            bill.Balance = 0;
                        }
                    }
                }
            }
            var sortedList = listOfPayments.OrderBy(x => x.DateOfBill).ThenBy(x => x.DateOfPayment).ToList();
            logic.SetPayDocs(sortedList);
        }
    }
}
