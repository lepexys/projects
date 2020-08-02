using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using System.IO;
using Microsoft.VisualBasic;
using System.Xml.Linq;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;

namespace SUBD
{
    class Program
    {
        interface IData
        {
            IEnumerable<Bill> GetBills(string FileName);
            IEnumerable<PayDoc> GetPayDocs(string FileName);
            void SetPayDocs(IEnumerable<Payment> payments);
        }
        class RepositoryFactory
        {
            public static IData GetRepository()
            {
                string tp = ConfigurationManager.AppSettings["TransferType"];
            }
        }
        static void Main(string[] args)
        {
            PaymentLogic calc = new PaymentLogic();
            calc.CalculatePayments();
            Console.ReadKey();
        }
        class Bill
        {
            public string name;
            public DateTime date;
            public string number;
            public double monkey;
        }

        class PayDoc
        {
            public string name;
            public DateTime date;
            public string number;
            public double monkey;
        }

        class Payment
        {
            public string name;
            public DateTime datep;
            public string numberp;
            public DateTime dates;
            public string numbers;
            public double monkey;
        }
        class DBwork : IData
        {
            public DBwork() { }
            public IEnumerable<PayDoc> GetPayDocs(string fileName)
            {
                try
                {
                    List<PayDoc> result = new List<PayDoc>();
                    using (var cnn = new SqlConnection(@"Data Source=WINDOWS81\SQLEXPRESS;Initial Catalog=Lab5Db;Integrated Security=True"))
                    {
                        cnn.Open();
                        var PayDocs = new DataTable();
                        var adapter = new SqlDataAdapter("SELECT * FROM dbo.PayDocs", cnn);
                        adapter.Fill(PayDocs);
                        foreach (DataRow dr in PayDocs.Rows)
                        {
                            PayDoc pdd = new PayDoc();
                            pdd.name = (string)dr[1];
                            pdd.date = (DateTime)dr[2];
                            pdd.number = (string)dr[3];
                            pdd.monkey = (double)dr[4];
                            result.Add(new PayDoc());
                        }
                    }
                    return result;
                }
                catch (Exception)
                {
                    Console.WriteLine("Неправильный формат платежей");
                    Environment.Exit(0);
                    return null;
                }
            }
            public IEnumerable<Bill> GetBills(string fileName)
            {
                try
                {
                    List<Bill> result = new List<Bill>();
                    string[] fields = new string[5];
                    using (var cnn = new SqlConnection(@"Data Source=WINDOWS81\SQLEXPRESS;Initial Catalog=Lab5Db;Integrated Security=True"))
                    {
                        cnn.Open();
                        var Bills = new DataTable();
                        var adapter = new SqlDataAdapter("SELECT * FROM dbo.Bills", cnn);
                        adapter.Fill(Bills);
                        foreach (DataRow dr in Bills.Rows)
                        {
                            Bill bill = new Bill();
                            bill.name = (string)dr[1];
                            bill.date = (DateTime)dr[2];
                            bill.number = (string)dr[3];
                            bill.monkey = (double)dr[4];
                            result.Add(new Bill());
                        }
                    }
                    return result;
                }
                catch (Exception)
                {
                    Console.WriteLine("Неправильный формат платежей");
                    Environment.Exit(0);
                    return null;
                }
            }
            public void SetPayDocs(IEnumerable<Payment> TradeList)
            {
                using (var cnn = new SqlConnection(@"Data Source=WINDOWS81\SQLEXPRESS;Initial Catalog=Lab5Db;Integrated Security=True"))
                {
                    cnn.Open();
                        foreach (Payment trade in TradeList)
                        {
                            var insertPayments = new SqlCommand(@"INSERT INTO dbo.Payments (PayDocId, BillId, Sum )					
                                                              VALUES (@p, @b, @sum )", cnn);
                            insertPayments.Parameters.AddWithValue("@p", trade.numberp);
                            insertPayments.Parameters.AddWithValue("@b", trade.numbers);
                            insertPayments.Parameters.AddWithValue("@sum", trade.monkey);
                            insertPayments.ExecuteNonQuery();
                        }
                }
            }
        }
        class PaymentRepository : IData
        {
            public IEnumerable<Bill> GetBills(string FileName)
            {
                XmlTextReader rdd = new XmlTextReader(FileName);
                string b;
                List<Bill> a = new List<Bill>();
                while (rdd.Read())
                {
                    switch (rdd.NodeType)
                    {
                        case XmlNodeType.Element:
                            {
                                if (rdd.Name != "Bills")
                                    try
                                    {
                                        a.Add(new Bill());
                                        a[a.Count - 1] = new Bill();
                                        a[a.Count - 1].name = rdd.GetAttribute(0);
                                        b = rdd.GetAttribute(1);
                                        a[a.Count - 1].date = new DateTime(int.Parse(b.Split('.')[2]), int.Parse(b.Split('.')[1]), int.Parse(b.Split('.')[0]));
                                        a[a.Count - 1].number = rdd.GetAttribute(2);
                                        b = rdd.GetAttribute(3).Split('.')[0];
                                        if (rdd.GetAttribute(3).Split('.').Count() == 2)
                                            b += "," + rdd.GetAttribute(3).Split('.')[1];
                                        a[a.Count - 1].monkey = double.Parse(b);
                                    }
                                    catch (Exception e)
                                    {
                                        Console.WriteLine(e.Message);
                                    }
                                break;
                            }
                    }
                }
                return a;
            }

