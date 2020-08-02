using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
    class MagazineCollection<TKey>
    {
        protected Dictionary<TKey, Magazine> magazines = new Dictionary<TKey, Magazine>();
        protected Magazine.KeySelector<TKey> keys;
        public MagazineCollection(Magazine.KeySelector<TKey> a)
        {
            keys = a;
        }
        public void AddDefaults()
        {
            magazines.Add(keys(new Magazine()), new Magazine());
            MagazinesChanged(this, new MagazinesChangedEventArgs<TKey>(Naming, Update.Add, "", magazines.Keys.Last()));
            
        }
        public void AddMagazines(params Magazine[] a)
        {
            foreach (Magazine h in a)
            {
                magazines.Add(keys(h), h);
                MagazinesChanged(this, new MagazinesChangedEventArgs<TKey>(Naming, Update.Add,"", magazines.Keys.Last()));
            }
        }
        public override string ToString()
        {
            string ret = "";
            foreach (Magazine a in magazines.Values)
            {
                ret += a.ToString();
            }
            return ret;
        }
        public virtual string ToShortString()
        {
            string ret = "";
            foreach (Magazine a in magazines.Values)
            {
                ret += a.ToShortString();
                ret += a.Magp.Count + " ";
                ret += a.Maga.Count + " ";
            }
            return ret;
        }
        public double Msr
        {
            get
            {
                if (magazines.Count == 0)
                    return 228;
                else
                    return magazines.Max((magazines) => magazines.Value.Mr);
            }
        }
        public IEnumerable<KeyValuePair<TKey, Magazine>> FrequencyGroup(Frequency value)
        {
            return magazines.Where((magazines) => magazines.Value.Magf == value);
        }
        public IEnumerable<IGrouping<Frequency, KeyValuePair<TKey, Magazine>>> Paris
        {
            get
            {
                return magazines.GroupBy((magazines) => magazines.Value.Magf);
            }
        }
        public string Naming { get; set; }
        public bool Replace(Magazine mold, Magazine mnew)
        {
            if (magazines.Values.Contains(mold))
            {
                foreach (TKey a in magazines.Keys)
                    if (magazines[a] == mold)
                    {
                        magazines[a] = mnew;
                        MagazinesChanged(this,new MagazinesChangedEventArgs<TKey> (Naming,Update.Replace,"",a));
                        return true;
                    }
                return false;
            }
            else return false;
        }
        public event Magazine.MagazinesChangedHandler<TKey> MagazinesChanged;
    }
}
