using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;


namespace Laba2sharp
{
    [Serializable]
    class Edition : INotifyPropertyChanged
    {
        public Edition(string Namei, DateTime DAtaEnd, int Tirr1)
        {
            this.NameI = Namei;
            this.Dateend = DAtaEnd;
            this.Tir1 = Tirr1;
        }
        public Edition()
        {
            NameI = "lolkek";
            Dateend = new DateTime(1000, 01, 10);
            Tir1 = 550;
        }

        protected string nameI;

        public string NameI
        {
            get { return nameI; }
            set { nameI = value;
                OnPropertyChanged("nameI");
            }
        }
        protected DateTime dateend;

        public DateTime Dateend
        {
            get { return dateend; }
            set { dateend = value;
                OnPropertyChanged("Dateend");
            }
        }

        protected int tir1;

        public int Tir1
        {
            get { return tir1; }
            set
            {
                if (value > 0)
                {
                    tir1 = value;
                }
                else
                {
                    throw new ArgumentException("Введено отрицательное число");
                }
                OnPropertyChanged("Tir1");
            }
        }
        /*public override Edition DeepCopy()
        {
            return new Edition(this.NameI, this.Dateend, this.Tir1);
        }*/
        public override bool Equals(object obj)
        {
            if (obj == null) { return false; }
            if (!(obj is Edition)) { return false; }
            Edition obj1 = (Edition)obj;
            return (NameI == obj1.NameI) && (Dateend == obj1.Dateend) && (Tir1 == obj1.Tir1);
        }

        public static bool operator ==(Edition a, Edition b)
        {
            if (System.Object.ReferenceEquals(a, b))
            {
                return true;
            }
            if (((object)a == null) || ((object)b == null))
            {
                return false;
            }
            return a.NameI == b.NameI && a.Dateend == b.Dateend && a.Tir1 == b.Tir1;
        }
        public static bool operator !=(Edition a, Edition b)
        {
            return !(a == b);
        }

        public override int GetHashCode()
        {
            return NameI.GetHashCode() + Dateend.GetHashCode() + Tir1.GetHashCode();
        }
        public override string ToString()
        {
            return NameI+" " + Dateend+" " + Tir1+"\n";
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

    }
}
