using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Xml.Serialization;
using System.Collections;
using System.Threading;
using System.Runtime.Serialization.Formatters.Binary;
using System.Linq;

namespace Laba2sharp
{
    [Serializable]
    class Magazine : Edition 
    {
        private Frequency Periodically;// переодичность выпуска  
        private List<Article> listArt = new List<Article>(); // информация о издателe
        private List<Person> listPerson = new List<Person>();

        public Edition MyEdition
        {
            get { return new Edition(this.NameI, this.Dateend, this.Tir1); }
            set { this.NameI = value.NameI; this.Dateend = value.Dateend; this.Tir1 = value.Tir1;
                OnPropertyChanged("MyEdition");
            }
        }

        public List<Article> ListArt
        {
            get { return listArt; }
            set { listArt = value;
                OnPropertyChanged("ListArt");
            }
        }

        public List<Person> ListPerson
        {
            get { return listPerson; }
            set { listPerson = value;
                OnPropertyChanged("ListPerson");
            }
        }

        public Magazine()
        {
            this.NameI = "Popular Mechanics";
            this.Periodically = new Frequency();
            this.Dateend = new DateTime(1980, 01, 01);
            this.Tir1 = 100;
            this.ListArt = new List<Article>();
            this.ListPerson = new List<Person>();
        }

        public Magazine(string Naaa, Frequency Perrrr, DateTime Data, int tiirr)
        {
            this.NameI = Naaa;
            this.Periodically = Perrrr;
            this.Dateend = new DateTime(1980, 01, 01);
            this.Tir1 = 100;
            this.ListArt = new List<Article>();
            this.ListPerson = new List<Person>();
        }
        public Frequency Pereod
        {
            get { return Periodically; }
            set { Periodically = value; }
        }
        public double AvgRate
        {
            get
            {
                double result = 0;
                foreach (Article article in ListArt)
                {
                    result += article.Rating;
                }
                return result / ListArt.Count;
            }
        }

        public bool this[Frequency index]
        {
            get
            {
                return this.Pereod == index;
            }
        }

        public void AddArticles(params Article[] articles)
        {
            this.ListArt.AddRange(articles);
        }

        public override string ToString()
        {
            return NameI + " " + Periodically + " " + Dateend + " " + Tir1 + "\n" + string.Join(" ", ListArt) + " " + string.Join(" ", ListPerson) + "\n";
        }

        public string ToShortString()
        {
            return string.Format("{0} {1} {2} {3}, {4}", NameI, Periodically, Dateend, Tir1, ListArt, ListPerson);
        }

        public void AddEditors(params Person[] NewPerson)
        {
            foreach (var item in NewPerson)
            {
                listPerson.Add(item);
            }
        }
        public double Ratingg { get; }


        #region Методы интерфейса IRateAndCopy
        public virtual Magazine DeepCopy()
        {
            Magazine obj = new Magazine(this.NameI, this.Pereod, this.Dateend, this.Tir1);

            foreach (var item in this.ListArt)
            {
                obj.listArt.Add(item);
            }


            foreach (var item in this.ListPerson)
            {
                obj.ListPerson.Add(item);
            }

            return obj;
        }

        public DateTime Date { get; set; }

        #endregion Методы интерфейса IRateAndCopy

        #region Итератор TestAndExam
        public IEnumerable STRating(double rat)
        {
            foreach (var item in this.ListArt)
            {
                if (((Article)item).Rating > rat)
                    yield return item;
            }

        }

        #endregion Итератор TestAndExam

        #region Итератор STname
        public IEnumerable STname(string N)
        {
            foreach (var item in this.ListPerson)
            {
                if (NameI.Contains(N))
                {
                    yield return item;
                }
            }

        }

        #endregion Итератор STname

        #region
        public IEnumerable STperson()
        {
            foreach (Person ed in ListPerson)
            {
                int flag = 1;
                foreach (Article art in ListArt)
                {
                    if (ed == art.Author)
                    {
                        flag = 0;
                    }
                }
                if (flag == 1) yield return ed;
            }

        }
        #endregion
        #region Итератор TestWhereExamDone
        public IEnumerable STArt()
        {
            foreach (Article art in ListArt)
            {
                if (this.ListPerson.Contains(art.Author)) yield return art;
            }
        }

        public void SortByTitle()
        {
            ListArt.Sort();
        }
        public void SortBySurname()
        {
            IComparer<Article> cr = new Article();

            ListArt.Sort(cr);
        }
        public void SortByRating()
        {
            IComparer<Article> cr = new Artice();

            ListArt.Sort(cr);
        }
        

