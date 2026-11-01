#include <graphics.h>
#include <string.h>
#include "resource.h"
#include <time.h>
#include <cstdio>

#define QZ 37

int broad[10][9];//0为没有，1为车，2为马 ，3为象，4为士，5为将，6为兵，7为炮
int fbroad[10][9][2];//0为没有，1为车，2为马 ，3为象，4为士，5为将，6为兵，7为炮
int cx = 0;//移动的坐标
int cy = 0;

bool sound;
bool xianz;
bool patton;

bool t;

PIMAGE qi = newimage();
PIMAGE bj = newimage();

PIMAGE rcs = newimage();
PIMAGE rms = newimage();
PIMAGE rxs = newimage();
PIMAGE rss = newimage();
PIMAGE rjs = newimage();
PIMAGE rbs = newimage();
PIMAGE rps = newimage();
PIMAGE bcs = newimage();
PIMAGE bms = newimage();
PIMAGE bxs = newimage();
PIMAGE bss = newimage();
PIMAGE bjs = newimage();
PIMAGE bbs = newimage();
PIMAGE bps = newimage();
PIMAGE fqs = newimage();

MUSIC music;

int x;//棋子的坐标
int y;
int temp = 0;//模式：0为棋子，1为移动;位置：0为上面，1为下面
int player = 1;//1为红，-1为黑
int x1[100];
int y1[100];
int c = 0;

void draw();
void draws();
void clean();
void click();
int run(int t);
void menu();
int window(const char text1[12], const char text2[12], const char text3[12]);//txet1为第一行，text2为第二行
int window(const char text1[12], const char text2[12], const char text3[12], const char no[2], const char yes[2]);
int window(const char text1[12], const char text2[12], const char no[2], const char yes[2]);
void fplay();
void fclean();
void fdraw();
void frun(int t);
void setting();
void initialize();
void fdraws();
void cplay();
void cdraws();
void cdraw();
void cclean();
void crun(int t);
int decideche(int xzb,int yzb);

void cdraw() {
	cleardevice();
	putimage(0, 0, bj);
	setfont(40, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(18, 9, "模式：残棋对弈");
	setfont(30, 0, "华文隶书");
	xyprintf(7 * QZ, 15.2 * QZ, "返回主界面");
	xyprintf(7.5 * QZ, 14.2 * QZ, "重新开始");
	setfillcolor(EGEARGB(0xFF, 0xDB, 0xDA, 0x7D));//深黄色
	ege_fillrect(1.5 * QZ, 3.5 * QZ, 9 * QZ, 10 * QZ);
	//bar(2 * QZ, 4 * QZ, 10 * QZ, 13 * QZ);
	setlinewidth(4);
	rectangle(1.4 * QZ, 3.4 * QZ, 10.7 * QZ, 13.7 * QZ);
	setlinewidth(1);
	setcolor(BLACK);
	for (int i = 0; i < QZ * 10; i += QZ) {
		line(2 * QZ, 4 * QZ + i, 10 * QZ, 4 * QZ + i);
	}
	for (int i = 0; i < QZ * 9; i += QZ) {
		if (i == 0) {
			line(2 * QZ, 8 * QZ, 2 * QZ, 9 * QZ);
			line(10 * QZ, 8 * QZ, 10 * QZ + i, 9 * QZ);
		}
		line(2 * QZ + i, 4 * QZ, 2 * QZ + i, 8 * QZ);
		line(2 * QZ + i, 9 * QZ, 2 * QZ + i, 13 * QZ);
	}
	line(5 * QZ, 4 * QZ, 7 * QZ, 6 * QZ);
	line(7 * QZ, 4 * QZ, 5 * QZ, 6 * QZ);
	line(5 * QZ, 11 * QZ, 7 * QZ, 13 * QZ);
	line(7 * QZ, 11 * QZ, 5 * QZ, 13 * QZ);
	
	for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			if (broad[i][t] == 0) {
				continue;
			}
			else if (broad[i][t] == 1) {
				getimage(qi, "img/红车.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 2) {
				getimage(qi, "img/红马.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 3) {
				getimage(qi, "img/红相.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 4) {
				getimage(qi, "img/红士.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 5) {
				getimage(qi, "img/红帅.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 6) {
				getimage(qi, "img/红兵.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 7) {
				getimage(qi, "img/红炮.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -1) {
				getimage(qi, "img/黑车.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -2) {
				getimage(qi, "img/黑马.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -3) {
				getimage(qi, "img/黑象.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -4) {
				getimage(qi, "img/黑士.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -5) {
				getimage(qi, "img/黑将.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -6) {
				getimage(qi, "img/黑卒.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -7) {
				getimage(qi, "img/黑炮.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
		}
	}
}

void cdraws() {
	cleardevice();
	putimage(0, 0, bj);
	setfont(40, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(18, 9, "模式：残棋对弈");
	setfont(30, 0, "华文隶书");
	xyprintf(7 * QZ, 15.2 * QZ, "返回主界面");
	xyprintf(7.5 * QZ, 14.2 * QZ, "重新开始");
	setfillcolor(EGEARGB(0xFF, 0xDB, 0xDA, 0x7D));//深黄色
	ege_fillrect(1.5 * QZ, 3.5 * QZ, 9 * QZ, 10 * QZ);
	//bar(2 * QZ, 4 * QZ, 10 * QZ, 13 * QZ);
	setlinewidth(4);
	rectangle(1.4 * QZ, 3.4 * QZ, 10.7 * QZ, 13.7 * QZ);
	setlinewidth(1);
	setcolor(BLACK);
	for (int i = 0; i < QZ * 10; i += QZ) {
		line(2 * QZ, 4 * QZ + i, 10 * QZ, 4 * QZ + i);
	}
	for (int i = 0; i < QZ * 9; i += QZ) {
		if (i == 0) {
			line(2 * QZ, 8 * QZ, 2 * QZ, 9 * QZ);
			line(10 * QZ, 8 * QZ, 10 * QZ + i, 9 * QZ);
		}
		line(2 * QZ + i, 4 * QZ, 2 * QZ + i, 8 * QZ);
		line(2 * QZ + i, 9 * QZ, 2 * QZ + i, 13 * QZ);
	}
	line(5 * QZ, 4 * QZ, 7 * QZ, 6 * QZ);
	line(7 * QZ, 4 * QZ, 5 * QZ, 6 * QZ);
	line(5 * QZ, 11 * QZ, 7 * QZ, 13 * QZ);
	line(7 * QZ, 11 * QZ, 5 * QZ, 13 * QZ);
	
	for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			if (broad[i][t] == 0) {
				continue;
			}
			else if (broad[i][t] == 1) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rcs);
				continue;
			}
			else if (broad[i][t] == 2) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rms);
				continue;
			}
			else if (broad[i][t] == 3) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rxs);
				continue;
			}
			else if (broad[i][t] == 4) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rss);
				continue;
			}
			else if (broad[i][t] == 5) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rjs);
				continue;
			}
			else if (broad[i][t] == 6) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rbs);
				continue;
			}
			else if (broad[i][t] == 7) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rps);
				continue;
			}
			else if (broad[i][t] == -1) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bcs);
				continue;
			}
			else if (broad[i][t] == -2) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bms);
				continue;
			}
			else if (broad[i][t] == -3) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bxs);
				continue;
			}
			else if (broad[i][t] == -4) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bss);
				continue;
			}
			else if (broad[i][t] == -5) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bjs);
				continue;
			}
			else if (broad[i][t] == -6) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bbs);
				continue;
			}
			else if (broad[i][t] == -7) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bps);
				continue;
			}
		}
	}
}

