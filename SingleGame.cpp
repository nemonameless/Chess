#include "SingleGame.h"
#include <QTimer>
#include <QDebug>
SingleGame::SingleGame(QWidget *parent) : Board(parent)
{
    _level = 4;
}

SingleGame::~SingleGame()
{

}

void SingleGame::back()
{
    if(_bRedTurn)
    {
        backOne();
        backOne();
    }
}

void SingleGame::click(int id, int row, int col)
{
    //不是红走，就什么也不干

    if(_bRedTurn)
    {
        Board::click(id, row, col);//红走，重载Bored的click函数，只要直接调用
        if(!_bRedTurn)//红走了，轮到黑走，就调用computerMove
        {
            /* 启动0.1秒定时器，在0.1秒后电脑再思考
             * 否则clicked函数中轮到黑走时，先去计算下一步再下一步才相应主进程去重绘
             */
            QTimer::singleShot(100, this, SLOT(computerMove()));
        }
    }
}

void SingleGame::computerMove()
{
    Step* step = getBestMove();
    moveStone(step->_moveid, step->_killid, step->_rowTo, step->_colTo);
    delete step;
    update();
}

Step* SingleGame::getBestMove()
{
    /*
            2.试着走一下
            3.评估走的结果
            4.取最好的结果作为参考
     */

        //  1.看看有那些步骤可以走
    Step* ret = NULL;
    QVector<Step*> steps;
    getAllPossibleMove(steps);
    // 2.试着走一下
    // 3.评估走的结果
    int maxInAllMinScore = -300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        fakeMove(step);
        int minScore = getMinScore(this->_level-1, maxInAllMinScore);
        unfakeMove(step);

        if(minScore > maxInAllMinScore)
        {
            if(ret)
                delete ret;

            ret = step; //是的话就保存
            maxInAllMinScore = minScore;
        }
        else
        {
            delete step;
        }
    }
    return ret;     // 4.取最好的结果作为参考
}

int SingleGame::score()     //评价局面分，黑棋分的总数 - 红旗分的总数
{
  //  enum TYPE{CHE, MA, PAO, BING, JIANG, SHI, XIANG};
    static int s[] = {1000, 499, 501, 200, 15000, 100, 100};
    int scoreBlack = 0;
    int scoreRed = 0;
    for(int i=0; i<16; ++i)
    {
        if(_s[i]._dead) continue;
        scoreRed += s[_s[i]._type];     //_s[i]._type是下标
    }
    for(int i=16; i<32; ++i)
    {
        if(_s[i]._dead) continue;
        scoreBlack += s[_s[i]._type];
    }
    return scoreBlack - scoreRed;   // 黑棋分的总数 - 红旗分的总数
}

int SingleGame::getMinScore(int level, int curMin)
{
    if(level == 0)
        return score();

    QVector<Step*> steps;   // 1.看看有那些步骤可以走
    getAllPossibleMove(steps);// 是红棋的possiblemove
    int minInAllMaxScore = 300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast(); //释放当前内存

        fakeMove(step);
        int maxScore = getMaxScore(level-1, minInAllMaxScore);
        unfakeMove(step);
        delete step;

        if(maxScore <= curMin)
        {
            while(steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return maxScore;
        }

        if(maxScore < minInAllMaxScore)
        {
            minInAllMaxScore = maxScore;
        }


    }
    return minInAllMaxScore;
}
int SingleGame::getMaxScore(int level, int curMax)
{
    if(level == 0)
        return score();

    QVector<Step*> steps;
    getAllPossibleMove(steps);
    int maxInAllMinScore = -300000;

    while(steps.count())
    {
        Step* step = steps.last();
        steps.removeLast();

        fakeMove(step);
        int minScore = getMinScore(level-1, maxInAllMinScore);
        unfakeMove(step);
        delete step;

        if(minScore >= curMax)
        {
            while(steps.count())
            {
                Step* step = steps.last();
                steps.removeLast();
                delete step;
            }
            return minScore;
        }
        if(minScore > maxInAllMinScore)
        {
            maxInAllMinScore = minScore;
        }


    }
    return maxInAllMinScore;
}


void SingleGame::fakeMove(Step *step)
{
    killStone(step->_killid);
    moveStone(step->_moveid, step->_rowTo, step->_colTo);
}

void SingleGame::unfakeMove(Step *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_rowFrom, step->_colFrom);
}

void SingleGame::getAllPossibleMove(QVector<Step *> &steps)
{
    int min, max;
    if(this->_bRedTurn)         //红棋去走下一步，这是假想的
    {
        min = 0, max = 16;
    }
    else
    {
        min = 16, max = 32;
    }

    for(int i=min;i<max; i++)   //死棋不应该再计算getAllPossibleMove
    {
        if(this->_s[i]._dead) continue;
        for(int row = 0; row<=9; ++row)
        {
            for(int col=0; col<=8; ++col)
            {
                int killid = this->getStoneId(row, col);
                if(sameColor(i, killid)) continue;

                if(canMove(i, killid, row, col))
                {
                    saveStep(i, killid, row, col, steps);
                }
            }
        }
    }
}
