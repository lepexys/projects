using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

namespace lab5
{
    [Serializable]
    class TimesList
    {
        
        private List<TimeItem> times_list;

        public TimesList(string name)
        {
            name += ".dat";
            if(File.Exists(name))
            {
                Console.WriteLine("\n\t\tЗагрузка существующего файла:");
                LoadFromBinaryFile(name);
            }
            else
            {
                times_list = new List<TimeItem>();
                Console.WriteLine("\n\t\tСоздание нового файла\n");
            }
        }

        public void Add(TimeItem ti)
        {
            times_list.Add(ti);
        }

        public void SaveFromBinaryFile(string name)
        {
            try {
                name += ".dat";
                BinaryFormatter saver = new BinaryFormatter();
                FileStream fs = new FileStream(name, FileMode.Create);
                saver.Serialize(fs, times_list);
                fs.Close();
            }
            catch
            {
                Console.WriteLine("\\n\n\t\t!!! Ошибка сохранения !!!\n");
            }
        }
        public void LoadFromBinaryFile(string name)
        {
            try
            {
                BinaryFormatter saver = new BinaryFormatter();
                FileStream fs = new FileStream(name, FileMode.Open);
                times_list = (List<TimeItem>)saver.Deserialize(fs);
                fs.Close();
              
                Console.WriteLine(ToString());

            }
            catch
            {
                Console.WriteLine("\\n\n\t\t!!! Ошибка загрузки !!!\n");
            }
        }

        public override string ToString()
        {
            string str = "\n";

            foreach (TimeItem tl in times_list)
            {
               
                str += tl.ToString();
            }
            return str;
        }
    }
}
