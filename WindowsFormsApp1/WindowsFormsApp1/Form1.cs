using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        void Messagemake(MouseEventArgs mea)
        {
            knopka1.BackColor = Color.Aqua;
            MessageBox.Show("X:"+mea.X+" Y:"+mea.Y+" Radius:"+knopka1.Radius);
        }
    }
}
