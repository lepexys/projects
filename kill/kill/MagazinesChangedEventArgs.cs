using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
        class MagazinesChangedEventArgs<TKey> : EventArgs
        {
        public string Naming { get; set; }
        public Update Whosumme { get; set; }
        public string NameConf { get; set; }
        public TKey SixNine { get; set; }
        public MagazinesChangedEventArgs(string a, Update b, string c, TKey d)
        {
            Naming = a;
            Whosumme = b;
            NameConf = c;
            SixNine = d;
        }
        public override string ToString()
        {
            return Naming + " " + Whosumme.ToString() + " " + NameConf + " " + SixNine.ToString();
        }
        }
}
