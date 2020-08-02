using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Number9
{
    class Program
    {
        static void Main(string[] args)
        {
            StreamReader rdd = new StreamReader(args[0]);
            Regex mail = new Regex(@"(\w*)@(\w+)\.(\w+)");
            Regex telephone = new Regex(@"\d{11}");
            int amount = 0,correct_telephones = 0,correct_mails = 0;
            string[] buff = new string[3];
            rdd.ReadLine();
            while (!rdd.EndOfStream)
            {
                buff = rdd.ReadLine().Split('.');
                amount++;
                if (mail.IsMatch(buff[1].Trim('\"'))) correct_mails++;
                if (telephone.IsMatch(buff[2].Trim('\"'))) correct_telephones++;
            }
            Console.WriteLine("Всего сотрудников: " + amount);
            Console.WriteLine("Правильных электронных адресов: {0}, неправильных: {1}", correct_mails, amount - correct_mails);
            Console.WriteLine("Правильных телефонов: {0}, неправильных: {1}", correct_telephones, amount - correct_telephones);
        }
    }
}
