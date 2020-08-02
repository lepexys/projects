using Microsoft.VisualBasic.FileIO;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace laba4dot
{
    class PaymentRepository : IRepository
    {
        private string nameOfBillFile;
        private string nameOfPayDocFile;

        public PaymentRepository(string nameOfBillFile, string nameOfPayDocFile)
        {
            this.nameOfBillFile = nameOfBillFile;
            this.nameOfPayDocFile = nameOfPayDocFile;
        }

        public IEnumerable<Bill> GetBills()
        {
            IEnumerable<Bill> bills = new List<Bill>();
            XDocument xdoc = XDocument.Load(nameOfBillFile);
            bills = from item in xdoc.Element("Bills").Elements("Bill")
                    select new Bill(item.Attribute("Client").Value, new DateTime(int.Parse(item.Attribute("Date").Value.Split(new char[] { '.' })[2]), int.Parse(item.Attribute("Date").Value.Split(new char[] { '.' })[1]), int.Parse(item.Attribute("Date").Value.Split(new char[] { '.' })[0])), item.Attribute("Number").Value, double.Parse(item.Attribute("Sum").Value.Replace('.',',')));
            return bills;
        }

        public IEnumerable<PayDoc> GetPayDocs()
        {
            List<PayDoc> listOfPayments = new List<PayDoc>();
            using (TextFieldParser tfp = new TextFieldParser(nameOfPayDocFile))
            {
                tfp.TextFieldType = FieldType.Delimited;
                tfp.SetDelimiters(";");
                tfp.ReadFields(); 
                while (!tfp.EndOfData)
                {
                    int[] mas = new int[3];
                    string[] fields = tfp.ReadFields();
                    for (int i = 0; i < 3; i++)
                    {
                        mas[i] = int.Parse((fields[1].Split(new char[] { '.' })[i]));
                    }
                    listOfPayments.Add(new PayDoc(fields[0], new DateTime(mas[2], mas[1], mas[0]), fields[2], double.Parse(fields[3].Replace('.',','))));
                }
            }
            return listOfPayments;
        }

        public void SetPayDocs(IEnumerable<Payment> payments)
        {
            XDocument xdoc = new XDocument();
            XElement root = new XElement("Payments");
            xdoc.Add(root);
            foreach (Payment pay in payments)
            {
                XElement elem = new XElement("Payment");
                elem.Add(new XAttribute("Client",pay.NameOfClient), new XAttribute("DatePay",pay.DateOfPayment.ToLongDateString()), new XAttribute("PayNumber",pay.NameOfPayment), new XAttribute("DateBill",pay.DateOfBill.ToLongDateString()), new XAttribute("BillNumber",pay.NameOfBill), new XAttribute("SumPay",pay.SumOfPayment));
                root.Add(elem);
            }
            xdoc.Save("Payments.xml");
        }
    }
}
