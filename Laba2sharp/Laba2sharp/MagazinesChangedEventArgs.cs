using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba2sharp
{
    class MagazinesChangedEventArgs<Tkey> : EventArgs
    {
        public string CollectionName { get; set; }
        public Update update { get; set; }
        public string Magname { get; set; }
        public Tkey ElementKey { get; set; }

        public MagazinesChangedEventArgs(string Name, Update Kind, string Mag, Tkey Key)
        {
            this.CollectionName = Name;
            this.update = Kind;
            this.Magname = Mag;
            this.ElementKey = Key;
        }

        public override string ToString()
        {
            return CollectionName + "\n" + update.ToString() + "\n" + Magname + "\n" + ElementKey.ToString() + "\n" + "\n";
        }
    }
}
