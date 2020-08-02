using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp6
{
    class Server_Example
    {
        int port;
        IPAddress iPAddress;
        TcpListener server;
        public Server_Example()
        {
            port = 12345;
            iPAddress = IPAddress.Parse("127.0.0.1");
            server = new TcpListener(iPAddress, port);
        }
        public Server_Example(int port_value, String ip_value)
        {
            port = port_value;
            iPAddress = IPAddress.Parse(ip_value);
            server = new TcpListener(iPAddress, port);
        }
        public void start_server()
        {
            server.Start();
            Console.WriteLine("Сервер запущен, ожидание подключений");
            TcpClient client = server.AcceptTcpClient();
            Console.WriteLine("Клиент подключен");
            NetworkStream stream_server_client = client.GetStream(); //сетевой поток для общения сервера и клиента
            string server_answer = "Бла-бла-бла";
            byte[] data = Encoding.UTF8.GetBytes(server_answer);
            stream_server_client.Write(data, 0, data.Length);
            Console.WriteLine("Отправлен ответ");
            stream_server_client.Close();
            client.Close();
        }
        public void stop_server()
        {
            server.Stop();
        }
    }
}
