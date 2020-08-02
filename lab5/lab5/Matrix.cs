using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab5
{
    public delegate double GetDelegate(int i, int j);

    public class Matrix
    {
        public int size { get; }
        public double[] row { get; }
        double[] x;
        double[] y;
        double[] right;

        public Matrix()
        {
            Console.Write("\n\t Введите число элементов: ");

            size = Convert.ToInt32(Console.ReadLine());
            row = new double[size];
            x = new double[size];
            right= new double[size];

            Console.Write("\n\t\tВведите [0] элемент матрицы: ");
            row[0] = Convert.ToInt32(Console.ReadLine());
            
            for (int i = 1; i < size; i++)
            {
                Console.Write("\n\t\tВведите ["+i+"] элемент матрицы: ");
                row[i] = Convert.ToInt32(Console.ReadLine()); 
            }
        }
        public Matrix(int size) {

            this.size = size;

            Random r = new Random((int)DateTime.Now.Ticks);
            row = new double[size];

            row[0] = r.NextDouble() / 100;

            for (int i = 1; i < size; i++)
            {
                row[i] = r.NextDouble() / 100 + 1000;
            }
            x = new double[size];
            y = new double[size];
	        right = new double[size];
        }
  
        public double[] Solve(double[] right)
        {

            for (int i = 0; i < size; i++)
            {
                this.right[i] = right[i];
            }

            double[] x_rec = new double[size];

            double F;
            double r;
            double s;

            x[0] = 1 / row[0];

            for (int k = 1; k < size; k++)
            {
                F = 0;
                r = 0;
                s = 0;

                for (int i = 0; i < k; i++)
                {
                    F += row[k - i] * x[i];
                }
                r = 1 / (1 - F * F);
                s = -r * F;

                for (int i = 0; i < k; i++)
                {
                    x_rec[i] = x[i];
                }

                x[0] = x_rec[0] * r;

                for (int i = 1; i < k; i++)
                {
                    x[i] = x_rec[i] * r + x_rec[k - i] * s;
                }

                x[k] = x_rec[0] * s;
                

            }

            for (int i = 0; i < size; i++)
            {
                x_rec[i] = GetMultiplyElement(GetReverseMatrixElement, GetRightElement, i, 0, size);
            }
            return x_rec;
        }

        double GetRightElement(int i, int j)
        {
            return right[i];
        }

        double GetMultiplyElement(GetDelegate reverse, GetDelegate right, int i, int j, int size2)
        {
	        double temp = 0;
	        for (int i1 = 0; i1<size2; i1++)
	        {
		        temp += reverse(i, i1)*right(i1, j);
        }
	        return temp;
        }

        double GetReverseMatrixElement(int i, int j)
        {
            double p = GetMultiplyElement(GetElementM1,GetElementM2, i, j, size);
            double p2 = GetMultiplyElement(GetElementM3, GetElementM4, i, j, size);
            return (p - p2) / x[0];
        }

        double GetElementM1(int i, int j)
        {
            if (j <= i)
                return x[i - j];
            else
                return 0;
        }
        double GetElementM2(int i, int j)
        {
            if (j >= i)
                return x[j - i];
            else
                return 0;
        }
        double GetElementM3(int i, int j)
        {
            if (i >= 1 && j < i)
                return x[size - i + j];
            else return 0;
        }
        double GetElementM4(int i, int j)
        {
            if (j > 0 && j > i)
                return x[size + i - j];
            else
                return 0;
        }

        public override string ToString()
        {
            string res = "";
            for (int i = 0; i < size; i++)
            {
                res += "\n ";
                for (int j = 0; j < size; j++)
                {
                    if (i < j)
                    {
                        res += ("\t"+row[j - i] );
                    }
                    else
                    {
                        res += ("\t" + row[i-j] );
                    }
                }
            }
            return res;
        }
    }
}
