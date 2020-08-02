using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Number5
{
    public class Stack<T>
    {
        public T[] stack;
        const int n = 10;
        public int Count { get; set; }
        public void Fill(int k)
        {
            for (int i = 0; i < k; i++)
                Push(default(T));
        }
        public Stack()
        {
            stack = new T[n];
            Count = 0;
        }
        public Stack(int a)
        {
            stack = new T[a];
            Count = 0;
        }
        public void Push(T a)
        {
            if (Count < stack.Length)
            {
                stack[Count] = a;
                Count++;
            return;
            }
            throw new InvalidOperationException("Достигнут предел вместимости стека");
        }
        public T Pop()
        {
            T ret = stack[Count-1];
            stack[Count - 1] = default(T);
            Count--;
            return ret;
        }
        public T Top()
        {
            T ret = stack[Count - 1];
            return ret;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Stack<int> s = new Stack<int>(100);
            s.Push(20);
            Console.WriteLine(s.Top());
            Console.WriteLine(s.Pop());
            try
            {
                s.Fill(200);
            }
            catch(Exception e)
            { Console.WriteLine(e.Message); }
            Console.ReadKey();
        }
    }
}
