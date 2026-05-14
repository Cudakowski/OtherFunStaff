#ifndef MAGICCONTAINER_H
#define MAGICCONTAINER_H
// https://www.youtube.com/watch?v=L4xOCvELWlU


template<typename T>
class MagicContainer{
private:
    std::vector<size_t> indexes;
    size_t numOfIndexes;
    std::vector<T> values;
public:
    MagicContainer(): numOfIndexes{} {}
    void push(T x)
    {
        if(numOfIndexes<indexes.size())
        {
            values[indexes[numOfIndexes]]=x;
            numOfIndexes++;
        }
        else
        {
            values.push_back(x);
            indexes.push_back(numOfIndexes);
            numOfIndexes++;
        }
    }

    void erase(size_t i)
    {
        numOfIndexes--;
        std::swap(indexes[i],indexes[numOfIndexes]);
    }

    T& operator[](size_t index)
    {
        return values[indexes[index]];
    }

    T& operator[](size_t index) const
    {
        return values[indexes[index]];
    }

    size_t size(){return numOfIndexes;}
};

#endif
