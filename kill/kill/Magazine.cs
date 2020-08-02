using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
    class Magazine : Edition
    {
        List<Person> magp;
        List<Article> maga;
        protected Frequency magf;

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
        public string Name
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
        public DateTime Time
        {
            get
            {
                return time;
            }
            set
            {
                time = value;
            }
        }
        public int Tire
        {
            get
            {
                return tire;
            }
            set
            {
                tire = value;
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
        public object DeepCopy()
        {
            Frequency rmagf = magf;
            string rname = name;
            DateTime rtime = new DateTime(time.Year, time.Month, time.Day);
            int rtire = tire;
            Magazine ret = new Magazine(rname, rmagf, rtime, rtire);
            ret.Maga = new List<Article>(maga);
            ret.Magp = new List<Person>(magp);
            return ret;
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