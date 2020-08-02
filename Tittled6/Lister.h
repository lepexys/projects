#ifndef LISTER_H
#define LISTER_H

struct Lister
{
    int num;
    Lister* next,*prev;
    Lister* Delete();
    Lister(int,Lister*,Lister*);
};

#endif // LISTER_H
