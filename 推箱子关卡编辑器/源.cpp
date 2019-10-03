#include<graphics.h>
#include<fstream>
using namespace std;

const int MapSize = 16; //��ͼ��λ����
const int MapHig = 35;  //��ͼ����Ԫ����
const int MapLen = 50; //��ͼ����Ԫ����

const int ButtonSize = 32; //��ť�뾶
const int ButtonNum = 4; //��ť����

const int WinL = MapSize * MapLen; //��ͼ���泤
const int WinH = MapSize * MapHig; //��ͼ�����

int Map[MapLen][MapHig] = { 0 }; //��ʼ����ͼԪ������
int MapObjectValue = 0; //��ͼԪ��ֵ,Ĭ��Ϊ 0
const int MapObjectValueMax = 6; //���ֵ
const int MapObjectValueMin = 0; //��Сֵ��Ĭ��Ϊ�գ���Ĭ��Ϊ0

IMAGE Background;
IMAGE Man;
IMAGE Box;
IMAGE Wall;
IMAGE Way;
IMAGE Hole;
IMAGE Finish;
IMAGE Win;
void LoadDate();
struct Point  //��ť�ṹ�� ��������
{
	int x;
	int y;
};

struct Point ButtonClear = { WinL + ButtonSize * 2,ButtonSize * 1 }; //�����ť
struct Point ButtonChoose = { WinL + ButtonSize * 2,ButtonSize * 5 }; //ѡ���ͼԪ��
struct Point ButtonHelp = { WinL + ButtonSize * 2,ButtonSize * 7 };//����
struct Point ButtonSaveExit = { WinL + ButtonSize * 2,ButtonSize * 3 };//���沢�˳�

void Button(int x, int y);//�ж�����һ����ť
//*****************************
//               ��ť���ܺ���
void Button_help();
void Button_clear();
void Button_choose();
void Button_save_exit();
//****************************
void CreatMapDateText(); //����ͼԪ�ش洢��map.txt��

void DrawLine(); //������ͼ�༭������

bool CanEdit(int x, int y);//�Ƿ����ڿɱ༭��Χ

