using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Search
{
    class Index
    {
        public string where;
        public int place;
    }
    class Range
    {
        public long distance;
        public string words;
    }
    class FileSearch
    {
        public string folder;
        public Dictionary<string, List <Index>> DamnSon = new Dictionary<string, List <Index>>();
        public char Convert (int a)
            {
            char b=(char)a;
            if(char.IsLetter(b))
            {
                b = char.ToLower(b);
            }
            if (b==','||b=='.'||b=='-'||b==':'||b==';'||b=='!'||b=='?')
            {
                b = ' ';
            }
            return b;
            }
        public void BuildIndex()
        {
            Stopwatch t = new Stopwatch();
            t.Start();
            string[] files = Directory.GetFiles(folder);
            StreamReader str;
            List<Index> g = new List <Index>();

            int index = 0;
            int k = 0;
            int q = 0;
            int i = 0;
            int u;
            foreach (string f in files)
            {
                str = new StreamReader(f,Encoding.Default);
                k = 1;
                int j = 0;
                index = 0;
                while (k == 1)
                {
                    char[] buff = new char[20];
                    q = 1;
                    u = str.Read();
                    if (u < 0)
                        break;
                    buff[0] = Convert(u);
                    i = 1;
                    while (q == 1)
                    {
                        u = str.Read();
                        if (u < 0)
                        {
                            k = 0;
                            g.Add(new Index());
                            g[j].where = f;
                            g[j].place = index;
                            if (!DamnSon.ContainsKey(new string(buff)))
                            {
                                DamnSon.Add(new string(buff), new List<Index>());
                                DamnSon[new string(buff)].Add(g[j]);
                            }
                            else
                                DamnSon[new string(buff)].Add(g[j]);
                            j++;
                            break;
                        }
                        if (char.IsWhiteSpace((char)u))
                        {
                            if (!DamnSon.ContainsKey(new string(buff)))
                            {
                                g.Add(new Index());
                                g[j].where = f;
                                g[j].place = index;
                                DamnSon.Add(new string(buff), new List<Index>());
                                DamnSon[new string(buff)].Add(g[j]);
                                j++;
                            }
                            else
                            {
                                g.Add(new Index());
                                g[j].where = f;
                                g[j].place = index;
                                DamnSon[new string(buff)].Add(g[j]);
                                j++;
                            }
                            break;
                        }
                        if (Convert(u) == ' ')
                            continue;
                        index++;
                        buff[i] = Convert(u);
                        i++;
                    }
                }
            }
            t.Stop();
            Console.WriteLine(t.ElapsedMilliseconds+"ms");
        }
        public IEnumerable<string> Find(string phrase)
        {
            string[] a = phrase.Split(new char[] { ' ' }, StringSplitOptions.RemoveEmptyEntries);
            List <Index> h;
            List<Range> r = new List<Range>();
            int u;
            int c=0;
            int j;
            char[] buff;
            StreamReader dog;
            string[] files = Directory.GetFiles(folder);
            foreach (string f in files)
            {
                foreach (string g in a)
                {
                    if (!DamnSon.ContainsKey(g))
                        break;
                    h = DamnSon[g];
                    for (int i = 0; i < h.Count; i++)
                    {
                        dog = new StreamReader(h[i].where, true);
                        buff = dog.ReadToEnd().ToCharArray();
                        j = h[i].place - 1;
                        u = buff[j];
                        while (j > 0 || Convert(u) != ' ')
                        {
                            u = buff[j];
                            c += (byte)u - (byte)Convert(u);
                            j--;
                        }
                        if (h[i].place > 10)
                            dog.ReadBlock(buff, h[i].place - 8, 40);
                        else
                            dog.ReadBlock(buff, 0, 40);
                        yield return (h[i].where + " " + c.ToString() + " ..." + dog.ToString() + "...");
                    }
                }
            }
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            FileSearch a = new FileSearch();
            a.folder = Console.ReadLine();
            string phrase = Console.ReadLine();
            a.BuildIndex();
            foreach(string gg in a.Find(phrase))
            {
                Console.WriteLine(gg);
            }
            Console.ReadKey();
        }
    }
}