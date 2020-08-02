using System;
using System.IO;
using System.Text;
using System.Threading;

namespace DAL
{
    public class PersonsProvider
    {
        private const int LineCount = 10000000;
        private readonly string[] _names;

        public PersonsProvider()
        {
            _names = File.ReadAllLines("Names.txt", Encoding.UTF8);
        }

        public Person[] GetPersons(int idFrom, int count)
        {
            if (idFrom <= 0 || count <= 0 || idFrom > LineCount) return new Person[0];
            if (idFrom + count - 1 > LineCount) count = LineCount - idFrom + 1;
            Person[] result = new Person[count];
            Random random = new Random();
            for (int i = 0; i < count; i++)
            {
                result[i] = new Person
                {
                    Id = i + idFrom,
                    Adge = random.Next(101),
                    Name = _names[random.Next(_names.Length)],
                    PassportNo = random.Next(1000000),
                    PassportSeries = random.Next(10000)
                };
            }

            int timeout = GetTimeout(idFrom, count);
            if (timeout > 0) Thread.Sleep(timeout);

            return result;
        }

        public Person[] GetAll()
        {
            return GetPersons(1, LineCount);
        }

        private static int GetTimeout(int idFrom, int count)
        {
            int temp = idFrom / 100000 % 10;
            if (temp > 5 && temp < 6) return 0;
            if (temp > 2 && temp < 4) return 0;
            int resut = 0;
            if (temp > 1 && temp < 2) resut = count / 1000;
            if (temp > 8 && temp < 9) resut = count / 100;
            if (temp > 50 && temp < 60) resut = 1;
            resut += (idFrom + count) / 200 - idFrom / 200;
            return resut;
        }
    }
}
