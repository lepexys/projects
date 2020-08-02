using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace lab5
{

    public static class ImportDLL
    {
        private const string FileNameDLL = @"C:\Users\Владик\source\repos\lab5\Debug\MatrixDLL.dll";
        [DllImport(FileNameDLL, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I8)]
        private extern static Int64 CreateAndRepeatSolveC([param: MarshalAs(UnmanagedType.I4)]int n, [param: MarshalAs(UnmanagedType.I4)]int r);
        [DllImport(FileNameDLL, CallingConvention = CallingConvention.Cdecl)]
        private extern static IntPtr CreateAndSolveC([param: MarshalAs(UnmanagedType.I4)]int s, double[] r, double[] right);
        public static long CreateAndRepeate(int n, int r)
        {
            return CreateAndRepeatSolveC(n, r);
        }
        public static double[] CreateAndSolve(Matrix a, double[] right)
        {
            double[] result = new double[a.size];
            Marshal.Copy(CreateAndSolveC(a.size, a.row, right), result, 0, a.size);
            return result;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {

            // Task 1
        
            Console.WriteLine("\n 1) Проверка работы C#\n");

            Matrix matrix = new Matrix();
            double[] right = new double[matrix.size];
            double[] solve = new double[matrix.size];

            Console.WriteLine("\n"+matrix.ToString());

            Console.WriteLine("\n\tВведите правую часть:");
            for (int i = 0; i < matrix.size; i++)
            {
                Console.Write("\n\t\tВведите [" + i + "] элемент вектора: ");
                right[i] = Convert.ToInt32(Console.ReadLine());
            }

            solve = matrix.Solve(right);
            Console.WriteLine("\n\n\tРешение C#:\n");
            for (int i = 0; i < matrix.size; i++)
            {
                Console.WriteLine("\t\t" + solve[i].ToString());
            }

            SolveChecking(matrix, solve, right);


            // Task 2

            Console.WriteLine("\n\n 2) Проверка работы C++\n");

            solve = ImportDLL.CreateAndSolve(matrix, right);
            Console.WriteLine("\n\tРешение C++:\n");
            foreach (double s in solve)
            {
                Console.WriteLine("\t\t" + s);
            }

            SolveChecking(matrix, solve, right);

    
            // Task 3
            
            Console.WriteLine("\n\n 3) Сериализация\n");

            Console.Write("\n\tВведите название файла: ");

            string name = Console.ReadLine();
            TimesList list1 = new TimesList(name);
            string ans = "y";

            do
            {
                TimeItem time_item = new TimeItem();
                Console.Write("\n\tВведите порядок матрицы: ");
                int size = Convert.ToInt32(Console.ReadLine());
                Console.Write("\n\tВведите количество повторов: ");
                int repeat_num = Convert.ToInt32(Console.ReadLine());

                right = new double[size];
                for (int i = 0; i < size; i++)
                {
                    right[i] = i;
                }
                matrix = new Matrix(size);

                Stopwatch timer = Stopwatch.StartNew();
                for (int i = 0; i < repeat_num; i++)
                {
                    matrix.Solve(right);
                }
                timer.Stop();

                time_item.TimeCharp = timer.Elapsed.Milliseconds;
                time_item.TimeC = ImportDLL.CreateAndRepeate(size, repeat_num);
                time_item.Coeffiecient = time_item.TimeCharp / time_item.TimeC;
                time_item.Size = size;
                time_item.RepeatNum = repeat_num;

                list1.Add(time_item);

                Console.Write("\n\tДля повтора введите \"y\": ");
                ans = Console.ReadLine();
            } while (ans == "y");

            list1.SaveFromBinaryFile(name);
            Console.WriteLine("\n" + list1.ToString());
            Console.Read();

        }

        // Проверка решения

        static void SolveChecking(Matrix matrix, double[] solve, double[] right)
        {

            double ans = 0;
            for (int j = 0; j < matrix.size; j++)
            {
                for (int i = 0; i < matrix.size; i++)
                {
                    if (j > i)
                    {
                        ans += matrix.row[j - i] * solve[i];
                    }
                    else
                    {
                        ans += matrix.row[i - j] * solve[i];
                    }

                }
            }
            for (int i = 0; i < matrix.size; i++)
            {
                ans -= right[i];
            }
            Console.Write("\n\tПогрешность: " + ans / matrix.size + "\n");
        }
    }
}

