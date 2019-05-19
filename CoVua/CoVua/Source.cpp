#include <SFML/Graphics.hpp>
#include<iostream>
#include<math.h>
#include <time.h>
#include<stack>
#include<algorithm>// min, max
#include<Windows.h>
#include<sqlext.h>
#include<sqltypes.h>
#include<sql.h>
#include<SFML\Audio.hpp>
#include<TGUI/TGUI.hpp>
#include <TGUI/Font.hpp>
using namespace sf;
using namespace std;
//skdjskdksdksdksdmksdmksmdskm

Vector2f offset(28 + 24, 28 + 48);
RenderWindow window;

int board[8][8] =
{ -1,-2,-3,-4,-5,-3,-2,-1,
-6,-6,-6,-6,-6,-6,-6,-6,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
0, 0, 0, 0, 0, 0, 0, 0,
6, 6, 6, 6, 6, 6, 6, 6,
1, 2, 3, 4, 5, 3, 2, 1 };
// bang diem cho quan trang
int TotAI[8][8] =
{
	0,  0,  0,  0,  0,  0,  0,  0,
	50, 50, 50, 50, 50, 50, 50, 50,
	10, 10, 20, 30, 30, 20, 10, 10,
	5,  5, 10, 25, 25, 10,  5,  5,
	0,  0,  0, 20, 20,  0,  0,  0,
	5, -5,-10,  0,  0,-10, -5,  5,
	5, 10, 10,-20,-20, 10, 10,  5,
	0,  0,  0,  0,  0,  0,  0,  0
};

int MaAI[8][8] =
{
	-50, -40, -30, -30, -30, -30, -40, -50,
	-40, -20, 0, 0, 0, 0, -20, -40,
	-30, 0, 10, 15, 15, 10, 0, -30,
	-30, 5, 15, 20, 20, 15, 5, -30,
	-30, 0, 15, 20, 20, 15, 0, -30 ,
	-30, 5, 10, 15, 15, 10, 5, -30,
	-40, -20, 0, 5, 5, 0, -20, -40,
	-50, -40, -30, -30 , -30, -30, -40, -50
};

int TuongAI[8][8] =
{
	-20, -10, -10, -10, -10, -10, -10, -20,
	-10, 0, 0, 0, 0, 0, 0, -10,
	-10, 0, 5, 10, 10, 5, 0, -10,
	-10, 5, 5, 10, 10, 5, 5, -10,
	-10, 0, 10, 10, 10, 10, 0, -10,
	-10, 10, 10, 10, 10, 10, 10, -10,
	-10, 5, 0, 0, 0, 0, 5, -10,
	-20, -10, -10, -10, -10, -10, -10, -20
};

int XeAI[8][8] =
{
	0, 0, 0, 0, 0, 0, 0, 0,
	5, 10, 10, 10, 10, 10, 10, 5,
	-5, 0, 0, 0, 0, 0, 0, -5 ,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	-5, 0, 0, 0, 0, 0, 0, -5,
	0, 0, 0, 5, 5, 0, 0, 0
};

int HauAI[8][8] =
{
	-20, -10, -10, -5, -5, -10, -10, -20,
	-10, 0, 0, 0, 0, 0, 0, -10,
	-10, 0, 5, 5, 5, 5, 0, -10,
	-5, 0, 5, 5, 5, 5, 0, -5,
	0, 0, 5, 5, 5, 5, 0, -5,
	-10 , 5, 5, 5, 5, 5, 0, -10,
	-10, 0, 5, 0, 0, 0, 0, -10,
	-20, -10, -10, -5, -5, -10, -10, -20
};

int VuaAI[8][8] =
{
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30 ,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-30, -40, -40, -50, -50, -40, -40, -30,
	-20, -30, -30, -40, -40, -30, -30, -20,
	-10, -20, -20, -20, -20, -20, -20, -10,
	20, 20 , 0, 0, 0, 0, 20, 20,
	20, 30, 10, 0, 0, 10, 30, 20
};

typedef struct QuanCo
{
	Sprite s;
	int index, cost;
	int sgrid[9][9];
	float x, y;
};



class GameManager
{
public:
	QuanCo f[33]; //mang luu cac quan co
	Vector2f positiveMove[32]; //vi tri cac nuoc co the di chuyen
	int positiveCount; // so nuoc co the di chuyen
	stack<Vector2f> posS; //luu tru vi tri cac nuoc di
	stack<int> nS; //luu tru index cua quan di
	Font cms;

	void move(int n, Vector2f oldPos, Vector2f newPos); //ham danh co
	void Undo(); //ham quay lai
	void Create();
	void Continue();
	void Continueplay(RenderWindow &window, bool &cont);
	void Menu(RenderWindow &window, bool &cont);
	void Play(RenderWindow &window, bool check, bool &cont); // choi: moi thao tac o day
	void Guide(RenderWindow &window, bool &cont);
	void Save(RenderWindow &window, bool &cont);
	void HighScore(RenderWindow &window, bool &cont);
	void LoadSave(RenderWindow &window, bool &cont);
	bool gameOver();


