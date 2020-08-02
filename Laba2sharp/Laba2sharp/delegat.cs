using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;

namespace Laba2sharp
{
    enum Update { Add, Replace, Property }
    enum Frequency { Weekly, Monthly, Yearly }

    delegate KeyValuePair<TKey, TValue> 
        GenerateElement<TKey, TValue>(int j);

    delegate void MagazinesChangedHandler<TKey>
           (object source, MagazinesChangedEventArgs<TKey> args);

    //delegate void PropertyChangedEventHandler
    //(Object sender, PropertyChangedEventArgs e);
}
