#ifndef _FUNCTION_H_
#define _FUNCTION_H_

#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <ctime>
#include <map>
#include <vector>
#include <queue>
#include <windows.h>
using namespace std;

#define MAX_SIZE 8 //���鿪��һ���ֹ�±�Խ��qwq
#define START_NUM 2
#define END_NUM 2048
#define FONT TEXT("����")

int _SIZE = 4;//4*4������5*5�Ĵ�С
HWND hwnd;
ExMessage msg;//��Ϣ�ṹ��

class pos//����
{
public:
	int x, y;
	pos(int a = 0, int b = 0)
	{
		x = a; y = b;
	}
};
map <BYTE, pos> motion = { {VK_UP,pos(-1,0)},{VK_LEFT,pos(0,-1)},{VK_DOWN,pos(1,0)},{VK_RIGHT,pos(0,1)},{'W',pos(-1,0)},{'A',pos(0,-1)},{'S',pos(1,0)},{'D',pos(0,1)}};
//��������Ӧ���ƶ�
pos d[4] = {pos(0,1),pos(0,-1),pos(1,0),pos(-1,0)};
bool musicon=1;
void playbgm()
{
	musicon = !musicon;
	if (musicon) mciSendString(TEXT("resume bgm"), 0, 0, 0);
	else mciSendString(TEXT("pause bgm"), 0, 0, 0);
}
map<int, int> width = { {2,320},{4,320},{8,320},{16,280},{32,280},{64,280},{128,240},{256,240},{512,240},{1024,200},{2048,200} };
map<int,int> fontc= { {2,0},{4,0},{8,0},{16,0xffffff},{32,0xffffff},{64,0xffffff},{128,0xffffff},{256,0xffffff},{512,0xffffff},{1024,0xffffff,},{2048,0xffffff} };
map<int, int> color = { {2,0xf0f0e0} ,{4,0xfffacd},{8,0xffa500},{16,0xffa07a},{32,0xff4500},{64,0xff0000},{128,0xffd700},{256,0xffe4b5},{512,0x00bfff},{1024,0x00e8e8},{2048,0xff1493} };
#define MAXLEN 100
void draw(int x,int y,int num)//�������ַ���
{
	setlinecolor(BLACK);
	setfillcolor(color[num]);
	fillroundrect(x, y, x + 400/_SIZE, y + 400/_SIZE, 25, 25);
	settextstyle(width[num]/_SIZE, 0, FONT);
	setbkmode(TRANSPARENT);
	settextcolor(fontc[num]);
	wchar_t s[10] = {};
	wsprintf(s, TEXT("%d"), num);
	int bx = (400/_SIZE - textwidth(s)) / 2;
	int by = (400/_SIZE - textheight(s)) / 2;
	outtextxy(x + bx, y + by, s);
}
void helpmenu()//�����˵�
{
	cleardevice();
	settextstyle(25, 0, FONT);
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	outtextxy(20, 20, TEXT("����һ����׵�2048��Ϸ����������ģʽ��"));
	outtextxy(20, 70, TEXT("����ģʽ���淨ͬ�����2048"));
	outtextxy(20, 120, TEXT("����ģʽ��ÿ���ƶ���һ�����ʵ����������Ч���ĵ���"));
	outtextxy(20, 170, TEXT("���ģʽ�����ߵĴ�����������"));
	outtextxy(20, 220, TEXT("����Ϸ�п���ͨ��wasd�뷽�򰴼����������ֵ��ƶ�"));
	outtextxy(20, 270, TEXT("Ҳ����ͨ�������ѡ�в���������"));
	outtextxy(20, 320, TEXT("����Ϸ�а�Esc�����Է������˵�"));
	settextstyle(15, 0, FONT);
	settextcolor(BLACK);
	outtextxy(20, 380, TEXT("�����������..."));
}
class button
{
private:
	
public:
	int left,top,right,bottom;
	wchar_t content[MAXLEN];
	void (*fun)();
	button() :left(), top(), right(), bottom(), content(), fun() {};
	button(int a, int b, int c, int d, void (*f)()):content()
	{
		left = a; top = b; right = c; bottom = d;
		fun = f;
	}
	void paint(int color=RED)
	{
		setlinecolor(BLACK);
		setfillcolor(color);
		fillroundrect(left,top,right,bottom, 25, 25);
		settextstyle(20, 0, FONT);
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		int bx = ((right-left) - textwidth(content)) / 2;
		int by = ((bottom-top) - textheight(content)) / 2;
		outtextxy(left+bx,top+by,content);
	}
	bool valid()//��ⰴť�Ƿ񱻵��
	{
		//if (msg.message != EX_MOUSE) return 0;
		if (left < msg.x && msg.x < right && top < msg.y && msg.y < bottom) return 1;
		return 0;
	}
};
button music(20, 420, 200, 460, playbgm);
void welcome()//��������
{
	settextstyle(200, 120, FONT);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	wchar_t s[10];
	wsprintf(s, TEXT("2048"));
	int bx = (720 - textwidth(s)) / 2;
	int by = (480 - textheight(s)) / 2;
	outtextxy(bx, by, s);
	mciSendString(TEXT("open start.mp3 alias start"), 0, 0, 0);
	mciSendString(TEXT("play start"), 0, 0, 0);
}
int mainmenu()//���˵�
{
	cleardevice();
	wchar_t s[15] = {};
	wsprintf(s, TEXT("20"));
	settextstyle(220, 150, FONT);
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	outtextxy(50, 20, s);
	memset(s, 0, 15 * sizeof(wchar_t));
	wsprintf(s, TEXT("48"));
	outtextxy(50, 220, s);
	button classic(400, 20, 600, 100, NULL);
	wsprintf(classic.content, TEXT("����ģʽ"));
	classic.paint();
	button prop(400, 120, 600, 200, NULL);
	wsprintf(prop.content, TEXT("����ģʽ"));
	prop.paint();
	button random(400, 220, 600, 300, NULL);
	wsprintf(random.content, TEXT("���ģʽ"));
	random.paint();
	button help(400, 320, 600, 400, NULL);
	wsprintf(help.content, TEXT("����"));
	help.paint();
	button range(400, 420, 480, 460, NULL);
	wsprintf(range.content, TEXT("%d*%d"), _SIZE, _SIZE);
	range.paint();
	wsprintf(music.content, TEXT("music:%s"), (musicon ? TEXT("on") : TEXT("off")));
	music.paint((musicon?BLUE:RED));
	while (1)
	{
		getmessage(&msg, EX_MOUSE);
		
		if (msg.message== WM_LBUTTONDOWN)
		{
			if (classic.valid()) return 1;
			if (prop.valid()) return 2;
			if (random.valid()) return 3;
			if (help.valid()) return 4;
			if (range.valid())
			{
				_SIZE = 9 - _SIZE;
				memset(range.content, 0, MAXLEN * sizeof(wchar_t));
				wsprintf(range.content, TEXT("%d*%d"),_SIZE,_SIZE);
				range.paint();
			}
			if (music.valid())
			{
				music.fun();
				memset(music.content, 0, MAXLEN * sizeof(wchar_t));
				wsprintf(music.content, TEXT("music:%s"), (musicon ? TEXT("on") : TEXT("off")));
				music.paint((musicon ? BLUE : RED));
			}
		}
	}
}

