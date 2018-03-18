# QT跨平台中国象棋（人机对战和人人对战）
## 运行环境
Qt Creater 5.4
点击Chess.pro文件，会自动加载到Qt Creater上，可选择构建在Win或Android上，再运行
### UI界面部分：
利用QT界面绘制技术，使用QPainter绘制类画出棋盘、九宫格、楚河汉界、棋子等。
### 操作控制部分：
鼠标点击选中棋子去行走或吃棋，不同棋子行走或吃棋规则各不相同；同时记录己方行走路径，点击悔棋按钮可悔棋。
### 人机对战算法部分：
给各棋子分配相应分值，计算双方局面总分差值，电脑下棋时思考两步，利用Minimax算法（极小化极大算法）搜索，选择假定电脑和人轮流走一步后使电脑局面分收益最小情况中的最大收益值，该值所在路径为电脑真正的下一步，可实现两步人工智能。
### 算法改进部分：
加大电脑下棋Minimax算法的搜索深度，利用Alpha-Beta剪枝算法优化改进，搜索结果不变且是最优解但删减了不需要遍历的分支，效率更高，可实现六步人工智能。
### 人人对战部分:
利用QTcpServer和QTcpSocket实现服务器和客户端通信，实现人人对战。
## 效果图
![](http://wx1.sinaimg.cn/mw690/e3b52512ly1fd66d841dnj21kv0qoaml.jpg)
