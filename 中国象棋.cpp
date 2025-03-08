/*
使用了easyx图形库
*/
#include<stdio.h>
#include <graphics.h>	// 引用图形库头文件
#include <conio.h>//实现鼠标点击
#define INTERVAL 50//距离左边的间隔
#define CHESSGRID 70//棋盘宽度
#define ROW 10
#define COL 9//10行9列
#define JG 10//外边框的间隔
struct Chess //象棋属性
{	
	char name[4];//象棋名字 一汉字2到3个字符 加上\0
	int x;
	int y;
	char type;//棋子是红是黑
	bool flag;//判断是否过河
	bool selected; // 新增：判断是否被选中
}map[ROW][COL];
const char* redChess[7] = {"车","马","象","士","将","炮","卒"};
const char* blackChess[7] = { "俥","馬","相","仕","帅","炮","兵" };
//初始化数据
void GameInit() {
	//遍历
	for (int i = 0; i < ROW; i++) {
		int temp = 0;
		int temp1 = 0;
		int temp2 = 1;
		for (int k = 0; k < COL; k++) {
			char chessname[4] = "";
			char ccolor = 'B';//黑棋
			//初始化黑棋
			if (i <= 4) {
				if (i == 0) {
					if (temp <= 4) {
						temp++;
					}
					else {
						temp1 = 4 - temp2;
						temp2++;
					}
					sprintf(chessname, "%s", blackChess[temp1]);
					temp1++;
				}
				if (i == 2 && (k == 1 || k == 7)) {
					strcpy(chessname, blackChess[5]);
				}
				if (i == 3 && (k%2==0)) {
					strcpy(chessname, blackChess[6]);
				}
			}
			//初始化红棋
			else {
				ccolor = 'R';//红棋
				if (i == ROW-1) {
					if (temp <= 4) {
						temp++;
					}
					else {
						temp1 = 4 - temp2;
						temp2++;
					}
					sprintf(chessname, "%s", redChess[temp1]);
					temp1++;
				}
				if (i == 7 && (k == 1 || k == 7)) {
					strcpy(chessname, redChess[5]);
				}
				if (i == 6 && (k % 2 == 0)) {
					strcpy(chessname, redChess[6]);
				}
			}
			map[i][k].type = ccolor;
			strcpy(map[i][k].name, chessname);
			map[i][k].flag = false;
			map[i][k].selected = false;
			map[i][k].x = k*CHESSGRID+INTERVAL;
			map[i][k].y = i*CHESSGRID+INTERVAL;
		}
	}
}
//游戏绘制
void GameDraw() {
	//绘制棋盘 颜色为棕色
	setbkcolor(RGB(252, 215, 162));
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	//绘制棋盘中的线
	for (int i = 0; i < 10; i++) {
		//画横线
		line(INTERVAL, i * CHESSGRID + INTERVAL, CHESSGRID * 8 + INTERVAL, i * CHESSGRID + INTERVAL);
		if (i < 9) {
			//画竖线
			line(i * CHESSGRID + INTERVAL, INTERVAL, i * CHESSGRID + INTERVAL, 9 * CHESSGRID + INTERVAL);
		}
	}
	//显示楚河汉界
	setfillcolor(RGB(252, 215, 162));
	fillrectangle(INTERVAL, 4 * CHESSGRID + INTERVAL, 8 * CHESSGRID + INTERVAL, 5 * CHESSGRID + INTERVAL);
	settextcolor(BLUE);
	settextstyle(50, 0, _T("黑体"));
	int twidth = textwidth(_T("楚河      汉界"));
	int theight = textheight(_T("楚河      汉界"));
	//这是字体距离矩形两边的间隔 目的在于让文字居中
	twidth = (8 * CHESSGRID - twidth) / 2;
	theight = (CHESSGRID - theight) / 2;
	outtextxy(INTERVAL+twidth,4*CHESSGRID+theight+INTERVAL,_T( "楚河      汉界"));
	//画外边框
	//画上下
	line(INTERVAL -JG , INTERVAL -JG , CHESSGRID * 8 + INTERVAL+JG, INTERVAL -JG);
	line(INTERVAL - JG, 9*CHESSGRID+INTERVAL +JG, CHESSGRID * 8 + INTERVAL + JG, 9 * CHESSGRID + INTERVAL + JG);//画横线纵坐标一样 画竖线横坐标一样
	//画左右
	line(INTERVAL-JG, INTERVAL-JG,INTERVAL-JG,9 * CHESSGRID+ INTERVAL+JG);
	line(8*CHESSGRID+INTERVAL+JG, INTERVAL - JG, 8 * CHESSGRID + INTERVAL+JG, 9 * CHESSGRID + INTERVAL + JG);
	//画米 先上后下
	line(3 * CHESSGRID + INTERVAL, INTERVAL, 5 * CHESSGRID + INTERVAL, 2 * CHESSGRID + INTERVAL);
	line(3 * CHESSGRID + INTERVAL, 2 * CHESSGRID + INTERVAL, 5 * CHESSGRID + INTERVAL, INTERVAL);
	line(3 * CHESSGRID + INTERVAL, 7*CHESSGRID+INTERVAL, 5 * CHESSGRID + INTERVAL,9 * CHESSGRID + INTERVAL);
	line(3 * CHESSGRID + INTERVAL, 9 * CHESSGRID + INTERVAL, 5 * CHESSGRID + INTERVAL,7*CHESSGRID+ INTERVAL);
	//画棋子
	settextstyle(30, 0, _T("黑体"));
	for (int i = 0; i < ROW; i++) {
		for (int k = 0; k < COL; k++) {
			if (strcmp(map[i][k].name, "") != 0) {
				if (map[i][k].type == 'B') {
					settextcolor(BLACK);
					setlinecolor(BLACK);
				}
				else {
					settextcolor(RED);
					setlinecolor(RED);
				}
				fillcircle(map[i][k].x,map[i][k].y,30);
				outtextxy(map[i][k].x-15, map[i][k].y-15, map[i][k].name);
			}
		}
	}

}
//实现棋子的移动
void GetPlayerInput(int* fromX, int* fromY, int* toX, int* toY) {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		//左键选择棋子
		if (m.uMsg == WM_LBUTTONDOWN) {
			*fromX = (m.x - INTERVAL) / CHESSGRID;
			*fromY = (m.y - INTERVAL) / CHESSGRID;
			break;
		}
	}
	//再次左键实现移动
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			*toX = (m.x - INTERVAL) / CHESSGRID;
			*toY = (m.y - INTERVAL) / CHESSGRID;
			break;
		}
	}
}
void UpdateBoard(int fromX, int fromY, int toX, int toY) {
	Chess temp = map[fromX][fromY];
	map[fromX][fromY] = Chess{ "",0,0,' ',false }; // 清空原位置
	map[toX][toY] = temp; // 设置新位置
	fillcircle(map[toX][toY].x, map[toX][toY].y, 30);

	// 打印移动信息
	printf("Move piece %s from (%d, %d) to (%d, %d)\n",
		temp.name, fromX, fromY, toX, toY);
}
// 验证移动合法性函数
bool IsValidMove(int fromX, int fromY, int toX, int toY) {
	return true;
	//游戏主循环
}void GameLoop() {
	MOUSEMSG m;
	int fromX = -1, fromY = -1; // 用于存储首次点击的位置
	while (true) {
		if (MouseHit()) { // 检查是否有鼠标消息
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) { // 处理左键点击
				int x = (m.x - INTERVAL) / CHESSGRID;
				int y = (m.y - INTERVAL) / CHESSGRID;
				if (fromX == -1 && fromY == -1) { // 第一次点击选择棋子
					fromX = x;
					fromY = y;
				}
				else { // 第二次点击确定目标位置
					int toX = x;
					int toY = y;
					if (IsValidMove(fromX, fromY, toX, toY)) {
						UpdateBoard(fromX, fromY, toX, toY);
						GameDraw(); // 重新绘制棋盘
					}
					fromX = -1; // 重置选择状态
					fromY = -1;
				}
			}
		}
		//Sleep(10); // 简单的延时以减少CPU使用率
	}
}
int main() 
{
	initgraph(800, 800); // 初始化图形窗口
	GameInit(); // 初始化游戏数据
	GameDraw(); // 绘制初始棋盘
	GameLoop(); // 进入游戏主循环
	return 0;
}