void cplay() {
	cdraw();
	int a = 0;
	int b = 0;
	for (; is_run(); delay_fps(60)) {
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			if (msg.is_down() && msg.is_left()) {
				a = msg.x;
				b = msg.y;
				if (a >= 280 && a <= 400 && b >= 530 && b <= 550) {
					if (window("你真的要重新吗？", "", "")) {
						cclean();
						if (patton) {
							cdraws();
						}
						else {
							cdraw();
						}
						break;
					}
					else {
						if (patton) {
							cdraws();
						}
						else {
							cdraw();
						}
					}
				}
				if (a >= 260 && a <= 405 && b >= 560 && b <= 585) {
					if (window("你真的要返回主界面吗？", "你的状态将不会保存！！", "")) {
						menu();
						break;
					}
					else {
						if (patton) {
							cdraws();
						}
						else {
							cdraw();
						}
					}
				}
				if (a >= 55 && a <= 390 && b >= 130 && b <= 500) {//如果在棋盘内
					a = (a - (1.5 * QZ)) / QZ;
					b = (b - (3.5 * QZ)) / QZ;
					x = a;
					y = b;
					
					if (broad[y][x] > 0) {//如果是红棋
						if (broad[y][x] == 1) {//红车
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							for (int i = 1; i < 10; i++) {//竖上
								if (broad[y - i][x] == 0 && y - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
								}
								else if (broad[y - i][x] < 0 && y - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
									break;
								}
								else break;
							}
							for (int i = 1; i < 10; i++) {//竖下
								if (broad[y + i][x] == 0 && y + i - 1 != 9) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
								}
								else if (broad[y + i][x] < 0 && y + i - 1 != 9) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
									break;
								}
								else break;
							}
							for (int i = 1; i < 11; i++) {//横左
								if (broad[y][x - i] == 0 && x - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - i;
									y1[c] = y;
									c++;
								}
								else if (broad[y][x - i] < 0 && x - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - i;
									y1[c] = y;
									c++;
									break;
								}
								else break;
							}
							for (int i = 1; i < 11; i++) {//横右
								if (broad[y][x + i] == 0 && x + i - 1 != 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + i;
									y1[c] = y;
									c++;
								}
								else if (broad[y][x + i] < 0 && x + i - 1 != 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + i;
									y1[c] = y;
									c++;
									break;
								}
								else break;
							}
						}
						if (broad[y][x] == 2) {//红马
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y - 1][x] == 0) {
								if (broad[y - 2][x + 1] <= 0 && y - 2 >= 0 && x + 1 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x + 1;
									y1[c] = y - 2;
									c++;
								}
								if (broad[y - 2][x - 1] <= 0 && y - 2 >= 0 && x - 1 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x - 1;
									y1[c] = y - 2;
									c++;
								}
								
							}
							if (broad[y + 1][x] == 0) {
								if (broad[y + 2][x + 1] <= 0 && y + 2 <= 9 && x + 1 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x + 1;
									y1[c] = y + 2;
									c++;
								}
								if (broad[y + 2][x - 1] <= 0 && y + 2 <= 9 && x - 1 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x - 1;
									y1[c] = y + 2;
									c++;
								}
								
							}
							if (broad[y][x - 1] == 0) {
								if (broad[y + 1][x - 2] <= 0 && y + 1 <= 9 && x - 2 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y + 1;
									c++;
								}
								if (broad[y - 1][x - 2] <= 0 && y - 1 >= 0 && x - 2 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y - 1;
									c++;
								}
							}
							if (broad[y][x + 1] == 0) {
								if (broad[y + 1][x + 2] <= 0 && y + 1 <= 9 && x + 2 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y + 1;
									c++;
								}
								if (broad[y - 1][x + 2] <= 0 && y - 1 >= 0 && x + 2 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y - 1;
									c++;
								}
							}
						}
						if (broad[y][x] == 3) {//红相
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y - 1][x - 1] == 0 && y - 2 >= 0 && x - 2 >= 0 && y != 5) {
								if (broad[y - 2][x - 2] <= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y - 2;
									c++;
								}
							}
							if (broad[y + 1][x + 1] == 0 && y + 2 <= 9 && x + 2 <= 8) {
								if (broad[y + 2][x + 2] <= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y + 2;
									c++;
								}
							}
							if (broad[y - 1][x + 1] == 0 && y - 2 >= 0 && x + 2 <= 8 && y != 5) {
								if (broad[y - 2][x + 2] <= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y - 2;
									c++;
								}
							}
							if (broad[y + 1][x - 1] == 0 && y + 2 <= 9 && x - 2 >= 0) {
								if (broad[y + 2][x - 2] <= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y + 2;
									c++;
								}
							}
						}
						if (broad[y][x] == 4) {//红士
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y + 1][x + 1] <= 0 && x < 5 && y < 9) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x + 1;
								y1[c] = y + 1;
								c++;
							}
							if (broad[y - 1][x - 1] <= 0 && x > 3 && y > 7) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x - 1;
								y1[c] = y - 1;
								c++;
							}
							if (broad[y + 1][x - 1] <= 0 && x > 3 && y < 9) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x - 1;
								y1[c] = y + 1;
								c++;
							}
							if (broad[y - 1][x + 1] <= 0 && x < 5 && y > 7) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x + 1;
								y1[c] = y - 1;
								c++;
							}
						}
						if (broad[y][x] == 5) {//红帅
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y + 1][x] <= 0 && y < 9) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x;
								y1[c] = y + 1;
								c++;
							}
							if (broad[y - 1][x] <= 0 && y > 7) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x;
								y1[c] = y - 1;
								c++;
							}
							if (broad[y][x + 1] <= 0 && x < 5) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
								x1[c] = x + 1;
								y1[c] = y;
								c++;
							}
							if (broad[y][x - 1] <= 0 && x > 3) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
								x1[c] = x - 1;
								y1[c] = y;
								c++;
							}
							for (int i = 1; i < 11; i++) {
								if (broad[y - i][x] == 0) {
									continue;
								}
								else if (broad[y - i][x] == -5) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
								}
								else break;
								
							}
						}
						if (broad[y][x] == 6) {//红兵
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y - 1][x] <= 0 && y > 0) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x;
								y1[c] = y - 1;
								c++;
							}
							if (y < 5) {
								if (broad[y][x - 1] <= 0 && x > 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - 1;
									y1[c] = y;
									c++;
								}
								if (broad[y][x + 1] <= 0 && x < 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + 1;
									y1[c] = y;
									c++;
								}
							}
						}
						if (broad[y][x] == 7) {//红炮
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							for (int i = 1; i < 10; i++) {//竖上
								if (broad[y - i][x] == 0 && y - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
								}
								else break;
							}
							for (int i = 1; i < 10; i++) {//竖上
								if (broad[y - i][x] != 0 && y - i + 1 != 0 && y - i >= 0) {
									for (int t = 1; t < 10; t++) {
										if (broad[y - i - t][x] > 0) {
											break;
										}
										if (broad[y - i - t][x] < 0 && y - i + 1 != 0) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i - t) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y - i - t;
											c++;
											break;
										}
									}
									break;
								}
							}
							for (int i = 1; i < 10; i++) {//竖下
								if (broad[y + i][x] == 0 && y + i - 1 != 9) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
								}
								else break;
							}
							for (int i = 1; i < 10; i++) {//竖下
								if (broad[y + i][x] != 0 && y + i - 1 != 9) {
									for (int t = 1; t < 10; t++) {
										if (broad[y + i + t][x] > 0) {
											break;
										}
										if (broad[y + i + t][x] < 0 && y + i - 1 != 9 && (y + i + t) <= 9) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i + t) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y + i + t;
											c++;
											break;
										}
									}
									break;
								}
							}
							
							for (int i = 1; i < 11; i++) {//横左
								if (broad[y][x - i] == 0 && x - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - i;
									y1[c] = y;
									c++;
									//break;
								}
								else break;
							}
							for (int i = 1; i < 11; i++) {//横左
								if (broad[y][x - i] != 0 && x - i + 1 != 0) {
									for (int t = 1; t < 10; t++) {
										if (broad[y][x - i - t] > 0) {
											break;
										}
										if (broad[y][x - i - t] < 0 && x - i + 1 != 0 && (x - i - t) >= 0) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x - i - t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x - i - t;
											y1[c] = y;
											c++;
											break;
										}
									}
									break;
								}
							}
							
							for (int i = 1; i < 11; i++) {//横右
								if (broad[y][x + i] == 0 && x + i - 1 != 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + i;
									y1[c] = y;
									c++;
									//break;
								}
								else break;
							}
							
							for (int i = 1; i < 11; i++) {//横右
								if (broad[y][x + i] != 0 && x + i - 1 != 8) {
									for (int t = 1; t < 10; t++) {
										if (broad[y][x + i + t] > 0) {
											break;
										}
										if (broad[y][x + i + t] < 0 && x + i - 1 != 8 && (x + i + t) <= 9) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x + i + t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x + i + t;
											y1[c] = y;
											c++;
											break;
										}
									}
									break;
								}
							}
						}
					}
					else if (broad[y][x] < 0) {
						cplay();
					}
					else {
						cplay();
					}
					crun(1);
				}
			}
		}
	}
}

void cclean() {
	memset(broad, 0, sizeof(broad));
	memset(x1, 0, sizeof(x1));
	memset(y1, 0, sizeof(y1));
	c = 0;
	temp = 0;
	t = true;
	player = 1;
	srand(time(NULL));
	
	broad[2][0] = -3;
	broad[0][2] = -3;
	broad[0][3] = -4;
	broad[0][4] = -5;
	broad[1][4] = -4;
	broad[9][4] = 5;
	broad[5][2] = 1;
}

int decideche(int xzb,int yzb) {
	
	c = 0;
	if (broad[cy][cx] == 1) {//红车
		for (int i = 1; i < 10; i++) {//竖上
			if (broad[cy - i][cx] == 0 && cy - i + 1 != 0) {
				x1[c] = cx;
				y1[c] = cy - i;
				c++;
			}
			else if (broad[cy - i][cx] < 0 && cy - i + 1 != 0) {
				x1[c] = cx;
				y1[c] = cy - i;
				c++;
				break;
			}
			else break;
		}
		for (int i = 1; i < 10; i++) {//竖下
			if (broad[cy + i][cx] == 0 && cy + i - 1 != 9) {
				x1[c] = cx;
				y1[c] = cy + i;
				c++;
			}
			else if (broad[cy + i][cx] < 0 && cy + i - 1 != 9) {
				x1[c] = cx;
				y1[c] = cy + i;
				c++;
				break;
			}
			else break;
		}
		for (int i = 1; i < 11; i++) {//横左
			if (broad[cy][cx - i] == 0 && cx - i + 1 != 0) {
				x1[c] = cx - i;
				y1[c] = cy;
				c++;
			}
			else if (broad[cy][cx - i] < 0 && cx - i + 1 != 0) {
				x1[c] = cx - i;
				y1[c] = cy;
				c++;
				break;
			}
			else break;
		}
		for (int i = 1; i < 11; i++) {//横右
			if (broad[cy][cx + i] == 0 && cx + i - 1 != 8) {
				x1[c] = cx + i;
				y1[c] = cy;
				c++;
			}
			else if (broad[cy][cx + i] < 0 && cx + i - 1 != 8) {
				x1[c] = cx + i;
				y1[c] = cy;
				c++;
				break;
			}
			else break;
		}
	}
	
	for (int i = 0; i < c; i++) {
		//xyprintf(i * 10, i * 10, "%d  %d", x1[i], y1[i]);
		//getch();
		if (x1[i] == xzb && y1[i] == yzb) {
			return 1;
		}
	}
	return 0;
}

void crun(int t) {
	int a = 0;
	int b = 0;
	int p = 0;
	
	if (t == 1) {//选择移动的地方
		for (; is_run(); delay_fps(60)) {
			while (mousemsg()) {
				mouse_msg msg = getmouse();
				a = msg.x;
				b = msg.y;
				if (msg.is_left() && msg.is_down()) {
					if (a >= 55 && a <= 390 && b >= 130 && b <= 500) {
						a = (a - (1.5 * QZ)) / QZ;
						b = (b - (3.5 * QZ)) / QZ;
						cx = a;
						cy = b;
						if (player == 1) {
							if (broad[y][x] != broad[cy][cx]) {
								for (int i = 0; i < c; i++) {
									if (x1[i] == cx && y1[i] == cy) {
										p = 1;
										player = -1;
									}
								}
								if (p) {
									if (sound) {
										music.Play(0);
									}
									broad[cy][cx] = broad[y][x];
									broad[y][x] = 0;
									c = 0;
									if (patton) {
										cdraws();
										crun(2);
									}
									else {
										cdraw();
										crun(2);
									}
									cplay();
								}
								else {
									c = 0;
									cplay();
								}
							}
							else {
								c = 0;
							}
						}
					}
					else {
						player = -player;
						cplay();
					}
				}
			}
		}
	}
	else if (t == 2) {
		int a = 0;
		int b = 0;
		if (player == -1) {
			player = 1;
			for (int i = 0; i < 9; i++) {//横
				for (int j = 0; j < 10; j++) {//列
					if (broad[j][i] < 0) {
						if (broad[j][i] == -3) {
							a = i;
							b = j;
							if (decideche(a, b)) {
								
							}
							
						}
					}
				}
			}
			cplay();
		}
	}
	
}

void fdraws() {
	cleardevice();
	putimage(0, 0, bj);
	if (xianz) {
		if (!t) {
			if (player == 1) {
				setfont(20, 0, "华文隶书");
				setbkmode(TRANSPARENT);
				xyprintf(9, 14.5 * QZ, "状态：现在是红棋走");
			}
			else if (player == -1) {
				setfont(20, 0, "华文隶书");
				setbkmode(TRANSPARENT);
				xyprintf(9, 14.5 * QZ, "状态：现在是黑棋走");
			}
		}
	}
	setfont(40, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(18, 9, "模式：翻棋对弈");
	setfont(30, 0, "华文隶书");
	xyprintf(7 * QZ, 15.2 * QZ, "返回主界面");
	xyprintf(7.5 * QZ, 14.2 * QZ, "重新开始");
	setfillcolor(EGEARGB(0xFF, 0xDB, 0xDA, 0x7D));//深黄色
	ege_fillrect(1.5 * QZ, 3.5 * QZ, 9 * QZ, 10 * QZ);
	//bar(2 * QZ, 4 * QZ, 10 * QZ, 13 * QZ);
	setlinewidth(4);
	rectangle(1.4 * QZ, 3.4 * QZ, 10.7 * QZ, 13.7 * QZ);
	setlinewidth(1);
	setcolor(BLACK);
	for (int i = 0; i < QZ * 10; i += QZ) {
		line(2 * QZ, 4 * QZ + i, 10 * QZ, 4 * QZ + i);
	}
	for (int i = 0; i < QZ * 9; i += QZ) {
		if (i == 0) {
			line(2 * QZ, 8 * QZ, 2 * QZ, 9 * QZ);
			line(10 * QZ, 8 * QZ, 10 * QZ + i, 9 * QZ);
		}
		line(2 * QZ + i, 4 * QZ, 2 * QZ + i, 8 * QZ);
		line(2 * QZ + i, 9 * QZ, 2 * QZ + i, 13 * QZ);
	}
	line(5 * QZ, 4 * QZ, 7 * QZ, 6 * QZ);
	line(7 * QZ, 4 * QZ, 5 * QZ, 6 * QZ);
	line(5 * QZ, 11 * QZ, 7 * QZ, 13 * QZ);
	line(7 * QZ, 11 * QZ, 5 * QZ, 13 * QZ);
	for (int t = 0; t < 9; t++) {
		for (int i = 0; i < 10; i++) {
			if (fbroad[i][t][1]) {
				if (fbroad[i][t][0] == 0) {
					continue;
				}
				else if (fbroad[i][t][0] == 1) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rcs);
					continue;
				}
				else if (fbroad[i][t][0] == 2) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rms);
					continue;
				}
				else if (fbroad[i][t][0] == 3) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rxs);
					continue;
				}
				else if (fbroad[i][t][0] == 4) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rss);
					continue;
				}
				else if (fbroad[i][t][0] == 5) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rjs);
					continue;
				}
				else if (fbroad[i][t][0] == 6) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rbs);
					continue;
				}
				else if (fbroad[i][t][0] == 7) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rps);
					continue;
				}
				else if (fbroad[i][t][0] == -1) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bcs);
					continue;
				}
				else if (fbroad[i][t][0] == -2) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bms);
					continue;
				}
				else if (fbroad[i][t][0] == -3) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bxs);
					continue;
				}
				else if (fbroad[i][t][0] == -4) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bss);
					continue;
				}
				else if (fbroad[i][t][0] == -5) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bjs);
					continue;
				}
				else if (fbroad[i][t][0] == -6) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bbs);
					continue;
				}
				else if (fbroad[i][t][0] == -7) {
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bps);
					continue;
				}
			}
			else {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, fqs);
				continue;
			}
		}
	}
}

