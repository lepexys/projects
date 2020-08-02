using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ConsoleApplication1
{
    class Person
    {
        protected string name;
        protected string surname;
        protected System.DateTime field;
        protected Object e;

        public string nprop
        {
            get
            {
                return (string)e;
            }
            set
            {
                e = name;
            }
        }

        public string sprop
        {
            get
            {
                return (string) e;
            }
            set
            {
                e = surname;
            }
        }

        public DateTime dprop
        {
            get
            {
                return (DateTime) e;
            }
            set
            {
                e = field;
            }
        }

        Person(string name1, string surname1, DateTime field1) 
        {
            name = name1;
            surname = surname1;
            field = field1;
        }
        void inits()
        {
            name = "Vasia";
            surname = "Ygolkov";
            field = new DateTime(1995, 10, 20);
        }
    }
}
