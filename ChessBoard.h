#ifndef     CHESSBOARD
#define     CHESSBOARD
#include    "OneBlock.h"
#include    <vector>
#define     width 4

using std::vector;

class ChessBoard
{
private:
    vector<vector<OneBlock>> oneboard;  //改成其他容器也行吧，看自己喜好来
public:
    ChessBoard();
    ~ChessBoard();
    bool Combine(const char& input); //进行合并，如果合并有效返回True，合并无效则返回False
    OneBlock getOneBlock(const int& i, const int& j) const;//get坐标为(i,j)的block
    void setOneBlock(const int& i, const int& j);
    void reset();   //指棋盘重置
    bool checkwin() const; //检查是否有2048
    bool checkfail() const; //检查游戏是否失败
};

ChessBoard::ChessBoard()    //默认构造函数，可以修改
{
    vector<OneBlock> tmp;
    for (int i = 0; i < width; i++)
        tmp.push_back(OneBlock());
    for (int i = 0; i < width; i++)
        oneboard.push_back(tmp);
}

ChessBoard::~ChessBoard()
{
}

#endif