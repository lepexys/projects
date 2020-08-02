using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Number2
{
    class Complex
    {
        int Im { get; set; }
        int Re { get; set; }
        public Complex() { }
        public Complex(int a)
        {
            Re = a;
            Im = 0;
        }
        public Complex(int a,int b)
        {
            Re = a;
            Im = b;
        }
        double Mod()
        {
            return Math.Sqrt(Im^2+Re^2);
        }
        double Arg()
        {
            return Math.Atan((double)Im/Re);
        }
        public static Complex CreateComplex(double mod, double arg)
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
        public static explicit operator double (Complex a)
        {
            return a.Mod();
        }
        public static implicit operator Complex (int a)
        {
            return new Complex(a, 0);
        }
    }
    abstract class Body3D
    {
        abstract public double Square();
        abstract public double Volume();
        abstract public double Lenght();
    }
    class Parallelepiped : Body3D
    {
        public Parallelepiped(double x, double y, double z)
        {
            A = x;
            B = y;
            C = z;
        }
        double A { get; set; }
        double B { get; set; }
        double C { get; set; }
        public override double Lenght()
        {
            return A * 4 + B * 4 + C * 4;
        }

        public override double Square()
        {
            return A * B * 2 + A * C * 2 + C * B * 2;
        }

        public override double Volume()
        {
            return A * B * C;
        }
    }
    class Ball : Body3D
    {
        public Ball(double x)
        {
            Radius = x;
        }
        double Radius { get; set; }
        public override double Lenght()
        {
            return 0;
        }

        public override double Square()
        {
            return 4 * Math.PI * Radius * Radius;
        }

        public override double Volume()
        {
            return (double)4 / 3 * Math.PI * Radius * Radius * Radius;
        }
    }
    class Tetrahedron : Body3D
    {
        public Tetrahedron(double x)
        {
            Side = x;
        }
        double Side { get; set; }
        public override double Lenght()
        {
            return Side * 6;
        }

        public override double Square()
        {
            return Side * Side * Math.Sqrt(3);
        }

        public override double Volume()
        {
            return Side * Side * Side * Math.Sqrt(3) / 12;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            Body3D[] x = new Body3D[3];
            x[0] = new Parallelepiped(1, 2, 3);
            x[1] = new Ball(4.3);
            x[2] = new Tetrahedron(6.8);
            Console.WriteLine(x[0].Lenght() + " " + x[1].Square()+" "+ x[2].Volume());
            Console.ReadKey();
        }
    }
}
