#include <easyx.h>
#include <conio.h>
#include <graphics.h>
#include "function.h"
#include <locale>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
using namespace std;
extern HWND hwnd;
extern ExMessage msg;
extern effect effects[5];
extern int active;
int main()
{
	setlocale(LC_ALL, "chs");//��������
	initgraph(720, 480);
	hwnd = GetHWnd();
	SetWindowText(hwnd, TEXT("2048"));//�޸�����
	setbkcolor(WHITE);
	cleardevice();
	welcome();
	srand(time(0));//���������
	loadeffects();
	mciSendString(TEXT("open bgm.mp3 alias bgm"), 0, 0, 0);
	Sleep(2000);
	mciSendString(TEXT("play bgm repeat"), 0, 0, 0);
	int t, m;
	while (1)
	{
		m=mainmenu();
		if (m == 4)
		{
			helpmenu();
			getmessage(EX_KEY);//�����������
			continue;
		}
		game x(m);
		x.init();
		x.output();
		char opt;
		while (1)
		{
			while (1)
			{
				getmessage(&msg, EX_KEY|EX_MOUSE);
				if (msg.message == WM_KEYDOWN && msg.prevdown == 0) break;//���¼�����֮ǰû�б�����
				if (msg.message == WM_LBUTTONDOWN && x.mode == 2)//����������ǵ���ģʽ
				{
					int c = checkeffect();
					if (active<=0)
					{
						active = c;
						if (active>0) break;
					}
					else
					{
						if (c == -1) break;
						if (c)
						{
							active = (active == c ? 0 : c);
							break;
						}
						if (x.useeffect())
						{
							--effects[active].cnt;
							active = 0;
							break;
						}
						
					}
				}
			}
			if (active == 4)//�������
			{
				if (MessageBox(hwnd, TEXT("��ȷ��Ҫ�����������������"), TEXT("Question"), MB_OKCANCEL | MB_ICONQUESTION) == IDOK)
				{
					x.rearrange();
					MessageBox(hwnd, TEXT("���ϵ������Ѿ�������ţ�"), TEXT("Inform"), MB_OK);
					--effects[4].cnt;
				}
				active = 0;
			}
			if (msg.message == WM_KEYDOWN)
			{
				opt = msg.vkcode;
				if (opt == VK_ESCAPE)//����Esc�����Է������˵�
				{
					if (MessageBox(hwnd, TEXT("ȷ��Ҫ���������Ϸ���������˵���"), TEXT("Exit"), MB_OKCANCEL | MB_ICONWARNING) == IDOK) break;
					continue;
				}
				if (x.move(opt))
				{
					x.generate();
					x.output();
					if (x.mode != 1)
					{
						int p=(x.mode-2)*addeffect();
						if (p) x.randeffect(p);
					}
				}
			}
			if (x.mode == 2) loadeffects();
			x.output();
			t = x.winning();//�жϸþ���Ϸ�Ƿ����
			if (t == 0) continue;
			if (t == 1) MessageBox(hwnd, TEXT("��ϲ��ɹ��ϳɳ���2048��"), TEXT("Congratulation"), MB_OK);
			else MessageBox(hwnd, TEXT("�������������Ѿ��޷��ƶ�����Ϸ������"), TEXT("Lose"), MB_OK);
			break;
		}
	}

	system("pause");
	closegraph();
	return 0;
}