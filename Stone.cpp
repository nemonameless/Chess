#include "Stone.h"
#include <QDebug>

Stone::Stone()
{

}

Stone::~Stone()
{

}

QString Stone::name()//根据棋子的类型返回中文名字
{
    switch(this->_type)
    {
    case CHE:
        return "车";
    case MA:
        return "马";
    case PAO:
        return "炮";
    case BING:
        return "兵";
    case JIANG:
        return "将";
    case SHI:
        return "士";
    case XIANG:
        return "相";
    }
    return "错误";
}

void Stone::init(int id)//初始化棋子，画出棋子来
{
    struct {
        int row, col;
        Stone::TYPE type;
    } pos[16] = {
    {0, 0, Stone::CHE},//坐标点（0,0）定义车
    {0, 1, Stone::MA},
    {0, 2, Stone::XIANG},
    {0, 3, Stone::SHI},
    {0, 4, Stone::JIANG},
    {0, 5, Stone::SHI},
    {0, 6, Stone::XIANG},
    {0, 7, Stone::MA},
    {0, 8, Stone::CHE},

    {2, 1, Stone::PAO},
    {2, 7, Stone::PAO},
    {3, 0, Stone::BING},
    {3, 2, Stone::BING},
    {3, 4, Stone::BING},
    {3, 6, Stone::BING},
    {3, 8, Stone::BING},
    };

    if(id < 16)
    {
        this->_col = pos[id].col;
        this->_row = pos[id].row;
        this->_type = pos[id].type;
    }
    else
    {
        this->_col = 8-pos[id-16].col;
        this->_row = 9-pos[id-16].row;
        this->_type = pos[id-16].type;
    }

    this->_dead = false;
    this->_red = id<16;
}

void Stone::rotate()
{
    this->_col = 8-this->_col;//左上角和右下角才是对称，坐标对称特征：col列相加为8
    this->_row = 9-this->_row;//row行相加为9
}
