#include "NetGame.h"

NetGame::NetGame(bool server, QWidget *parent) : Board(parent)
{
    _server = NULL;     //初始化为null
    _socket = NULL;
    _bServer = server;

    if(_bServer)
    {
        _server = new QTcpServer(this);     //创建服务器
        _server->listen(QHostAddress::Any, 9899);   //监听端口9999
        connect(_server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    }   //槽函数连接
    else
    {   //是客户端
        _socket = new QTcpSocket(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"), 9899);
        connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));
    }
}

void NetGame::slotNewConnection()
{
    if(_socket) return;

    _socket = _server->nextPendingConnection();
    connect(_socket, SIGNAL(readyRead()), this, SLOT(slotDataArrive()));

    /* 产生随机数来决定谁走红色 */
    bool bRedSide = qrand()%2>0;
    init(bRedSide);

    /* 发送给对方 */
    QByteArray buf;
    buf.append(1);
    buf.append(bRedSide?0:1);
    _socket->write(buf);
}

void NetGame::back()
{
    if(_bRedTurn != _bSide)
        return;
    backOne();
    backOne();

    QByteArray buf;
    buf.append(3);
    _socket->write(buf);
}

void NetGame::click(int id, int row, int col)
{
    if(_bRedTurn != _bSide)//只能点自己的棋。即一边只能点红棋，一边只能点黑棋
        return;

    Board::click(id, row, col);//一定要调用父类的click，父类的，即下棋

    /* 把下棋信息发送给对方 */
    QByteArray buf;
    buf.append(2);
    buf.append(id);
    buf.append(row);
    buf.append(col);
    _socket->write(buf);
}

void NetGame::backFromNetwork(QByteArray)
{
    backOne();
    backOne();
}
void NetGame::clickFromNetwork(QByteArray buf)
{
    Board::click(buf[1], 9-buf[2], 8-buf[3]);
}
void NetGame::initFromNetwork(QByteArray buf)
{
    bool bRedSide = buf.at(1)>0?true:false;
    init(bRedSide);
}

void NetGame::slotDataArrive()
{
    QByteArray buf = _socket->readAll();
    switch (buf.at(0)) {
    case 1:
        initFromNetwork(buf);//报文头是1，则初始化，画棋盘
        break;
    case 2:
        clickFromNetwork(buf);//报文头是2，则鼠标点击
        break;
    case 3:
        backFromNetwork(buf);//报文头是3，则鼠标点击
        break;
    default:
        break;
    }
}

NetGame::~NetGame()
{

}

