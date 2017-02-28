#ifndef BOARD_H
#define BOARD_H

#include <QFrame>
#include "Stone.h"
#include "Step.h"
#include <QVector>

class Board : public QFrame
{
    Q_OBJECT
public:
    explicit Board(QWidget *parent = 0);
    ~Board();

    /* game data */
    Stone _s[32];//
    int _r;       //棋子半径
    QPoint _off;   //車与窗口角落的偏移
    bool _bSide;    //红方 黑方

    QVector<Step*> _steps;//记录每走一步棋，悔棋用

    /* game status */
    int _selectid;          //选中的棋子编号，0-31
    bool _bRedTurn;         //true表当前红方走
    void init(bool bRedSide);//摆棋子，bRedSide为true表红在下，网络对战时用

    /* draw functions */
    void paintEvent(QPaintEvent *);
    void drawPlate(QPainter& p);     //棋盘
    void drawPlace(QPainter& p);    //九宫
    void drawInitPosition(QPainter& p);//初始位置
    void drawInitPosition(QPainter& p, int row, int col);//炮和兵的初始位置处的折角
    void drawStone(QPainter& p);
    void drawStone(QPainter& p, int id);

    /* function for coordinate 坐标转换*/
    QPoint center(int row, int col);    //某行某列对应的棋子像素中心点
    QPoint center(int id);              //棋子的中心点
    QPoint topLeft(int row, int col);   //某行某列对应的棋子覆盖方框的左上角点
    QPoint topLeft(int id);
    QRect cell(int row, int col);       //某行某列对应的棋子覆盖方框范围
    QRect cell(int id);

    bool getClickRowCol(QPoint pt, int& row, int& col);//点击在那个棋子圆范围内都会当做选中该棋子，如吃对方棋时用

    /* help function */
    QString name(int id);       //如输入数字0转换为字符車
    bool red(int id);           //id是红的则返回true;
    bool sameColor(int id1, int id2);//id1，id2颜色相同返回true;
    int getStoneId(int row, int col);
    void killStone(int id);     //吃掉对方的id的棋子
    void reliveStone(int id);       //恢复死去的棋子，悔棋用
    void moveStone(int moveid, int row, int col);//moveStone只是改坐标
    bool isDead(int id);

    /* move stone */
    void mouseReleaseEvent(QMouseEvent *);
    void click(QPoint pt);
    virtual void click(int id, int row, int col);
    void trySelectStone(int id);     //尝试选中棋子，但未必能选中，如红走时是选不中黑的棋的
    void tryMoveStone(int killid, int row, int col);
    void moveStone(int moveid, int killid, int row, int col);//****moveStone还要记录吃掉的棋子，悔棋用
    void saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps);
    void backOne();
    void back(Step* step);  //悔棋两步以上
    virtual void back();

    /* rule 各棋子走法规则*/
    bool canMove(int moveid, int killid, int row, int col);
    bool canMoveChe(int moveid, int killid, int row, int col);
    bool canMoveMa(int moveid, int killid, int row, int col);
    bool canMovePao(int moveid, int killid, int row, int col);
    bool canMoveBing(int moveid, int killid, int row, int col);
    bool canMoveJiang(int moveid, int killid, int row, int col);
    bool canMoveShi(int moveid, int killid, int row, int col);
    bool canMoveXiang(int moveid, int killid, int row, int col);

    bool canSelect(int id);//红方只可选红棋

    /* rule helper */
    int getStoneCountAtLine(int row1, int col1, int row2, int col2);//直线上两坐标点之间getStoneCount有多少棋子
    int relation(int row1, int col1, int row, int col);
    bool isBottomSide(int id);

signals:

public slots:
    void slotBack();

};

#endif // BOARD_H
