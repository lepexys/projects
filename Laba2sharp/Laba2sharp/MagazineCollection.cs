using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using static System.Linq.Enumerable;
using System.ComponentModel;

namespace Laba2sharp
{
    class MagazineCollection<TKey> 
    {
        KeySelector<TKey> MyKeySelector;
        public void translateEvent(object subject, EventArgs e)
        {
            var me = (PropertyChangedEventArgs)e;
            var mg = (Magazine)subject;
            TKey key = myKaySelector(mg);
            MagazinesChanged(Update.Property, me.PropertyName.ToString(), key);
        }

        public string CollectionName { get; set; }
        public bool Replace(Magazine mold, Magazine mnew)
        {
            TKey key1 = myKaySelector(mold);
            TKey key2 = myKaySelector(mnew);
            if (MgDict.ContainsKey(key1)== true)
            {
                MgDict[key1] = MgDict[key2];
                MagazinesChanged(Update.Replace, "collection", key1);
                return true;
            }
            return false;
        }
        public event MagazinesChangedHandler<TKey> MgChanged;

        private void MagazinesChanged(Update up, string name, TKey key)
        {
            if (MgChanged != null)
            {
                MgChanged(this, new MagazinesChangedEventArgs<TKey>(CollectionName, up, name, key));
            }
        }

        private Dictionary<TKey, Magazine> MgDict = new Dictionary<TKey, Magazine>();
        private KeySelector<TKey> myKaySelector;

        public MagazineCollection(KeySelector<TKey> keySelector)
        {
            this.myKaySelector = keySelector;
        }
        public void AddDefaults()
        {
            Magazine magazine = new Magazine();
            TKey key = myKaySelector(magazine);
            MgDict.Add(key, magazine);
            MagazinesChanged(Update.Add, "collection", key);
            magazine.PropertyChanged += translateEvent;
        }
        public void AddMagazines(params Magazine[] magazines)
        {
            foreach (var item in magazines)
            {

                TKey key = myKaySelector(item);
                MgDict.Add(key, item);
                MagazinesChanged(Update.Add, "collection", key);
                item.PropertyChanged += translateEvent;
            }
        }
        public override string ToString()
        {
            string ret = "";
            foreach (var item in MgDict)
            {
                ret += item.Key.ToString();
                ret += "\n";
                ret += item.Value.ToString();
            }
            return ret;
        }
        public string ToShortString()
        {
            string ret = "";
            foreach (var item in MgDict)
            {
                ret += item.Key.ToString();
                ret += "    ";
                ret += item.Value.AvgRate.ToString();
                ret += item.Value.ToString();
            }
            return ret;
        }

        public double MaxAverageRat
        {
            get
            {
                if (MgDict.Count > 0) return MgDict.Values.Max(x => x.AvgRate);
                return 0;
            }
        }
        public IEnumerable<KeyValuePair<TKey, Magazine>> FrequencyGroup(Frequency value)
        {
            return MgDict.Where(x => x.Value.Pereod == value);
        }
        public IEnumerable<IGrouping<Frequency, KeyValuePair<TKey, Magazine>>> GoupEl
        {
            get
            {
                return MgDict.GroupBy(x => x.Value.Pereod);
            }
        }
    }
}
