using System;
using System.IO;
using System.Diagnostics;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba2sharp
{
    [Serializable]
    class Person 
    {


        public static void Main(string[] args)
        {
            #region
            //Edition Myedition1 = new Edition();
            //Edition Myedition2 = new Edition();

            //if ((object)Myedition1 == (object)Myedition2)
            //    Console.WriteLine("Ссылки равны. " + "\n");
            //else
            //    Console.WriteLine("Ссылки не равны. " + "\n");

            //if (Myedition1 == Myedition2)
            //    Console.WriteLine("Объекты равны. " + "\n");
            //else
            //    Console.WriteLine("Объекты не равны. " + "\n");

            //Console.WriteLine("Хеш-код 1: " + Myedition1.GetHashCode().ToString() + "\n");
            //Console.WriteLine("Хеш-код 2: " + Myedition2.GetHashCode().ToString() + "\n");
            //try
            //{
            //    Edition Myedition3 = new Edition();
            //    Myedition3.Tir1 = -100;
            //}
            //catch (ArgumentException e)
            //{
            //    Console.WriteLine(e.Message + "\n");
            //}
            //catch (Exception ex)
            //{
            //    Console.WriteLine(ex.Message + "\n");
            //}
            //Magazine myMagazine = new Magazine("jurnal", new Frequency(), new DateTime(1999, 10, 10), 60000);
            //myMagazine.AddArticles(new Article(new Person("igor", "igor", new DateTime()), "titulnik", 45.2));
            //myMagazine.AddEditors(new Person());

            //Console.WriteLine(myMagazine.ToShortString() + "\n" + "\n");

            //Console.WriteLine(myMagazine.MyEdition.ToString() + " \n" + "\n");

            //Magazine myMagazineCopy = myMagazine.DeepCopy();

            //if (myMagazine == myMagazineCopy)
            //    Console.WriteLine("Объекты равны. " + "\n");
            //else
            //    Console.WriteLine("Объекты не равны. " + "\n");

            //Console.WriteLine(myMagazine.ToString() + " \n" + "\n");
            //Console.WriteLine(myMagazineCopy.ToString() + " \n" + "\n");


            //Console.WriteLine("список всех статей с рейтингом  больше 30");
            //foreach (var item in myMagazine.STRating(30.2))
            //{
            //    Console.WriteLine(item.ToString() + "\n");
            //}

            //Console.WriteLine("список всех статей с названием jurnal");
            //foreach (var item in myMagazine.STname("ju"))
            //{
            //    Console.WriteLine(item.ToString() + "\n");
            //}

            //Console.WriteLine("список редакторов журнала не являющиеся авторами");
            //foreach (var item in myMagazine.STArt())
            //{
            //    Console.WriteLine(item.ToString() + "\n");
            //}
            //Console.WriteLine("список редакторов журнала являющиеся авторами");
            //foreach (var item in myMagazine.STperson())
            //{
            //    Console.WriteLine(item.ToString() + "\n");
            //}
            //Console.WriteLine("список редакторов журнала являющиеся авторами и редакторами");

            //myMagazine.AddArticles(new Article(new Person("Your", "Mom", new DateTime(2228, 4, 20)), "Ha ha, benis", 9.11));
            //foreach (Article art in myMagazine)
            //{
            //    Console.WriteLine(art.ToString());
            //}
            #endregion
            #region

            /*Magazine mag = new Magazine();
            mag.AddArticles(new Article());
            mag.AddArticles(new Article(new Person(), "jfsjk", 78.6));
            mag.AddArticles(new Article(new Person("People", "not", new DateTime(1991, 11, 11)), "ooooooop", 78.3));
            mag.AddArticles(new Article(new Person("alibaba", "i 40 db", new DateTime()), "phahahah", 99.9));


            mag.SortByTitle();
            Console.WriteLine(mag.ToString() + "\n");
            mag.SortBySurname();
            Console.WriteLine(mag.ToString() + "\n");
            mag.SortByRating();
            Console.WriteLine(mag.ToString() + "\n");

            KeySelector<string> selector = delegate (Magazine input)
            {
                return input.GetHashCode().ToString();
            };

            var obj = new MagazineCollection<string>(selector);

            Magazine mag1 = new Magazine("hfshrgdfb", new Frequency(), new DateTime(), 636);
            Magazine mag2 = new Magazine("hf", new Frequency(), new DateTime(), 2563);
            Magazine mag3 = new Magazine("hfsh", new Frequency(), new DateTime(), 600);
            obj.AddMagazines(mag1, mag2, mag3, mag);
            Console.WriteLine(obj.ToString() + "\n");


            Console.WriteLine("ВЫЗОВ МЕТОДОВ MagazineCollection");

            Console.WriteLine(obj.MaxAverageRat + "\n");

            foreach (var item in obj.FrequencyGroup(Frequency.Monthly))
                Console.WriteLine(item.ToString() + "\n");


            foreach (var item in obj.GoupEl)
            {
                Console.WriteLine(item.Key);
                Console.WriteLine();
                foreach (var name in item)
                    Console.WriteLine(name);
            }
            GenerateElement<Edition, Magazine> d = delegate (int j)
            {
                var key = new Edition("tron" + j, new DateTime(), 212);
                var value = new Magazine("fwgehdg" + j, new Frequency(), new DateTime(), 212);
                return new KeyValuePair<Edition, Magazine>(key, value);
            };
            Console.WriteLine("Введите колличество элементов");
            bool f = false;
            while (f == false)
            {
                try
                {
                    int c = int.Parse(Console.ReadLine());
                    f = true;
                    var testObj = new TestCollections<Edition, Magazine>(c, d);
                    testObj.SearchInTKeyList();
                    testObj.SearchInStrList();
                    testObj.SearcInTKeyDictionary();
                    testObj.SearcInStrDictionary();
                    testObj.SearcInTKeyDictionaryByValue();
                    testObj.SearcInStrDictionaryByValue();
                }
                catch (Exception ex)
                {
                    Console.WriteLine("Ошибка :" + ex.Message + "\n" + "Допустимы только целочисленные значения");
                }
            }
        }*/
            #endregion
            #region
            //    KeySelector<string> selector = delegate (Magazine input)
            //    {
            //        return input.GetHashCode().ToString();
            //    };

            //    Magazine m1 = new Magazine("dsvetugv", new Frequency(), new DateTime(), 100);
            //    Magazine m2 = new Magazine("dsvev",new Frequency(),new DateTime(),110);
            //    Magazine m3 = new Magazine("dksdjozfnf", new Frequency(), new DateTime(), 115);
            //    Magazine m4 = new Magazine("kollllloook", new Frequency(), new DateTime(), 120);



            //    var col1 = new MagazineCollection<string>(selector);
            //    col1.CollectionName = "Collection 1";
            //    var col2 = new MagazineCollection<string>(selector);
            //    col2.CollectionName = "Collection 2";

            //    Listener listener = new Listener();

            //    //Устанавливаем слушателей событий в коллекциях
            //    col1.MgChanged += listener.NewListEntry;
            //    col2.MgChanged += listener.NewListEntry;


            //    //Устанавливаем слушателей событий в классе Magazine
            //    m1.PropertyChanged += listener.NewListEntry2;
            //    m2.PropertyChanged += listener.NewListEntry2;
            //    m3.PropertyChanged += listener.NewListEntry2;
            //    m4.PropertyChanged += listener.NewListEntry2;

            //    col1.AddDefaults();
            //    col1.AddMagazines(m1, m2);
            //    col2.AddDefaults();
            //    col2.AddMagazines(m3, m4);


            //    m3.Tir1 = 150;
            //    m4.MyEdition =new Edition();

            //    col1.Replace(m1, m2);
            //    m1.Tir1 = 150;

            //    Console.WriteLine(listener.ToString());

            //}
            #endregion
            Magazine myMagazine = new Magazine("jurnal", new Frequency(), new DateTime(1999, 10, 10), 60000);
            myMagazine.AddArticles(new Article());
            Magazine myMagazine1 = myMagazine.DepCopy();
            Console.WriteLine(myMagazine.ToString());
            Console.WriteLine(myMagazine1.ToString());
            Console.WriteLine("Введите Имя Файла");
            string Filename1 = Console.ReadLine();
            Magazine magazine = new Magazine("jurnal", new Frequency(), new DateTime(1999, 10, 10), 60000);
            magazine.AddFromConsole();
            magazine.Save(Filename1);
            bool ff = Magazine.Save(Filename1, magazine);
            Console.WriteLine(magazine.ToString());
            Console.WriteLine("Введите Имя Файла");
            string Filename = Console.ReadLine();
            string dirName = @"C:\Users\Acer\source\repos\Laba2sharp\Laba2sharp\bin\Debug";
            if (Directory.Exists(dirName))
            {
                string[] files = Directory.GetFiles(dirName);
                foreach (string s in files)
                {
                    if (s.Contains(Filename))
                    {
                        Magazine magazine2 = new Magazine();
                        magazine2.Load(Filename);
                        Console.WriteLine(magazine2.ToString());
                    }
                }
            }
            else
                Console.WriteLine("директории нет");

        }
        private string name;
        private string secondname;
        private System.DateTime DateOfBirth;

        public Person(string name, string secondname, System.DateTime birthday)
        {
            this.name = name;
            this.secondname = secondname;
            this.DateOfBirth = birthday;
        }
        public Person()
        {
            this.name = "Name";
            this.secondname = "Secondname";
            this.DateOfBirth = new DateTime(1996, 11, 10);
        }
        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public string SecondName
        {
            get { return secondname; }
            set { secondname = value; }
        }
        public DateTime DateOfBirthP
        {
            get { return DateOfBirth; }
            set { DateOfBirth = value; }
        }
        public int YearOfDateTime
        {
            get { return DateOfBirth.Year; }
            set { DateOfBirth = new DateTime(value, DateOfBirth.Month, DateOfBirth.Day); }
        }
        public override string ToString()
        {
            return DateOfBirth + " " + secondname + " " + name;
        }
        public string ToShortString()
        {
            return name.ToString() + secondname.ToString();
        }
        public override bool Equals(object obj)
        {
            if (obj == null) { return false; }
            if (!(obj is Person)) { return false; }
            Person obj1 = (Person)obj;
            return (name == obj1.name) && (secondname == obj1.secondname) && (DateOfBirth == obj1.DateOfBirth);
        }

        public static bool operator ==(Person a, Person b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.name == b.name && a.secondname == b.secondname && a.DateOfBirth == b.DateOfBirth;
        }
        public static bool operator !=(Person a, Person b)
        {
            return !(a == b);
        }

        public override int GetHashCode()
        {
            return name.GetHashCode() + secondname.GetHashCode() + DateOfBirth.GetHashCode();
        }

        public virtual object DeepCopy()
        {
            return new Person(this.name, this.secondname, this.DateOfBirth);
        }
    }
}
