using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
    class TestCollections<TKey, Tvalue>
    {
        public List<TKey> listk = new List<TKey>();
        public List<string> lists = new List<string>();
        public Dictionary<TKey, Tvalue> dict = new Dictionary<TKey, Tvalue>();
        public Dictionary<string, Tvalue> dics = new Dictionary<string, Tvalue>();
        public Magazine.GenerateElement<TKey, Tvalue> general;
        public TestCollections(int a, Magazine.GenerateElement<TKey, Tvalue> b)
        {
            for (int i = 0; i < a; i++)
            {
                listk.Add(b(i).Key);
                lists.Add(b(i).Key.ToString());
                dict.Add(b(i).Key, b(i).Value);
                dics.Add(b(i).Key.ToString(), b(i).Value);
            }
        }
    }
}