            public IEnumerable<PayDoc> GetPayDocs(string FileName)
            {
                StreamReader rdd = new StreamReader(FileName);
                string[] buff = new string[4];
                string b;
                List<PayDoc> a = new List<PayDoc>();
                rdd.ReadLine();
                while (!rdd.EndOfStream)
                {
                    buff = rdd.ReadLine().Split(';');
                    a.Add(new PayDoc());
                    try
                    {
                        a[a.Count - 1] = new PayDoc();
                        a[a.Count - 1].name = buff[0];
                        b = buff[1];
                        a[a.Count - 1].date = new DateTime(int.Parse(b.Split('.')[2]), int.Parse(b.Split('.')[1]), int.Parse(b.Split('.')[0]));
                        a[a.Count - 1].number = buff[2];
                        b = buff[3].Split('.')[0];
                        if (buff[3].Split('.').Count() == 2)
                            b += "," + buff[3].Split('.')[1];
                        a[a.Count - 1].monkey = double.Parse(b);
                    }
                    catch (Exception e)
                    {
                        Console.WriteLine(e.Message);
                    }
                }
                return a;
            }
            public void SetPayDocs(IEnumerable<Payment> payments)
            {
                {
                    XDocument xdoc = new XDocument();
                    XElement root = new XElement("Payments");
                    xdoc.Add(root);
                    foreach (Payment pay in payments)
                    {
                        XElement elem = new XElement("Payment");
                        elem.Add(new XAttribute("Client", pay.name), new XAttribute("DatePay", pay.datep.ToLongDateString()), new XAttribute("PayNumber", pay.numberp), new XAttribute("DateBill", pay.dates.ToLongDateString()), new XAttribute("BillNumber", pay.numbers), new XAttribute("SumPay", pay.monkey));
                        root.Add(elem);
                    }
                    xdoc.Save("Payments.xml");
                }
            }
        }
        class PaymentLogic
        {
            public void CalculatePayments()
            {
                PaymentRepository PR = new PaymentRepository();
                List<Payment> payments = new List<Payment>();
                PayDoc swp;
                List<PayDoc> PD = PR.GetPayDocs(file) as List<PayDoc>;
                for (int i = 0; i < PD.Count - 1; i++)
                    for (int j = 0; j < PD.Count - i - 1; j++)
                        if (PD[j].date > PD[j + 1].date)
                        {
                            swp = PD[j];
                            PD[j] = PD[j + 1];
                            PD[j + 1] = swp;
                        }
                Bill swg;
                List<Bill> PB = PR.GetBills(file) as List<Bill>;
                for (int i = 0; i < PB.Count - 1; i++)
                    for (int j = 0; j < PB.Count - i - 1; j++)
                        if (PB[j].date > PB[j + 1].date)
                        {
                            swg = PB[j];
                            PB[j] = PB[j + 1];
                            PB[j + 1] = swg;
                        }
                Payment bup;
                foreach (Bill a in PB)
                    foreach (PayDoc b in PD.Where((RP) => RP.name == a.name && RP.monkey != 0))
                    {
                        if (a.monkey < b.monkey)
                        {
                            bup = new Payment();
                            bup.monkey = a.monkey;
                            bup.name = b.name;
                            bup.numberp = b.number;
                            bup.numbers = a.number;
                            bup.datep = b.date;
                            bup.dates = a.date;
                            payments.Add(bup);
                            b.monkey -= a.monkey;
                            break;
                        }
                        else if (a.monkey > b.monkey)
                        {
                            bup = new Payment();
                            bup.monkey = b.monkey;
                            bup.name = b.name;
                            bup.numberp = b.number;
                            bup.numbers = a.number;
                            bup.datep = b.date;
                            bup.dates = a.date;
                            payments.Add(bup);
                            a.monkey -= b.monkey;
                            b.monkey = 0;
                        }
                        else if (a.monkey == b.monkey)
                        {
                            bup = new Payment();
                            bup.monkey = b.monkey;
                            bup.name = b.name;
                            bup.numberp = b.number;
                            bup.numbers = a.number;
                            bup.datep = b.date;
                            bup.dates = a.date;
                            payments.Add(bup);
                            a.monkey = 0;
                            b.monkey = 0;
                            break;
                        }
                    }
                PR.SetPayDocs(payments);
            }
        }
    }
}

