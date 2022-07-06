#include<iostream>
using namespace std;
#include "Application.h"

int main()
{
	Application A;
	initgraph(950, 550);
	IMAGE* welcome = new IMAGE;
	loadimage(welcome, "data/image/welcome.png", 950, 550);
	putimage(0, 0, welcome);//显示图片
	while (1)
	{
		if (MouseHit())
		{
			MOUSEMSG msg = GetMouseMsg();//创建鼠标消息对象,同时获取鼠标消息
			//消息分发
			switch (msg.uMsg)
			{
			case WM_LBUTTONDOWN:
				if (msg.x > 752 && msg.y > 431 && msg.x < 910 && msg.y < 491)
					MainWindow(A);
				break;
			}
		}
	}
	char a = getchar();
	closegraph();
}