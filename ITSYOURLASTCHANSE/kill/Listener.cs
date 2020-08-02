using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
    class Listener
    {
        class ListEntry
        {
            public string Naming { get; set; }
            public Update Whosumme { get; set; }
            public string NameConf { get; set; }
            public string SixNine { get; set; }
            public ListEntry(string a, Update b, string c, string d)
            {
                Naming = a;
                Whosumme = b;
                NameConf = c;
                SixNine = d;
            }
            public override string ToString()
            {
                return Naming + " " + Whosumme.ToString() + " " + NameConf + " " + SixNine;
            }
        }
        private List<ListEntry> lister = new List<ListEntry>();
        public void Lookmeineye (object sourse, MagazinesChangedEventArgs<string> obj)
        {
            ListEntry le = new ListEntry(obj.Naming, obj.Whosumme, obj.NameConf, obj.SixNine.ToString());
            lister.Add(le);
        }
        public override string ToString()
        {
            string ret = "";
            foreach(ListEntry a in lister)
            {
                ret += a.ToString() + " \n";
            }
            return ret;
        }
    }
}
