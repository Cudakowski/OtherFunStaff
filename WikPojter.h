#ifndef WIKPOJTER_H
#define WIKPOJTER_H

#include <iostream>
#include "SzerdPojter.h"

template<typename T>
class WikPojter 
{
private:
    T *ptr;
    int *szerdCount;
    int *wikCount;
public:
    WikPojter(): ptr(nullptr), szerdCount(nullptr), wikCount(nullptr) {}
    ~WikPojter()
    {
        reset();
    }

    WikPojter(WikPojter&& other): ptr(other.ptr), szerdCount(other.szerdCount), wikCount(other.wikCount)
    {
        other.ptr=nullptr;
        other.szerdCount=nullptr;
        other.wikCount=nullptr;
    }
    WikPojter& operator=(WikPojter&& other)
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
    
    WikPojter(WikPojter& other): ptr(other.ptr), szerdCount(other.szerdCount), wikCount(other.wikCount)
    {
        (*wikCount)++;
    }
    WikPojter& operator=(WikPojter& other)
    {
        if(this == &other)
            return *this;
        
        reset();

        ptr=other.ptr;
        szerdCount=other.szerdCount;
        wikCount=other.wikCount;
        (*wikCount)++;
        return *this;
    }

    WikPojter(SzerdPojter<T>& other): ptr(other.ptr), szerdCount(other.szerdCount), wikCount(other.wikCount)
    {
        (*wikCount)++;
    }
    WikPojter& operator=(SzerdPojter<T>& other)
    {
        reset();

        ptr=other.ptr;
        szerdCount=other.szerdCount;
        wikCount=other.wikCount;
        (*wikCount)++;
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
        if(szerdCount&&wikCount)
        {
            (*wikCount)--;
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


