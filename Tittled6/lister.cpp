#include "Lister.h"

Lister::Lister(int lil, Lister* n,Lister* p)
{
    num = lil;
    next = n;
    prev = p;
}

Lister* Lister::Delete()
{
    if(this->prev==nullptr && this->next==nullptr)
        return nullptr;
    if(this->prev!=nullptr)
    {
        Lister* cur = this->prev;
        cur->next = this->next;
        if(cur->next!=nullptr)
            cur->prev = cur;
        return cur;
    }
    else
    {
        if(this->next != nullptr)
        {
            Lister* cur = this->next;
            cur->prev = nullptr;
            return cur;
        }
    }
}
