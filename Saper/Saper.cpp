#include "random.h"
#include <iostream>
#include <memory>
#include <vector>
#include <exception>
#include <list>
#include <string>

template<typename T>
class myContainer{
private:
    std::vector<size_t> indexes;
    size_t numOfIndexes;
    std::vector<T> values;
public:
    myContainer(): numOfIndexes{} {}
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

struct Point{
    int row;
    int col;
};

class Board{
private:
    std::vector<std::vector<int>> b;
    int bombCount; 
    Point dim;
    int uncoveredCount;
public:
    Board(int bombCountP, int rows, int cols): bombCount{bombCountP}, dim{rows,cols}, uncoveredCount{}
    {
        if(bombCount > dim.row*dim.col )
        {
            throw std::runtime_error("more bombs than board spaces");
        }

    b = std::vector<std::vector<int>>(dim.row,std::vector<int>(dim.col,0));

    myContainer<int*> emptySpaces;
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

    int &operator[](Point index){ return b[index.row][index.col];}
    //int operator[](Point index)const{ return b[index.row][index.col];}

    int getRows()const{return dim.row;}
    int getCols()const{return dim.col;}
    Point getDimensions()const{return dim;}
    int getBombCount()const{return bombCount;}

    void addUncovered(int add){ uncoveredCount+=add;}
    bool czyWygrana()const 
    {
        return uncoveredCount+bombCount==dim.row*dim.col;
    }
};




void printBoard(Board &b)
{
    std::cout<<'\t';
    for (size_t col{};col<b.getCols();col++)
        std::cout<<col;
    std::cout<<'\n';
    for(size_t row{};row<b.getRows();row++)
    {
        std::cout<<static_cast<char>('A'+row)<<"\t";
        for (size_t col{};col<b.getCols();col++)
        {
            if(b[row][col]>9)
                std::cout<<"@";
            else
            {
                switch (b[row][col])
                {
                case 0:
                    std::cout<<" ";
                    break;
                case 9:
                    std::cout<<"*";
                    break;
                default:
                    std::cout<<b[row][col];
                    break;
                }
            }
        }
        std::cout<< '\n';
    }
            
}



Point getInput()
{
    std::string a,b;
    Point m;
    m.col=-1;
    m.row=-1;

    while(1)
    {
        std::cout<<"Podaj koordynaty kafeli w formacie: 'A 1'\n";
        std::cin >> a>>b;
        m.row=a[0]-'A';
        m.col=std::stoi(b);
        std::cout<<"Test: "<<a<<" ___ "<<b<<'\n';
        if(m.row>=0&&m.col>=0)
            return m;
        std::cout<<"Zle dane\n";
    }
    
}

void uncoverTile(Board &b,int row, int col)
{
    if(b[row][col]>=10)
    {
        b[row][col]-=10;
        
    }
    
}

void uncoverBoard(Board &b)
{
    for(size_t row{};row<b.getRows();row++)
        for (size_t col{};col<b.getCols();col++)
            uncoverTile(b,row,col);
}

int updateTile(Board &b,int row, int col)
{
    if(b[row][col]<9)
        return 0;
    else if(b[row][col]==10)
    {
        int sum=1;
        b[row][col]=0;
        for(int rowT{row-1};rowT<=row+1;rowT++)
            for (int colT{col-1};colT<=col+1;colT++)
                if (colT>=0         &&
                    colT<b.getCols()&&
                    rowT>=0         &&
                    rowT<b.getRows()&&
                    (rowT != row || colT != col)
                   )
                {
                   sum+= updateTile(b,rowT,colT);    
                }
        
        return sum;
    }
    else
    {
        b[row][col]-=10;
        return 1;
    }
    
}

bool updateBoard(Board &b,Point &m)
{
    if(b[m]==19)
        return true;
    
    b.addUncovered(updateTile(b,m.row,m.col));
    return false;
}

int main(int argc, char const *argv[])
{
    const int ALL_BOMB_COUNT{5};
    const int ROWS{5};
    const int COLS{6};

    Board board(ALL_BOMB_COUNT, ROWS,COLS);
    Point coordinates;
    bool isGameOver=false;

    while(!isGameOver)
    {
        printBoard(board);
        coordinates = getInput();
        isGameOver = updateBoard(board,coordinates);
        if(board.czyWygrana())
        {
            std::cout<<"Wygrana!\n";
            break;
        }
        
    }
    uncoverBoard(board);
    printBoard(board);
    std::cout<<"Koniec gry!\n";

    return 0;
}
