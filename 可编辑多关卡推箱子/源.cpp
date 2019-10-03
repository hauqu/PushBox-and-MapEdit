#include<graphics.h>
#include<fstream>
#include<string>
#include<istream>
#include<iostream>
#include<conio.h>
using namespace std;
#define GAMEMAP "game.txt" 
const  int MapSize = 24;
const int LevelN = 36;
string LEVELS[LevelN] = 
{
	"Level_1.txt","Level_2.txt","Level_3.txt","Level_4.txt","Level_5.txt",
	"Level_6.txt","Level_7.txt","Level_8.txt","Level_9.txt","Level_10.txt",
	"Level_11.txt","Level_12.txt","Level_13.txt","Level_14.txt","Level_15.txt",
	"Level_16.txt","Level_17.txt","Level_18.txt","Level_19.txt","Level_20.txt",
	"Level_21.txt","Level_22.txt","Level_23.txt","Level_24.txt","Level_25.txt",
	"Level_26.txt","Level_27.txt","Level_28.txt","Level_29.txt","Level_30.txt",
	"Play_1.txt","Play_2.txt","Play_3.txt","Play_4.txt","Play_5.txt","game.txt"
}; //30个自带关卡 ，5个玩家自定义关卡，一个继续游戏关卡


IMAGE Background;
IMAGE Man;
IMAGE Box;
IMAGE Wall;
IMAGE Way;
IMAGE Hole;
IMAGE Finish;
IMAGE Win;

void LoadDate();


