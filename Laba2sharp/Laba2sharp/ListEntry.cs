using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Laba2sharp
{
    class ListEntry
    {
        public string CollectionName { get; set; }
        public Update UpType { get; set; }
        public string PropName { get; set; }
        public string KeyTxt { get; set; }

        public ListEntry(string Name, Update Type, string Prop, string Key)
        {
            this.CollectionName = Name;
            this.UpType = Type;
            this.PropName = Prop;
            this.KeyTxt = Key;
        }
        public override string ToString()
        {
            return CollectionName + "\n" + UpType.ToString() + "\n" + PropName + "\n" + KeyTxt + "\n" + "\n";
        }
    }
}
