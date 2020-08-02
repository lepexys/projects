using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace Number11
{
    class Program
    {
        static void Main(string[] args)
        {
            bool k = true;
            Fabric fabric = new Fabric();
            fabric = fabric.Begin();
            while (k)
            {
                Console.WriteLine("1-добавить нового сотрудника, 2-поиск по фамилии, 3-поиск по имени, 4-поиск по отчеству, 5-поиск по номеру телефона, 6-поиск по адресу, любое другое-выйти с сохранением данных");
                Console.Write("Ваш выбор: ");
                switch (Console.ReadLine())
                {
                    case "1":
                        {
                            fabric.Add();
                            break;
                        }
                    case "2":
                        {
                            Console.Write("Введите фамилию: ");
                            fabric.Search_S(Console.ReadLine());
                            break;
                        }
                    case "3":
                        {
                            Console.Write("Введите имя: ");
                            fabric.Search_N(Console.ReadLine());
                            break;
                        }
                    case "4":
                        {
                            Console.Write("Введите отчество: ");
                            fabric.Search_P(Console.ReadLine());
                            break;
                        }
                    case "5":
                        {
                            Console.Write("Введите телефон: ");
                            fabric.Search_T(Console.ReadLine());
                            break;
                        }
                    case "6":
                        {
                            Console.Write("Введите адрес: ");
                            fabric.Search_A(Console.ReadLine());
                            break;
                        }
                    default:
                        {
                            fabric.Save();
                            k = false;
                            break;
                        }
                }
            }
        }
        [Serializable]
        class User
        {
            public string Surname { get; set; }
            public string Name { get; set; }
            public string Patronymic { get; set; }
            public string Telephone { get; set; }
            public string Address { get; set; }
            public User(string s, string n, string p, string t, string a)
            {
                Surname = s;
                Name = n;
                Patronymic = p;
                Telephone = t;
                Address = a;
            }
            public override string ToString()
            {
                return Surname + " " + Name + " " + Patronymic + " " + Telephone + " " + Address;
            }
        }
        [Serializable]
        class Fabric
        {
            private List<User> users;
            public Fabric()
            {
                users = new List<User>();
            }
            public Fabric Begin()
            {
                if (File.Exists("Data"))
                {
                    IFormatter formatter = new BinaryFormatter();
                    using (var stream = new FileStream("Data", FileMode.Open, FileAccess.Read, FileShare.Read))
                    {
                         return (Fabric)formatter.Deserialize(stream);
                    }
                }
                return null;
            }
            public void Add()
            {
                string s, n, p, t, a;
                Console.Write("Введите фамилию: ");
                s = Console.ReadLine();
                Console.Write("Введите имя: ");
                n = Console.ReadLine();
                Console.Write("Введите отчество: ");
                p = Console.ReadLine();
                Console.Write("Введите телефон: ");
                t = Console.ReadLine();
                Console.Write("Введите адрес: ");
                a = Console.ReadLine();
                users.Add(new User(s, n, p, t, a));
            }
            public void Search_S(string s)
            {
                if (users.Where((a) => s == a.Surname) != null)
                    foreach (User a in users.Where((a) => s == a.Surname))
                        Console.WriteLine(a.ToString());
                else
                    Console.WriteLine("Нет таких сотрудников");
            }
            public void Search_N(string n)
            {
                if (users.Where((a) => n == a.Name) != null)
                    foreach (User a in users.Where((a) => n == a.Name))
                        Console.WriteLine(a.ToString());
                else
                    Console.WriteLine("Нет таких сотрудников");
            }
            public void Search_P(string p)
            {
                if (users.Where((a) => p == a.Patronymic) != null)
                    foreach (User a in users.Where((a) => p == a.Patronymic))
                        Console.WriteLine(a.ToString());
                else
                    Console.WriteLine("Нет таких сотрудников");
            }
            public void Search_T(string t)
            {
                if (users.Where((a) => t == a.Telephone) != null)
                    foreach (User a in users.Where((a) => t == a.Telephone))
                        Console.WriteLine(a.ToString());
                else
                    Console.WriteLine("Нет таких сотрудников");
            }
            public void Search_A(string a)
            {
                if (users.Where((b) => a == b.Address) != null)
                    foreach (User b in users.Where((b) => a == b.Address))
                        Console.WriteLine(b.ToString());
                else
                    Console.WriteLine("Нет таких сотрудников");
            }
            public void Save()
            {
                IFormatter formatter = new BinaryFormatter();
                using (var stream = new FileStream("Data", FileMode.Create, FileAccess.Write, FileShare.None))
                {
                    formatter.Serialize(stream, this);
                }
            }
        }
    }
}
