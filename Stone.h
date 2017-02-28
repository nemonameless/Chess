#ifndef STONE_H
#define STONE_H

#include <QRect>
#include <QPainter>

class Stone
{
public:
    Stone();
    ~Stone();

    enum TYPE{CHE, MA, PAO, BING, JIANG, SHI, XIANG};

    void init(int id);

    int _row;
    int _col;
    TYPE _type;//是哪个棋子
    bool _dead;//
    bool _red;
    int _id;

    QString name();//返回棋子中文名字，用于绘制

    void rotate();//网络对战时旋转棋盘
};

#endif // STONE_H