	void PositiveXe(int n, int x, int y, int grid[9][9]);//tim cac nuoc co the di cua Quan Xe
	void PositiveTuong(int n, int x, int y, int grid[9][9]);
	void PositiveMa(int n, int x, int y, int grid[9][9]);
	void PositiveVua(int n, int x, int y, int grid[9][9]);
	void PositiveTot(int n, int x, int y, int grid[9][9]);

	void IncreasePositive(int i, int j);//tang so nuoc co the di
	void PositiveMoving(int n);//tim cac nuoc co the di ung voi index n
							   //AI
	int CostMove();//gia tri diem cua toan bo ban co ung voi gia tri moi quan
				   //int Minimax(int depth,bool luot);// Chien luoc Minimax 
	int Alpha_Beta(int depth, bool luot, int alpha, int beta);//cat tia alpha beta
	Vector2f getNextMove(bool luot);// tra ve nuoc di tot nhat theo chien luoc phia tren
};

void GameManager::Continue() {

}

int GameManager::Alpha_Beta(int depth, bool luot, int alpha, int beta)
{
	if (depth == 0) {
		return CostMove();
	}
	Vector2f positiveMovetemp[32];//luu lai vi tri cac nuoc co the di
	if (luot == true) {
		int bestMove = -10000;//gia cua bestMove ban dau
		for (int j = 16; j < 32; j++)//cac quan cua nguoi choi
		{
			if (f[j].s.getPosition() == Vector2f(-100, -100))	continue;
			PositiveMoving(j);
			int coun = positiveCount;//ta khong the dung PositiveCount vi no thay doi lien tuc khi ta de quy
			positiveCount = 0;
			for (int i = 0; i < coun; i++)		positiveMovetemp[i] = positiveMove[i];
			for (int i = 0; i < coun; i++)
			{
				move(j, f[j].s.getPosition(), positiveMovetemp[i]);
				bestMove = max(bestMove, Alpha_Beta(depth - 1, !luot, alpha, beta));
				//undo
				Undo();
				alpha = max(alpha, bestMove);
				if (beta <= alpha)		return bestMove;
			}
		}
		return bestMove;
	}
	else {
		int bestMove = 10000; //gia cua bestMove ban dau
		for (int j = 0; j < 16; j++) //quan cua may
		{
			if (f[j].s.getPosition() == Vector2f(-100, -100))	continue;
			PositiveMoving(j);
			int coun = positiveCount;//ta khong the dung PositiveCount vi no thay doi lien tuc khi ta de quy
			positiveCount = 0;
			for (int i = 0; i < coun; i++)		positiveMovetemp[i] = positiveMove[i];
			for (int i = 0; i < coun; i++)
			{
				move(j, f[j].s.getPosition(), positiveMovetemp[i]);
				bestMove = min(bestMove, Alpha_Beta(depth - 1, !luot, alpha, beta));
				//undo
				Undo();
				beta = min(beta, bestMove);
				if (beta <= alpha)		return bestMove;
			}
		}
		return bestMove;
	}
}

void GameManager::IncreasePositive(int i, int j) {
	positiveMove[positiveCount] = Vector2f(i * 56, j * 56) + offset;
	positiveCount++;
}

void GameManager::move(int n, Vector2f oldPos, Vector2f newPos)
{
	posS.push(oldPos);
	posS.push(newPos);
	nS.push(n);
	int y = int((newPos - offset).y / 56); //kiem tra xem co phong hau hay khong
										   //phong hau cho tot  quen chua doi bang diem vi tri,, nhung thuong phong hau la den cuoi roi nen thoi 
	if (y == 0 && f[n].index == 6) {
		nS.push(100); //de ty undo xoa phong hau di
		f[n].index = 4;
		f[n].cost = 90;
		f[n].s.setTextureRect(IntRect(3 * 56, 56, 56, 56));
	}
	if (y == 7 && f[n].index == -6) {
		nS.push(-100);
		f[n].index = -4;
		f[n].cost = -90;
		f[n].s.setTextureRect(IntRect(3 * 56, 0, 56, 56));
	}
	//di chuyen em an vao vi tri moi	
	for (int i = 0; i < 32; i++) {
		if (f[i].s.getPosition() == newPos) {
			f[i].s.setPosition(-100, -100);//di chuyen em bi an ra khoi man hinh
			posS.push(newPos);
			posS.push(Vector2f(-100, -100));
			nS.push(i);
			break;//neu ta dat f[n].s.setPosition(newPos) len truoc ma ko co break=> bi mat not con nay
		}
	}
	f[n].s.setPosition(newPos);
}

void GameManager::Undo()
{
	if (nS.empty() == true)	return;
	int n = nS.top();
	nS.pop();
	Vector2f p = posS.top();//kiem tra xem co = (-100,-100) => day la con bi an
	posS.pop();
	Vector2f q = posS.top();
	posS.pop();
	if (n == 100) {
		n = nS.top();
		nS.pop();
		f[n].index = 6;
		f[n].cost = 10;
		f[n].s.setTextureRect(IntRect(5 * 56, 56, 56, 56));
	}
	if (n == -100) {
		n = nS.top();
		nS.pop();
		f[n].index = -6;
		f[n].cost = -10;
		f[n].s.setTextureRect(IntRect(5 * 56, 0, 56, 56));
	}
	f[n].s.setPosition(q);

	if (p == Vector2f(-100, -100))	 Undo();// luc nay moi dy chuyen con an
}