int active;//��ǰ׼��ʹ�õĵ��߱��
class effect
{
public:
	button b;
	int cnt;
	effect(int c=0) :b(), cnt(c) {};
}effects[5];//�ֱ���+2,*2,erase,re

wchar_t name[5][MAXLEN] = { TEXT("\0"),TEXT("������2"),TEXT("����"),TEXT("ɾ��"),TEXT("�������")};
int _rand[10] = { 1,1,1,1,2,3,3,3,4,4 };//��ͬ���ߵ���ĸ���Ҳ��ͬ
int addeffect()//ÿ�κϷ��ƶ�֮������ж��Ƿ�������
{
	if (rand() % (int)(0.5*_SIZE*_SIZE)) return 0;
	int t = _rand[(rand()%100)/10];
	++effects[t].cnt;
	wchar_t buff[MAXLEN] = {};
	wsprintf(buff, TEXT("�ڴ˴��ƶ��е�����һ�����ߣ�%s"), name[t]);
	MessageBox(hwnd, buff, TEXT("Inform"), MB_OK);
	return t;
}
bool ifinit;
void loadeffects()
{
	if (!ifinit)
	{
		ifinit = 1;
		for (int i = 1; i <= 4; ++i)
		{
			effects[i].b = button(425, 40 + 80 * i, 675, 100 + 80 * i, NULL);
			effects[i].cnt = 0;
		}
	}
	for (int i = 1; i <= 4; ++i)
	{
		memset(effects[i].b.content, 0, MAXLEN * sizeof(wchar_t));
		wsprintf(effects[i].b.content, TEXT("%s ʣ��%d"), name[i], effects[i].cnt);
	}
}
int checkeffect()//�������֮���ж��Ƿ�ѡ�е��ߣ�ѡ�з��ض�Ӧ���֣�δѡ�з���0����-1
{
	if (msg.message != WM_LBUTTONDOWN) return -1;
	for (int i = 1; i <= 4; ++i)
	{
		if (effects[i].b.valid())
		{
			if(effects[i].cnt) return i;
			MessageBox(hwnd, TEXT("���ֵ���ʣ������Ϊ0���޷�ʹ�ã�"), TEXT("Error"), MB_OK | MB_ICONWARNING);
			return -1;
		}
	}
	if (music.valid())
	{
		music.fun();
		memset(music.content, 0, MAXLEN * sizeof(wchar_t));
		wsprintf(music.content, TEXT("music:%s"), (musicon ? TEXT("on") : TEXT("off")));
		music.paint((musicon ? BLUE : RED));
	}
	return 0;
}
void newgame()//����Ϸ
{
	ifinit = 0;
	active = 0;
	loadeffects();
}
class game//�Ծֵ���
{
private:
	

public:
	int map[MAX_SIZE][MAX_SIZE];
	int step;
	int score;
	
