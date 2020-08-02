using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp7
{
    class Program
    {
        static void Main(string[] args)
        {
            Client_example client1 = new Client_example();
            client1.start_client();
            client1.stop_client();
        }
    }
}