void GameManager::Continueplay(RenderWindow &window, bool &cont) {
	if (cont)
		Play(window, false, cont);
	else
		Play(window, true, cont);
}

void GameManager::Create() //gan gia tri can thiet vao danh sach Quan co
{
	positiveCount = 0; //so nuoc co the di ban dau duong nhien =0(chua chon gi ca)
	int k = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			//hinh anh va vi tri ban dau
			int n = board[i][j];
			if (!n) continue;
			int x = abs(n) - 1;
			int y = n > 0 ? 1 : 0;
			f[k].index = n;
			f[k].s.setTextureRect(IntRect(56 * x, 56 * y, 56, 56));
			f[k].x = 56 * j + offset.x;
			f[k].y = 56 * i + offset.y;
			f[k].s.setPosition(f[k].x, f[k].y);
			//cost : gia tri cua tung quan co
			int v = 0, g;
			g = abs(f[k].index);
			if (g == 1)			v = 500;
			else if (g == 2 || g == 3)		v = 300;
			else if (g == 4)		v = 900;
			else if (g == 5)		v = 9000;
			else if (g == 6)		v = 100;
			f[k].cost = f[k].index / g * v;
			k++;
		}
	}
	//+ sgrid : tinh diem theo vi tri
	for (int p = 0; p < 32; p++) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (f[p].index == 1)			f[p].sgrid[i][j] = XeAI[i][j];
				else if (f[p].index == -1)		f[p].sgrid[i][j] = -XeAI[7 - i][7 - j];
				else if (f[p].index == 2)		f[p].sgrid[i][j] = MaAI[i][j];
				else if (f[p].index == -2)		f[p].sgrid[i][j] = -MaAI[7 - i][7 - j];
				else if (f[p].index == 3)		f[p].sgrid[i][j] = TuongAI[i][j];
				else if (f[p].index == -3)		f[p].sgrid[i][j] = -TuongAI[7 - i][7 - j];
				else if (f[p].index == 4)		f[p].sgrid[i][j] = HauAI[i][j];
				else if (f[p].index == -4)		f[p].sgrid[i][j] = -HauAI[7 - i][7 - j];
				else if (f[p].index == 5)		f[p].sgrid[i][j] = VuaAI[i][j];
				else if (f[p].index == -5)		f[p].sgrid[i][j] = -VuaAI[7 - i][7 - j];
				else if (f[p].index == 6)		f[p].sgrid[i][j] = TotAI[i][j];
				else if (f[p].index == -6)		f[p].sgrid[i][j] = -TotAI[7 - i][7 - j];
			}
		}
	}
}

Vector2f GameManager::getNextMove(bool luot)
{
	Vector2f oldPos, newPos, oldPostemp, newPostemp;// ta can tim vi tri co minimax nho nhat de ung voi may( quan den)
	int minimaxtemp = 10000, minimax = 10000;
	int count1, n;
	Vector2f positiveMovetemp[32];

	for (int i = 0; i < 16; i++)
	{
		if (f[i].s.getPosition() == Vector2f(-100, -100))	continue;
		//////
		PositiveMoving(i);
		count1 = positiveCount;//khong the dung PositiveCount vi no thay doi lien tuc khi ta de quy
		positiveCount = 0;
		///set///
		for (int k = 0; k < count1; k++)	positiveMovetemp[k] = positiveMove[k];
		//set oldPos va newPos  tam thoi
		oldPostemp = f[i].s.getPosition();
		//newPostemp=positiveMove[0];
		for (int j = 0; j < count1; j++)
		{
			move(i, oldPostemp, positiveMovetemp[j]);
			int alpha = -9999, beta = 9999;
			int temp = Alpha_Beta(3, !luot, alpha, beta);
			if (minimaxtemp > temp) {
				newPostemp = positiveMovetemp[j];
				minimaxtemp = temp;
			}
			Undo();
		}
		if (minimax > minimaxtemp) {
			minimax = minimaxtemp;
			oldPos = oldPostemp;
			newPos = newPostemp;
			n = i;
		}
	}
	//lay cac thong tin nuoc di
	posS.push(oldPos);//luu tam o trong stack ty ra ngoai xoa di
	nS.push(n);
	return newPos;
}

bool GameManager::gameOver()
{
	if (f[4].s.getPosition() == Vector2f(-100, -100)) {
		cout << endl << "          Nguoi Choi THang     !!!Hoan Ho!!!" << endl;
		return true;
	}
	if (f[28].s.getPosition() == Vector2f(-100, -100)) {
		cout << endl << "          May THang     !!!Ha Ha!!!" << endl;
		return true;
	}
}
int GameManager::CostMove()// don gian con nao bi chet thi khong tinh diem cua con day
{
	int s = 0;
	for (int i = 0; i < 32; i++)
	{
		Vector2f p = f[i].s.getPosition();
		if (p == Vector2f(-100, -100))	continue;//neu no da bi out-> ko tinh diem
		int x = int((p - offset).x / 56);
		int y = int((p - offset).y / 56);
		s += f[i].cost;
		s += f[i].sgrid[y][x];// truc tao do trong game theo chieu nay
	}
	return s;
}

