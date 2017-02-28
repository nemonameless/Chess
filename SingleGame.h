#ifndef SINGLEGAME_H
#define SINGLEGAME_H

#include "Board.h"

class SingleGame : public Board
{
    Q_OBJECT
public:
    explicit SingleGame(QWidget *parent = 0);

    ~SingleGame();

    int _level;

    void back();
    void click(int id, int row, int col);

    Step* getBestMove();
    void getAllPossibleMove(QVector<Step*>& steps);
    int getMinScore(int level, int curMin);
    int getMaxScore(int level, int curMax);
    int score();

    void fakeMove(Step* step);
    void unfakeMove(Step* step);

signals:

public slots:
    void computerMove();//添加槽函数开头要加Q_OBJECT，并且重新编译，且在workspace里删掉build chess....文件夹
};

#endif // SINGLEGAME_H
