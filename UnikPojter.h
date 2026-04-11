#ifndef UNIKPOJTER_H
#define UNIKPOJTER_H

template<typename T>
class UnikPojter;

template<typename G, typename ...R>
UnikPojter<G> zrobUnik(R... r)
{
return std::move(UnikPojter<G>(new G(r...)));
}

template<typename T>
class UnikPojter 
{

template<typename G, typename ...R>
friend UnikPojter<G> zrobUnik(R... r);

private:
    T *ptr;

public:
    UnikPojter(T *a): ptr(a){}
    //UnikPojter(R... r): ptr(new T(r...)){}
    UnikPojter(): ptr(nullptr){}
    ~UnikPojter()
    {
        delete ptr;
        //ptr=nullptr;
    }

    UnikPojter(UnikPojter&& other): ptr(other.ptr)
    {
        other.ptr=nullptr;
    }
    UnikPojter& operator=(UnikPojter&& other)
    {
        ptr=other.ptr;
        other.ptr=nullptr;
        return *this;
    }
    
    UnikPojter& operator=(UnikPojter& other)=delete;
    UnikPojter(UnikPojter& other)=delete;

    T& operator*()
    {
        return *ptr;
    }
};



#endif
