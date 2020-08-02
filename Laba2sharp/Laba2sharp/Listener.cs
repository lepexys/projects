using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace Laba2sharp
{
    class Listener 
    {
        private List<ListEntry> ListOfAllEntry = new List<ListEntry>();

        public void NewListEntry(object subject, EventArgs e)
        {
            var me = (MagazinesChangedEventArgs<string>)e;
            ListEntry newListEntry = new ListEntry(me.CollectionName, me.update, me.Magname, me.ElementKey.ToString());
            ListOfAllEntry.Add(newListEntry);
        }
        public void NewListEntry2(object subject, EventArgs e)
        {
            var me = (PropertyChangedEventArgs)e;
            ListEntry newListEntry = new ListEntry("", Update.Property, me.PropertyName.ToString(), "");
            ListOfAllEntry.Add(newListEntry);
        }
        public override string ToString()
        {
            string entryNames = "";
            foreach (ListEntry item in ListOfAllEntry)
            {
                entryNames += item.ToString() + "\n";
            }
            return entryNames;
        }
    }
}
