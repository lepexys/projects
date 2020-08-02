using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Runtime.CompilerServices;

namespace kill
{
    class Edition : IComparable, IComparer<Edition>, INotifyPropertyChanged
    {
        protected string name;
        protected DateTime time;
        protected int tire;

        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
                OnPropertyChanged("Название");
            }
        }
        DateTime Time
        {
            get
            {
                return time;
            }
            set
            {
                time = value;
                OnPropertyChanged("Дата");
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
                if (value < 0)
                {
                    throw new Exception("Тираж не может быть отрицательным");
                }
                else
                {
                    tire = value;
                    OnPropertyChanged("Тираж");
                }
            }
        }
        public Edition(string name1, DateTime time1, int tire1)
        {
            name = name1;
            time = time1;
            tire = tire1;
        }
        public Edition()
        {
            name = "Dorfa";
            time = new DateTime(2001, 9, 11);
            tire = 10000;
        }

        public object DeepCopy()
        {
            string rname = name;
            DateTime rtime = new DateTime(time.Year, time.Month, time.Day);
            int rtire = tire;
            Edition ret = new Edition(rname, rtime, rtire);
            return ret;
        }
        public override bool Equals(object obj)
        {
            bool k = false;
            Edition h = obj as Edition;
            if (name.Equals(h.name))
                if (time.Equals(h.time))
                    if (tire.Equals(h.tire))
                        k = true;
            return k;
        }
        public static bool operator ==(Edition obj1, Edition obj2)
        {
            return obj1.Equals(obj2);
        }
        public static bool operator !=(Edition obj1, Edition obj2)
        {
            if (obj1.Equals(obj2) == true)
                return false;
            else
                return true;
        }
        public override int GetHashCode()
        {
            int ret;
            Edition h = this as Edition;
            ret = h.ToString().GetHashCode();
            return ret;
        }
        public override string ToString()
        {
            string ret = "";
            ret += name;
            ret += tire.ToString();
            ret += time.ToString();
            return ret;
        }

        public int CompareTo(object obj)
        {
            Edition o = obj as Edition;
            if (String.Compare(Name, o.Name)>1)
                return 1;
            if (String.Compare(Name, o.Name)<1)
                return -1;
            else
                return 0;
        }
        public int Compare(Edition x, Edition y)
        {
            if (x.Time > y.Time)
                return 1;
            if (x.Time < y.Time)
                return -1;
            else
                return 0;
        }
        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChangedEventHandler handler = PropertyChanged;
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
