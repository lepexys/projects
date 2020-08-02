using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;


namespace Client
{
    class Client
    {
        static void Main(string[] args)
        {
            Client client = new Client(777, "folder");
            client.start_client();
        }
        TcpClient client = new TcpClient();
        int port;
        string dirr;
        Client(int p, string d)
        {
            port = p;
            dirr = d;
        }
        public void HandleCustomRequest(object sourse, string request)
        {
            StringBuilder answer_from_client = new StringBuilder();

            Console.WriteLine("Сам узнал: {0}", answer_from_client.ToString());
        }
        public void start_client()
        {
            client.Connect(IPAddress.Parse("127.0.0.1"), 777);
            NetworkStream stream_server_client = client.GetStream();
            byte[] server_data = new byte[500];
            StringBuilder answer_from_server = new StringBuilder();
            do
            {
                int bytes_count = stream_server_client.Read(server_data, 0, server_data.Length);
                answer_from_server.Append(Encoding.UTF8.GetString(server_data, 0, bytes_count));

            } while (stream_server_client.DataAvailable);
            Console.WriteLine("Ответ от сервера: {0}", answer_from_server.ToString());
            stream_server_client.Close();
        }
        public void stop_client()
        {
            client.Close();
        }
    }
}
