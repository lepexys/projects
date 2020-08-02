using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace laba4dot
{
    class Program
    {
        static void Main()
        {

            PaymentLogic logic = new PaymentLogic("Lab_4_scheta.xml", "Lab_4_platezhi.csv");
            
            {
                logic.CalculatePayments();
            }
       
        }
        public static void messenge(string vau)
        {
            Console.WriteLine(vau);
            Console.ReadKey();
        }
    }
}
