using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Number9._2
{
    class Program
    {
        static void Main(string[] args)
        {
            FileSystemWatcher watcher = new FileSystemWatcher();
            watcher.Path = args[0];
            watcher.NotifyFilter = NotifyFilters.LastAccess | NotifyFilters.LastWrite | NotifyFilters.FileName | NotifyFilters.DirectoryName;
            watcher.Filter = "*.cs";
            StreamWriter write = new StreamWriter(args[1]);
            watcher.Changed += new FileSystemEventHandler(OnChanged);
            watcher.Created += new FileSystemEventHandler(OnChanged);
            watcher.Deleted += new FileSystemEventHandler(OnChanged);
            void OnChanged(object sender, FileSystemEventArgs e)
            {
                Console.WriteLine(DateTime.Now.ToString("HH:mm:ss") + "  " + e.FullPath + "  " + e.ChangeType);
                write.WriteLine(DateTime.Now.ToString("HH:mm:ss") + "  " + e.FullPath + "  " + e.ChangeType);
                write.Flush();
            }
            Console.ReadKey();
        }
    }
}