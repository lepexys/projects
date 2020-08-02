using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace kill
{
    enum Frequency { Weekly, Monthly, Yearly }
    enum Update { Add, Replace, Property }
    class Person
    {
        string Kk(Magazine m)
        {
            return m.ToString();
        }
        KeyValuePair<Edition, Magazine> Generate(int a)
        {
            KeyValuePair<Edition, Magazine> kvp;
            Magazine m = new Magazine(a.ToString(), Frequency.Monthly, new DateTime(a + 1, a % 12 + 1, a % 28 + 1), a);
            Edition e = new Edition(a.ToString(), new DateTime(a + 1, a % 12 + 1, a % 28 + 1), a);
            return kvp = new KeyValuePair<Edition, Magazine>(e, m);
        }
        static void Main(string[] args)
        {
            Person p = new Person();
            MagazineCollection<string> abu = new MagazineCollection<string>(p.Kk);
            MagazineCollection<string> dabi = new MagazineCollection<string>(p.Kk);
            Listener litun = new Listener();
            Magazine mag1 = new Magazine("Timeses", Frequency.Monthly, new DateTime(1999, 5, 14), 10000);
            Magazine mag2 = new Magazine("Goga", Frequency.Yearly, new DateTime(1997, 7, 16), 1000);
            abu.MagazinesChanged += litun.Lookmeineye;
            dabi.MagazinesChanged += litun.Lookmeineye;
            abu.AddMagazines(mag2);
            dabi.AddMagazines(mag1);
            abu.Replace(mag2, mag1);
            dabi.Replace(mag1, mag2);
            Console.WriteLine(litun.ToString());
            Console.ReadKey();
        }
        protected string name;
        protected string surname;
        protected DateTime field;
        protected Object e;

        public string Nprop
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
            }
        }

        public string Sprop
        {
            get
            {
                return surname;
            }
            set
            {
                surname = value;
            }
        }

        public DateTime Dprop
        {
            get
            {
                return (DateTime)e;
            }
            set
            {
                e = field;
            }
        }

        public int Dtime
        {
            get
            {
                return field.Year;
            }
            set
            {
                field = new DateTime(value, field.Month, field.Day);
            }
        }

        public Person(string name1, string surname1, DateTime field1)
        {
            name = name1;
            surname = surname1;
            field = field1;
        }
        public Person()
        {
            name = "Vasia";
            surname = "Ygolkov";
            field = new DateTime(1995, 10, 20);
        }
        public override string ToString()
        {
            return name + " " + surname + " " + field;
        }
        public string ToShortString()
        {
            return name + " " + surname;
        }
        public override bool Equals(object obj)
        {
            bool k = false;
            Person h = obj as Person;
            if (name.Equals(h.name))
                if (surname.Equals(h.surname))
                    if (field.Equals(h.field))
                        k = true;
            return k;
        }
        public static bool operator ==(Person obj1, Person obj2)
        {
            return obj1.Equals(obj2);
        }
        public static bool operator !=(Person obj1, Person obj2)
        {
            if (obj1.Equals(obj2) == true)
                return false;
            else
                return true;
        }
        public override int GetHashCode()
        {
            int ret;
            Person h = this as Person;
            ret = h.ToString().GetHashCode();
            return ret;
        }
        public Person DeepCopy()
        {
            string rname = name;
            string rsurname = surname;
            DateTime rfield = new DateTime(field.Year, field.Month, field.Day);
            Person ret = new Person(rname, rsurname, rfield);
            return ret;
        }
    }
}