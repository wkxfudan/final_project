#ifndef     ONEBLOCK
#define     ONEBLOCK

class OneBlock
{
private:
    int BlockState;         //一个block的State，指里面的数字，也可以自行修改成枚举类型，总之看自己喜好来
    
public:
    OneBlock();
    ~OneBlock();
    int getBlockState() const; //
    void setBlockState(const int& blockstate);
};

OneBlock::OneBlock()
{
}

OneBlock::~OneBlock()
{
}



#endif