void initialize() {
	putimage(0, 0, bj);
	setcolor(BLACK);
	setfont(60, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(100, 60, "中国象棋");
	window("正在初始化", "请稍等...", "", "");
	char ch = 0;
	FILE* fp = nullptr;
	if ((fp = fopen("user.dat","r")) == NULL) {
		if (window("提示:","找不到配置文件，是否初始","化？")) {
			if ((fp = fopen("user.dat", "w+")) == NULL) {
				exit(1);
			}
			else {
				cleardevice();
				fputs("************************\n中国象棋配置文件\n************************\n", fp);
				putimage(0, 0, bj);
				if (window("提示:", "你需要在下棋的时候开启声", "音吗？", "不了", "是的")) {
					fputs("$声音：",fp);
					fputs("开启\n", fp);
				}
				else {
					fputs("%声音：", fp);
					fputs("关闭\n", fp);
				}
				if (window("你需要在下棋的时候开启严", "格限制吗？（比如限制连续", "走棋）", "不了", "是的")) {
					fputs("$限制：", fp);
					fputs("开启\n", fp);
				}
				else {
					fputs("%限制：", fp);
					fputs("关闭\n", fp);
				}
				if (window("你需要节约还是流畅？", "（建议选择流畅）","", "节约", "流畅")) {
					fputs("$模式：", fp);
					fputs("开启\n", fp);
				}
				else {
					fputs("%模式：", fp);
					fputs("关闭\n", fp);
				}
				
				fclose(fp);
				menu();
			}
		}
		else {
			exit(1);
		}
	}
	else {
		fseek(fp, 70, SEEK_SET);
		ch = fgetc(fp);
		if (ch == '$') {
			sound = true;
		}
		else {
			sound = false;
		}
		fseek(fp, 83, SEEK_SET);
		ch = fgetc(fp);
		if (ch == '$') {
			xianz = true;
		}
		else {
			xianz = false;
		}
		fseek(fp, 96, SEEK_SET);
		ch = fgetc(fp);
		if (ch == '$') {
			patton = true;
		}
		else {
			patton = false;
		}
		
		if (patton) {
			getimage(rcs, "img/红车.bmp");
			getimage(rms, "img/红马.bmp");
			getimage(rxs, "img/红相.bmp");
			getimage(rss, "img/红士.bmp");
			getimage(rjs, "img/红帅.bmp");
			getimage(rbs, "img/红兵.bmp");
			getimage(rps, "img/红炮.bmp");
			getimage(bcs, "img/黑车.bmp");
			getimage(bms, "img/黑马.bmp");
			getimage(bxs, "img/黑象.bmp");
			getimage(bss, "img/黑士.bmp");
			getimage(bjs, "img/黑将.bmp");
			getimage(bbs, "img/黑卒.bmp");
			getimage(bps, "img/黑炮.bmp");
			getimage(fqs, "img/翻棋.bmp");
		}
		else {
			delimage(rcs);
			delimage(rms);
			delimage(rxs);
			delimage(rss);
			delimage(rjs);
			delimage(rbs);
			delimage(rps);
			delimage(bcs);
			delimage(bms);
			delimage(bxs);
			delimage(bss);
			delimage(bjs);
			delimage(bbs);
			delimage(bps);
			delimage(fqs);
		}
		if (sound) {
			music.OpenFile("media/ta.wav");
		}
		else {
			music.Close();
		}
	}
	
	
	fclose(fp);
}

void setting() {
	FILE* fp;
	cleardevice();
	putimage(0, 0, bj);
	setfont(60, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(100, 50, "设      置");
	int x = 0;
	int y = 0;
	char ch[15] = {};
	setfont(30, 0, "隶书");
	if ((fp = fopen("user.dat", "r")) == NULL) {
		window("警告：", "找不到配置文件!!", "");
		menu();
	}
	else {
		fseek(fp, 70, SEEK_SET);//70+13
		fgets(ch, 15, fp);
		xyprintf(50, 150, "%c%c%c%c",ch[1],ch[2],ch[3],ch[4]);
		if (ch[0]=='$') {
			xyprintf(120, 150, "：开启");
		}
		else if (ch[0] == '%') {
			xyprintf(120, 150, "：关闭");
		}
		else {
			cleardevice();
			putimage(0, 0, bj);
			window("警告：", "读取配置文件失败!!", "");
			fclose(fp);
			remove("user.dat");
			menu();
		}
		fseek(fp, 83, SEEK_SET);//70+13
		fgets(ch, 15, fp);
		xyprintf(50, 180, "%c%c%c%c", ch[1], ch[2], ch[3], ch[4]);
		if (ch[0] == '$') {
			xyprintf(120, 180, "：开启");//+30
		}
		else if (ch[0] == '%') {
			xyprintf(120, 180, "：关闭");
		}
		else {
			cleardevice();
			putimage(0, 0, bj);
			window("警告：", "读取配置文件失败!!", "");
			fclose(fp);
			remove("user.dat");
			menu();
		}
		fseek(fp, 96, SEEK_SET);//70+13
		fgets(ch, 15, fp);
		xyprintf(50, 210, "%c%c%c%c", ch[1], ch[2], ch[3], ch[4]);
		if (ch[0] == '$') {
			xyprintf(120, 210, "：使用更多的内存以提速");//+30
		}
		else if (ch[0] == '%') {
			xyprintf(120, 210, "：占用较少的内存");
		}
		else {
			cleardevice();
			putimage(0, 0, bj);
			window("警告：", "读取配置文件失败!!", "");
			fclose(fp);
			remove("user.dat");
			menu();
		}
		
		setcolor(BLACK);
		setbkmode(TRANSPARENT);
		setfont(30, 0, "隶书");
		xyprintf(9.5 * QZ, 15 * QZ, "退出");
		for (; is_run(); delay_fps(60)) {
			mouse_msg msg = getmouse();
			x = msg.x;
			y = msg.y;
			if (msg.is_left() && msg.is_down()) {
				if (x >= 350 && x <= 410 && y >= 560 && y <= 580) {
					fclose(fp);
					menu();
				}
			}
		}
	}
}

void frun(int t) {
	int a;
	int b;
	int p = 0;
	if (t == 1) {//选择移动的地方
		for (; is_run(); delay_fps(60)) {
			while (mousemsg()) {
				mouse_msg msg = getmouse();
				a = msg.x;
				b = msg.y;
				if (msg.is_left() && msg.is_down()) {
					if (a >= 55 && a <= 390 && b >= 130 && b <= 500) {
						a = (a - (1.5 * QZ)) / QZ;
						b = (b - (3.5 * QZ)) / QZ;
						for (int i = 0; i < c; i++) {
							if (x1[i] == a && y1[i] == b) {
								p = 1;
							}
						}
						if (p) {
							cx = a;
							cy = b;
							if (temp && fbroad[y][x][0] == -fbroad[cy][cx][0]) {
								if (sound) {
									music.Play(0);
								}
								fbroad[y][x][0] = 0;
								fbroad[cy][cx][0] = 0;
								fplay();
								temp = 0;
							}
							else {
								if (sound) {
									music.Play(0);
								}
								fbroad[cy][cx][0] = fbroad[y][x][0];
								fbroad[y][x][0] = 0;
								c = 0;
								fplay();
							}
						}
						else {
							player = -player;
							fplay();
						}
					}
					else {
						player = -player;
						fplay();
					}
				}
			}
		}
	}
}

void fclean() {
	memset(fbroad, 0, sizeof(fbroad));
	memset(x1, 0, sizeof(x1));
	memset(y1, 0, sizeof(y1));
	c = 0;
	temp = 0;
	t = true;
	player = 0;
	srand(time(NULL));
	int j = 0;
	int k = 0;
	for (int t = 0; t < 9; t++) {
		for (int i = 0; i < 10; i++) {
			while (1) {
				j = rand() % 8;
				if (j != 0) {
					break;
				}
			}
			k = rand() % 2;
			if (k == 0) {
				k = 1;
			}
			else if (k == 1) {
				k = -1;
			}
			fbroad[i][t][0] = j * k;
		}
	}
	
}

void fdraw() {
	cleardevice();
	putimage(0, 0, bj);
	if (xianz) {
		if (!t) {
			if (player == 1) {
				setfont(20, 0, "华文隶书");
				setbkmode(TRANSPARENT);
				xyprintf(9, 14.5 * QZ, "状态：现在是红棋走");
			}
			else if (player == -1) {
				setfont(20, 0, "华文隶书");
				setbkmode(TRANSPARENT);
				xyprintf(9, 14.5 * QZ, "状态：现在是黑棋走");
			}
		}
	}
	setfont(40, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(18, 9, "模式：翻棋对弈");
	setfont(30, 0, "华文隶书");
	xyprintf(7 * QZ, 15.2 * QZ, "返回主界面");
	xyprintf(7.5 * QZ, 14.2 * QZ, "重新开始");
	setfillcolor(EGEARGB(0xFF, 0xDB, 0xDA, 0x7D));//深黄色
	ege_fillrect(1.5 * QZ, 3.5 * QZ, 9 * QZ, 10 * QZ);
	//bar(2 * QZ, 4 * QZ, 10 * QZ, 13 * QZ);
	setlinewidth(4);
	rectangle(1.4 * QZ, 3.4 * QZ, 10.7 * QZ, 13.7 * QZ);
	setlinewidth(1);
	setcolor(BLACK);
	for (int i = 0; i < QZ * 10; i += QZ) {
		line(2 * QZ, 4 * QZ + i, 10 * QZ, 4 * QZ + i);
	}
	for (int i = 0; i < QZ * 9; i += QZ) {
		if (i == 0) {
			line(2 * QZ, 8 * QZ, 2 * QZ, 9 * QZ);
			line(10 * QZ, 8 * QZ, 10 * QZ + i, 9 * QZ);
		}
		line(2 * QZ + i, 4 * QZ, 2 * QZ + i, 8 * QZ);
		line(2 * QZ + i, 9 * QZ, 2 * QZ + i, 13 * QZ);
	}
	line(5 * QZ, 4 * QZ, 7 * QZ, 6 * QZ);
	line(7 * QZ, 4 * QZ, 5 * QZ, 6 * QZ);
	line(5 * QZ, 11 * QZ, 7 * QZ, 13 * QZ);
	line(7 * QZ, 11 * QZ, 5 * QZ, 13 * QZ);
	for (int t = 0; t < 9; t++) {
		for (int i = 0; i < 10; i++) {
			if (fbroad[i][t][1]) {
				if (fbroad[i][t][0] == 0) {
					continue;
				}
				else if (fbroad[i][t][0] == 1) {
					getimage(qi, "img/红车.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == 2) {
					getimage(qi, "img/红马.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == 3) {
					getimage(qi, "img/红相.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == 4) {
					getimage(qi, "img/红士.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == 5) {
					getimage(qi, "img/红帅.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == 6) {
					getimage(qi, "img/红兵.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == 7) {
					getimage(qi, "img/红炮.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == -1) {
					getimage(qi, "img/黑车.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == -2) {
					getimage(qi, "img/黑马.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == -3) {
					getimage(qi, "img/黑象.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == -4) {
					getimage(qi, "img/黑士.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == -5) {
					getimage(qi, "img/黑将.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == -6) {
					getimage(qi, "img/黑卒.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
				else if (fbroad[i][t][0] == -7) {
					getimage(qi, "img/黑炮.bmp");
					putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
					continue;
				}
			}
			else {
				getimage(qi, "img/翻棋.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
		}
	}
}

void fplay() {//0为选项，1为翻棋
	if (patton) {
		fdraws();
	}
	else {
		fdraw();
	}
	int a;
	int b;
	while (1) {
		for (; is_run(); delay_fps(60)) {
			while (mousemsg()) {
				mouse_msg msg = getmouse();
				if (msg.is_left() && msg.is_down()) {
					a = msg.x;
					b = msg.y;
					if (a >= 280 && a <= 400 && b >= 530 && b <= 550) {
						if (window("你真的要重新吗？", "", "")) {
							fclean();
							if (patton) {
								fdraws();
							}
							else {
								fdraw();
							}
							break;
						}
						else {
							if (patton) {
								fdraws();
							}
							else {
								fdraw();
							}
						}
					}
					if (a >= 260 && a <= 405 && b >= 560 && b <= 585) {
						if (window("你真的要返回主界面吗？", "你的状态将不会保存！！", "")) {
							menu();
							break;
						}
						else {
							if (patton) {
								fdraws();
							}
							else {
								fdraw();
							}
						}
					}
					if (a >= 55 && a <= 390 && b >= 130 && b <= 500) {//如果在棋盘内
						a = (a - (1.5 * QZ)) / QZ;
						b = (b - (3.5 * QZ)) / QZ;
						if (fbroad[b][a][1] == 0) {//如果是未翻的棋
							fbroad[b][a][1] = 1;
							if (t) {
								if (fbroad[b][a][0] < 0) {
									player = -1;
									t = false;
								}
								if (fbroad[b][a][0] > 0) {
									player = 1;
									t = false;
								}
							}
							player = -player;
							if (patton) {
								fdraws();
							}
							else {
								fdraw();
							}
						}
						else if (fbroad[b][a][1] == 1) {//如果是翻了的棋
							x = a;
							y = b;
							if (fbroad[y][x][0] == 0) {
								fplay();
							}
							if (fbroad[y][x][0] > 0) {//如果是红棋
								if (xianz) {
									if (player == 1) {
										player = -1;
									}
									else {
										fplay();
									}
								}
								if (fbroad[y][x][0] == 1) {//如果是红车
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (fbroad[y - 1][x][1] == 1) {
										if (y - 1 >= 0 && (fbroad[y - 1][x][0] == -6 || fbroad[y - 1][x][0] == -2 || fbroad[y - 1][x][0] == -7 || fbroad[y - 1][x][0] == -1 || fbroad[y - 1][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y - 1;
											c++;
										}
										if (y - 2 >= 0 && fbroad[y - 2][x][1] == 1 && (fbroad[y - 2][x][0] == -6 || fbroad[y - 2][x][0] == -2 || fbroad[y - 2][x][0] == -7 || fbroad[y - 2][x][0] == -1 || fbroad[y - 2][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y - 2;
											c++;
										}
									}
									if (fbroad[y + 1][x][1] == 1) {
										if (y + 1 <= 9 && (fbroad[y + 1][x][0] == -6 || fbroad[y + 1][x][0] == -2 || fbroad[y + 1][x][0] == -7 || fbroad[y + 1][x][0] == -1 || fbroad[y + 1][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y + 1;
											c++;
										}
										if (y + 2 <= 9 && fbroad[y + 2][x][1] == 1 && (fbroad[y + 2][x][0] == -6 || fbroad[y + 2][x][0] == -2 || fbroad[y + 2][x][0] == -7 || fbroad[y + 2][x][0] == -1 || fbroad[y + 2][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y + 2;
											c++;
										}
									}
									if (fbroad[y][x - 1][1] == 1) {
										if (x - 1 >= 0 && (fbroad[y][x - 1][0] == -6 || fbroad[y][x - 1][0] == -2 || fbroad[y][x - 1][0] == -7 || fbroad[y][x - 1][0] == -1 || fbroad[y][x - 1][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x - 1;
											y1[c] = y;
											c++;
										}
										if (x - 2 >= 0 && fbroad[y][x - 2][1] == 1 && (fbroad[y][x - 2][0] == -6 || fbroad[y][x - 2][0] == -2 || fbroad[y][x - 2][0] == -7 || fbroad[y][x - 2][0] == -1 || fbroad[y][x - 2][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x - 2;
											y1[c] = y;
											c++;
										}
									}
									if (fbroad[y][x + 1][1] == 1) {
										if (x + 1 <= 8 && (fbroad[y][x + 1][0] == -6 || fbroad[y][x + 1][0] == -2 || fbroad[y][x + 1][0] == -7 || fbroad[y][x + 1][0] == -1 || fbroad[y][x + 1][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x + 1;
											y1[c] = y;
											c++;
										}
										if (x + 2 <= 8 && fbroad[y][x + 2][1] == 1 && (fbroad[y][x + 2][0] == -6 || fbroad[y][x + 2][0] == -2 || fbroad[y][x + 2][0] == -7 || fbroad[y][x + 2][0] == -1 || fbroad[y][x + 2][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x + 2;
											y1[c] = y;
											c++;
										}
									}
								}
								if (fbroad[y][x][0] == 2) {//如果是红马
									temp = 0;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (x + 1 <= 8 && y + 1 <= 9 && fbroad[y + 1][x + 1][1] == 1 && fbroad[y + 1][x + 1][0] <= 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y + 1;
										c++;
									}
									if (x + 1 <= 8 && y - 1 >= 0 && fbroad[y - 1][x + 1][1] == 1 && fbroad[y - 1][x + 1][0] <= 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y - 1;
										c++;
									}
									if (x - 1 >= 0 && y + 1 <= 9 && fbroad[y + 1][x - 1][1] == 1 && fbroad[y + 1][x - 1][0] <= 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y + 1;
										c++;
									}
									if (x - 1 >= 0 && y - 1 >= 0 && fbroad[y - 1][x - 1][1] == 1 && fbroad[y - 1][x - 1][0] <= 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y - 1;
										c++;
									}
								}
								if (fbroad[y][x][0] == 3) {//如果是红象
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (x + 1 <= 8 && y + 1 <= 9 && fbroad[y + 1][x + 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y + 1;
										c++;
									}
									if (x + 1 <= 8 && y - 1 >= 0 && fbroad[y - 1][x + 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y - 1;
										c++;
									}
									if (x - 1 >= 0 && y + 1 <= 9 && fbroad[y + 1][x - 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y + 1;
										c++;
									}
									if (x - 1 >= 0 && y - 1 >= 0 && fbroad[y - 1][x - 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y - 1;
										c++;
									}
									if (fbroad[y - 1][x][1] == 1) {
										if (y - 1 >= 0 && (fbroad[y - 1][x][0] == -1 || fbroad[y - 1][x][0] == -2 || fbroad[y - 1][x][0] == -6 || fbroad[y - 1][x][0] == -7 || fbroad[y - 1][x][0] == -3 || fbroad[y - 1][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y - 1;
											c++;
										}
									}
									if (fbroad[y + 1][x][1] == 1) {
										if (y + 1 <= 9 && (fbroad[y + 1][x][0] == -1 || fbroad[y + 1][x][0] == -2 || fbroad[y + 1][x][0] == -6 || fbroad[y + 1][x][0] == -7 || fbroad[y + 1][x][0] == -3 || fbroad[y + 1][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y + 1;
											c++;
										}
									}
									if (fbroad[y][x - 1][1] == 1) {
										if (x - 1 >= 0 && (fbroad[y][x - 1][0] == -1 || fbroad[y][x - 1][0] == -2 || fbroad[y][x - 1][0] == -6 || fbroad[y][x - 1][0] == -7 || fbroad[y][x - 1][0] == -3 || fbroad[y][x - 1][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x - 1;
											y1[c] = y;
											c++;
										}
									}
									if (fbroad[y][x + 1][1] == 1) {
										if (x + 1 <= 8 && (fbroad[y][x + 1][0] == -1 || fbroad[y][x + 1][0] == -2 || fbroad[y][x + 1][0] == -6 || fbroad[y][x + 1][0] == -7 || fbroad[y][x + 1][0] == -3 || fbroad[y][x + 1][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x + 1;
											y1[c] = y;
											c++;
										}
									}
								}
								if (fbroad[y][x][0] == 4) {//如果是红士
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (y + 1 <= 9 && fbroad[y + 1][x][1] == 1 && fbroad[y + 1][x][0] <= 0 && fbroad[y + 1][x][0] != -5) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y + 1;
										c++;
									}
									if (y - 1 >= 0 && fbroad[y - 1][x][1] == 1 && fbroad[y - 1][x][0] <= 0 && fbroad[y - 1][x][0] != -5) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y - 1;
										c++;
									}
									if (x + 1 <= 8 && fbroad[y][x + 1][1] == 1 && fbroad[y][x + 1][0] <= 0 && fbroad[y][x + 1][0] != -5) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y;
										c++;
									}
									if (x - 1 >= 0 && fbroad[y][x - 1][1] == 1 && fbroad[y][x - 1][0] <= 0 && fbroad[y][x - 1][0] != -5) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y;
										c++;
									}
								}
								if (fbroad[y][x][0] == 5) {//如果是红帅
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (y + 1 <= 9 && fbroad[y + 1][x][1] == 1 && fbroad[y + 1][x][0] <= 0 && fbroad[y + 1][x][0] != -6) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y + 1;
										c++;
									}
									if (y - 1 >= 0 && fbroad[y - 1][x][1] == 1 && fbroad[y - 1][x][0] <= 0 && fbroad[y - 1][x][0] != -6) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y - 1;
										c++;
									}
									if (x + 1 <= 8 && fbroad[y][x + 1][1] == 1 && fbroad[y][x + 1][0] <= 0 && fbroad[y][x + 1][0] != -6) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y;
										c++;
									}
									if (x - 1 >= 0 && fbroad[y][x - 1][1] == 1 && fbroad[y][x - 1][0] <= 0 && fbroad[y][x - 1][0] != -6) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y;
										c++;
									}
								}
								if (fbroad[y][x][0] == 6) {//如果是红兵
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (y + 1 <= 9 && fbroad[y + 1][x][1] == 1 && fbroad[y + 1][x][0] <= 0 && (fbroad[y + 1][x][0] == -5 || fbroad[y + 1][x][0] == -6 || fbroad[y + 1][x][0] == 0)) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y + 1;
										c++;
									}
									if (y - 1 >= 0 && fbroad[y - 1][x][1] == 1 && fbroad[y - 1][x][0] <= 0 && (fbroad[y - 1][x][0] == -5 || fbroad[y - 1][x][0] == -6 || fbroad[y - 1][x][0] == 0)) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y - 1;
										c++;
									}
									if (x + 1 <= 8 && fbroad[y][x + 1][1] == 1 && fbroad[y][x + 1][0] <= 0 && (fbroad[y][x + 1][0] == -5 || fbroad[y][x + 1][0] == -6 || fbroad[y][x + 1][0] == 0)) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y;
										c++;
									}
									if (x - 1 >= 0 && fbroad[y][x - 1][1] == 1 && fbroad[y][x - 1][0] <= 0 && (fbroad[y][x - 1][0] == -5 || fbroad[y][x - 1][0] == -6 || fbroad[y][x - 1][0] == 0)) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y;
										c++;
									}
								}
								if (fbroad[y][x][0] == 7) {//如果是红炮
									temp = 0;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (y + 1 <= 9 && fbroad[y + 1][x][1] == 1 && fbroad[y + 1][x][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y + 1;
										c++;
									}
									if (y - 1 >= 0 && fbroad[y - 1][x][1] == 1 && fbroad[y - 1][x][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y - 1;
										c++;
									}
									if (x + 1 <= 8 && fbroad[y][x + 1][1] == 1 && fbroad[y][x + 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y;
										c++;
									}
									if (x - 1 >= 0 && fbroad[y][x - 1][1] == 1 && fbroad[y][x - 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y;
										c++;
									}
									for (int i = 1; i < 10; i++) {//竖上
										if (fbroad[y - i][x][0] != 0 && y - i + 1 != 0 && y - i >= 0) {
											for (int t = 1; t < 10; t++) {
												if (fbroad[y - i - t][x][0] > 0) {
													break;
												}
												if (fbroad[y - i - t][x][0] < 0 && y - i + 1 != 0 && fbroad[y - i - t][x][1] == 1) {
													setfillcolor(EGEACOLOR(0xFF, BLACK));
													ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i - t) * QZ - 5, 10, 10);
													x1[c] = x;
													y1[c] = y - i - t;
													c++;
													break;
												}
											}
											break;
										}
									}
									for (int i = 1; i < 10; i++) {//竖下
										if (fbroad[y + i][x][0] != 0 && y + i - 1 != 9) {
											for (int t = 1; t < 10; t++) {
												if (fbroad[y + i + t][x][0] > 0) {
													break;
												}
												if (fbroad[y + i + t][x][0] < 0 && y + i - 1 != 9 && (y + i + t) <= 9 && fbroad[y + i + t][x][1] == 1) {
													setfillcolor(EGEACOLOR(0xFF, BLACK));
													ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i + t) * QZ - 5, 10, 10);
													x1[c] = x;
													y1[c] = y + i + t;
													c++;
													break;
												}
											}
											break;
										}
									}
									for (int i = 1; i < 11; i++) {//横左
										if (fbroad[y][x - i][0] != 0 && x - i + 1 != 0) {
											for (int t = 1; t < 10; t++) {
												if (fbroad[y][x - i - t][0] > 0) {
													break;
												}
												if (fbroad[y][x - i - t][0] < 0 && x - i + 1 != 0 && (x - i - t) >= 0 && fbroad[y][x - i - t][1] == 1) {
													setfillcolor(EGEACOLOR(0xFF, BLACK));
													ege_fillellipse(2 * QZ + (x - i - t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
													x1[c] = x - i - t;
													y1[c] = y;
													c++;
													break;
												}
											}
											break;
										}
									}
									for (int i = 1; i < 11; i++) {//横右
										if (fbroad[y][x + i][0] != 0 && x + i - 1 != 8) {
											for (int t = 1; t < 10; t++) {
												if (fbroad[y][x + i + t][0] > 0) {
													break;
												}
												if (fbroad[y][x + i + t][0] < 0 && x + i - 1 != 8 && (x + i + t) <= 9 && fbroad[y][x + i + t][1] == 1) {
													setfillcolor(EGEACOLOR(0xFF, BLACK));
													ege_fillellipse(2 * QZ + (x + i + t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
													x1[c] = x + i + t;
													y1[c] = y;
													c++;
													break;
												}
											}
											break;
										}
									}
								}
							}
							if (fbroad[y][x][0] < 0) {//如果是黑棋
								if (xianz) {
									if (player == -1) {
										player = 1;
									}
									else {
										fplay();
									}
								}
								if (fbroad[y][x][0] == -1) {//如果是黑车
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (fbroad[y - 1][x][1] == 1) {
										if (y - 1 >= 0 && (fbroad[y - 1][x][0] == 6 || fbroad[y - 1][x][0] == 2 || fbroad[y - 1][x][0] == 7 || fbroad[y - 1][x][0] == 1 || fbroad[y - 1][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y - 1;
											c++;
										}
										if (y - 2 >= 0 && fbroad[y - 2][x][1] == 1 && (fbroad[y - 2][x][0] == 6 || fbroad[y - 2][x][0] == 2 || fbroad[y - 2][x][0] == 7 || fbroad[y - 2][x][0] == 1 || fbroad[y - 2][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y - 2;
											c++;
										}
									}
									if (fbroad[y + 1][x][1] == 1) {
										if (y + 1 <= 9 && (fbroad[y + 1][x][0] == 6 || fbroad[y + 1][x][0] == 2 || fbroad[y + 1][x][0] == 7 || fbroad[y + 1][x][0] == 1 || fbroad[y + 1][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y + 1;
											c++;
										}
										if (y + 2 <= 9 && fbroad[y + 2][x][1] == 1 && (fbroad[y + 2][x][0] == 6 || fbroad[y + 2][x][0] == 2 || fbroad[y + 2][x][0] == 7 || fbroad[y + 2][x][0] == 1 || fbroad[y + 2][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y + 2;
											c++;
										}
									}
									if (fbroad[y][x - 1][1] == 1) {
										if (x - 1 >= 0 && (fbroad[y][x - 1][0] == 6 || fbroad[y][x - 1][0] == 2 || fbroad[y][x - 1][0] == 7 || fbroad[y][x - 1][0] == 1 || fbroad[y][x - 1][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x - 1;
											y1[c] = y;
											c++;
										}
										if (x - 2 >= 0 && fbroad[y][x - 2][1] == 1 && (fbroad[y][x - 2][0] == 6 || fbroad[y][x - 2][0] == 2 || fbroad[y][x - 2][0] == 7 || fbroad[y][x - 2][0] == 1 || fbroad[y][x - 2][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x - 2;
											y1[c] = y;
											c++;
										}
									}
									if (fbroad[y][x + 1][1] == 1) {
										if (x + 1 <= 8 && (fbroad[y][x + 1][0] == 6 || fbroad[y][x + 1][0] == 2 || fbroad[y][x + 1][0] == 7 || fbroad[y][x + 1][0] == 1 || fbroad[y][x + 1][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x + 1;
											y1[c] = y;
											c++;
										}
										if (x + 2 <= 8 && fbroad[y][x + 2][1] == 1 && (fbroad[y][x + 2][0] == 6 || fbroad[y][x + 2][0] == 2 || fbroad[y][x + 2][0] == 7 || fbroad[y][x + 2][0] == 1 || fbroad[y][x + 2][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x + 2;
											y1[c] = y;
											c++;
										}
									}
								}
								if (fbroad[y][x][0] == -2) {//如果是黑马
									temp = 0;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (x + 1 <= 8 && y + 1 <= 9 && fbroad[y + 1][x + 1][1] == 1 && fbroad[y + 1][x + 1][0] >= 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y + 1;
										c++;
									}
									if (x + 1 <= 8 && y - 1 >= 0 && fbroad[y - 1][x + 1][1] == 1 && fbroad[y - 1][x + 1][0] >= 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y - 1;
										c++;
									}
									if (x - 1 >= 0 && y + 1 <= 9 && fbroad[y + 1][x - 1][1] == 1 && fbroad[y + 1][x - 1][0] >= 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y + 1;
										c++;
									}
									if (x - 1 >= 0 && y - 1 >= 0 && fbroad[y - 1][x - 1][1] == 1 && fbroad[y - 1][x - 1][0] >= 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y - 1;
										c++;
									}
								}
								if (fbroad[y][x][0] == -3) {//如果是黑象
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (x + 1 <= 8 && y + 1 <= 9 && fbroad[y + 1][x + 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y + 1;
										c++;
									}
									if (x + 1 <= 8 && y - 1 >= 0 && fbroad[y - 1][x + 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y - 1;
										c++;
									}
									if (x - 1 >= 0 && y + 1 <= 9 && fbroad[y + 1][x - 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y + 1;
										c++;
									}
									if (x - 1 >= 0 && y - 1 >= 0 && fbroad[y - 1][x - 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y - 1;
										c++;
									}
									if (fbroad[y - 1][x][1] == 1) {
										if (y - 1 >= 0 && (fbroad[y - 1][x][0] == 1 || fbroad[y - 1][x][0] == 2 || fbroad[y - 1][x][0] == 6 || fbroad[y - 1][x][0] == 7 || fbroad[y - 1][x][0] == 3 || fbroad[y - 1][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y - 1;
											c++;
										}
									}
									if (fbroad[y + 1][x][1] == 1) {
										if (y + 1 <= 9 && (fbroad[y + 1][x][0] == 1 || fbroad[y + 1][x][0] == 2 || fbroad[y + 1][x][0] == 6 || fbroad[y + 1][x][0] == 7 || fbroad[y + 1][x][0] == 3 || fbroad[y + 1][x][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y + 1;
											c++;
										}
									}
									if (fbroad[y][x - 1][1] == 1) {
										if (x - 1 >= 0 && (fbroad[y][x - 1][0] == 1 || fbroad[y][x - 1][0] == 2 || fbroad[y][x - 1][0] == 6 || fbroad[y][x - 1][0] == 7 || fbroad[y][x - 1][0] == 3 || fbroad[y][x - 1][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x - 1;
											y1[c] = y;
											c++;
										}
									}
									if (fbroad[y][x + 1][1] == 1) {
										if (x + 1 <= 8 && (fbroad[y][x + 1][0] == 1 || fbroad[y][x + 1][0] == 2 || fbroad[y][x + 1][0] == 6 || fbroad[y][x + 1][0] == 7 || fbroad[y][x + 1][0] == 3 || fbroad[y][x + 1][0] == 0)) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x + 1;
											y1[c] = y;
											c++;
										}
									}
								}
								if (fbroad[y][x][0] == -4) {//如果是黑士
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (y + 1 <= 9 && fbroad[y + 1][x][1] == 1 && fbroad[y + 1][x][0] >= 0 && fbroad[y + 1][x][0] != 5) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y + 1;
										c++;
									}
									if (y - 1 >= 0 && fbroad[y - 1][x][1] == 1 && fbroad[y - 1][x][0] >= 0 && fbroad[y - 1][x][0] != 5) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y - 1;
										c++;
									}
									if (x + 1 <= 8 && fbroad[y][x + 1][1] == 1 && fbroad[y][x + 1][0] >= 0 && fbroad[y][x + 1][0] != 5) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y;
										c++;
									}
									if (x - 1 >= 0 && fbroad[y][x - 1][1] == 1 && fbroad[y][x - 1][0] >= 0 && fbroad[y][x - 1][0] != 5) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y;
										c++;
									}
								}
								if (fbroad[y][x][0] == -5) {//如果是黑将
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (y + 1 <= 9 && fbroad[y + 1][x][1] == 1 && fbroad[y + 1][x][0] >= 0 && fbroad[y + 1][x][0] != 6) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y + 1;
										c++;
									}
									if (y - 1 >= 0 && fbroad[y - 1][x][1] == 1 && fbroad[y - 1][x][0] >= 0 && fbroad[y - 1][x][0] != 6) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y - 1;
										c++;
									}
									if (x + 1 <= 8 && fbroad[y][x + 1][1] == 1 && fbroad[y][x + 1][0] >= 0 && fbroad[y][x + 1][0] != 6) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y;
										c++;
									}
									if (x - 1 >= 0 && fbroad[y][x - 1][1] == 1 && fbroad[y][x - 1][0] >= 0 && fbroad[y][x - 1][0] != 6) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y;
										c++;
									}
								}
								if (fbroad[y][x][0] == -6) {//如果是黑兵
									temp = 1;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (y + 1 <= 9 && fbroad[y + 1][x][1] == 1 && fbroad[y + 1][x][0] >= 0 && (fbroad[y + 1][x][0] == 5 || fbroad[y + 1][x][0] == 6 || fbroad[y + 1][x][0] == 0)) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y + 1;
										c++;
									}
									if (y - 1 >= 0 && fbroad[y - 1][x][1] == 1 && fbroad[y - 1][x][0] >= 0 && (fbroad[y - 1][x][0] == 5 || fbroad[y - 1][x][0] == 6 || fbroad[y - 1][x][0] == 0)) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y - 1;
										c++;
									}
									if (x + 1 <= 8 && fbroad[y][x + 1][1] == 1 && fbroad[y][x + 1][0] >= 0 && (fbroad[y][x + 1][0] == 5 || fbroad[y][x + 1][0] == 6 || fbroad[y][x + 1][0] == 0)) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y;
										c++;
									}
									if (x - 1 >= 0 && fbroad[y][x - 1][1] == 1 && fbroad[y][x - 1][0] >= 0 && (fbroad[y][x - 1][0] == 5 || fbroad[y][x - 1][0] == 6 || fbroad[y][x - 1][0] == 0)) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y;
										c++;
									}
								}
								if (fbroad[y][x][0] == -7) {//如果是黑炮
									temp = 0;
									setlinewidth(2);
									rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
									if (y + 1 <= 9 && fbroad[y + 1][x][1] == 1 && fbroad[y + 1][x][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y + 1;
										c++;
									}
									if (y - 1 >= 0 && fbroad[y - 1][x][1] == 1 && fbroad[y - 1][x][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
										x1[c] = x;
										y1[c] = y - 1;
										c++;
									}
									if (x + 1 <= 8 && fbroad[y][x + 1][1] == 1 && fbroad[y][x + 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x + 1;
										y1[c] = y;
										c++;
									}
									if (x - 1 >= 0 && fbroad[y][x - 1][1] == 1 && fbroad[y][x - 1][0] == 0) {
										setfillcolor(EGEACOLOR(0xFF, BLACK));
										ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
										x1[c] = x - 1;
										y1[c] = y;
										c++;
									}
									for (int i = 1; i < 10; i++) {//竖上
										if (fbroad[y - i][x][0] != 0 && y - i + 1 != 0 && y - i >= 0) {
											for (int t = 1; t < 10; t++) {
												if (fbroad[y - i - t][x][0] < 0) {
													break;
												}
												if (fbroad[y - i - t][x][0] > 0 && y - i + 1 != 0 && fbroad[y - i - t][x][1] == 1) {
													setfillcolor(EGEACOLOR(0xFF, BLACK));
													ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i - t) * QZ - 5, 10, 10);
													x1[c] = x;
													y1[c] = y - i - t;
													c++;
													break;
												}
											}
											break;
										}
									}
									for (int i = 1; i < 10; i++) {//竖下
										if (fbroad[y + i][x][0] != 0 && y + i - 1 != 9) {
											for (int t = 1; t < 10; t++) {
												if (fbroad[y + i + t][x][0] < 0) {
													break;
												}
												if (fbroad[y + i + t][x][0] > 0 && y + i - 1 != 9 && (y + i + t) <= 9 && fbroad[y + i + t][x][1] == 1) {
													setfillcolor(EGEACOLOR(0xFF, BLACK));
													ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i + t) * QZ - 5, 10, 10);
													x1[c] = x;
													y1[c] = y + i + t;
													c++;
													break;
												}
											}
											break;
										}
									}
									for (int i = 1; i < 11; i++) {//横左
										if (fbroad[y][x - i][0] != 0 && x - i + 1 != 0) {
											for (int t = 1; t < 10; t++) {
												if (fbroad[y][x - i - t][0] < 0) {
													break;
												}
												if (fbroad[y][x - i - t][0] > 0 && x - i + 1 != 0 && (x - i - t) >= 0 && fbroad[y][x - i - t][1] == 1) {
													setfillcolor(EGEACOLOR(0xFF, BLACK));
													ege_fillellipse(2 * QZ + (x - i - t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
													x1[c] = x - i - t;
													y1[c] = y;
													c++;
													break;
												}
											}
											break;
										}
									}
									for (int i = 1; i < 11; i++) {//横右
										if (fbroad[y][x + i][0] != 0 && x + i - 1 != 8) {
											for (int t = 1; t < 10; t++) {
												if (fbroad[y][x + i + t][0] < 0) {
													break;
												}
												if (fbroad[y][x + i + t][0] > 0 && x + i - 1 != 8 && (x + i + t) <= 9 && fbroad[y][x + i + t][1] == 1) {
													setfillcolor(EGEACOLOR(0xFF, BLACK));
													ege_fillellipse(2 * QZ + (x + i + t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
													x1[c] = x + i + t;
													y1[c] = y;
													c++;
													break;
												}
											}
											break;
										}
									}
								}
								
							}
							frun(1);
						}
					}
				}
			}
		}
	}
}

void play() {
	if (patton) {
		draws();
	}
	else {
		draw();
	}
	click();
}

int window(const char text1[12],const char text2[12],const char text3[12]) {
	PIMAGE title = newimage();
	int x = 0;
	int y = 0;
	getimage(title, "img/title.bmp");
	putimage(1.25 * QZ, 5 * QZ, title);
	setfont(25, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(2 * QZ, 6 * QZ, "%s", text1);
	xyprintf(2 * QZ, 6.5 * QZ, "%s", text2);
	xyprintf(2 * QZ, 7 * QZ, "%s", text3);
	setfont(30, 0, "华文隶书");
	xyprintf(3.5 * QZ, 8 * QZ, "取消");
	xyprintf(7 * QZ, 8 * QZ, "确定");
	for (; is_run(); delay_fps(60)) {
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down()) {
				x = msg.x;
				y = msg.y;
				if (x >= 130 && x <= 190 && y >= 300 && y <= 320) {
					return 0;
				}
				if (x >= 260 && x <= 320 && y >= 300 && y <= 320) {
					return 1;
				}
			}
		}
	}
}

int window(const char text1[12], const char text2[12], const char text3[12], const char no[2], const char yes[2]) {
	PIMAGE title = newimage();
	int x = 0;
	int y = 0;
	getimage(title, "img/title.bmp");
	putimage(1.25 * QZ, 5 * QZ, title);
	setfont(25, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(2 * QZ, 6 * QZ, "%s", text1);
	xyprintf(2 * QZ, 6.5 * QZ, "%s", text2);
	xyprintf(2 * QZ, 7 * QZ, "%s", text3);
	setfont(30, 0, "华文隶书");
	xyprintf(3.5 * QZ, 8 * QZ, "%s", no);
	xyprintf(7 * QZ, 8 * QZ, "%s", yes);
	for (; is_run(); delay_fps(60)) {
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			if (msg.is_left() && msg.is_down()) {
				x = msg.x;
				y = msg.y;
				if (x >= 130 && x <= 190 && y >= 300 && y <= 320) {
					return 0;
				}
				if (x >= 260 && x <= 320 && y >= 300 && y <= 320) {
					return 1;
				}
			}
		}
	}
}

int window(const char text1[12], const char text2[12], const char no[2], const char yes[2]) {
	PIMAGE title = newimage();
	int x = 0;
	int y = 0;
	getimage(title, "img/title.bmp");
	putimage(1.25 * QZ, 5 * QZ, title);
	setfont(25, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(2 * QZ, 6 * QZ, "%s", text1);
	xyprintf(2 * QZ, 6.5 * QZ, "%s", text2);
	setfont(30, 0, "华文隶书");
	xyprintf(3.5 * QZ, 8 * QZ, "%s", no);
	xyprintf(7 * QZ, 8 * QZ, "%s", yes);
	return 0;
}

int run(int t) {
	int p = 0;
	if (t == 2) {
		temp = 0;
		if (broad[y][x] != broad[cy][cx]) {
			for (int i = 0; i < c; i++) {
				if (x1[i] == cx && y1[i] == cy) {
					p = 1;
				}
			}
			if (p) {
				if (sound) {
					music.Play(0);
				}
				broad[cy][cx] = broad[y][x];
				broad[y][x] = 0;
				c = 0;
				if (patton) {
					draws();
				}
				else {
					draw();
				}
				click();
			}
			else {
				c = 0;
				play();
			}
		}
		else {
			c = 0;
			play();
		}
	}
	
	if (t == 1) {
		temp = 1;
		click();
		return 0;
	}
}

void click() {
	setfont(20, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(9, 14.5 * QZ, "状态：就绪");
	for (; is_run(); delay_fps(60)) {
		while (mousemsg()) {
			//cleardevice();
			mouse_msg msg = getmouse();
			if (msg.is_down() && msg.is_left()) {
				int a;
				int b;
				a = msg.x;
				b = msg.y;
				if (a >= 280 && a <= 400 && b >= 530 && b <= 550) {
					if (window("你真的要重新吗？", "", "")) {
						clean();
						temp = 0;
						if (patton) {
							draws();
						}
						else {
							draw();
						}
						click();
						break;
					}
					else {
						if (patton) {
							draws();
						}
						else {
							draw();
						}
					}
				}
				if (a >= 260 && a <= 405 && b >= 560 && b <= 585) {
					if (window("你真的要返回主界面吗？", "你的状态将不会保存！！", "")) {
						clean();
						temp = 0;
						menu();
						break;
					}
					else {
						if (patton) {
							draws();
						}
						else {
							draw();
						}
					}
				}
				if (temp == 0) {
					x = msg.x;
					y = msg.y;
					x = (x - (1.5 * QZ)) / QZ;
					y = (y - (3.5 * QZ)) / QZ;
					
					if (broad[y][x] > 0) {//如果是红棋
						if (broad[y][x] == 1) {//红车
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							for (int i = 1; i < 10; i++) {//竖上
								if (broad[y - i][x] == 0 && y - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
								}
								else if (broad[y - i][x] < 0 && y - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
									break;
								}
								else break;
							}
							for (int i = 1; i < 10; i++) {//竖下
								if (broad[y + i][x] == 0 && y + i - 1 != 9) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
								}
								else if (broad[y + i][x] < 0 && y + i - 1 != 9) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
									break;
								}
								else break;
							}
							for (int i = 1; i < 11; i++) {//横左
								if (broad[y][x - i] == 0 && x - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - i;
									y1[c] = y;
									c++;
								}
								else if (broad[y][x - i] < 0 && x - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - i;
									y1[c] = y;
									c++;
									break;
								}
								else break;
							}
							for (int i = 1; i < 11; i++) {//横右
								if (broad[y][x + i] == 0 && x + i - 1 != 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + i;
									y1[c] = y;
									c++;
								}
								else if (broad[y][x + i] < 0 && x + i - 1 != 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + i;
									y1[c] = y;
									c++;
									break;
								}
								else break;
							}
						}
						if (broad[y][x] == 2) {//红马
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y - 1][x] == 0) {
								if (broad[y - 2][x + 1] <= 0 && y - 2 >= 0 && x + 1 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x + 1;
									y1[c] = y - 2;
									c++;
								}
								if (broad[y - 2][x - 1] <= 0 && y - 2 >= 0 && x - 1 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x - 1;
									y1[c] = y - 2;
									c++;
								}
								
							}
							if (broad[y + 1][x] == 0) {
								if (broad[y + 2][x + 1] <= 0 && y + 2 <= 9 && x + 1 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x + 1;
									y1[c] = y + 2;
									c++;
								}
								if (broad[y + 2][x - 1] <= 0 && y + 2 <= 9 && x - 1 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x - 1;
									y1[c] = y + 2;
									c++;
								}
								
							}
							if (broad[y][x - 1] == 0) {
								if (broad[y + 1][x - 2] <= 0 && y + 1 <= 9 && x - 2 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y + 1;
									c++;
								}
								if (broad[y - 1][x - 2] <= 0 && y - 1 >= 0 && x - 2 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y - 1;
									c++;
								}
							}
							if (broad[y][x + 1] == 0) {
								if (broad[y + 1][x + 2] <= 0 && y + 1 <= 9 && x + 2 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y + 1;
									c++;
								}
								if (broad[y - 1][x + 2] <= 0 && y - 1 >= 0 && x + 2 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y - 1;
									c++;
								}
							}
						}
						if (broad[y][x] == 3) {//红相
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y - 1][x - 1] == 0 && y - 2 >= 0 && x - 2 >= 0 && y != 5) {
								if (broad[y - 2][x - 2] <= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y - 2;
									c++;
								}
							}
							if (broad[y + 1][x + 1] == 0 && y + 2 <= 9 && x + 2 <= 8) {
								if (broad[y + 2][x + 2] <= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y + 2;
									c++;
								}
							}
							if (broad[y - 1][x + 1] == 0 && y - 2 >= 0 && x + 2 <= 8 && y != 5) {
								if (broad[y - 2][x + 2] <= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y - 2;
									c++;
								}
							}
							if (broad[y + 1][x - 1] == 0 && y + 2 <= 9 && x - 2 >= 0) {
								if (broad[y + 2][x - 2] <= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y + 2;
									c++;
								}
							}
						}
						if (broad[y][x] == 4) {//红士
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y + 1][x + 1] <= 0 && x < 5 && y < 9) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x + 1;
								y1[c] = y + 1;
								c++;
							}
							if (broad[y - 1][x - 1] <= 0 && x > 3 && y > 7) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x - 1;
								y1[c] = y - 1;
								c++;
							}
							if (broad[y + 1][x - 1] <= 0 && x > 3 && y < 9) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x - 1;
								y1[c] = y + 1;
								c++;
							}
							if (broad[y - 1][x + 1] <= 0 && x < 5 && y > 7) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x + 1;
								y1[c] = y - 1;
								c++;
							}
						}
						if (broad[y][x] == 5) {//红帅
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y + 1][x] <= 0 && y < 9) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x;
								y1[c] = y + 1;
								c++;
							}
							if (broad[y - 1][x] <= 0 && y > 7) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x;
								y1[c] = y - 1;
								c++;
							}
							if (broad[y][x + 1] <= 0 && x < 5) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
								x1[c] = x + 1;
								y1[c] = y;
								c++;
							}
							if (broad[y][x - 1] <= 0 && x > 3) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
								x1[c] = x - 1;
								y1[c] = y;
								c++;
							}
							for (int i = 1; i < 11; i++) {
								if (broad[y - i][x] == 0) {
									continue;
								}
								else if (broad[y - i][x] == -5) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
								}
								else break;
								
							}
						}
						if (broad[y][x] == 6) {//红兵
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y - 1][x] <= 0 && y > 0) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x;
								y1[c] = y - 1;
								c++;
							}
							if (y < 5) {
								if (broad[y][x - 1] <= 0 && x > 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - 1;
									y1[c] = y;
									c++;
								}
								if (broad[y][x + 1] <= 0 && x < 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + 1;
									y1[c] = y;
									c++;
								}
							}
						}
						if (broad[y][x] == 7) {//红炮
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							for (int i = 1; i < 10; i++) {//竖上
								if (broad[y - i][x] == 0 && y - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
								}
								else break;
							}
							for (int i = 1; i < 10; i++) {//竖上
								if (broad[y - i][x] != 0 && y - i + 1 != 0 && y - i >= 0) {
									for (int t = 1; t < 10; t++) {
										if (broad[y - i - t][x] > 0) {
											break;
										}
										if (broad[y - i - t][x] < 0 && y - i + 1 != 0) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i - t) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y - i - t;
											c++;
											break;
										}
									}
									break;
								}
							}
							for (int i = 1; i < 10; i++) {//竖下
								if (broad[y + i][x] == 0 && y + i - 1 != 9) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
								}
								else break;
							}
							for (int i = 1; i < 10; i++) {//竖下
								if (broad[y + i][x] != 0 && y + i - 1 != 9) {
									for (int t = 1; t < 10; t++) {
										if (broad[y + i + t][x] > 0) {
											break;
										}
										if (broad[y + i + t][x] < 0 && y + i - 1 != 9 && (y + i + t) <= 9) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i + t) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y + i + t;
											c++;
											break;
										}
									}
									break;
								}
							}
							
							for (int i = 1; i < 11; i++) {//横左
								if (broad[y][x - i] == 0 && x - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - i;
									y1[c] = y;
									c++;
									//break;
								}
								else break;
							}
							for (int i = 1; i < 11; i++) {//横左
								if (broad[y][x - i] != 0 && x - i + 1 != 0) {
									for (int t = 1; t < 10; t++) {
										if (broad[y][x - i - t] > 0) {
											break;
										}
										if (broad[y][x - i - t] < 0 && x - i + 1 != 0 && (x - i - t) >= 0) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x - i - t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x - i - t;
											y1[c] = y;
											c++;
											break;
										}
									}
									break;
								}
							}
							
							for (int i = 1; i < 11; i++) {//横右
								if (broad[y][x + i] == 0 && x + i - 1 != 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + i;
									y1[c] = y;
									c++;
									//break;
								}
								else break;
							}
							
							for (int i = 1; i < 11; i++) {//横右
								if (broad[y][x + i] != 0 && x + i - 1 != 8) {
									for (int t = 1; t < 10; t++) {
										if (broad[y][x + i + t] > 0) {
											break;
										}
										if (broad[y][x + i + t] < 0 && x + i - 1 != 8 && (x + i + t) <= 9) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x + i + t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x + i + t;
											y1[c] = y;
											c++;
											break;
										}
									}
									break;
								}
							}
						}
					}
					
					if (broad[y][x] < 0) {//如果是黑棋
						if (broad[y][x] == -1) {//黑车
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							for (int i = 1; i < 10; i++) {//竖上
								if (broad[y - i][x] == 0 && y - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
								}
								else if (broad[y - i][x] > 0 && y - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
									break;
								}
								else break;
							}
							for (int i = 1; i < 10; i++) {//竖下
								if (broad[y + i][x] == 0 && y + i - 1 != 9) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
								}
								else if (broad[y + i][x] > 0 && y + i - 1 != 9) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
									break;
								}
								else break;
							}
							for (int i = 1; i < 11; i++) {//横左
								if (broad[y][x - i] == 0 && x - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - i;
									y1[c] = y;
									c++;
								}
								else if (broad[y][x - i] > 0 && x - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - i;
									y1[c] = y;
									c++;
									break;
								}
								else break;
							}
							for (int i = 1; i < 11; i++) {//横右
								if (broad[y][x + i] == 0 && x + i - 1 != 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + i;
									y1[c] = y;
									c++;
								}
								else if (broad[y][x + i] > 0 && x + i - 1 != 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + i;
									y1[c] = y;
									c++;
									break;
								}
								else break;
							}
						}
						if (broad[y][x] == -2) {//黑马
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y - 1][x] == 0) {
								if (broad[y - 2][x + 1] >= 0 && y - 2 >= 0 && x + 1 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x + 1;
									y1[c] = y - 2;
									c++;
								}
								if (broad[y - 2][x - 1] >= 0 && y - 2 >= 0 && x - 1 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x - 1;
									y1[c] = y - 2;
									c++;
								}
								
							}
							if (broad[y + 1][x] == 0) {
								if (broad[y + 2][x + 1] >= 0 && y + 2 <= 9 && x + 1 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x + 1;
									y1[c] = y + 2;
									c++;
								}
								if (broad[y + 2][x - 1] >= 0 && y + 2 <= 9 && x - 1 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x - 1;
									y1[c] = y + 2;
									c++;
								}
								
							}
							if (broad[y][x - 1] == 0) {
								if (broad[y + 1][x - 2] >= 0 && y + 1 <= 9 && x - 2 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y + 1;
									c++;
								}
								if (broad[y - 1][x - 2] >= 0 && y - 1 >= 0 && x - 2 >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y - 1;
									c++;
								}
							}
							if (broad[y][x + 1] == 0) {
								if (broad[y + 1][x + 2] >= 0 && y + 1 <= 9 && x + 2 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y + 1;
									c++;
								}
								if (broad[y - 1][x + 2] >= 0 && y - 1 >= 0 && x + 2 <= 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y - 1;
									c++;
								}
							}
						}
						if (broad[y][x] == -3) {//黑象
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y - 1][x - 1] == 0 && y - 2 >= 0 && x - 2 >= 0) {
								if (broad[y - 2][x - 2] >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y - 2;
									c++;
								}
							}
							if (broad[y + 1][x + 1] == 0 && y + 2 <= 9 && x + 2 <= 8 && y != 4) {
								if (broad[y + 2][x + 2] >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y + 2;
									c++;
								}
							}
							if (broad[y - 1][x + 1] == 0 && y - 2 >= 0 && x + 2 <= 8) {
								if (broad[y - 2][x + 2] >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 2) * QZ - 5, 4 * QZ + (y - 2) * QZ - 5, 10, 10);
									x1[c] = x + 2;
									y1[c] = y - 2;
									c++;
								}
							}
							if (broad[y + 1][x - 1] == 0 && y + 2 <= 9 && x - 2 >= 0 && y != 4) {
								if (broad[y + 2][x - 2] >= 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 2) * QZ - 5, 4 * QZ + (y + 2) * QZ - 5, 10, 10);
									x1[c] = x - 2;
									y1[c] = y + 2;
									c++;
								}
							}
						}
						if (broad[y][x] == -4) {//黑士
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y + 1][x + 1] >= 0 && x < 5 && y < 2) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x + 1;
								y1[c] = y + 1;
								c++;
							}
							if (broad[y - 1][x - 1] >= 0 && x > 3 && y > 0) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x - 1;
								y1[c] = y - 1;
								c++;
							}
							if (broad[y + 1][x - 1] >= 0 && x > 3 && y < 2) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x - 1;
								y1[c] = y + 1;
								c++;
							}
							if (broad[y - 1][x + 1] >= 0 && x < 5 && y > 0) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x + 1;
								y1[c] = y - 1;
								c++;
							}
						}
						if (broad[y][x] == -5) {//黑将
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y + 1][x] >= 0 && y < 2) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x;
								y1[c] = y + 1;
								c++;
							}
							if (broad[y - 1][x] >= 0 && y > 0) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - 1) * QZ - 5, 10, 10);
								x1[c] = x;
								y1[c] = y - 1;
								c++;
							}
							if (broad[y][x + 1] >= 0 && x < 5) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
								x1[c] = x + 1;
								y1[c] = y;
								c++;
							}
							if (broad[y][x - 1] >= 0 && x > 3) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
								x1[c] = x - 1;
								y1[c] = y;
								c++;
							}
							for (int i = 1; i < 11; i++) {
								if (broad[y + i][x] == 0) {
									continue;
								}
								else if (broad[y + i][x] == 5) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
								}
								else break;
								
							}
						}
						if (broad[y][x] == -6) {//黑卒
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							if (broad[y + 1][x] >= 0 && y < 9) {
								setfillcolor(EGEACOLOR(0xFF, BLACK));
								ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + 1) * QZ - 5, 10, 10);
								x1[c] = x;
								y1[c] = y + 1;
								c++;
							}
							if (y > 4) {
								if (broad[y][x - 1] >= 0 && x > 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - 1;
									y1[c] = y;
									c++;
								}
								if (broad[y][x + 1] >= 0 && x < 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + 1) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + 1;
									y1[c] = y;
									c++;
								}
							}
						}
						if (broad[y][x] == -7) {//黑炮
							setlinewidth(2);
							rectangle(2 * QZ + x * QZ - 20, 4 * QZ + y * QZ - 20, 2 * QZ + x * QZ + 18, 4 * QZ + y * QZ + 18);
							for (int i = 1; i < 10; i++) {//竖上
								if (broad[y - i][x] == 0 && y - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y - i;
									c++;
								}
								else break;
							}
							for (int i = 1; i < 10; i++) {//竖上
								if (broad[y - i][x] != 0 && y - i + 1 != 0) {
									for (int t = 1; t < 10; t++) {
										if (broad[y - i - t][x] < 0) {
											break;
										}
										if (broad[y - i - t][x] > 0 && y - i + 1 != 0 && y - i - t>= 0) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y - i - t) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y - i - t;
											c++;
											break;
										}
									}
									break;
								}
							}
							for (int i = 1; i < 10; i++) {//竖下
								if (broad[y + i][x] == 0 && y + i - 1 != 9) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i) * QZ - 5, 10, 10);
									x1[c] = x;
									y1[c] = y + i;
									c++;
									//break;
								}
								else break;
							}
							for (int i = 1; i < 10; i++) {//竖下
								if (broad[y + i][x] != 0 && y + i - 1 != 9) {
									for (int t = 1; t < 10; t++) {
										if (broad[y + i + t][x] < 0) {
											break;
										}
										if (broad[y + i + t][x] > 0 && y + i - 1 != 9 && (y + i + t) <= 9) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + x * QZ - 5, 4 * QZ + (y + i + t) * QZ - 5, 10, 10);
											x1[c] = x;
											y1[c] = y + i + t;
											c++;
											break;
										}
									}
									break;
								}
							}
							
							for (int i = 1; i < 11; i++) {//横左
								if (broad[y][x - i] == 0 && x - i + 1 != 0) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x - i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x - i;
									y1[c] = y;
									c++;
									//break;
								}
								else break;
							}
							for (int i = 1; i < 11; i++) {//横左
								if (broad[y][x - i] != 0 && x - i + 1 != 0) {
									for (int t = 1; t < 10; t++) {
										if (broad[y][x - i - t] < 0) {
											break;
										}
										if (broad[y][x - i - t] > 0 && x - i + 1 != 0 && (x - i - t) >= 0) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x - i - t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x - i - t;
											y1[c] = y;
											c++;
											break;
										}
									}
									break;
								}
							}
							
							for (int i = 1; i < 11; i++) {//横右
								if (broad[y][x + i] == 0 && x + i - 1 != 8) {
									setfillcolor(EGEACOLOR(0xFF, BLACK));
									ege_fillellipse(2 * QZ + (x + i) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
									x1[c] = x + i;
									y1[c] = y;
									c++;
									//break;
								}
								else break;
							}
							
							for (int i = 1; i < 11; i++) {//横右
								if (broad[y][x + i] != 0 && x + i - 1 != 8) {
									for (int t = 1; t < 10; t++) {
										if (broad[y][x + i + t] < 0) {
											break;
										}
										if (broad[y][x + i + t] > 0 && x + i - 1 != 8 && (x + i + t) <= 9) {
											setfillcolor(EGEACOLOR(0xFF, BLACK));
											ege_fillellipse(2 * QZ + (x + i + t) * QZ - 5, 4 * QZ + y * QZ - 5, 10, 10);
											x1[c] = x + i + t;
											y1[c] = y;
											c++;
											break;
										}
									}
									break;
								}
							}
						}
					}
					run(1);
				}
				
			}
			
			if (temp == 1) {
				if (x >= 0 && x <= 8 && y >=0 && y <= 9 && broad[y][x] != 0) {
					setfont(20, 0, "华文隶书");
					setbkmode(TRANSPARENT);
					xyprintf(9, 15 * QZ, "状态：已选中，单击以继续");
					for (; is_run(); delay_fps(60)) {
						mouse_msg msg = getmouse();
						if (msg.is_down() && msg.is_left()) {
							cx = msg.x;
							cy = msg.y;
							cx = (cx - (1.5 * QZ)) / QZ;
							cy = (cy - (3.5 * QZ)) / QZ;
							break;
						}
					}
					run(2);
				}
				else {
					temp = 0;
					c = 0;
					if (patton) {
						draws();
					}
					else {
						draw();
					}
					click();
				}
			}
		}
	}
}