void GameManager::PositiveTot(int n, int x, int y, int grid[9][9])
{
	int k = grid[x][y] / abs(grid[x][y]);// 1 hoac -1
	if ((y == 1 || y == 6) && grid[x][y - k] == 0 && grid[x][y - 2 * k] == 0 && y - 2 * k >= 0 && y - 2 * k < 8)	IncreasePositive(x, y - 2 * k);
	if (grid[x][y - k] == 0 && y - k >= 0 && y - k < 8)												IncreasePositive(x, y - k);
	if (grid[x + 1][y - k] * grid[x][y] < 0 && y - k >= 0 && y - k < 8 && x + 1 < 8)							IncreasePositive(x + 1, y - k);
	if (grid[x - 1][y - k] * grid[x][y] < 0 && y - k >= 0 && y - k < 8 && x - 1 >= 0)						IncreasePositive(x - 1, y - k);
}

void GameManager::PositiveVua(int n, int x, int y, int grid[9][9])//xet 8 vi tri co the di cua vua
{
	if ((grid[x + 1][y] == 0 || grid[x][y] * grid[x + 1][y] < 0) && x + 1 < 8)					IncreasePositive(x + 1, y);
	if ((grid[x - 1][y] == 0 || grid[x][y] * grid[x - 1][y] < 0) && x - 1 >= 0)					IncreasePositive(x - 1, y);
	if ((grid[x + 1][y + 1] == 0 || grid[x][y] * grid[x + 1][y + 1] < 0) && x + 1 < 8 && y + 1 < 8)		IncreasePositive(x + 1, y + 1);
	if ((grid[x - 1][y + 1] == 0 || grid[x][y] * grid[x - 1][y + 1] < 0) && x - 1 >= 0 && y + 1 < 8)		IncreasePositive(x - 1, y + 1);
	if ((grid[x][y + 1] == 0 || grid[x][y] * grid[x][y + 1] < 0) && y + 1 < 8)					IncreasePositive(x, y + 1);
	if ((grid[x - 1][y - 1] == 0 || grid[x][y] * grid[x - 1][y - 1] < 0) && x - 1 >= 0 && y - 1 >= 0)	IncreasePositive(x - 1, y - 1);
	if ((grid[x + 1][y - 1] == 0 || grid[x][y] * grid[x + 1][y - 1] < 0) && y - 1 >= 0 && x + 1 < 8)		IncreasePositive(x + 1, y - 1);
	if ((grid[x][y - 1] == 0 || grid[x][y] * grid[x][y - 1] < 0) && y - 1 >= 0)					IncreasePositive(x, y - 1);
}

void GameManager::PositiveMa(int n, int x, int y, int grid[9][9])//xet 8 vi tri co the di cua ma
{
	if ((grid[x + 2][y + 1] == 0 || grid[x][y] * grid[x + 2][y + 1] < 0) && x + 2 < 8 && y + 1 < 8)		IncreasePositive(x + 2, y + 1);
	if ((grid[x + 2][y - 1] == 0 || grid[x][y] * grid[x + 2][y - 1] < 0) && y - 1 >= 0 && x + 2 < 8)		IncreasePositive(x + 2, y - 1);
	if ((grid[x - 2][y + 1] == 0 || grid[x][y] * grid[x - 2][y + 1] < 0) && x - 2 >= 0 && y + 1 < 8)		IncreasePositive(x - 2, y + 1);
	if ((grid[x - 2][y - 1] == 0 || grid[x][y] * grid[x - 2][y - 1] < 0) && x - 2 >= 0 && y - 1 >= 0)	IncreasePositive(x - 2, y - 1);
	if ((grid[x + 1][y + 2] == 0 || grid[x][y] * grid[x + 1][y + 2] < 0) && x + 1 < 8 && y + 2 < 8)		IncreasePositive(x + 1, y + 2);
	if ((grid[x - 1][y + 2] == 0 || grid[x][y] * grid[x - 1][y + 2] < 0) && x - 1 >= 0 && y + 2 < 8)		IncreasePositive(x - 1, y + 2);
	if ((grid[x + 1][y - 2] == 0 || grid[x][y] * grid[x + 1][y - 2] < 0) && y - 2 >= 0 && x + 1 < 8)		IncreasePositive(x + 1, y - 2);
	if ((grid[x - 1][y - 2] == 0 || grid[x][y] * grid[x - 1][y - 2] < 0) && x - 1 >= 0 && y - 2 >= 0)	IncreasePositive(x - 1, y - 2);
}

