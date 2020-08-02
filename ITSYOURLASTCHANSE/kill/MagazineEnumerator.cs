using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace kill
{
    class MagazineEnumerator : IEnumerator<Article>
    {
        int position = 0;
        Magazine mag;

        public MagazineEnumerator(Magazine a)
        {
            mag = a;
        }

        public Article Current
        {
            get
            {
                return mag.Maga[position] as Article;
            }
        }

        object IEnumerator.Current
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public bool MoveNext()
        {
            do
            {
                position++;
            } while ((position < mag.Maga.Count) && (mag.Magp.LastIndexOf((mag.Maga[position] as Article).Man) == -1));
            return (position < mag.Maga.Count);
        }
        public void Reset()
        {
            position = 0;
        }

        public void Dispose()
        {
           
        }
    }
}
