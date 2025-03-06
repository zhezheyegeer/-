/*
ʹ����easyxͼ�ο�
*/
#include<stdio.h>
#include <graphics.h>	// ����ͼ�ο�ͷ�ļ�
#include <conio.h>//ʵ�������
#define INTERVAL 50//������ߵļ��
#define CHESSGRID 70//���̿��
#define ROW 10
#define COL 9//10��9��
#define JG 10//��߿�ļ��
struct Chess //��������
{	
	char name[4];//�������� һ����2��3���ַ� ����\0
	int x;
	int y;
	char type;//�����Ǻ��Ǻ�
	bool flag;//�ж��Ƿ����
	bool selected; // �������ж��Ƿ�ѡ��
}map[ROW][COL];
const char* redChess[7] = {"��","��","��","ʿ","��","��","��"};
const char* blackChess[7] = { "�e","�R","��","��","˧","��","��" };
//��ʼ������
void GameInit() {
	//����
	for (int i = 0; i < ROW; i++) {
		int temp = 0;
		int temp1 = 0;
		int temp2 = 1;
		for (int k = 0; k < COL; k++) {
			char chessname[4] = "";
			char ccolor = 'B';//����
			//��ʼ������
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
			//��ʼ������
			else {
				ccolor = 'R';//����
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
//��Ϸ����
void GameDraw() {
	//�������� ��ɫΪ��ɫ
	setbkcolor(RGB(252, 215, 162));
	cleardevice();
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	//���������е���
	for (int i = 0; i < 10; i++) {
		//������
		line(INTERVAL, i * CHESSGRID + INTERVAL, CHESSGRID * 8 + INTERVAL, i * CHESSGRID + INTERVAL);
		if (i < 9) {
			//������
			line(i * CHESSGRID + INTERVAL, INTERVAL, i * CHESSGRID + INTERVAL, 9 * CHESSGRID + INTERVAL);
		}
	}
	//��ʾ���Ӻ���
	setfillcolor(RGB(252, 215, 162));
	fillrectangle(INTERVAL, 4 * CHESSGRID + INTERVAL, 8 * CHESSGRID + INTERVAL, 5 * CHESSGRID + INTERVAL);
	settextcolor(BLUE);
	settextstyle(50, 0, _T("����"));
	int twidth = textwidth(_T("����      ����"));
	int theight = textheight(_T("����      ����"));
	//�����������������ߵļ�� Ŀ�����������־���
	twidth = (8 * CHESSGRID - twidth) / 2;
	theight = (CHESSGRID - theight) / 2;
	outtextxy(INTERVAL+twidth,4*CHESSGRID+theight+INTERVAL,_T( "����      ����"));
	//����߿�
	//������
	line(INTERVAL -JG , INTERVAL -JG , CHESSGRID * 8 + INTERVAL+JG, INTERVAL -JG);
	line(INTERVAL - JG, 9*CHESSGRID+INTERVAL +JG, CHESSGRID * 8 + INTERVAL + JG, 9 * CHESSGRID + INTERVAL + JG);//������������һ�� �����ߺ�����һ��
	//������
	line(INTERVAL-JG, INTERVAL-JG,INTERVAL-JG,9 * CHESSGRID+ INTERVAL+JG);
	line(8*CHESSGRID+INTERVAL+JG, INTERVAL - JG, 8 * CHESSGRID + INTERVAL+JG, 9 * CHESSGRID + INTERVAL + JG);
	//���� ���Ϻ���
	line(3 * CHESSGRID + INTERVAL, INTERVAL, 5 * CHESSGRID + INTERVAL, 2 * CHESSGRID + INTERVAL);
	line(3 * CHESSGRID + INTERVAL, 2 * CHESSGRID + INTERVAL, 5 * CHESSGRID + INTERVAL, INTERVAL);
	line(3 * CHESSGRID + INTERVAL, 7*CHESSGRID+INTERVAL, 5 * CHESSGRID + INTERVAL,9 * CHESSGRID + INTERVAL);
	line(3 * CHESSGRID + INTERVAL, 9 * CHESSGRID + INTERVAL, 5 * CHESSGRID + INTERVAL,7*CHESSGRID+ INTERVAL);
	//������
	settextstyle(30, 0, _T("����"));
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
//ʵ�����ӵ��ƶ�
void GetPlayerInput(int* fromX, int* fromY, int* toX, int* toY) {
	MOUSEMSG m;
	while (1) {
		m = GetMouseMsg();
		//���ѡ������
		if (m.uMsg == WM_LBUTTONDOWN) {
			*fromX = (m.x - INTERVAL) / CHESSGRID;
			*fromY = (m.y - INTERVAL) / CHESSGRID;
			break;
		}
	}
	//�ٴ����ʵ���ƶ�
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
	map[fromX][fromY] = Chess{ "",0,0,' ',false }; // ���ԭλ��
	map[toX][toY] = temp; // ������λ��
	fillcircle(map[toX][toY].x, map[toX][toY].y, 30);

	// ��ӡ�ƶ���Ϣ
	printf("Move piece %s from (%d, %d) to (%d, %d)\n",
		temp.name, fromX, fromY, toX, toY);
}
// ��֤�ƶ��Ϸ��Ժ���
bool IsValidMove(int fromX, int fromY, int toX, int toY) {
	return true;
	//��Ϸ��ѭ��
}void GameLoop() {
	MOUSEMSG m;
	int fromX = -1, fromY = -1; // ���ڴ洢�״ε����λ��
	while (true) {
		if (MouseHit()) { // ����Ƿ��������Ϣ
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) { // ����������
				int x = (m.x - INTERVAL) / CHESSGRID;
				int y = (m.y - INTERVAL) / CHESSGRID;
				if (fromX == -1 && fromY == -1) { // ��һ�ε��ѡ������
					fromX = x;
					fromY = y;
				}
				else { // �ڶ��ε��ȷ��Ŀ��λ��
					int toX = x;
					int toY = y;
					if (IsValidMove(fromX, fromY, toX, toY)) {
						UpdateBoard(fromX, fromY, toX, toY);
						GameDraw(); // ���»�������
					}
					fromX = -1; // ����ѡ��״̬
					fromY = -1;
				}
			}
		}
		//Sleep(10); // �򵥵���ʱ�Լ���CPUʹ����
	}
}
int main() 
{
	initgraph(800, 800); // ��ʼ��ͼ�δ���
	GameInit(); // ��ʼ����Ϸ����
	GameDraw(); // ���Ƴ�ʼ����
	GameLoop(); // ������Ϸ��ѭ��
	return 0;
}
