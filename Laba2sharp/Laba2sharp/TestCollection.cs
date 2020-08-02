using System;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;
using System.Text;
using System.Threading.Tasks;

namespace Laba2sharp
{
    class TestCollections<TKey, TValue>
    {
        private List<TKey> testTKeyList = new List<TKey>();
        private List<string> testStringList = new List<string>();
        private Dictionary<TKey, TValue> dictionaryTKey = new Dictionary<TKey, TValue>();
        private Dictionary<string, TValue> dictionaryString = new Dictionary<string, TValue>();
        private GenerateElement<TKey, TValue> generateElement;



        public TestCollections(int count, GenerateElement<TKey, TValue> j)
        {
            if (count <= 0) throw new ArgumentException();

            generateElement = j;
            for (int i = 0; i < count; i++)
            {
                var element = generateElement(i);
                dictionaryTKey.Add(element.Key, element.Value);
                dictionaryString.Add(element.Key.ToString(), element.Value);
                testTKeyList.Add(element.Key);
                testStringList.Add(element.Key.ToString());
            }
        }
        public void SearchInTKeyList()
        {
            var first = testTKeyList[0];
            var center = testTKeyList[testTKeyList.Count / 2];
            var last = testTKeyList[testTKeyList.Count - 1];
            var another = generateElement(testTKeyList.Count + 10).Key;

            var sw = Stopwatch.StartNew();
            testTKeyList.Contains(first);
            sw.Stop();
            Console.WriteLine("In TKey List\nДля первого элемента: " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            testTKeyList.Contains(center);
            sw.Stop();
            Console.WriteLine("Для центрального элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            testTKeyList.Contains(last);
            sw.Stop();
            Console.WriteLine("Для последнего элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            testTKeyList.Contains(another);
            sw.Stop();
            Console.WriteLine("для элемента не входящего в коллекцию:  " + sw.Elapsed + "\n");
        }
        public void SearchInStrList()
        {
            var first = testStringList[0];
            var center = testStringList[testStringList.Count / 2];
            var last = testStringList[testStringList.Count - 1];
            var another = generateElement(testStringList.Count + 10).Key.ToString();

            var sw = Stopwatch.StartNew();
            testStringList.Contains(first);
            sw.Stop();
            Console.WriteLine("In string List\n  Для первого элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            testStringList.Contains(center);
            sw.Stop();
            Console.WriteLine("Для центрального элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            testStringList.Contains(last);
            sw.Stop();
            Console.WriteLine("Для последнего элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            testStringList.Contains(another);
            sw.Stop();
            Console.WriteLine("для элемента не входящего в коллекцию:  " + sw.Elapsed + "\n");
        }

        public void SearcInTKeyDictionary()
        {
            var first = dictionaryTKey.ElementAt(0).Key;
            var center = dictionaryTKey.ElementAt(dictionaryTKey.Count / 2).Key;
            var last = dictionaryTKey.ElementAt(dictionaryTKey.Count - 1).Key;
            var another = generateElement(dictionaryTKey.Count + 10).Key;

            var sw = Stopwatch.StartNew();
            dictionaryTKey.ContainsKey(first);
            sw.Stop();
            Console.WriteLine("In TKey  Dictionary by key\nДля первого элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryTKey.ContainsKey(center);
            sw.Stop();
            Console.WriteLine("Для центрального элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryTKey.ContainsKey(last);
            sw.Stop();
            Console.WriteLine("Для последнего элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryTKey.ContainsKey(another);
            sw.Stop();
            Console.WriteLine("для элемента не входящего в коллекцию:  " + sw.Elapsed + "\n");
        }

        public void SearcInStrDictionary()
        {
            var first = dictionaryString.ElementAt(0).Key;
            var center = dictionaryString.ElementAt(dictionaryString.Count / 2).Key;
            var last = dictionaryString.ElementAt(dictionaryString.Count - 1).Key;
            var another = generateElement(dictionaryString.Count + 10).Key.ToString();

            var sw = Stopwatch.StartNew();
            dictionaryString.ContainsKey(first);
            sw.Stop();
            Console.WriteLine("In string  Dictionary by key\nДля первого элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryString.ContainsKey(center);
            sw.Stop();
            Console.WriteLine("Для центрального элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryString.ContainsKey(last);
            sw.Stop();
            Console.WriteLine("Для последнего элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryString.ContainsKey(another);
            sw.Stop();
            Console.WriteLine("для элемента не входящего в коллекцию:  " + sw.Elapsed + "\n");
        }

        public void SearcInTKeyDictionaryByValue()
        {
            var first = dictionaryTKey.ElementAt(0).Value;
            var center = dictionaryTKey.ElementAt(dictionaryTKey.Count / 2).Value;
            var last = dictionaryTKey.ElementAt(dictionaryTKey.Count - 1).Value;
            var another = generateElement(dictionaryTKey.Count + 10).Value;

            var sw = Stopwatch.StartNew();
            dictionaryTKey.ContainsValue(first);
            sw.Stop();
            Console.WriteLine("In TKey  Dictionary by value\nДля первого элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryTKey.ContainsValue(center);
            sw.Stop();
            Console.WriteLine("Для центрального элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryTKey.ContainsValue(last);
            sw.Stop();
            Console.WriteLine("Для последнего элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryTKey.ContainsValue(another);
            sw.Stop();
            Console.WriteLine("для элемента не входящего в коллекцию:  " + sw.Elapsed + "\n");
        }

        public void SearcInStrDictionaryByValue()
        {
            var first = dictionaryString.ElementAt(0).Value;
            var center = dictionaryString.ElementAt(dictionaryString.Count / 2).Value;
            var last = dictionaryString.ElementAt(dictionaryString.Count - 1).Value;
            var another = generateElement(dictionaryString.Count + 10).Value;

            var sw = Stopwatch.StartNew();
            dictionaryString.ContainsValue(first);
            sw.Stop();
            Console.WriteLine("In string  Dictionary by value\nДля первого элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryString.ContainsValue(center);
            sw.Stop();
            Console.WriteLine("Для центрального элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryString.ContainsValue(last);
            sw.Stop();
            Console.WriteLine("Для последнего элемента:  " + sw.Elapsed);

            sw = Stopwatch.StartNew();
            dictionaryString.ContainsValue(another);
            sw.Stop();
            Console.WriteLine("для элемента не входящего в коллекцию:  " + sw.Elapsed + "\n");
        }
    }
}