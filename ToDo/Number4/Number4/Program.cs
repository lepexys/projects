using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Number4
{
    class Complex
    {
        int Im { get; set; }
        int Re { get; set; }
        Complex(int a)
        {
            Re = a;
            Im = 0;
        }
        Complex(int a, int b)
        {
            Re = a;
            Im = b;
        }
        double Mod()
        {
            return Math.Sqrt(Im ^ 2 + Re ^ 2);
        }
        double Arg()
        {
            return Math.Atan((double)Im / Re);
        }
        static Complex CreateComplex(double mod, double arg)
        {
            int re = (int)(mod * Math.Sin(arg)) / 1;
            int im = (int)(mod * Math.Cos(arg)) / 1;
            Complex a = new Complex(re, im);
            return a;
        }
        public static Complex operator +(Complex one, Complex two)
        {
            return new Complex(one.Re + two.Re, one.Im + two.Im);
        }
        public static Complex operator -(Complex one, Complex two)
        {
            return new Complex(one.Re - two.Re, one.Im - two.Im);
        }
        public static Complex operator *(Complex one, Complex two)
        {
            return new Complex(one.Re * two.Re, one.Im * two.Im);
        }
        public static Complex operator /(Complex one, Complex two)
        {
            return new Complex(one.Re / two.Re, one.Im / two.Im);
        }
        public override string ToString()
        {
            if (Re == 0 && Im == 0)
                return "0";
            if (Re == 0)
                return Im + "i";
            if (Im == 0)
                return Re.ToString();
            if (Im < 0)
                return Re + " - " + Math.Abs(Im) + "i";
            return Re + " + " + Im + "i";
        }
        public static bool operator ==(Complex one, Complex two)
        {
            return one.Equals(two);
        }
        public static bool operator !=(Complex one, Complex two)
        {
            return !one.Equals(two);
        }
        public override bool Equals(object one)
        {
            Complex x = one as Complex;
            return ToString() == x.ToString();
        }
        public override int GetHashCode()
        {
            return ToString().GetHashCode();
        }
        public static explicit operator double(Complex a)
        {
            return a.Mod();
        }
        public static implicit operator Complex(int a)
        {
            return new Complex(a, 0);
        }
    }
    class Queue
    {
        public class Element
        {
            public Element Prev { get; set; }
            public Element Next { get; set; }
            public Complex Digit { get; set; }
            public Element(Complex x,Element p,Element n)
            {
                Prev = p;
                Next = n;
                Digit = x;
            }
        }
        public Queue()
        {
            Count = 0;
            Tail = null;
            Head = null;
        }
        public Element Tail { get; set; }
        public Element Head { get; set; }
        public int Count { get; set; }
        void Enqueue(Complex a)
        {
            if (Tail == null)
            {
                Element node = new Element(a,null,null);
                Tail = node;
                Head = node;
                return;
            }
            Element nod = new Element(a, Head, null);
            Head.Next = nod;
            Head = nod;
        }
        Complex Dequeue()
        {
            Complex ret = Tail.Digit;
            Tail.Next.Prev = null;
            Tail = Tail.Next;
            Count--;
            return ret;
        }
        Complex Peek()
        {
            return Tail.Digit;
        }
        void Print()
        {
            Element current = Tail;
            while (current != null)
            {
                Console.WriteLine(current.Digit.ToString());
                current = current.Next;
            }
        }
    } 
    class Program
    {
        static void Main(string[] args)
        {
        }
    }
}