	const int mode;
	game(int mode = 1) :mode(mode), step(), score(), map() {}; //���캯��
	void init();//��ʼ��
	void output();//���
	void compress(const pos& dir);//��ָ���������֡�ѹ����
	void merge(const pos& dir);//��ָ���������֡��ϲ���
	bool move(char oper);//�ƶ�
	void generate();//�������һ���µ�����
	int winning();//�ж��Ƿ�ʤ��
	void rearrange();//�����������
	bool useeffect();//ʹ�õ���
	void randeffect(int p);//���ʹ�õ�p������
};
void game::init()//��ʼ��
{
	const pos corner[4] = { pos(1,1),pos(1,_SIZE),pos(_SIZE,1),pos(_SIZE,_SIZE) };
	int t = rand() % 4;
	map[corner[t].x][corner[t].y] = START_NUM;
	int x = rand() % _SIZE + 1, y = rand() % _SIZE + 1;
	while (map[x][y])
	{
		x = rand() % _SIZE + 1;
		y = rand() % _SIZE + 1;
	}
	map[x][y] = START_NUM;
	newgame();
}
void game::output()
{
	cleardevice();
	setlinecolor(BLACK);
	setfillcolor(0xffffff);
	fillroundrect(0,0,400,400, 25, 25);
	for (int i = 1; i <= _SIZE; ++i)
	{
		for (int j = 1; j <= _SIZE; ++j)
		{
			if(map[i][j]) draw((400/_SIZE) * (j - 1), (400/_SIZE) * (i - 1), map[i][j]);
		}
	}
	settextstyle(50, 0, FONT);
	setbkmode(TRANSPARENT);
	settextcolor(BLUE);
	wchar_t s[MAXLEN];
	wsprintf(s, TEXT("steps:%d"), step);
	outtextxy(425, 5, s);
	memset(s, 0, MAXLEN * sizeof(wchar_t));
	wsprintf(s, TEXT("score:%d"), score);
	outtextxy(425, 45, s);
	memset(s, 0, MAXLEN * sizeof(wchar_t));
	wsprintf(s, TEXT("(score/2-step=%d)"), score/2-step);
	settextstyle(20, 0, FONT);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(425, 95, s);
	music.paint((musicon?BLUE:RED));
	if (mode != 2) return;
	for (int i = 1; i <= 4; ++i) effects[i].b.paint((i==active?BLUE:RED));
}
void game::compress(const pos& dir)
{
	queue <int> q;
	if (dir.x)
	{
		for (int j = 1; j <= _SIZE; ++j)
		{
			for (int i = (dir.x > 0 ? _SIZE : 1); i <= _SIZE && i >= 1; i -= dir.x)
			{
				if (map[i][j])
				{
					q.push(map[i][j]);
					map[i][j] = 0;
				}
			}
			for (int i = (dir.x > 0 ? _SIZE : 1); !q.empty(); i -= dir.x)
			{
				map[i][j] = q.front();
				q.pop();
			}
		}
	}
	if (dir.y)
	{
		for (int i = 1; i <= _SIZE; ++i)
		{
			for (int j = (dir.y > 0 ? _SIZE : 1); j <= _SIZE && j >= 1; j -= dir.y)
			{
				if (map[i][j])
				{
					q.push(map[i][j]);
					map[i][j] = 0;
				}
			}
			for (int j = (dir.y > 0 ? _SIZE : 1); !q.empty(); j -= dir.y)
			{
				map[i][j] = q.front();
				q.pop();
			}
		}
	}
}
void game::merge(const pos& dir)
{
	if (dir.x)
	{
		for (int j = 1; j <= _SIZE; ++j)
		{
			for (int i = (dir.x > 0 ? _SIZE : 1); i <= _SIZE && i >= 1; i -= dir.x)
			{
				if (map[i][j] && map[i][j] == map[i - dir.x][j])
				{
					map[i][j] *= 2;
					score += map[i][j];
					map[i - dir.x][j] = 0;
				}
			}
		}
	}
	if (dir.y)
	{
		for (int i = 1; i <= _SIZE; ++i)
		{
			for (int j = (dir.y > 0 ? _SIZE : 1); j <= _SIZE && j >= 1; j -= dir.y)
			{
				if (map[i][j] && map[i][j] == map[i][j - dir.y])
				{
					map[i][j] *= 2;
					score += map[i][j];
					map[i][j - dir.y] = 0;
				}
			}
		}
	}
}
bool game::move(char oper)
{
	pos dir = motion[oper];
	if (dir.x + dir.y == 0) return 0;
	++step;
	int tmp[MAX_SIZE][MAX_SIZE];
	for (int i = 1; i <= _SIZE; ++i)
		for (int j = 1; j <= _SIZE; ++j)
			tmp[i][j] = map[i][j];//���ڼ��˴��ƶ��Ƿ�Ϊ��Ч�ƶ�����ʱ����
	this->compress(dir);//ѹ��
	this->merge(dir);//�ϲ�
	this->compress(dir);//��ѹ��
	for (int i = 1; i <= _SIZE; ++i)
		for (int j = 1; j <= _SIZE; ++j)
			if (map[i][j] != tmp[i][j])
				return 1;
	--step;//�������Ч�ƶ��Ļ��ⲽ�Ĳ�����Ч
	return 0;
}
void game::generate()
{
	vector <pos> v;//��ǰΪ0�ĸ���
	for (int i = 1; i <= _SIZE; ++i)
	{
		for (int j = 1; j <= _SIZE; ++j)
		{
			if (map[i][j] == 0)
			{
				v.push_back(pos(i, j));
			}
		}
	}
	int random = rand() % v.size();
	if(rand()%3) map[v[random].x][v[random].y] = START_NUM;
	else map[v[random].x][v[random].y] = START_NUM * 2;
}
int game::winning()//��ʤ����1��ʧ�ܷ���-1�����෵��0
{
	for (int i = 1; i <= _SIZE; ++i)
		for (int j = 1; j <= _SIZE; ++j)
			if (map[i][j] == END_NUM) return 1;
	if (mode == 2)
	{
		for (int i = 2; i <= 4; ++i) if (effects[i].cnt) return 0;
	}
	for (int i = 1; i <= _SIZE; ++i)
		for (int j = 1; j <= _SIZE; ++j)
			if (map[i][j]==0||map[i][j]==map[i-1][j]||map[i][j]==map[i][j-1]) return 0;
	return -1;
}
void game::rearrange()
{
	if (mode == 1) return;
	vector<int> v;
	for (int i = 1; i <= _SIZE; ++i)
		for (int j = 1; j <= _SIZE; ++j)
			v.push_back(map[i][j]);
	int random;
	for (int i = 1; i <= _SIZE; ++i)
	{
		for (int j = 1; j <= _SIZE; ++j)
		{
			random = rand() % v.size();
			map[i][j] = v[random];
			v.erase(v.begin() + random);
		}
	}
}
bool game::useeffect()
{
	if (mode == 1) return 0;
	if (msg.message != WM_LBUTTONDOWN) return 0;
	if (active <= 0) return 0;
	int i = msg.y / (400/_SIZE) + 1, j = msg.x / (400/_SIZE) + 1;
	if (i > _SIZE || j > _SIZE) return 0;
	switch (active)
	{
	case 1:
		if (map[i][j])
		{
			MessageBox(hwnd, TEXT("��ѡ����ȷ��λ�ã�"), TEXT("Error"), MB_OK | MB_ICONWARNING);
			return 0;
		}
		map[i][j] = 2;
		return 1;
	case 2:
	case 3:
		if (map[i][j])
		{
			map[i][j] += (5 - 2 * active) * map[i][j];
			return 1;
		}
		MessageBox(hwnd, TEXT("��ѡ����ȷ��λ�ã�"), TEXT("Error"), MB_OK | MB_ICONWARNING);
		return 0;
	}
	return 0;
}
void game::randeffect(int p)
{
	if (mode != 3 || p == 0) return;
	vector<pos> v1,v2;
	for (int i = 1; i <= _SIZE; ++i)
	{
		for (int j = 1; j <= _SIZE; ++j)
		{
			if (map[i][j]) v2.push_back(pos(i, j));
			else v1.push_back(pos(i, j));
		}
	}
	int r;
	wchar_t buff[MAXLEN] = {};
	switch (p)
	{
	case 1:
		if (v1.size() == 0)
		{
			MessageBox(hwnd, TEXT("����û��ʣ��ռ䣬������2ʧ�ܣ�"), TEXT("Error"), MB_OK);
			return;
		}
		r = rand() % v1.size();
		map[v1[r].x][v1[r].y] = 2;
		wsprintf(buff, TEXT("����%d��%d�д�������һ��2��"),v1[r].x,v1[r].y);
		break;
	case 2:
	case 3:
		r = rand() % v2.size();
		if (p == 2) wsprintf(buff, TEXT("����%d��%d�д��������ѱ�����"), v2[r].x, v2[r].y);
		else wsprintf(buff, TEXT("����%d��%d�д�������%d�ѱ�ɾ��!"),v2[r].x, v2[r].y,map[v2[r].x][v2[r].y]);
		map[v2[r].x][v2[r].y] += (5 - 2 * p) * map[v2[r].x][v2[r].y];
		break;
	case 4:
		rearrange();
		wsprintf(buff, TEXT("���ϵ�������������ţ�"));
	}
	MessageBox(hwnd, buff, TEXT("Inform"), MB_OK);
}
#endif