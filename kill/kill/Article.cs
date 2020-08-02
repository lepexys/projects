using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
    class Article : IComparable, IComparer<Article>
    {
        public Person man;
        public string art;
        public double rat;

        public Person Man
        {
            get
            {
                return man;
            }
            set
            {
                man = value;
            }
        }
        public string Art
        {
            get
            {
                return art;
            }
            set
            {
                art = value;
            }
        }
        public double Rat
        {
            get
            {
                return rat;
            }
            set
            {
                rat = value;
            }
        }
        public Article(Person man1, string art1, double rat1)
        {
            man = man1;
            art = art1;
            rat = rat1;
        }
        public Article()
        {
            DateTime field = new DateTime(1995, 10, 20);
            man = new Person("Иван", "Окишев", field);
            art = "20!8";
            rat = 7.8;
        }
        public override string ToString()
        {
            string ret = "";
            ret += man.ToString();
            ret += art;
            ret += rat.ToString();
            return ret;
        }
        public object DeepCopy()
        {
            Article ret = new Article();
            ret.art = art;
            ret.man = man.DeepCopy();
            ret.rat = rat;
            return ret;
        }

        public int CompareTo(object obj)
        {
            Article o = obj as Article;
            if (String.Compare(Art, o.Art) > 0)
                return 1;
            if (String.Compare(Art, o.Art) < 0)
                return -1;
            else
                return 0;
        }

        public int Compare(Article x, Article y)
        {
            if (string.Compare(x.man.Sprop, y.man.Sprop) > 0) 
                return 1;
            if (string.Compare(x.man.Sprop, y.man.Sprop) < 0) 
                return -1;
            else
                return 0;
        }

        interface IRateAndCopy
        {
            double Rating { get; }
            object DeepCopy();
        }

    }
}