int main()
{
	initgraph(MapLen * MapSize + 56 + ButtonSize * 3, MapHig * MapSize + 56);
	LoadDate();
	DrawLine();
	MOUSEMSG click;
	while (1)
	{
		click = GetMouseMsg();
		if (click.mkRButton)
		{
			if (CanEdit(click.x, click.y))
			{
				Map[click.x / MapSize][click.y / MapSize] = MapObjectValueMin;
				putimage(click.x / MapSize * MapSize, click.y / MapSize * MapSize, &Wall);
				rectangle(click.x / MapSize * MapSize, click.y / MapSize * MapSize, click.x / MapSize * MapSize + MapSize, click.y / MapSize * MapSize + MapSize);
			}
			else { Button(click.x, click.y); }
		}
		if (click.mkMButton)
		{
			break;
		}
		if (click.mkLButton)
		{
			if (CanEdit(click.x, click.y))
			{
				Map[click.x / MapSize][click.y / MapSize] = MapObjectValue;
				switch (MapObjectValue)
				{
				case 0:
					putimage(click.x / MapSize * MapSize, click.y / MapSize * MapSize, &Wall);
					break;
				case 1:
					putimage(click.x / MapSize * MapSize, click.y / MapSize * MapSize, &Way);
					break;
				case 2:
					putimage(click.x / MapSize * MapSize, click.y / MapSize * MapSize, &Box);
					break;
				case 3:
					putimage(click.x / MapSize * MapSize, click.y / MapSize * MapSize, &Hole);
					break;
				case 4:
					putimage(click.x / MapSize * MapSize, click.y / MapSize * MapSize, &Finish);
					break;
				case 5:
				case 6:
					putimage(click.x / MapSize * MapSize, click.y / MapSize * MapSize, &Man);
					break;
				default:
					break;
				}
				rectangle(click.x / MapSize * MapSize, click.y / MapSize * MapSize, click.x / MapSize * MapSize + MapSize, click.y / MapSize * MapSize + MapSize);
			}
			else { Button(click.x, click.y); }
		}
	}
	return 0;
}
void CreatMapDateText()
{
	ofstream mapdate; //��Ԫ��
	ofstream maparraw; //����
	ofstream level; //������ĵ�ͼ�ؿ�
	maparraw.open("maparraw.txt");
	mapdate.open("mapdate.txt");
	level.open("level.txt");
	int l_start = 0; int h_start = 0;
	int l_end = MapLen; int h_end = MapHig;
	for (int j = 0; j < MapHig; j++)
	{
		for (int i = 0; i < MapLen; i++)
		{
			mapdate << Map[i][j];
			maparraw << Map[i][j];
			maparraw << ",";
		}
		mapdate << endl;
		maparraw << endl;
	}
	for (int j = 0; j < MapHig; j++)
	{
		bool key = false;
		for (int i = 0; i < MapLen; i++)
		{
			if (Map[i][j]!=0)
			{
				h_start = j;
				key = true;
				break;
			}
		}if (key)
		{
			break;
		}
	}
	for (int j = MapHig-1; j >0; j--)
	{
		bool key = false;
		for (int i = MapLen-1; i > 0; i--)
		{
			if (Map[i][j] != 0)
			{
				h_end = j;
				key = true;
				break;
			}
		}if (key)
		{
			break;
		}
	}
	for (int i = 0; i < MapLen; i++)
	{
		bool key = false;
		for (int j = 0; j < MapHig; j++)
		{
			if (Map[i][j] != 0)
			{
				l_start = i;
				key = true;
				break;
			}
		}if (key)
		{
			break;
		}
	}
	for (int i = MapLen-1; i > 0; i--)
	{
		bool key = false;
		for (int j = MapHig-1; j > 0; j--)
		{
			if (Map[i][j] != 0)
			{
				l_end = i;
				key = true;
				break;
			}
		}if (key)
		{
			break;
		}
	}
	for (int i = l_start; i <=l_end+2; i++)
	{
		level << 0;
	}
	level << endl;
	for (int j = h_start; j <= h_end; j++)
	{
		level << 0;
		for (int i = l_start; i <= l_end; i++)
		{
			level << Map[i][j];
		}level << 0<<endl;
	}
	for (int i = l_start; i <= l_end+2; i++)
	{
		level << 0;
	}
	level << endl;
	mapdate << '#';
	level << '#';
	mapdate.close();
	maparraw.close();
	level.close();
}
void DrawLine()
{
	for (int i = 0; i <= MapLen; i++)
	{
		for (int j = 0; j <= MapHig; j++)
		{
			line(i * MapSize, 0, i * MapSize, WinH);
			line(0, j * MapSize, WinL, j * MapSize);
		}
	}//��������
	for (int i = 0; i < MapLen;)
	{
		char numl[MapLen * 2 + 1] = { "0103050709111213151719212325272931333537394143454749" };
		outtextxy(i * MapSize - 7, WinH, numl[i]);
		outtextxy(i * MapSize - 7 + 7, WinH, numl[i + 1]);
		i++;
		i++;
	}//�������
	for (int i = 0; i < MapHig;)
	{
		char numh[MapHig * 2 + 1] = { "010305070911131517192123252729313335" };
		outtextxy(WinL, i * MapSize - 7, numh[i]);
		outtextxy(WinL + 7, i * MapSize - 7, numh[i + 1]);
		i++;
		i++;
	}//���/����

	setfillcolor(RGB(128, 128, 64));
	fillcircle(ButtonChoose.x, ButtonChoose.y, 32);
	fillcircle(ButtonClear.x, ButtonClear.y, 32);
	fillcircle(ButtonSaveExit.x, ButtonSaveExit.y, 32);
	fillcircle(ButtonHelp.x, ButtonHelp.y, 32);

	putimage(ButtonHelp.x, ButtonHelp.y + 32 * 2, &Wall);

	setbkmode(TRANSPARENT);
	outtextxy(ButtonClear.x - 12, ButtonClear.y - 6, "���");
	outtextxy(ButtonSaveExit.x - 12, ButtonSaveExit.y - 6, "���");
	outtextxy(ButtonChoose.x - 12, ButtonChoose.y - 6, "�л�");
	outtextxy(ButtonHelp.x - 12, ButtonHelp.y - 6, "����");
	setfillcolor(RGB(256, 256, 256));
	//����Բ�ΰ�ť
}
bool CanEdit(int x, int y)
{
	if (x > MapLen * MapSize - 2)
	{
		return false;
	}

	if (y > MapHig * MapSize - 2)
	{
		return false;
	}
	return true;
}
void Button(int x, int y)
{
	float distance[ButtonNum] = {
		sqrt((x - ButtonClear.x) * (x - ButtonClear.x) + (y - ButtonClear.y) * (y - ButtonClear.y)),
		sqrt((x - ButtonChoose.x) * (x - ButtonChoose.x) + (y - ButtonChoose.y) * (y - ButtonChoose.y)),
		sqrt((x - ButtonHelp.x) * (x - ButtonHelp.x) + (y - ButtonHelp.y) * (y - ButtonHelp.y)),
		sqrt((x - ButtonSaveExit.x) * (x - ButtonSaveExit.x) + (y - ButtonSaveExit.y) * (y - ButtonSaveExit.y))
	};
	int n = 0;
	for (int i = 0; i < ButtonNum; i++)
	{
		if (distance[i] < ButtonSize)
		{
			n = i;
			n++;
			switch (n)
			{
			case 1:	Button_clear();
				break;
			case 2:	Button_choose();
				break;
			case 3: Button_help();
				break;
			case 4: Button_save_exit();
				break;
			default:
				break;
			}
		}
	}
}
void Button_clear()
{
	cleardevice();
	graphdefaults();
	MapObjectValue = 0;
	for (int i = 0; i < MapLen; i++)
	{
		for (int j = 0; j < MapHig; j++)
		{
			Map[i][j] = 0;
		}
	}
	DrawLine();
}
void Button_choose()
{
	if (++MapObjectValue == 7)
	{
		MapObjectValue = 0;
	}
	switch (MapObjectValue)
	{
	case 0:
		putimage(ButtonHelp.x, ButtonHelp.y + ButtonSize * 2, &Wall);
		break;
	case 1:
		putimage(ButtonHelp.x, ButtonHelp.y +	ButtonSize * 2, &Way);
		break;
	case 2:
		putimage(ButtonHelp.x, ButtonHelp.y + ButtonSize * 2, &Box);
		break;
	case 3:
		putimage(ButtonHelp.x, ButtonHelp.y + ButtonSize * 2, &Hole);
		break;
	case 4:
		putimage(ButtonHelp.x, ButtonHelp.y + ButtonSize * 2, &Finish);
		break;
	case 5:
	case 6:
		putimage(ButtonHelp.x, ButtonHelp.y + ButtonSize * 2, &Man);
		break;
	default:
		break;
	}
}
void Button_save_exit()
{
	CreatMapDateText();
	cleardevice();
	outtextxy(0, 50 * 4, "        ��ͼ������map.txt�У�ÿ�����г��򸲸�");
	outtextxy(0, 50 * 5, "                �������˳�");
	Sleep(2000);

	while (true)
	{
		MOUSEMSG m = GetMouseMsg();
		if (m.mkCtrl || m.mkLButton || m.mkMButton || m.mkRButton)
		{
			break;
		}
	}
	closegraph();
	exit(-1);
}
void Button_help()
{
	cleardevice();
	settextstyle(30, 25, "����");
	outtext("��������䣬�Ҽ����أ��м��˳�");
	outtextxy(0, 50, "���-��յ�ǰ");
	outtextxy(0, 50 * 2, "���-���沢�˳�");
	outtextxy(0, 50 * 3, "�л�-�л����Ԫ��");
	outtextxy(0, 50 * 4, "��ͼ������map.txt�У�ÿ�����г��򸲸�");
	outtextxy(0, 50 * 5, "���������");
	MapObjectValue = 1;
	for (int i = 0; i < MapLen; i++)
	{
		for (int j = 0; j < MapHig; j++)
		{
			Map[i][j] = 0;
		}
	}
	while (true)
	{
		MOUSEMSG m = GetMouseMsg();
		if (m.mkCtrl || m.mkLButton || m.mkMButton || m.mkRButton)
		{
			
			cleardevice();
			graphdefaults();
			DrawLine();
			break;
		}
	}
}
void LoadDate() //����ͼƬ
{
	loadimage(&Background, "background.jpg", 860, 640);
	loadimage(&Win, "win.jpg", 860, 640);
	loadimage(&Man, "man.jpg", MapSize, MapSize);
	loadimage(&Way, "way.jpg", MapSize, MapSize);
	loadimage(&Box, "box.jpg", MapSize, MapSize);
	loadimage(&Hole, "hole.jpg", MapSize, MapSize);
	loadimage(&Wall, "wall.jpg", MapSize, MapSize);
	loadimage(&Finish, "finish.jpg", MapSize, MapSize);
}
