using System;
using System.Collections.Generic;
using System.IO;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UnitTestProject1
{
    public class ZIP
    {
        byte[] Pack(byte[] data)
        {
            if (data == null)
                throw new ArgumentNullException();
            List<byte> retlist = new List<byte>();
            byte inb;
            long col = 1;
            byte sym = data[0];
            for (long i = 1; i < data.LongLength; i++)
            {
                inb = data[i];
                if (i == data.LongLength - 1)
                {
                    if (sym == inb)
                    {
                        col++;
                        while (col > 255)
                        {
                            retlist.Add(sym);
                            retlist.Add(255);
                            col -= 255;
                        }
                        retlist.Add(sym);
                        retlist.Add((byte)col);
                        break;
                    }
                    else
                    {
                        while (col > 255)
                        {
                            retlist.Add(sym);
                            retlist.Add(255);
                            col -= 255;
                        }
                        retlist.Add(sym);
                        retlist.Add((byte)col);
                        retlist.Add(inb);
                        retlist.Add(1);
                        break;
                    }
                }
                if (sym == inb)
                    col++;
                else
                {
                    while (col > 255)
                    {
                        retlist.Add(sym);
                        retlist.Add(255);
                        col -= 255;
                    }
                    retlist.Add(sym);
                    retlist.Add((byte)col);
                    sym = inb;
                    col = 1;
                }
            }
            return retlist.ToArray();
        }
        byte[] Unpack(byte[] data)
        {
            if (data == null)
                throw new ArgumentNullException();
            if (data.LongLength % 2 == 1)
                throw new ArgumentException();
            byte inb, col;
            List<byte> ret = new List<byte>();
            long counter = 0;
            while (true)
            {
                if (counter >= data.LongLength - 1)
                {
                    break;
                }
                inb = data[counter];
                col = data[counter + 1];
                for (int i = 0; i < col; i++)
                {
                    ret.Add(inb);
                }
                counter += 2;
            }
            return ret.ToArray();
        }
        [TestClass]
        public class UnitTest1
        {
            [TestMethod]
            public void TestMethod1()
            {
                byte[] test1 = { 2,2,2,2,6,6,6,7,7 };
                byte[] expect = { 2, 4, 6, 3, 7, 2 };
                ZIP t = new ZIP();
                    CollectionAssert.AreEqual(expect,t.Pack(test1));
            }
            [TestMethod]
            public void TestMethod2()
            {
                byte[] test2 = new byte[300];
                byte[] expect = {0,255,0,45};
                for (int i = 0; i < 300; i++)
                    test2[i] = 0;
                ZIP t = new ZIP();
                    CollectionAssert.AreEqual(expect, t.Pack(test2));
            }
            [TestMethod]
            [ExpectedException (typeof(ArgumentNullException))]
            public void TestMethod3()
            {
                byte[] test3 = null;
                ZIP t = new ZIP();
                t.Pack(test3);
            }
            [TestMethod]
            [ExpectedException(typeof(ArgumentNullException))]
            public void TestMethod4()
            {
                byte[] test3 = null;
                ZIP t = new ZIP();
                t.Pack(test3);
            }
            [TestMethod]
            [ExpectedException(typeof(ArgumentException))]
            public void TestMethod5()
            {
                byte[] test5 = { 2, 2, 2, 2, 6, 6, 6, 7, 7 };
                ZIP t = new ZIP();
                t.Unpack(test5);
            }
            [TestMethod]
            public void TestMethod6()
            {
                byte[] test1 = { 2, 1, 5, 2, 10, 1};
                byte[] expect = { 2, 5, 5, 10};
                ZIP t = new ZIP();
                CollectionAssert.AreEqual(expect, t.Unpack(test1));
            }
        }
    }
}