void GameManager::PositiveTuong(int n, int x, int y, int grid[9][9])//tu vi tri (x,y) xet ra 4 huong cheo
{
	for (int i = x + 1, j = y + 1; (i < 8 && j < 8); i++, j++)
	{
		if (grid[i][j] != 0) {
			if (grid[i][j] * grid[x][y] < 0)		IncreasePositive(i, j);
			break;
		}
		IncreasePositive(i, j);
	}
	for (int i = x + 1, j = y - 1; (i < 8 && j >= 0); i++, j--)
	{
		if (grid[i][j] != 0) {
			if (grid[i][j] * grid[x][y] < 0)		IncreasePositive(i, j);
			break;
		}
		IncreasePositive(i, j);
	}
	for (int i = x - 1, j = y + 1; (i >= 0 && j < 8); i--, j++)
	{
		if (grid[i][j] != 0) {
			if (grid[i][j] * grid[x][y] < 0)		IncreasePositive(i, j);
			break;
		}
		IncreasePositive(i, j);
	}
	for (int i = x - 1, j = y - 1; (i >= 0 && j >= 0); i--, j--)
	{
		if (grid[i][j] != 0) {
			if (grid[i][j] * grid[x][y] < 0)		IncreasePositive(i, j);
			break;
		}
		IncreasePositive(i, j);
	}
}

void GameManager::PositiveXe(int n, int x, int y, int grid[9][9])//tu vi tri (x,y) xet ra 4 huong ngang
{
	for (int i = x + 1; i < 8; i++)
	{
		if (grid[i][y] != 0) {
			if (grid[i][y] * grid[x][y] < 0)		IncreasePositive(i, y);
			break;
		}
		IncreasePositive(i, y);
	}
	for (int i = x - 1; i >= 0; i--)
	{
		if (grid[i][y] != 0) {
			if (grid[i][y] * grid[x][y] < 0)		IncreasePositive(i, y);
			break;
		}
		IncreasePositive(i, y);
	}
	for (int j = y + 1; j < 8; j++)
	{
		if (grid[x][j] != 0) {
			if (grid[x][j] * grid[x][y] < 0)		IncreasePositive(x, j);
			break;
		}
		IncreasePositive(x, j);
	}
	for (int j = y - 1; j >= 0; j--)
	{
		if (grid[x][j] != 0) {
			if (grid[x][j] * grid[x][y] < 0)		IncreasePositive(x, j);
			break;
		}
		IncreasePositive(x, j);
	}
}

void GameManager::PositiveMoving(int n)
{
	Vector2f pos = f[n].s.getPosition() - offset;
	int x = pos.x / 56;
	int y = pos.y / 56;

	int grid[9][9];//mang luoi(8x8) luu lai cac vi tri ban co: 
	Vector2i vtri;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			grid[i][j] = 0;// neu khong co quan co nao o O nay thi =0
	for (int j = 0; j < 32; j++)
	{
		if (f[j].s.getPosition() == Vector2f(-100, -100))	continue;
		vtri = Vector2i(f[j].s.getPosition() - offset);
		grid[vtri.x / 56][vtri.y / 56] = f[j].index;// neu co = index cua quan co
	}

	if (abs(f[n].index) == 1)		PositiveXe(n, x, y, grid);//xe
	else if (abs(f[n].index) == 2)		PositiveMa(n, x, y, grid);//ma
	else if (abs(f[n].index) == 3)		PositiveTuong(n, x, y, grid);//tuong	
	else if (abs(f[n].index) == 4)//hau: hop lai cac nuoc cua ca xe va tuong
	{
		PositiveXe(n, x, y, grid);
		PositiveTuong(n, x, y, grid);
	}
	else if (abs(f[n].index) == 5)		PositiveVua(n, x, y, grid);//vua
	else 		PositiveTot(n, x, y, grid); //tot
}

void GameManager::Guide(RenderWindow &window, bool &cont)
{

	tgui::Gui gui(window);
	tgui::Theme theme{ "themes/BabyChess.txt" };
	tgui::Picture::Ptr te[8];
	te[0] = tgui::Picture::create("Graphics/guide1.png");
	te[1] = tgui::Picture::create("Graphics/guide2.png");
	te[2] = tgui::Picture::create("Graphics/guide3.png");
	te[3] = tgui::Picture::create("Graphics/guide4.png");
	te[4] = tgui::Picture::create("Graphics/guide5.png");
	te[5] = tgui::Picture::create("Graphics/guide6.png");
	te[6] = tgui::Picture::create("Graphics/guide7.png");
	te[7] = tgui::Picture::create("Graphics/guide8.png");
	//Sprite sBack(back);
	//sBack.setPosition(0, 350);

	auto back = tgui::Button::create(L"Back");
	back->setRenderer(theme.getRenderer("Button"));
	back->setPosition(550, 540);
	back->setSize(200, 30);
	back->setTextSize(18);
	back->setInheritedFont("Graphics/windsorb.ttf");
	back->connect("pressed", [&]() { GameManager::Menu(window, cont); });
	int count = 0;
	//Vector2i pos;//vitri chuot khi click
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		Event event;

		//window.draw(guide);
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Left)
				{
					if (count > 0) count--;


				}
				else if (event.key.code == Keyboard::Right)
				{
					if (count < 7) {
						count++;


					}
				}


			}

			/*if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					pos = Mouse::getPosition(window) - Vector2i(offset);
				}*/


			gui.handleEvent(event);

		}



		gui.add(te[count]);
		//window.draw(sBack);
		gui.add(back);
		gui.draw();
		window.display();
	}
}

