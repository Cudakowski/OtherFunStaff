#ifndef SZERDPOJTER_H
#define SZERDPOJTER_H

#include <iostream>

template<typename T>
class SzerdPojter;

template<typename G, typename ...R>
SzerdPojter<G> zrobSzerd(R... r)
{
return std::move(SzerdPojter<G>(new G(r...), new int(1), new int(0)));
}

template<typename T>
class SzerdPojter 
{

template<typename G, typename ...R>
friend SzerdPojter<G> zrobSzerd(R... r);

template<typename D>
friend class WikPojter;

private:
    T *ptr;
    int *szerdCount;
    int *wikCount;
public:
    SzerdPojter(T *a, int* b, int* c): ptr(a), szerdCount(b), wikCount(c) {}
    SzerdPojter(): ptr(nullptr), szerdCount(nullptr), wikCount(nullptr) {}
    ~SzerdPojter()
    {
        reset();
    }

    SzerdPojter(SzerdPojter&& other): ptr(other.ptr), szerdCount(other.szerdCount), wikCount(other.wikCount)
    {
        other.ptr=nullptr;
        other.szerdCount=nullptr;
        other.wikCount=nullptr;
    }
    SzerdPojter& operator=(SzerdPojter&& other)
    {
        if(this == &other)
            return *this;
        reset();

        ptr=other.ptr;
        szerdCount=other.szerdCount;
        wikCount=other.wikCount;
        other.ptr=nullptr;
        other.szerdCount=nullptr;
        other.wikCount=nullptr;
        return *this;
    }
    
    SzerdPojter(SzerdPojter& other): ptr(other.ptr), szerdCount(other.szerdCount)
    {
        (*szerdCount)++;
    }
    SzerdPojter& operator=(SzerdPojter& other)
    {
        if(this == &other)
            return *this;
        
        reset();

        ptr=other.ptr;
        szerdCount=other.szerdCount;
        wikCount=other.wikCount;
        (*szerdCount)++;
        return *this;
    }

    T& operator*()
    {
        return *ptr;
    }

    int getCount()
    {
        return *szerdCount;
    }

    int getWikCount()
    {
        return *wikCount;
    }

    void reset()
    {
        if(szerdCount && wikCount)
        {
            (*szerdCount)--;
            if(*wikCount==0 && *szerdCount == 0)
            {
                delete szerdCount;
                delete wikCount;
                delete ptr;
                std::cout<<"Zdekonstruowao mnie!\n";
            }
            ptr=nullptr;
            szerdCount=nullptr;
            wikCount=nullptr;
        }

        
    }
};

#endif
