using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Number8
{
    class Reverse
    {
        public double Solve(double a, double b, Func<double,double> f, double y, double e)
        {
            double x = (b - a) / 2;
            while (Math.Abs(y - f(x)) >= e)
            {
                if (Math.Abs(y - f(a + (b - a) * 3 / 4)) >= Math.Abs(y - f(a + (b - a) * 1 / 4)))
                {
                    x = a + (b - a) * 1 / 4;
                    b = b - (b - a) / 2;
                }
                else
                {
                    x = a + (b - a) * 3 / 4;
                    a = a + (b - a) / 2;
                }
                Console.WriteLine("x = {0}, погрешность: {1}", x, Math.Abs(y - f(x)));
            }
            return x;
        }
    }
    class Program
    {
        public static double Funk(double t)
        {
            return Math.Sin(t);
        }
        delegate double Fun(double t);
        static void Main()
        {
            double Funk1(double t)
            {
                return t * t + Math.Sin(t - 2);
            }
            Fun one = Funk;
            Reverse rev = new Reverse();
            rev.Solve(0.1, 1.3, Funk, 0.5, 0.0001);
            rev.Solve(2.5, 3.5, Funk1, 8, 0.0001);
            rev.Solve(-1.6, -0.2, (double x)=> x*x, 1.4, 0.0001);
            Console.ReadKey();
        }
    }
}
