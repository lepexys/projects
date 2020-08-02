using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
    [Serializable]
    class Magazine : Edition
    {
        private List<Person> magp;
        private List<Article> maga;
        private Frequency magf;

        public Magazine(string name1, Frequency magf1, DateTime time1, int tire1)
        {
            name = name1;
            magf = magf1;
            time = time1;
            tire = tire1;
            maga = new List<Article>();
            magp = new List<Person>();
        }
        public Magazine()
        {
            Frequency f = Frequency.Weekly;
            DateTime d = new DateTime(1995, 10, 20);
            time = d;
            magf = f;
            name = "Мурзилка";
            tire = 60000;
            maga = new List<Article>();
            magp = new List<Person>();
        }
        public Frequency Magf
        {
            get
            {
                return magf;
            }
            set
            {
                magf = value;
            }
        }
        public List<Article> Maga
        {
            get
            {
                return maga;
            }
            set
            {
                maga = value;
            }
        }
        public List<Person> Magp
        {
            get
            {
                return magp;
            }
            set
            {
                magp = value;
            }
        }
        public double Mr
        {
            get
            {
                double col = 0;
                Article r;
                for (int i = 0; i < maga.Count; i++)
                {
                    r = maga[i] as Article;
                    col += r.rat;
                }
                col = col / (maga.Count);
                return col;
            }
        }
        bool this[Frequency fr]
        {
            get
            {
                bool a;
                a = Equals(magf, fr);
                return a;
            }
        }
        public void AddArticles(params Article[] args)
        {
            maga.AddRange(args);
        }
        public void AddPerson(params Person[] args)
        {
            magp.AddRange(args);
        }
        public override string ToString()
        {
            string ret = "";
            ret += name + " ";
            ret += magf.ToString() + " ";
            ret += tire.ToString() + " ";
            ret += time.ToString() + " ";
            for (int i = 0; i < maga.Count; i++)
                ret += maga[i].ToString() + " ";
            for (int i = 0; i < magp.Count; i++)
                ret += maga[i].ToString() + " ";
            return ret;
        }
        public string ToShortString()
        {
            string ret = "";
            ret += name + " ";
            ret += magf.ToString() + " ";
            ret += tire.ToString() + " ";
            ret += time.ToString() + " ";
            ret += Mr.ToString() + " ";
            return ret;
        }
        public override bool Equals(object obj)
        {
            bool k = false;
            Magazine h = obj as Magazine;
            if (name.Equals(h.name))
                if (time.Equals(h.time))
                    if (magf.Equals(h.magf))
                        if (tire.Equals(h.tire))
                            k = true;
            return k;
        }
        public static bool operator ==(Magazine obj1, Magazine obj2)
        {
            return obj1.Equals(obj2);
        }
        public static bool operator !=(Magazine obj1, Magazine obj2)
        {
            if (obj1.Equals(obj2) == true)
                return false;
            else
                return true;
        }
        public override int GetHashCode()
        {
            int ret;
            Magazine h = this as Magazine;
            ret = h.ToString().GetHashCode();
            return ret;
        }
        interface IRateAndCopy
        {
            double Rating { get; }
            object DeepCopy();
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
                    AddArticles(new Article(new Person(args[1], args[2], new DateTime(int.Parse(args[5]), int.Parse(args[4]), int.Parse(args[3]))), args[0], double.Parse(args[6])));
                    K = 1;
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
            FileStream retstream = new FileStream(filename, FileMode.OpenOrCreate);
            BinaryFormatter binFormat = new BinaryFormatter();
            try
            {
                binFormat.Serialize(retstream, this as Magazine);
                retstream.Dispose();
                return true;
            }
            catch
            {
                Console.WriteLine("Serialization isn't 1337\n");
                return false;
            }
        }
        public bool Load (string filename)
        {
            FileStream retstream = new FileStream(filename, FileMode.Open);
            BinaryFormatter binFormat = new BinaryFormatter();
            try
            {
                Magazine initialazer =  binFormat.Deserialize(retstream) as Magazine;
                Maga = initialazer.Maga;
                Magf = initialazer.Magf;
                Magp = initialazer.Magp;
                Name = initialazer.Name;
                Time = initialazer.Time;
                Tire = initialazer.Tire;
                retstream.Dispose();
                return true;
            }
            catch
            {
                Console.WriteLine("Load aint complete");
                return false;
            }
        }
        public static bool Save(string filename, Magazine obj)
        {
            try
            {
                BinaryFormatter formatter = new BinaryFormatter();
                using (var Fstreem = new FileStream(filename, FileMode.Create, FileAccess.Write, FileShare.None))
                {
                    formatter.Serialize(Fstreem, obj);
                    Fstreem.Dispose();
                    return true;
                }

            }
            catch
            {
                Console.WriteLine("Save is endless");
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
                    Fstreem.Dispose();
                    return true;
                }
            }
            catch (Exception)
            {
                Console.WriteLine("Load is Reckless");
                return false;
            }
        }
        public void Sori()
        {
            Article r;
            if (maga.Count < 2);
            else
                for (int i = 0; i < maga.Count - 1; i++)
                    for (int j = 0; j < maga.Count - 1 - i; j++)
                        if (maga[j].CompareTo(maga[j + 1]) == 1)
                        {
                            r = maga[j + 1];
                            maga[j + 1] = maga[j];
                            maga[j] = r;
                        }
        }
        public void Sorifam()
        {
            Article e = new Article();
            if (maga.Count < 2) ;
            else
                for (int i = 0; i < maga.Count - 1; i++)
                    for (int j = 0; j < maga.Count - 1 - i; j++)
                        if (e.Compare(maga[j], maga[j+1]) == 1)
                        {
                            e = maga[j + 1];
                            maga[j + 1] = maga[j];
                            maga[j] = e;
                        }
        }
        public void Sorirat()
        {
            Article r;
            HelpArticle e = new HelpArticle();
            if (maga.Count < 2) ;
            else
                for (int i = 0; i < maga.Count - 1; i++)
                    for (int j = 0; j < maga.Count - 1 - i; j++)
                        if (e.Compare(maga[j + 1], maga[j]) == -1)
                        {
                            r = maga[j + 1];
                            maga[j + 1] = maga[j];
                            maga[j] = r;
                        }
        }
        public delegate TKey KeySelector<TKey>(Magazine mg);
        public delegate KeyValuePair<TKey, Tvalue> GenerateElement<TKey, Tvalue>(int a);
        public delegate void MagazinesChangedHandler<TKey>(object source, MagazinesChangedEventArgs<TKey> args);
    }
}