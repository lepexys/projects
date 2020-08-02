using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ClassLibrary1
{
    public class Knopka : Button
    {
        public double Radius { set; get; }
        public delegate void Delegate(MouseEventArgs mea);
        public event Delegate Centered;
        protected override void OnMouseMove(MouseEventArgs mea)
        {
            if (Math.Sqrt((mea.X - Location.X - Width / 2)^2 + (mea.Y - Location.Y - Height / 2) ^2) < Radius) 
            {
                Centered(mea);
            }
        }
    }
}
