#ifndef BOARD_H
#define BOARD_H

#include "Point2D.h"
#include "MagicContainer.h"
#include "random.h"

class Board{
private:
    std::vector<std::vector<int>> b;
    int bombCount; 
    Point2D dim;
    int uncoveredCount;
public:
    Board(int bombCountP, int rows, int cols): bombCount{bombCountP}, dim{rows,cols}, uncoveredCount{}
    {
        if(bombCount > dim.row*dim.col )
        {
            throw std::runtime_error("more bombs than board spaces");
        }

    b = std::vector<std::vector<int>>(dim.row,std::vector<int>(dim.col,0));

    MagicContainer<int*> emptySpaces;
    for( auto && v: b)
        for (auto &&i:v)
            emptySpaces.push(&i);
    
    for (size_t i = 0; i < bombCount; i++)
    {
        size_t rand = Random::get(0,emptySpaces.size()-1);
        *(emptySpaces[rand])=9;
        emptySpaces.erase(rand);
    }
    
    for(int row{};row<dim.row;row++)
        for (int col{};col<dim.col;col++)
            if(b[row][col]!=9)
            {
                int count{};
                
                for(int rowT{row-1};rowT<=row+1;rowT++)
                    for (int colT{col-1};colT<=col+1;colT++)
                        if( rowT<dim.row && 
                            rowT>=0   &&
                            colT<dim.col &&
                            colT>=0   &&
                            (rowT != row || colT != col) &&
                            b[rowT][colT]==9)
                                count++;
                
                b[row][col]=count;
            }
    
    for(size_t row{};row<dim.row;row++)
        for (size_t col{};col<dim.col;col++)
            b[row][col]+=10;
    }

    std::vector<int> &operator[](size_t index){ return b[index];}
    //std::vector<int> operator[](size_t index)const{ return b[index];}

    int &operator[](Point2D index){ return b[index.row][index.col];}
    //int operator[](Point index)const{ return b[index.row][index.col];}

    int getRows()const{return dim.row;}
    int getCols()const{return dim.col;}
    Point2D getDimensions()const{return dim;}
    int getBombCount()const{return bombCount;}

    void addUncovered(int add){ uncoveredCount+=add;}
    bool czyWygrana()const 
    {
        return uncoveredCount+bombCount==dim.row*dim.col;
    }
};

#endif
