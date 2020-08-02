using System.Configuration;
namespace laba4dot
{
    class RepositoryFactory
    {
        public static IRepository GetRepository(string one, string two)
        {
            var connectionString = ConfigurationManager.AppSettings["key3"];
            if (connectionString.Split(new char[] {' '})[0] == "Data")
                return new SQLHandler();
            else return new PaymentRepository(one, two);
        }
    }
}
