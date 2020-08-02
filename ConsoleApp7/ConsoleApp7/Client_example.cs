using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp7
{
    class Client_example
    {
        int server_port;
        string server_ip;
        TcpClient client;
        public Client_example()
        {
            server_port = 12345;
            server_ip = "127.0.0.1";
            client = new TcpClient();
        }
        public Client_example(int port_value, String server_ip_value)
        {
            server_port = port_value;
            server_ip = server_ip_value;
            client = new TcpClient();
        }
        public void start_client()
        {
            client.Connect(server_ip, server_port);
            NetworkStream stream_server_client = client.GetStream();
            byte[] server_data = new byte[500];
            StringBuilder answer_from_server = new StringBuilder(); //хорошо
            //String afs="";//нехорошо
            do
            {
                int bytes_count = stream_server_client.Read(server_data, 0, server_data.Length);
                answer_from_server.Append(Encoding.UTF8.GetString(server_data, 0, bytes_count));//хорошо
                //afs += Encoding.UTF8.GetString(server_data, 0, bytes_count);//нехорошо

            } while (stream_server_client.DataAvailable);
            Console.WriteLine("Ответ от сервера: {0}", answer_from_server.ToString()); //хорошо
            //Console.WriteLine("Ответ от сервера: {0}", afs); //нехорошо
            stream_server_client.Close();
        }
        public void stop_client()
        {
            client.Close();
        }

    }
}
