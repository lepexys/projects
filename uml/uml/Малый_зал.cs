using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace uml
{
    public class Малый_зал : Театр
    {
        private int Количество_мест;

        public Афиша Афиша
        {
            get => default(Афиша);
            set
            {
            }
        }
    }
}