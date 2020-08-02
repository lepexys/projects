using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Archive
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                try
                {
                    string type = Console.ReadLine();
                    if (type == "pack")
                    {
                        string input = Console.ReadLine();
                        string output = Console.ReadLine();
                        int t = DateTime.Now.Second;
                        FileStream infile = new FileStream(@input + ".txt", FileMode.Open);
                        FileStream outfile = new FileStream(@output + ".txt", FileMode.Create);
                        while (true)
                        {
                            int inb = infile.ReadByte();
                            int k = 1;
                            if (inb < 0)
                                break;
                            long col = 1;
                            byte sym;
                            while (k == 1)
                            {
                                sym = (byte)inb;
                                k = 0;
                            }
                            if (sym == inb)
                                col++;
                            else
                            {
                                while (col > 255)
                                {
                                    outfile.WriteByte(sym);
                                    outfile.WriteByte(255);
                                    col -= 255;
                                }
                                outfile.WriteByte(sym);
                                outfile.WriteByte((byte)col);
                                sym = (byte)inb;
                                col = 1;
                            }
                            infile.Close();
                            outfile.Close();
                        }
                        t = DateTime.Now.Second - t;
                        Console.WriteLine("Time of work: " + t);
                        FileInfo inf1 = new FileInfo(input);
                        FileInfo inf2 = new FileInfo(output);
                        float koef = inf2.Length / inf1.Length;
                        Console.WriteLine("Coefficient: " + koef);
                    }
                    if (type == "unpack")
                    {
                    }
                    if (type == "test")
                    {
                        string input = Console.ReadLine();
                        int size = Console.Read();
                        FileStream test = new FileStream(@input + ".txt", FileMode.Create);
                        byte b;
                        Random s = new Random();
                        for (int i = 0; i < size; i++)
                        {
                            b = (byte)s.Next(255);
                            test.WriteByte(b);
                        }
                        test.Close();
                    }
                }
                catch (IOException e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }
    }
}