class BoxPush
{
public:
	void  MainGame(char ch);
	void Draw(int PosX, int PosY);
	void Show();
	bool IsVictory();
	BoxPush() {};
	~BoxPush() {};
	BoxPush(string level);
private:
	struct Point
	{
		short x;
		short y;
	};
	typedef struct  Point Point;
	enum Dir
	{
		Up, Right, Left, Down
	};
	Dir Keypro(char ch);
	void Find_N_Box_Hole();
	Point FindMan();
	int finish; //箱子推进目的地的数量
	int BoxN;
	int HoleN;
	int len;
	int hig;
	static const int MaxL = 50; //最大列数
	static const int MaxH = 50; //最大行数
	static const int MaxBox = 10; //最大箱子数
	static const int MaxHole = 10;
	char map[MaxL][MaxH] = { '0' };
};
void BoxPush::MainGame(char ch)
{
	Dir dir = Keypro(ch);
	Point man= FindMan();
	int x = man.x; //x 为行数 -1
	int y = man.y; //为列数 -1
	char temp = map[x][y];
	switch (dir)
	{
	case BoxPush::Up:
		switch (map[x-1][y])
		{
		case '1':
			if (map[x][y]=='5')
			{
				map[x][y] = '1';
				map[x - 1][y] = '5';
			}
			else 
			{
				map[x][y] = '3';
				map[x - 1][y] = '5';
			}
			break;
		case'0':
			//do nothing
			break;
		case'3':
			if (map[x][y] == '5')
			{
				map[x][y] = '1';
				map[x - 1][y] = '6';
			}
			else
			{
				map[x][y] = '3';
				map[x - 1][y] = '6';
			}
			break;
		case'2':
			if (map[x - 1-1][y] == '1')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x - 1][y] = '5';
					map[x - 1 - 1][y] = '2';
				}
				else
				{
					map[x][y] = '3';
					map[x - 1][y] = '5';
					map[x - 1 - 1][y] = '2';
				}
			}
			else if(map[x - 1 - 1][y] == '3')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x - 1][y] = '5';
					map[x - 1 - 1][y] = '4';
				}
				else
				{
					map[x][y] = '3';
					map[x - 1][y] = '5';
					map[x - 1 - 1][y] = '4';
				}
			}
			break;
		case'4':
			if (map[x - 1 - 1][y] == '1')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x - 1][y] = '6';
					map[x - 1 - 1][y] = '2';
				}
				else
				{
					map[x][y] = '3';
					map[x - 1][y] = '6';
					map[x - 1 - 1][y] = '2';
				}
			}
			else if (map[x - 1 - 1][y] == '3')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x - 1][y] = '6';
					map[x - 1 - 1][y] = '4';
				}
				else
				{
					map[x][y] = '3';
					map[x - 1][y] = '6';
					map[x - 1 - 1][y] = '4';
				}
			}
			break;
		default:
			break;
		}
		break;
	case BoxPush::Right:
		switch (map[x][y+1])
		{
		case '1':
			if (map[x][y] == '5')
			{
				map[x][y] = '1';
				map[x][y+1] = '5';
			}
			else
			{
				map[x][y] = '3';
				map[x][y+1] = '5';
			}
			break;
		case'0':
			//do nothing
			break;
		case'3':
			if (map[x][y] == '5')
			{
				map[x][y] = '1';
				map[x][y+1] = '6';
			}
			else
			{
				map[x][y] = '3';
				map[x][y+1] = '6';
			}
			break;
		case'2':
			if (map[x][y+1+1] == '1')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x][y+1] = '5';
					map[x][y+1+1] = '2';
				}
				else
				{
					map[x][y] = '3';
					map[x][y+1] = '5';
					map[x][y+1+1] = '2';
				}
			}
			else if (map[x][y+1+1] == '3')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x][y+1] = '5';
					map[x][y+1+1] = '4';
				}
				else
				{
					map[x][y] = '3';
					map[x][y+1] = '5';
					map[x][y+1+1] = '4';
				}
			}
			break;
		case'4':
			if (map[x][y+1+1] == '1')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x][y+1] = '6';
					map[x][y+1+1] = '2';
				}
				else
				{
					map[x][y] = '3';
					map[x][y+1] = '6';
					map[x][y+1+1] = '2';
				}
			}
			else if (map[x][y+1+1] == '3')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x][y+1] = '6';
					map[x][y+1+1] = '4';
				}
				else
				{
					map[x][y] = '3';
					map[x][y+1] = '6';
					map[x][y+1+1] = '4';
				}
			}
			break;
		default:
			break;
		}
		break;
	case BoxPush::Left:
		switch (map[x][y - 1])
		{
		case '1':
			if (map[x][y] == '5')
			{
				map[x][y] = '1';
				map[x][y - 1] = '5';
			}
			else
			{
				map[x][y] = '3';
				map[x][y - 1] = '5';
			}
			break;
		case'0':
			//do nothing
			break;
		case'3':
			if (map[x][y] == '5')
			{
				map[x][y] = '1';
				map[x][y - 1] = '6';
			}
			else
			{
				map[x][y] = '3';
				map[x][y - 1] = '6';
			}
			break;
		case'2':
			if (map[x][y - 1 - 1] == '1')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x][y - 1] = '5';
					map[x][y - 1 - 1] = '2';
				}
				else
				{
					map[x][y] = '3';
					map[x][y - 1] = '5';
					map[x][y - 1 - 1] = '2';
				}
			}
			else if (map[x][y - 1 - 1] == '3')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x][y - 1] = '5';
					map[x][y - 1 - 1] = '4';
				}
				else
				{
					map[x][y] = '3';
					map[x][y - 1] = '5';
					map[x][y - 1 - 1] = '4';
				}
			}
			break;
		case'4':
			if (map[x][y - 1 - 1] == '1')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x][y - 1] = '6';
					map[x][y - 1 - 1] = '2';
				}
				else
				{
					map[x][y] = '3';
					map[x][y - 1] = '6';
					map[x][y - 1 - 1] = '2';
				}
			}
			else if (map[x][y - 1 - 1] == '3')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x][y - 1] = '6';
					map[x][y - 1 - 1] = '4';
				}
				else
				{
					map[x][y] = '3';
					map[x][y - 1] = '6';
					map[x][y - 1 - 1] = '4';
				}
			}
			break;
		default:
			break;
		}
		break;
	case BoxPush::Down:
		switch (map[x + 1][y])
		{
		case '1':
			if (map[x][y] == '5')
			{
				map[x][y] = '1';
				map[x + 1][y] = '5';
			}
			else
			{
				map[x][y] = '3';
				map[x + 1][y] = '5';
			}
			break;
		case'0':
			//do nothing
			break;
		case'3':
			if (map[x][y] == '5')
			{
				map[x][y] = '1';
				map[x + 1][y] = '6';
			}
			else
			{
				map[x][y] = '3';
				map[x + 1][y] = '6';
			}
			break;
		case'2':
			if (map[x + 1 + 1][y] == '1')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x + 1][y] = '5';
					map[x + 1 + 1][y] = '2';
				}
				else
				{
					map[x][y] = '3';
					map[x + 1][y] = '5';
					map[x + 1 + 1][y] = '2';
				}
			}
			else if (map[x + 1 + 1][y] == '3')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x + 1][y] = '5';
					map[x + 1 + 1][y] = '4';
				}
				else
				{
					map[x][y] = '3';
					map[x + 1][y] = '5';
					map[x + 1 + 1][y] = '4';
				}
			}
			break;
		case'4':
			if (map[x + 1 + 1][y] == '1')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x + 1][y] = '6';
					map[x + 1 + 1][y] = '2';
				}
				else
				{
					map[x][y] = '3';
					map[x + 1][y] = '6';
					map[x + 1 + 1][y] = '2';
				}
			}
			else if (map[x + 1 + 1][y] == '3')
			{
				if (map[x][y] == '5')
				{
					map[x][y] = '1';
					map[x + 1][y] = '6';
					map[x + 1 + 1][y] = '4';
				}
				else
				{
					map[x][y] = '3';
					map[x + 1][y] = '6';
					map[x + 1 + 1][y] = '4';
				}
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
}
bool BoxPush::IsVictory()
{
	finish = 0;
	for (int i = 0; i < hig; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if (map[i][j] == '4' )	finish++;
		}
	}
	if (finish==BoxN||finish==HoleN)
	{
		return true;
	}
	else
	{
		return false;
	}
}
BoxPush::Point BoxPush::FindMan()
{
	Point pos = { 0,0 };
	for (int i = 0; i < hig; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if (map[i][j] == '5'|| map[i][j] == '6')
			{
				pos.x = i;
				pos.y = j;
				return pos;
			}	
		}
	}
	return pos;
	
}
void BoxPush::Find_N_Box_Hole()
{
	for (int  i = 0; i < hig; i++)
	{
		for(int j=0;j<len;j++)
		{
			if (map[i][j]=='2')
			{
				BoxN++;
			}
			else if(map[i][j] == '3')
			{
				HoleN++;
			}
			else if(map[i][j] == '4')
			{
				HoleN++;
				BoxN++;
			}
		}
	}
}
BoxPush::Dir BoxPush::Keypro(char ch)
{
	Dir dir =Up;
	switch (ch)
	{
	case 'a':
	case 'A':
	case 75:
		dir= Left;
		break;
	case 'd':
	case 'D':
	case 77:
		dir = Right;
		break;
	case 'W':
	case 'w':
	case 72:
		dir = Up;
		break;
	case 'S':
	case 's':
	case 80:
		dir = Down;
		break;
	default:
		break;
	}
	return dir;
}
void  BoxPush::Show()
{
	for (int  i = 0; i < hig; i++)
	{
		for (int j = 0; j < len; j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}
void BoxPush::Draw(int PosX,int PosY)
{
	for (int i = 0; i < MaxH; i++)
	{
		for (int j = 0; j < MaxL; j++)
		{
			switch (map[i][j])
			{
			case '0':
				putimage(PosX+j*MapSize,PosY+i*MapSize,&Wall);
				break;
			case '1':
				putimage(PosX + j * MapSize, PosY + i * MapSize, &Way);
				break;
			case '2':
				putimage(PosX + j * MapSize, PosY + i * MapSize, &Box);
				break;
			case '3':
				putimage(PosX + j * MapSize, PosY + i * MapSize, &Hole);
				break;
			case '4':
				putimage(PosX + j * MapSize, PosY + i * MapSize, &Finish);
				break;
			case '5':
				putimage(PosX + j * MapSize, PosY + i * MapSize, &Man);
				break;
			case '6':
				putimage(PosX + j * MapSize, PosY + i * MapSize, &Man);
				break;
			default:
				break;
			} 
		}	
	}
}
BoxPush::BoxPush(string level)
{
	for (int i = 0; i < MaxH; i++)
	{
		for (int j = 0; j < MaxL; j++)
		{
			map[i][j] = '0';
		}
	}
	len = 0;  hig = 0;
	BoxN = 0; HoleN = 0;
	finish = 0;
	ifstream Mapfile = ifstream(level); //从关卡中读取地图
	fstream Gamefile = fstream(GAMEMAP, ios::out); //写入到 类中
	Gamefile.clear(); //清除原有内容
	int l = 0; int h = 0;
	bool key = true;
	while (true)
	{
		char temp;
		Mapfile.get(temp);
		if (Mapfile.eof() || temp == '#')
		{
			break;
		}
		if (key && temp != '\n')
		{
			l++;
		}
		if (temp == '\n')
		{
			h++;
			key = false;
		}
		Gamefile << temp;
	}
	Gamefile << '#';//添加结束标志
	Gamefile.close();
	Gamefile.open(GAMEMAP, ios::in);
	Mapfile.close();
	this->hig = h;
	this->len = l;
	
	for (int i = 0; i < hig; i++)
	{
		for (int j = 0; j < len; j++)
		{
			char temp;
			Gamefile.get(temp);
			if (temp == '\n')
			{
				j--;//重新读取
				continue;
			}
			if (temp == '#')
			{
				break;//结束
			}
			map[i][j] = temp;	
		}
	}
	Gamefile.close();
	Find_N_Box_Hole();
}
void StartPage(); //开始界面
void ChooseLevelPage(); //选择关卡界面
void AboutPage(); //关于界面
void CheckPage();//查看各关卡成绩界面
void GoOnGame();//继续游戏


int main()
{
	int w = 860; int h = 640;
	BoxPush my = BoxPush(LEVELS[0]);
	initgraph(w, h);
	LoadDate();
	putimage(0, 0, &Background);
	my.Draw(100,100);
	do
	{
		my.MainGame(_getch());
		my.Draw(100,100);
	} while (!my.IsVictory());
	putimage(0, 0, &Win);
	_getch();
	return 0;
}
void LoadDate() //加载图片
{
	loadimage(&Background, L"background.jpg", 860, 640);
	loadimage(&Win, L"win.jpg", 860, 640);
	loadimage(&Man, L"man.jpg", MapSize, MapSize);
	loadimage(&Way, L"way.jpg", MapSize, MapSize);
	loadimage(&Box, L"box.jpg", MapSize, MapSize);
	loadimage(&Hole, L"hole.jpg", MapSize, MapSize);
	loadimage(&Wall, L"wall.jpg", MapSize, MapSize);
	loadimage(&Finish, L"finish.jpg",MapSize, MapSize);
}
void StartPage()
{
}
void ChooseLevelPage()
{
}
void AboutPage()
{

}
void CheckPage()
{

}
void GoOnGame()
{

}
