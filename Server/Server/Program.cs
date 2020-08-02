using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Server
{
    class Server
    {
        static void Main(string[] args)
        {
            string pot;
            Console.Write("Введите порт: ");
            pot = Console.ReadLine();
            Client ccnc = new Client();
            Server serv = new Server(int.Parse(pot), "folder");
            Console.Write("Подписаться? (1-<да> , 0-<нет>): ");
            if (int.Parse(Console.ReadKey().KeyChar.ToString()) == 1)
                serv.RiseCustomRequest += ccnc.HandleCustomRequest;
            Console.WriteLine();
            serv.Start();
        }
        public Server(int p, string d)
        {
            port = p;
            dirr = d;
            listener = new TcpListener(IPAddress.Any, port);
        }
        private void SendError(TcpClient Client, int Code)
        {
            string CodeStr = Code.ToString() + " " + ((HttpStatusCode)Code).ToString();
            string Html = "<html><body><h1>" + CodeStr + "</h1></body></html>";
            string Str = "HTTP/1.1 " + CodeStr + "\nContent-type: text/html\nContent-Length:" + Html.Length.ToString() + "\n\n" + Html;
            byte[] Buffer = Encoding.ASCII.GetBytes(Str);
            Client.GetStream().Write(Buffer, 0, Buffer.Length);
            Client.Close();
        }
        static int port;
        public string dirr;
        TcpListener listener;
        public TcpClient client;
        public delegate void EventHandler(object sourse, string reqest);
        public event EventHandler RiseCustomRequest;
        public void Start()
        {
            listener.Start();
            while (true)
            {
                Console.WriteLine("Жду отмашки");
                client = listener.AcceptTcpClient();
                Console.WriteLine("Дождался");
                if (RiseCustomRequest != null)
                {
                    var clientmessage = new StreamReader(client.GetStream());
                    RiseCustomRequest(this, clientmessage.ReadLine());
                    client.Close();
                    continue;
                }
                else
                {
                    Console.WriteLine("Accepted from {0}", client.Client.RemoteEndPoint);
                    FtpWebRequest FTPR = (FtpWebRequest)WebRequest.Create(new UriBuilder("ftp", "localhost", port).Uri);
                    FTPR.Method = WebRequestMethods.Ftp.DownloadFile;
                    var RIP = FTPR.GetRequestStream();
                    var stream = client.GetStream();
                    var jopa = new StreamReader(stream);
                    var line = jopa.ReadLine();
                    string file = dirr + line.Split(' ')[1];
                    var streamReader = new StreamReader(RIP);
                    byte[] buffer = new byte[1024];
                    using (var response = FTPR.GetResponse()) {
                        using (var ReStream = response.GetResponseStream()) {
                            using (var fs = new FileStream(file, FileMode.OpenOrCreate)) {
                                var findfile = new FileInfo(file);
                                int readCount = ReStream.Read(buffer, 0, 1024);
                                while (readCount > 0)
                                {
                                    Console.Write("#");
                                    fs.Write(buffer, 0, readCount);
                                    readCount = ReStream.Read(buffer, 0, 1024);
                                }
                            }
                        }
                    }
                    /*
                    var version = line.Split(' ')[2];
                    while (true)
                    {
                        line = streamReader.ReadLine();
                        if (string.IsNullOrEmpty(line))
                            break;
                    }
                    string response = version + " ";
                    string c_type = null;
                    long c_weight = 0;
                    HttpStatusCode err;
                    if (findfile.Exists)
                    {
                        err = HttpStatusCode.OK;
                        switch (findfile.Extension)
                        {
                            case ".html":
                            case ".htm":
                                { c_type = "text/html"; break; }
                            case ".css":
                                { c_type = "text/css"; break; }
                            case ".js":
                                { c_type = "text/javascript"; break; }
                            case ".jpg":
                            case ".jpeg":
                                { c_type = "image/jpeg"; break; }
                            case ".png":
                                { c_type = "image/png"; break; }
                            case ".gif":
                                { c_type = "image/gif"; break; }
                            default:
                                { c_type = "application/unknown"; break; }
                        }
                        c_weight = findfile.Length;
                        response += (int)err + " " + err.ToString() + "\n";
                        response += "Content-Type: " + c_type + "\n";
                        response += "Content-Length: " + c_weight + "\n\n";
                        byte[] HeadersBuff = Encoding.ASCII.GetBytes(response);
                        client.GetStream().Write(HeadersBuff, 0, HeadersBuff.Length);
                        response = null;
                        FileStream reqested_f = null;
                        try
                        {
                            reqested_f = new FileStream(file, FileMode.Open);
                        }
                        catch
                        {
                            SendError(client, 500);
                            continue;
                        }
                        byte[] res_bytes = new byte[1024];
                        int Count = 0;
                        while ((Count = reqested_f.Read(res_bytes, 0, res_bytes.Length)) != 0)
                        {
                            client.GetStream().Write(res_bytes, 0, Count);
                        }
                    }
                    else
                    {
                        SendError(client, 404);
                        continue;
                    }
                    client.Close();
                    */
                }
            }
        }
        class Client
        {
            public Client() {; }
            public void HandleCustomRequest(object sourse, string request)
            {
                try
                {
                    Server serv = sourse as Server;
                    StringBuilder answer_from_client = new StringBuilder();
                    Console.WriteLine(request.ToString());
                    if (request.Split(' ')[0] != "GET")
                    {
                        return;
                    }
                    string file = serv.dirr + request.Split(' ')[1];
                    var findfile = new FileInfo(file);
                    var version = request.Split(' ')[2];
                    string response = version + " ";
                    string c_type = null;
                    long c_weight = 0;
                    HttpStatusCode err;
                    if (findfile.Exists)
                    {
                        err = HttpStatusCode.OK;
                        switch (findfile.Extension)
                        {
                            case ".html":
                            case ".htm":
                                {
                                    c_type = "text/html"; break;
                                }
                            case ".css":
                                {
                                    c_type = "text/css"; break;
                                }
                            case ".js":
                                {
                                    c_type = "text/javascript"; break;
                                }
                            case ".jpg":
                            case ".jpeg":
                                {
                                    c_type = "image/jpeg"; break;
                                }
                            case ".png":
                                {
                                    c_type = "image/png"; break;
                                }
                            case ".gif":
                                {
                                    c_type = "image/gif"; break;
                                }
                            default:
                                {
                                    c_type = "application/unknown"; break;
                                }
                        }
                        c_weight = findfile.Length;
                        response += (int)err + " " + err.ToString() + "\n";
                        response += "Content-Type: " + c_type + "\n";
                        response += "Content-Length: " + c_weight + "\n\n";
                        answer_from_client.Append(response);
                        byte[] HeadersBuff = Encoding.ASCII.GetBytes(response);
                        serv.client.GetStream().Write(HeadersBuff, 0, HeadersBuff.Length);
                        response = null;
                        FileStream reqested_f = null;
                        try
                        {
                            reqested_f = new FileStream(file, FileMode.Open);
                        }
                        catch
                        {
                            serv.SendError(serv.client, 500);
                            return;
                        }
                        byte[] res_bytes = new byte[1024];
                        int Count = 0;
                        while ((Count = reqested_f.Read(res_bytes, 0, res_bytes.Length)) != 0)
                        {
                            serv.client.GetStream().Write(res_bytes, 0, Count);
                        }
                    }
                    else
                    {
                        serv.SendError(serv.client, 404);
                        return;
                    }
                    Console.WriteLine("Сам узнал: {0}", answer_from_client.ToString());
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }
    }
}