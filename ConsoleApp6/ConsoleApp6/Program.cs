using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp6
{
    class Program
    {
        static void Main(string[] args)
        {
            Server_Example server1 = new Server_Example();
            server1.start_server();
            server1.stop_server();            
        }
    }
}
