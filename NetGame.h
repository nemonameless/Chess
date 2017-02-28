#ifndef NETGAME_H
#define NETGAME_H

#include "Board.h"
#include <QTcpServer>
#include <QTcpSocket>

/*
 * 报文格式定义
 * 1.初始化    两个字节
 * 2.鼠标点击   四个字节
 * 3.悔棋      一个字节
 *
*/

class NetGame : public Board
{
    Q_OBJECT
public:
    explicit NetGame(bool server, QWidget *parent = 0);
    ~NetGame();

    bool _bServer;
    QTcpServer* _server;
    QTcpSocket* _socket;

    void back();
    void click(int id, int row, int col);

    void backFromNetwork(QByteArray buf);
    void clickFromNetwork(QByteArray buf);
    void initFromNetwork(QByteArray buf);

signals:

public slots:
    void slotNewConnection();
    void slotDataArrive();
};

#endif // NETGAME_H