void draw() {
	cleardevice();
	putimage(0, 0, bj);
	setfont(40, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(18, 9, "模式：双人对弈");
	setfont(30, 0, "华文隶书");
	xyprintf(7 * QZ, 15.2 * QZ, "返回主界面");
	xyprintf(7.5 * QZ, 14.2 * QZ, "重新开始");
	setfillcolor(EGEARGB(0xFF, 0xDB, 0xDA, 0x7D));//深黄色
	ege_fillrect(1.5 * QZ, 3.5 * QZ, 9 * QZ, 10 * QZ);
	//bar(2 * QZ, 4 * QZ, 10 * QZ, 13 * QZ);
	setlinewidth(4);
	rectangle(1.4 * QZ, 3.4 * QZ, 10.7 * QZ, 13.7 * QZ);
	setlinewidth(1);
	setcolor(BLACK);
	for (int i = 0; i < QZ * 10; i += QZ) {
		line(2 * QZ, 4 * QZ + i, 10 * QZ, 4 * QZ + i);
	}
	for (int i = 0; i < QZ * 9; i += QZ) {
		if (i == 0) {
			line(2 * QZ, 8 * QZ, 2 * QZ, 9 * QZ);
			line(10 * QZ, 8 * QZ, 10 * QZ + i, 9 * QZ);
		}
		line(2 * QZ + i, 4 * QZ, 2 * QZ + i, 8 * QZ);
		line(2 * QZ + i, 9 * QZ, 2 * QZ + i, 13 * QZ);
	}
	line(5 * QZ, 4 * QZ, 7 * QZ, 6 * QZ);
	line(7 * QZ, 4 * QZ, 5 * QZ, 6 * QZ);
	line(5 * QZ, 11 * QZ, 7 * QZ, 13 * QZ);
	line(7 * QZ, 11 * QZ, 5 * QZ, 13 * QZ);
	
	for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			if (broad[i][t] == 0) {
				continue;
			}
			else if (broad[i][t] == 1) {
				getimage(qi, "img/红车.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 2) {
				getimage(qi, "img/红马.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 3) {
				getimage(qi, "img/红相.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 4) {
				getimage(qi, "img/红士.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 5) {
				getimage(qi, "img/红帅.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 6) {
				getimage(qi, "img/红兵.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == 7) {
				getimage(qi, "img/红炮.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -1) {
				getimage(qi, "img/黑车.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -2) {
				getimage(qi, "img/黑马.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -3) {
				getimage(qi, "img/黑象.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -4) {
				getimage(qi, "img/黑士.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -5) {
				getimage(qi, "img/黑将.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -6) {
				getimage(qi, "img/黑卒.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
			else if (broad[i][t] == -7) {
				getimage(qi, "img/黑炮.bmp");
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, qi);
				continue;
			}
		}
	}
}

void draws() {
	cleardevice();
	putimage(0, 0, bj);
	setfont(40, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(18, 9, "模式：双人对弈");
	setfont(30, 0, "华文隶书");
	xyprintf(7 * QZ, 15.2 * QZ, "返回主界面");
	xyprintf(7.5 * QZ, 14.2 * QZ, "重新开始");
	setfillcolor(EGEARGB(0xFF, 0xDB, 0xDA, 0x7D));//深黄色
	ege_fillrect(1.5 * QZ, 3.5 * QZ, 9 * QZ, 10 * QZ);
	//bar(2 * QZ, 4 * QZ, 10 * QZ, 13 * QZ);
	setlinewidth(4);
	rectangle(1.4 * QZ, 3.4 * QZ, 10.7 * QZ, 13.7 * QZ);
	setlinewidth(1);
	setcolor(BLACK);
	for (int i = 0; i < QZ * 10; i += QZ) {
		line(2 * QZ, 4 * QZ + i, 10 * QZ, 4 * QZ + i);
	}
	for (int i = 0; i < QZ * 9; i += QZ) {
		if (i == 0) {
			line(2 * QZ, 8 * QZ, 2 * QZ, 9 * QZ);
			line(10 * QZ, 8 * QZ, 10 * QZ + i, 9 * QZ);
		}
		line(2 * QZ + i, 4 * QZ, 2 * QZ + i, 8 * QZ);
		line(2 * QZ + i, 9 * QZ, 2 * QZ + i, 13 * QZ);
	}
	line(5 * QZ, 4 * QZ, 7 * QZ, 6 * QZ);
	line(7 * QZ, 4 * QZ, 5 * QZ, 6 * QZ);
	line(5 * QZ, 11 * QZ, 7 * QZ, 13 * QZ);
	line(7 * QZ, 11 * QZ, 5 * QZ, 13 * QZ);
	
	for (int i = 0; i < 10; i++) {
		for (int t = 0; t < 9; t++) {
			if (broad[i][t] == 0) {
				continue;
			}
			else if (broad[i][t] == 1) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rcs);
				continue;
			}
			else if (broad[i][t] == 2) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rms);
				continue;
			}
			else if (broad[i][t] == 3) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rxs);
				continue;
			}
			else if (broad[i][t] == 4) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rss);
				continue;
			}
			else if (broad[i][t] == 5) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rjs);
				continue;
			}
			else if (broad[i][t] == 6) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rbs);
				continue;
			}
			else if (broad[i][t] == 7) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, rps);
				continue;
			}
			else if (broad[i][t] == -1) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bcs);
				continue;
			}
			else if (broad[i][t] == -2) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bms);
				continue;
			}
			else if (broad[i][t] == -3) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bxs);
				continue;
			}
			else if (broad[i][t] == -4) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bss);
				continue;
			}
			else if (broad[i][t] == -5) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bjs);
				continue;
			}
			else if (broad[i][t] == -6) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bbs);
				continue;
			}
			else if (broad[i][t] == -7) {
				putimage((t + 1.5) * QZ, (i + 3.5) * QZ, bps);
				continue;
			}
		}
		
	}
}

