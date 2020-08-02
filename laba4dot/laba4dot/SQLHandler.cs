using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SqlClient;
using System.Linq;
using System.Text;
using System.Configuration;
using System.Threading.Tasks;

namespace laba4dot
{
    class SQLHandler : IRepository
    {
        public IEnumerable<Bill> GetBills()
        {
            using (var cnn = new SqlConnection(ConfigurationManager.AppSettings["key3"]))
            {
                cnn.Open();
                var bills = new DataTable();
                SqlDataAdapter adapter = new SqlDataAdapter("SELECT * FROM dbo.Bills", cnn);
                adapter.Fill(bills);
                List<Bill> listBill = new List<Bill>();
                foreach (DataRow data in bills.Rows)
                {
                    object[] obj = data.ItemArray;
                    string[] item = new string[5];
                    for(int i = 0; i< obj.Length; i++)
                    {
                        item[i] = Convert.ToString(obj[i]);
                    }
                    listBill.Add(new Bill(item[1], Convert.ToDateTime(item[2]), item[3], Double.Parse(item[4])));
                }
                return listBill;
            }
        }

        public IEnumerable<PayDoc> GetPayDocs()
        {
            using (var cnn = new SqlConnection(ConfigurationManager.AppSettings["key3"]))
            {
                cnn.Open();
                var payDoc = new DataTable();
                SqlDataAdapter adapter = new SqlDataAdapter("SELECT * FROM dbo.PayDocs", cnn);
                adapter.Fill(payDoc);
                List<PayDoc> kistOfPay = new List<PayDoc>();
                foreach (DataRow data in payDoc.Rows)
                {
                    object[] obj = data.ItemArray;
                    string[] item = new string[5];
                    for (int i = 0; i < obj.Length; i++)
                    {
                        item[i] = Convert.ToString(obj[i]);
                    }
                    kistOfPay.Add(new PayDoc(item[1], Convert.ToDateTime(item[2]), item[3], Double.Parse(item[4])));
                }
                return kistOfPay;
            }
        }

        public void SetPayDocs(IEnumerable<Payment> payments)
        {
            using (var cnn = new SqlConnection(ConfigurationManager.AppSettings["key3"]))
            {
                cnn.Open();
                foreach (Payment pay in payments)
                {
                    var insertBill = new SqlCommand(@"INSERT INTO dbo.Payment ( Client, DateOfPayment, NameOfPayment, DateOfBill, NameOfBill, SumOfPayment )	VALUES ( @client, @dateOfPayment, @nameOfPayment, @dateOfBill, @nameOfBill, @sumOfPayment)", cnn);

                    insertBill.Parameters.AddWithValue("@client", pay.NameOfClient);
                    insertBill.Parameters.AddWithValue("@dateOfPayment", pay.DateOfPayment);
                    insertBill.Parameters.AddWithValue("@nameOfPayment", pay.NameOfPayment);
                    insertBill.Parameters.AddWithValue("@dateOfBill", pay.DateOfBill);
                    insertBill.Parameters.AddWithValue("@nameOfBill", pay.NameOfBill);
                    insertBill.Parameters.AddWithValue("@sumOfPayment", pay.SumOfPayment);
                    insertBill.ExecuteNonQuery();
                }
            }
        }
    }
}