void GameManager::Menu(RenderWindow &window, bool &cont)
{
	tgui::Gui gui(window);

	tgui::Theme theme{ "themes/BabyChess.txt" };
	//Load ảnh nền
	gui.add(tgui::Picture::create("Graphics/background.jpg"));
	/*backgroundtexture.loadFromFile("Graphics/background.jpg");
	backgroundsprite.setTexture(backgroundtexture);*/
	auto image = tgui::Picture::create("Graphics/menu.png");
	image->setPosition(270, 60);
	gui.add(image);
	/*menu.loadFromFile("Graphics/menu.png");
	image.setTexture(menu);*/
	auto start = tgui::Button::create(L"Chơi mới");
	start->setRenderer(theme.getRenderer("Button"));
	start->setPosition(290, 300);
	start->setSize(200, 30);
	start->setTextSize(18);
	start->setInheritedFont("Graphics/windsorb.ttf");
	start->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(1000));
	start->connect("pressed", [&]() { GameManager::Play(window, true, cont); });
	gui.add(start);

	auto resume = tgui::Button::create(L"Chơi tiếp");
	resume->setRenderer(theme.getRenderer("Button"));
	resume->setPosition(290, 350);
	resume->setSize(200, 30);
	resume->setTextSize(18);
	resume->setInheritedFont("Graphics/windsorb.ttf");
	resume->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(1200));
	resume->connect("pressed", [&]() { GameManager::Continueplay(window, cont); });
	gui.add(resume);


	auto load_save = tgui::Button::create(L"Load");
	load_save->setRenderer(theme.getRenderer("Button"));
	load_save->setPosition(290, 400);
	load_save->setSize(200, 30);
	load_save->setTextSize(18);
	load_save->setInheritedFont("Graphics/windsorb.ttf");
	load_save->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(1400));
	load_save->connect("pressed", [&]() { GameManager::LoadSave(window, cont); });
	gui.add(load_save);

	auto highScore = tgui::Button::create(L"Điểm cao");
	highScore->setRenderer(theme.getRenderer("Button"));
	highScore->setPosition(290, 450);
	highScore->setSize(200, 30);
	highScore->setTextSize(18);
	highScore->setInheritedFont("Graphics/windsorb.ttf");
	highScore->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(1600));
	highScore->connect("pressed", [&]() { GameManager::HighScore(window, cont); });
	gui.add(highScore);

	auto guide = tgui::Button::create(L"Hướng dẫn");
	guide->setRenderer(theme.getRenderer("Button"));
	guide->setPosition(290, 500);
	guide->setSize(200, 30);
	guide->setTextSize(18);
	guide->setInheritedFont("Graphics/windsorb.ttf");
	guide->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(1800));
	guide->connect("pressed", [&]() { GameManager::Guide(window, cont); });
	gui.add(guide);

	auto exit = tgui::Button::create(L"Thoát");
	exit->setRenderer(theme.getRenderer("Button"));
	exit->setPosition(290, 550);
	exit->setSize(200, 30);
	exit->setTextSize(18);
	exit->setInheritedFont("Graphics/windsorb.ttf");
	exit->showWithEffect(tgui::ShowAnimationType::SlideFromLeft, sf::milliseconds(2000));
	exit->connect("pressed", [&]() { window.close(); });
	gui.add(exit);


	while (window.isOpen())
	{
		Event event;
		Vector2f oldPos, newPos;// luu vi tri click lan1 va lan2
		int n = 0, click = 0, count = 0;
		Vector2i pos;//vitri chuot khi click
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					pos = Mouse::getPosition(window) - Vector2i(offset);
				}
			gui.handleEvent(event);
		}
		window.clear(Color::Color(190, 218, 168, 255));
		gui.draw();
		window.display();
	}
}

