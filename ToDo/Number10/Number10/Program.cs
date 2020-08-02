using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Numerics;
using System.Threading.Tasks;

namespace Number10
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                if (Assembly.Load("Number2") != null)
                {
                    Assembly ins = Assembly.Load("Number2");
                    Type t = ins.GetType("Number2.Complex");
                    Type[] constypes = new Type[2];
                    constypes[0] = typeof(int);
                    constypes[1] = typeof(int);
                    var cons = t.GetConstructor(constypes);
                    var x = cons.Invoke(new object[2] { 2, 3 });
                    var meth = t.GetMethod("CreateComplex");
                    var instanse = Activator.CreateInstance(t);
                    var y = meth.Invoke(instanse, new object[2] { 14, Math.PI / 4 });
                    var plus = t.GetMethod("op_Addition");
                    var res1 = plus.Invoke(instanse, new object[2] { x, y });
                    var multi = t.GetMethod("op_Multiply");
                    var res2 = multi.Invoke(instanse, new object[2] { res1, res1 });
                    var division = t.GetMethod("op_Division");
                    var digit = cons.Invoke(new object[2] { 27, 27 });
                    var z = division.Invoke(instanse, new object[2] { res2, digit });
                    var tostr = t.GetMethod("ToString");
                    var str = tostr.Invoke(z,new object[] { });
                    Console.WriteLine((string)str);
                    dynamic cons1 = t.GetConstructor(constypes);
                    dynamic a = cons.Invoke(new object[2] { 4, 1 });
                    dynamic meth1 = t.GetMethod("CreateComplex");
                    dynamic instanse1 = Activator.CreateInstance(t);
                    dynamic b = meth.Invoke(instanse, new object[2] { 2, Math.PI / 3 });
                    dynamic c1 = multi.Invoke(instanse1, new object[2] { a, a });
                    dynamic c2 = multi.Invoke(instanse1, new object[2] { b, b });
                    dynamic c3 = plus.Invoke(instanse1, new object[2] { c1, c2 });
                    dynamic c4 = multi.Invoke(instanse1, new object[2] { c3, c3 });
                    dynamic dig = cons.Invoke(new object[2] { 3, 3 });
                    dynamic c5 = multi.Invoke(instanse1, new object[2] { b, dig });
                    dynamic c = division.Invoke(instanse1, new object[2] { c4, c5 });
                    str = tostr.Invoke(c, new object[] { });
                    Console.WriteLine((string)str);
                    Console.ReadKey();
                }
                else
                {
                    Console.WriteLine("Нет нужной сборки");
                    Complex e = new Complex(1, 2);
                    Complex f = new Complex();
                    f = Complex.FromPolarCoordinates(3, Math.PI / 8);
                    Complex d = 34 + Complex.Pow(e, f);
                    Console.WriteLine(d.ToString());
                    Console.ReadKey();
                }
            }
            catch (Exception) { }
        }
    }
}