void clean() {
	memset(broad, 0, sizeof(broad));
	broad[9][0] = 1;
	broad[9][1] = 2;
	broad[9][2] = 3;
	broad[9][3] = 4;
	broad[9][4] = 5;
	broad[9][5] = 4;
	broad[9][6] = 3;
	broad[9][7] = 2;
	broad[9][8] = 1;
	broad[0][0] = -1;
	broad[0][1] = -2;
	broad[0][2] = -3;
	broad[0][3] = -4;
	broad[0][4] = -5;
	broad[0][5] = -4;
	broad[0][6] = -3;
	broad[0][7] = -2;
	broad[0][8] = -1;
	broad[7][1] = 7;
	broad[7][7] = 7;
	broad[2][1] = -7;
	broad[2][7] = -7;
	broad[3][0] = -6;
	broad[3][2] = -6;
	broad[3][4] = -6;
	broad[3][6] = -6;
	broad[3][8] = -6;
	broad[6][0] = 6;
	broad[6][2] = 6;
	broad[6][4] = 6;
	broad[6][6] = 6;
	broad[6][8] = 6;
}

void menu() {
	cleardevice();
	initialize();
	putimage(0, 0, bj);
	int x = 0;
	int y = 0;
	setcolor(BLACK);
	setfont(60, 0, "华文隶书");
	setbkmode(TRANSPARENT);
	xyprintf(100, 60, "中国象棋");
	PIMAGE an = newimage();
	getimage(an,"PNG", MAKEINTRESOURCEA(PNG_bt));
	putimage_transparent(NULL, an, 3 * QZ, 5 * QZ, BLACK);
	setfont(40, 0, "隶书");
	setbkmode(TRANSPARENT);
	xyprintf(3.7 * QZ, 6.2 * QZ, "双人对弈");
	putimage_transparent(NULL, an, 3 * QZ, 7.5 * QZ, BLACK);
	xyprintf(3.7 * QZ, 8.8 * QZ, "翻棋对弈");
	putimage_transparent(NULL, an, 3 * QZ, 10 * QZ, BLACK);
	xyprintf(3.7 * QZ, 11.4 * QZ, "残棋对弈");
	setfont(30, 0, "隶书");
	xyprintf(9.5 * QZ, 15 * QZ, "退出");
	xyprintf(1 * QZ, 15 * QZ, "设置");
	for (; is_run(); delay_fps(60)) {
		while (mousemsg()) {
			mouse_msg msg = getmouse();
			x = msg.x;
			y = msg.y;
			if (msg.is_left() && msg.is_down()) {
				//xyprintf(0, 0, "x = %d y = %d", x, y);
				//getch();
				if (x >= 35 && x <= 100 && y >= 100 && y <= 580) {
					setting();
				}
				if (x >= 120 && x <= 300 && y >= 300 && y <= 380) {
					fclean();
					fplay();
				}
				if (x >= 120 && x <= 300 && y >= 210 && y <= 280) {
					clean();
					play();
				}
				if (x >= 350 && x <= 410 && y >= 560 && y <= 580) {
					if (window("你真的要退出吗？", "", "")) {
						exit(1);
					}
					else {
						menu();
					}
				}
				
			}
		}
	}
}

int main(void) {
	initgraph(12 * QZ, 17 * QZ, INIT_RENDERMANUAL);
	setcaption("中国象棋-64位");
	setbkcolor(WHITE);
	ege_enable_aa(true);
	getimage(bj, "img/背景.bmp");
	
	menu();
	
	getch();
	closegraph();
	return 0;
}
