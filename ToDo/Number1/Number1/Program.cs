using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Number1
{
    class Program
    {
        static void Main(string[] args)
        {
            Random r = new Random();
            long n = 1000, t1, t2; //Тут задаётся размер матриц
            Stopwatch t = new Stopwatch();
            double[,] ar11 = new double[n, n];
            double[,] ar12 = new double[n, n];
            double[][] ar21 = new double[n][];
            double[][] ar22 = new double[n][];
            for (int i = 0; i < n; i++)
                ar21[i] = new double[n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    ar21[i][j] = r.NextDouble();
            for (int i = 0; i < n; i++)
                ar22[i] = new double[n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    ar22[i][j] = r.NextDouble();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    ar11[i, j] = r.NextDouble();
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    ar12[i, j] = r.NextDouble();
            t.Start();
            double[,] ar1 = new double[n, n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        ar1[i, j] += ar11[i, k] * ar12[k, j];
            t.Stop();
            t1 = t.ElapsedMilliseconds;
            t.Reset();
            t.Start();
            double[][] ar2 = new double[n][];
            for (int i = 0; i < n; i++)
                ar2[i] = new double[n];
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        ar2[i][j] += ar21[i][k] * ar22[k][j];
            t.Stop();
            t2 = t.ElapsedMilliseconds;
            t.Reset();
            Console.WriteLine("Время для матрицы в виде двумерного массива: " + t1);
            Console.WriteLine("Производительность для неё: " + 2 * (n ^ 3) / ((double)t1/1000));
            Console.WriteLine("Время для матрицы в виде вложенных массивов: " + t2);
            Console.WriteLine("Производительность для неё: " + 2 * (n ^ 3) / ((double)t2/1000));
            Console.ReadKey();
        }
    }
}