void GameManager::Play(RenderWindow &window, bool check, bool &cont)
{
	RenderWindow w_save;
	tgui::Gui gui(window);

	tgui::Theme theme{ "themes/BabyChess.txt" };
	gui.add(tgui::Picture::create("Graphics/background.jpg"));
	Texture t1, t2, t3, t4;
	SoundBuffer buf1;
	buf1.loadFromFile("Graphics/kimochi.wav");

	Sound sound1;
	sound1.setBuffer(buf1);
	sound1.play();
	t1.loadFromFile("Graphics/figures.png");
	auto board = tgui::Picture::create("Graphics/board1.png");
	board->setPosition(25, 48);
	gui.add(board);
	auto note = tgui::Picture::create("Graphics/note.png");
	note->setPosition(545, 34);
	gui.add(note);

	t3.loadFromFile("Graphics/no.png");



	auto undo = tgui::Button::create("Undo");
	undo->setRenderer(theme.getRenderer("Button"));
	undo->setSize(100, 30);
	undo->setPosition(650, 300);
	undo->setTextSize(15);
	undo->setInheritedFont("Graphics/windsorb.ttf");
	undo->connect("pressed", [&]() { GameManager::Undo(); GameManager::Undo(); });
	gui.add(undo);

	auto back = tgui::Button::create("Back");
	back->setRenderer(theme.getRenderer("Button"));
	back->setSize(100, 30);
	back->setPosition(650, 350);
	back->setTextSize(15);
	back->setInheritedFont("Graphics/windsorb.ttf");
	back->connect("pressed", [&]() { sound1.stop(); bool cont = true; GameManager::Menu(window, cont); });
	gui.add(back);

	auto save = tgui::Button::create("Save");
	save->setRenderer(theme.getRenderer("Button"));
	save->setSize(100, 30);
	save->setPosition(650, 400);
	save->setTextSize(15);
	save->setInheritedFont("Graphics/windsorb.ttf");
	save->connect("pressed", [&]() { GameManager::Save(w_save, cont); });
	gui.add(save);


	for (int i = 0; i < 32; i++) f[i].s.setTexture(t1);
	Sprite sBoard(t2);
	Sprite sPositive(t3);
	Sprite sBackplay(t4);
	sBackplay.setPosition(520, 100);
	if (check)	Create();//khoi tao

	bool LuotChoi = true;//luot choi : = true=> nguoi ... =false => may
	Vector2f oldPos, newPos;// luu vi tri click lan1 va lan2
	int n = 0, click = 0, count = 0;
	Vector2i pos;//vitri chuot khi click
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
			////move back//////

			/////click///////
			if (e.type == Event::MouseButtonPressed)
				if (e.key.code == Mouse::Left)
				{
					pos = Mouse::getPosition(window) - Vector2i(offset);
					click++;

				}
			gui.handleEvent(e);

		}
		if (LuotChoi == true)
		{
			if (click == 1) {
				bool isMove = false;
				for (int i = 16; i < 32; i++)
				{
					if (f[i].s.getGlobalBounds().contains(pos.x + offset.x, pos.y + offset.y))
					{
						isMove = true;
						n = i;
						f[n].s.setColor(Color::Green);
						oldPos = f[n].s.getPosition();
					}
				}
				if (!isMove)		click = 0;
				else { PositiveMoving(n); count = positiveCount; positiveCount = 0; }
			}
			if (click == 2)
			{
				f[n].s.setColor(Color::White);
				int x = pos.x / 56;			int y = pos.y / 56;
				newPos = Vector2f(x * 56, y * 56) + offset;
				//chi di chuyen trong vung positiveMove
				for (int i = 0; i < count; i++)
				{
					if (positiveMove[i] == newPos) {
						move(n, oldPos, newPos);
						LuotChoi = !LuotChoi;
					}
				}
				//reset
				count = 0;
				click = 0;
			}
		}
		else  //computer moving
		{
			newPos = getNextMove(LuotChoi);
			int c = nS.top();			nS.pop();//lay dk thong tin roi xoa di
			oldPos = posS.top();		posS.pop();//vi ham move tu nhet trong stack roi
			move(c, oldPos, newPos);
			LuotChoi = !LuotChoi;
			//reset	
			click = 0;
		}
		window.clear(Color::Color(190, 218, 168, 255));
		if (gameOver())	continue;
		////// draw  ///////
		window.draw(sBackplay);

		gui.draw();
		for (int i = 0; i < count; i++) {
			sPositive.setPosition(positiveMove[i]);
			window.draw(sPositive);
		}
		for (int i = 0; i < 32; i++) {
			window.draw(f[i].s);
		}


		window.display();

	}
}
void GameManager::Save(RenderWindow &window, bool &cont) {
	window.create(VideoMode(300, 225), "Save", Style::None);
	tgui::Gui gui(window);
	tgui::Theme theme{ "themes/TransparentGrey.txt" };

	auto pic = tgui::Picture::create("Graphics/save.png");

	pic->setSize(300, 225);
	gui.add(pic);
	auto name = tgui::EditBox::create();
	name->setRenderer(theme.getRenderer("EditBox"));
	name->setSize(237, 35);
	name->setPosition(31, 75);
	name->setTextSize(18);
	name->setInheritedFont("Graphics/windsorb.ttf");
	gui.add(name);
	auto cancel = tgui::Button::create("");
	cancel->setRenderer(theme.getRenderer("Button"));
	cancel->setSize(82, 49);
	cancel->setPosition(163, 140);
	cancel->setInheritedFont("Graphics/windsorb.ttf");
	cancel->connect("pressed", [&]() { window.close(); });
	gui.add(cancel);

	auto save = tgui::Button::create("");
	save->setRenderer(theme.getRenderer("ChatBox"));
	save->setSize(82, 49);
	save->setPosition(53, 140);
	save->setInheritedFont("Graphics/windsorb.ttf");
	save->connect("pressed", [&]() { window.close(); });
	gui.add(save);

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
			gui.handleEvent(e);
		}

		window.clear();
		gui.draw();
		window.display();
	}

}
void GameManager::LoadSave(RenderWindow &window, bool &cont) {
	tgui::Gui gui(window);
	tgui::Theme theme{ "themes/LoadHigh.txt" };
	//cms.loadFromFile("Graphics/comicsans.ttf");


	auto pic = tgui::Picture::create("Graphics/saveload.png");
	gui.add(pic);
	auto play = tgui::Button::create("PLAY");
	play->setRenderer(theme.getRenderer("Button"));
	play->setSize(220, 59);
	play->setPosition(291, 102);
	play->setTextSize(38);
	play->setInheritedFont("Graphics/windsorb.ttf");
	play->connect("pressed", [&]() { GameManager::Play(window, true, cont); });
	gui.add(play);
	auto back = tgui::Button::create("BACK");
	back->setRenderer(theme.getRenderer("Button"));
	back->setSize(186, 50);
	back->setPosition(317, 453);
	back->setTextSize(30);
	back->setInheritedFont("Graphics/windsorb.ttf");
	back->connect("pressed", [&]() { GameManager::Menu(window, cont); });
	gui.add(back);
	auto name = tgui::Button::create("HOAN");
	name->setRenderer(theme.getRenderer("Label"));
	name->setSize(256, 39);
	name->setPosition(272, 222);
	name->setTextSize(27);
	name->setInheritedFont("Graphics/windsorb.ttf");
	gui.add(name);

	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
			gui.handleEvent(e);
		}

		window.clear();
		gui.draw();
		window.display();
	}
}
void GameManager::HighScore(RenderWindow &window, bool &cont) {
	tgui::Gui gui(window);
	tgui::Theme theme{ "themes/LoadHigh.txt" };
	//cms.loadFromFile("Graphics/comicsans.ttf");


	auto pic = tgui::Picture::create("Graphics/highload.png");
	gui.add(pic);
	auto play = tgui::Button::create("PLAY");
	play->setRenderer(theme.getRenderer("Button"));
	play->setSize(220, 59);
	play->setPosition(291, 102);
	play->setTextSize(38);
	play->setInheritedFont("Graphics/windsorb.ttf");
	play->connect("pressed", [&]() { GameManager::Play(window, true, cont); });
	gui.add(play);
	auto back = tgui::Button::create("BACK");
	back->setRenderer(theme.getRenderer("Button"));
	back->setSize(186, 50);
	back->setPosition(317, 453);
	back->setTextSize(30);
	back->setInheritedFont("Graphics/windsorb.ttf");
	back->connect("pressed", [&]() { GameManager::Menu(window, cont); });
	gui.add(back);
	auto name = tgui::Button::create("HOAN             ");
	name->setRenderer(theme.getRenderer("Label"));
	name->setSize(256, 39);
	name->setPosition(272, 222);
	name->setTextSize(27);
	name->setInheritedFont("Graphics/windsorb.ttf");
	gui.add(name);
	auto highScore = tgui::Label::create("999999");
	highScore->setRenderer(theme.getRenderer("EditBox"));
	highScore->setPosition(403, 222);
	highScore->setTextSize(30);
	highScore->setInheritedFont("Graphics/windsorb.ttf");
	gui.add(highScore);
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
			gui.handleEvent(e);
		}

		window.clear();
		gui.draw();
		window.display();
	}
}

