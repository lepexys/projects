using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DAL
{
    public class Person
    {
        public int Id { get; set; }
        public string Name { get; set; }
        public int Adge { get; set; }
        public int PassportSeries { get; set; }
        public int PassportNo { get; set; }

        public override string ToString()
        {
            return string.Format("Id = {0}, Name = {1}, Adge = {2}, Passport = {3} {4:D6}", 
                Id, 
                Name, 
                Adge, 
                PassportSeries,
                PassportNo);
        }
    }
}
