using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections;

namespace Laba2sharp
{
    //class MagazineEnumerator : IEnumerator
    //{
    //    public MagazineEnumerator(ArrayList ListPerson, ArrayList ListArticle)
    //    {
    //        this.ListPerson = ListPerson;
    //        this.ListArticle = ListArticle;
    //    }

    //    private ArrayList ListPerson;
    //    private ArrayList ListArticle;
    //    int index = 0;
    //    int indexInPerson = -1;
    //    public object Current
    //    {
    //        get
    //        {
    //            return ListPerson[indexInPerson];
    //        }
    //    }

    //    public bool MoveNext()
    //    {
    //        for (int i = indexInPerson + 1; i < ListPerson.Count; i++)
    //        {
    //            foreach (var test in ListArticle)
    //            {
    //                if (((Article)test).Author.Name != ((Person)ListPerson[i]).Name)
    //                {
    //                    //index++;
    //                    indexInPerson = i;
    //                    return true;
    //                }

    //            }
    //        }
    //        return false;
    //    }

    //    public void Reset()
    //    {
    //        if (ListPerson.Count > 0) { index = 0; indexInPerson = 0; }
    //        else { index = -1; indexInPerson = -1; }

    //    }
    //}
    class MagazineEnumerator : IEnumerator
    {

        int position = -1;

        public MagazineEnumerator(ArrayList arts, ArrayList eds)
        {
            this.arts = arts;
            this.eds = eds;
        }
        public ArrayList arts;
        public ArrayList eds;

        public object Current
        {
            get
            {
                try
                {
                    return arts[position];
                }
                catch (IndexOutOfRangeException)
                {
                    throw new InvalidOperationException();
                }
            }
        }

        object IEnumerator.Current
        {
            get
            {
                return Current;
            }
        }

        public void Dispose()
        {

        }

        public bool MoveNext()
        {
            position++;
            if (position >= arts.Count) return (position < arts.Count);
            while (eds.Contains(arts[position]))
            {
                position++;
                if (position >= arts.Count) break;
            }
            return (position < arts.Count);
        }

        public void Reset()
        {
            position = -1;
        }
    }
}