int main()
{
	GameManager gm;
	bool cont = false;
	RenderWindow window(VideoMode(800, 600), "Chess Game", Style::Close);
	Image icon;
	icon.loadFromFile("Graphics/icon.png");
	window.setFramerateLimit(60); //60FPS
	window.setIcon(32, 32, icon.getPixelsPtr());
	gm.Menu(window, cont);
	//gm.HighScore(window, cont);

	//gm.Save(window, cont);
	//auto theme = tgui::Theme::create("TGUI/widgets/Black.txt");
	/*tgui::Gui gui(window);
	tgui::Theme theme{ "themes/Black.txt" };*/
	/*auto menu = tgui::MenuBar::create();
	menu->setRenderer(theme.getRenderer("MenuBar"));
	menu->setSize(static_cast<float>(window.getSize().x), 22.f);
	menu->addMenu("File");
	menu->addMenuItem("Load");
	menu->addMenuItem("Save");
	menu->addMenuItem("Exit");
	menu->addMenu("Edit");
	menu->addMenuItem("Copy");
	menu->addMenuItem("Paste");
	menu->addMenu("Help");
	menu->addMenuItem("About");
	gui.add(menu);*/
	/*auto editBox = tgui::EditBox::create();
	editBox->setRenderer(theme.getRenderer("EditBox"));
	editBox->setSize(200, 25);
	editBox->setTextSize(18);
	editBox->setPosition(10, 270);
	editBox->setDefaultText("Click to edit text...");
	gui.add(editBox);*/

	// Lấy dữ liệu từ textbox có tiếng việt toWideString
	/*editBox->getText().toWideString();
	while (window.isOpen()) {
		sf::Event e;
		while (window.pollEvent(e)) {
			if (e.type == sf::Event::Closed)
				window.close();
			gui.handleEvent(e);
		}

		window.clear();
		gui.draw();
		window.display();
	}*/

}