        public Magazine DepCopy()
        {
            BinaryFormatter formatter = new BinaryFormatter();
            using (var Mstreem = new MemoryStream())
            {
                formatter.Serialize(Mstreem, this);
                Mstreem.Position = 0;
                byte[] bytes = Mstreem.GetBuffer();
                Mstreem.Write(bytes, 0, bytes.Length);


                Mstreem.Position = 0;
                Magazine magazine = (Magazine)formatter.Deserialize(Mstreem);
                return magazine;

            }
        }
        public bool Save(string filename)
        {
            try
            {
                Magazine obj = new Magazine(this.NameI, this.Pereod, this.Dateend, this.Tir1);
                BinaryFormatter formatter = new BinaryFormatter();
                using (var Fstreem = new FileStream(filename, FileMode.Create, FileAccess.Write, FileShare.None))
                {
                    formatter.Serialize(Fstreem, obj);
                    return true;
                }

            }
            catch (Exception)
            {
                Console.WriteLine("RUUUUUUUUUUUUUUUN");
                return false;
            }
        }

        public bool Load(string filename)
        {
            try
            {
                using (var Fstreem = File.OpenRead(filename))
                {
                    BinaryFormatter formatter = new BinaryFormatter();
                    Magazine magazine = new Magazine();
                    magazine = (Magazine)formatter.Deserialize(Fstreem);
                    //this.ListArt.Add(magazine.ListArt[0]);
                    return true;
                }
            }
            catch(Exception)
            {
                Console.WriteLine("AAAAAAAAAAAAAAAAAAAAAAAAA");
                return false;
            }

        }
        public bool AddFromConsole()
        {
            int K = 0;
            while (K == 0)
            {
                try
                {
                    Console.WriteLine("Введите необходимые поля используя пробелы как разделители");
                    Console.WriteLine("1.Название статьи");
                    Console.WriteLine("2.Имя");
                    Console.WriteLine("3.Фамилия");
                    Console.WriteLine("4.Дата рождения(день)");
                    Console.WriteLine("5.Дата рождения(месяц)");
                    Console.WriteLine("6.Дата рождения(год)");
                    Console.WriteLine("7.Рейтинг статьи");
                    string argument;
                    argument = Console.ReadLine();
                    List<string> args;
                    args = argument.Split(new char[] { ' ', '.', ',', ':', '\t', '?', '!', '"', '\n', ';', '/', '-', }).ToList();
                    Magazine magazine = new Magazine();
                    magazine.AddArticles( new Article(new Person(args[1], args[2], new DateTime(int.Parse(args[5]), int.Parse(args[4]), int.Parse(args[4]))), args[0], double.Parse(args[6])));
                    K = 1;
                    ListArt.Add(new Article(new Person(args[1], args[2], new DateTime(int.Parse(args[5]), int.Parse(args[4]), int.Parse(args[4]))), args[0], double.Parse(args[6])));
                    return true;
                }
                catch (ArgumentOutOfRangeException)
                {
                    Console.WriteLine("Невеноезначение даты рождения");
                    return false;
                }
                catch (ArgumentNullException)
                {
                    Console.WriteLine("Нет входного значения");
                    return false;
                }
                catch (FormatException)
                {
                    Console.WriteLine("Недопустимый формат входных данных");
                    return false;
                }
                catch (OverflowException)
                {
                    Console.WriteLine("Выход за пределы памяти ");
                    return false;
                }
                catch (Exception)
                {
                    Console.WriteLine("Другая ошибка");
                    return false;
                }
                
            }
            return true;


        }

        public static bool Save(string filename, Magazine obj)
        {
            try
            {
                BinaryFormatter formatter = new BinaryFormatter();
                using (var Fstreem = new FileStream(filename, FileMode.Create, FileAccess.Write, FileShare.None))
                {
                    formatter.Serialize(Fstreem, obj);
                    return true;
                }

            }
            catch (Exception)
            {
                Console.WriteLine("RUUUUUUUUUUUUUUUN");
                return false;
            }
        }
        public static bool Load(string filename, Magazine obj)
        {
            try
            {
                using (var Fstreem = File.OpenRead(filename))
                {
                    BinaryFormatter formatter = new BinaryFormatter();
                    obj = (Magazine)formatter.Deserialize(Fstreem);
                    return true;
                }
            }
            catch (Exception)
            {
                Console.WriteLine("AAAAAAAAAAAAAAAAAAAAAAAAA");
                return false;
            }
        }


        #endregion Итератор TestWhereExamDone
        /*//public IEnumerator GetEnumerator()
        //{
        //    return new MagazineEnumerator(ListPerson, ListArt);
        //}

        //IEnumerator IEnumerable.GetEnumerator()
        //{
        //    return (IEnumerator)GetEnumerator();
        //}*/
    }
    delegate TKey KeySelector<TKey>(Magazine mg);
}