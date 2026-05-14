#include <Board.h>
#include <iostream>
#include <memory>
#include <vector>
#include <exception>
#include <list>
#include <string>



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



Point2D getInput()
{
    std::string a,b;
    Point2D m;
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

bool updateBoard(Board &b,Point2D &m)
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
    Point2D coordinates;
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
