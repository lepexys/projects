using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba2sharp
{
    [Serializable]
    class Article : IComparer<Article>, IComparable
    {
        public Person Author { get; set; } // автор 
        public string Title { get; set; } // название 
        public double Rating { get; set; } // рейтинг 

        public Article(Person Author, string Title, double Rating)
        {
            this.Author = Author;
            this.Title = Title;
            this.Rating = Rating;
        }
        public Article()
        {
            this.Author = new Person();
            this.Title = "Ukraina";
            this.Rating = 65.5;
        }
        public override string ToString()
        {
            return Author + " " + Title + " " + Rating + "\n";
        }
        #region Методы интерфейса IRateAndCopy

        /*public override Article DeepCopy()
        {
            return new Article(this.Author, this.Title, this.Rating);
        }*/

        public double Ratingg { get; }
        #endregion Методы интерфейса IRateAndCopy

        public int CompareTo(object obj)
        {
            Article p = new Article();
            if (p != null)
                return this.Title.CompareTo(p.Title);
            else
                throw new ArgumentException("Невозможно сравнить два объекта");

        }
        public int Compare(Article x, Article y)
        {
            if (x != null || y != null)
                return this.Author.SecondName.CompareTo(y.Author.SecondName);
            else
                throw new ArgumentException("Невозможно сравнить два объекта");
        }
    }
}