using DAL;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Number12
{
    class Program
    {
        static void Main(string[] args)
        {
            PersonsProvider provider1 = new PersonsProvider();
            PersonsProvider provider2 = new PersonsProvider();
            Person[] persons;
            int count1 = 1, count2 = 1;
            StreamWriter stream1 = new StreamWriter("file1.css");
            StreamWriter stream2 = new StreamWriter("file2.css");
            Stopwatch t = new Stopwatch();
            t.Start();
            while (true)
            {
                persons = provider1.GetPersons(count1, 100);
                if (persons.Count() == 0)
                    break;
                count1 += persons.Count();
                for (int i = 0; i < persons.Count(); i++)
                    stream1.WriteLine(persons[i].ToString());
            }
            t.Stop();
            Console.WriteLine("Время для однопоточного сохранения: " + t.ElapsedMilliseconds + "ms");
            List<Person> list = new List<Person>();
            t.Restart();
            while (true)
            {
                persons = provider2.GetPersons(count2, 100);
                if (persons.Count() == 0)
                    break;
                list.AddRange(persons.ToList());
                count2 += persons.Count();
            }
            for (int i = 0; i < count2-1; i++)
                    stream2.WriteLine(list[i].ToString());
            t.Stop();
            Console.WriteLine("Время для многопоточного сохранения: " + t.ElapsedMilliseconds + "ms");
            Console.ReadKey();
        }
    }
}
