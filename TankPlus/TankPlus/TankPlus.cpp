// TankPlus.cpp : Defines the entry point for the application.
//
/************************************************************************/
/*	����Ŀ�ģ��ļ���ʹ��
	�����ܣ��Ľ���̹�˴�ս������Ϸ�����Ķ�������������������ֲ�ͬ�ĵз�̹��
		���̹�����·����С����������̹��ǰ�����򣬿ո�������ڵ���
		��Ϸ�߱��˶�ȡini�ļ���txt�ļ������������ڴ�����������Ϸ����
		����ͨ����ȡ�ⲿ�ļ��ķ������������Ӳ���룬������Ϸά��
		�߻���Ա��������Ϸexe������ϵ�����£�ͨ�������ⲿ�ļ��ķ�ʽ�����ϵ�����Ϸ��ֵ
		ͬʱ����Ϸ�е��������ͼƬ�ķ�ʽ������������Ϸ�������ϰ���
	�����߸Ľ�:���������ϰ�����������ܶ����Ϸ������ز����������ⲿ�ļ���
	��д�ߣ������ף�hanhonglei@sina.com��*/
/************************************************************************/

#include "stdafx.h"
#include "TankPlus.h"
#include <time.h>
#include <math.h>
#include <stdio.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

enum Dir{UP, DOWN, LEFT, RIGHT, NONE};	// �˶�������ܵ��˶�����

typedef struct				// ��Ϸ�е�ʵ��ṹ��
{
	int x, y;				// λ��
	Dir dir;				// ����
	int v;					// ����
	int s;					// �߳���������
	int b;					// �Ƿ����ӵ�
	int p;					// �Ƿ�ֹͣ,ֻ����Ҳſ���ֹͣ
	int e;					// �Ƿ��ǵ���
	HBITMAP a[4];			// λͼ,4������
}Entity;

HBITMAP tank1[4],tank2[4],tank3[4],bulletPic[4],grass,background;	// ���������λͼ���
#define MAX_ENEMY 16		// ��������Ŀ
#define MAX_BULLETS 32		// ����ӵ���Ŀ
#define MAX_GRASS 64		// �����ϰ�������
int nLife = 3;				// �������
int nScore = 0;				// ��ҵ÷�
int nBullet = 0;			// ��Ҵ�����ӵ�����
int nEnemyBullet = 0;		// ���˷������ӵ�����
int nEnemy = 0;				// ��ǰ�ĵ�������
int nGrass = 0;				// �ϰ�������
int timeStep = 20;			// ��ʱ��ʱ����
int sz = 50;				// ̹�˳ߴ�
int velf = 4;				// ����̹������
int vels = 2;				// ����̹������
int szb = 20;				// �ӵ��ߴ�
int velb = 6;				// �ӵ�����
int enemyFirePer = 300;		// ���˷����ӵ����������
int enemyDirPer = 200;		// ��������ı䷽��ı���
int bFire = 0;				// �Ƿ��ڿ���״̬

Entity grasses[MAX_GRASS];	// �ݵ�
Entity enemys[MAX_ENEMY];	// ��������
Entity player;				// ���
Entity bullets[MAX_BULLETS];// ����ӵ�����
Entity enemyBullets[MAX_BULLETS];// �����ӵ�����
int wndWidth = 0;	int wndHeight = 0;  // ���ڳߴ�

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

// ���Ʋ���ָ������Ϸʵ��
void DrawEntity(HDC hdc, const Entity *ent)
{
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP bmp = ent->a[int(ent->dir)%4];
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, bmp);	// ѡ�����Ƶ�λͼ
	BITMAP bm;
	GetObject(bmp, sizeof(bm), &bm);
	SetStretchBltMode(hdc,STRETCH_HALFTONE);				// �趨λͼ����ģʽΪSTRETCH_HALFTONE,�����������
	// �Ա���͸���ķ�ʽ����λͼ,��ɫ��Ϊ͸��ɫ����Ҫ���� Library Msimg32.lib
	TransparentBlt(hdc,ent->x-ent->s/2, ent->y-ent->s/2, ent->s, ent->s, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight,RGB(255,255,255));
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
}
// ����������Ϸ����,�����е��ø��ԵĻ��ƺ�����������
void DrawScene(HDC hdc)
{
	// ���Ʊ���λͼ
	HDC hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, background);
	BITMAP bm;
	GetObject(background, sizeof(bm), &bm);
	SetStretchBltMode(hdc,STRETCH_HALFTONE);
	BitBlt(hdc, 0, 0, wndWidth, wndHeight, hdcMem, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	// ��ӡ��Ϸ��ʾ��Ϣ
	HFONT hf;
	WCHAR str[32];
	long lfHeight;
	lfHeight = -MulDiv(16, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	hf = CreateFont(lfHeight, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, L"Times New Roman");
	HFONT hfOld = (HFONT)SelectObject(hdc, hf);
	SetBkMode(hdc, TRANSPARENT);	// ������͸��ɫ
	if (nLife <= 0)					// ����������Ϊ0,����Ϸ����
	{
		SetTextColor(hdc, RGB(122, 0, 0));
		TextOut(hdc, wndWidth/2-100, wndHeight/2-40,L"Game Over",9);
		SelectObject(hdc, hfOld);
		return;
	}	
	SetTextColor(hdc, RGB(100, 100, 100));
	wsprintf(str, L"Life:%d Score:%d", nLife, nScore);	
	TextOut(hdc, wndWidth/2-100, wndHeight/2-40,str,wcslen(str));

	SelectObject(hdc, hfOld);		// �ָ�Ĭ������
	DeleteObject(hf);

	// ������Ϸʵ��
	Entity* ent = NULL;
	for (int i = 0; i < nEnemy; i++)	// ����
	{
		ent = enemys+i;
		DrawEntity(hdc, ent);
	}
	for (int i = 0; i < nBullet; i++)	// ����ڵ�
	{
		ent = bullets+i;
		DrawEntity(hdc, ent);
	}
	for (int i = 0; i < nEnemyBullet; i++)	// �����ڵ�
	{
		ent = enemyBullets+i;
		DrawEntity(hdc, ent);
	}
	for (int i = 0; i < nGrass; i++)	// �����е��ϰ���
	{
		ent = grasses+i;
		DrawEntity(hdc, ent);
	}

	DrawEntity(hdc, &player);			// ���
}
// ���������Ϣ
void ResetPlayer()
{
	player.s = sz;
	player.b = 0;
	memcpy(player.a, tank1, 4*sizeof(Dir));
	player.dir = UP;
	player.v = vels;
	player.x = wndWidth/2;
	player.y = wndHeight-sz;
	player.p = 1;
	player.e = 0;
}
// ͨ��ini�ļ���ȡ��ʼ����Ϣ
void ReadIni()
{
	timeStep=GetPrivateProfileInt(L"Global", L"timeStep",timeStep, L"Resources\\Init.ini");
	sz = GetPrivateProfileInt(L"Enemy", L"size",sz, L"Resources\\Init.ini");
	velf = GetPrivateProfileInt(L"Enemy", L"velf",velf, L"Resources\\Init.ini");
	vels = GetPrivateProfileInt(L"Enemy", L"vels",vels, L"Resources\\Init.ini");
	enemyFirePer = GetPrivateProfileInt(L"Enemy", L"firePer",enemyFirePer, L"Resources\\Init.ini");
	enemyDirPer = GetPrivateProfileInt(L"Enemy", L"dirPer",enemyDirPer, L"Resources\\Init.ini");
	nLife = GetPrivateProfileInt(L"Player", L"nLife",nLife, L"Resources\\Init.ini");
	szb = GetPrivateProfileInt(L"Bullet", L"size",szb, L"Resources\\Init.ini");
	velb = GetPrivateProfileInt(L"Bullet", L"vel",velb, L"Resources\\Init.ini");
}
// ��ȡ��ͼ�����ļ�,���Ϊ1�ĵط����ϰ���
void InitMap()
{
	FILE *f = fopen("Resources\\Map.txt", "r");	// �򿪵�ͼ�����ļ�
	if (f == NULL)
		return;
	char line[MAX_GRASS];
	int nLine = 0;
	while(!feof(f))
	{
		fgets(line, MAX_GRASS, f);				// ��ȡ�ļ��е�ÿһ��(���ַ�����ʽ)
		for (int i = 0; line[i] != '\0'; i++)	
		{
			if (line[i] == '1')					// �ַ�1��ʾ�˴����ϰ���
			{
				if (nGrass > MAX_GRASS)
					break;
				grasses[nGrass].s = sz;
				grasses[nGrass].b = 0;
				grasses[nGrass].e = 0;
				grasses[nGrass].dir = NONE;
				grasses[nGrass].v = 0;
				grasses[nGrass].a[0] = grasses[nGrass].a[1] = grasses[nGrass].a[2] = grasses[nGrass].a[3] = grass;
				grasses[nGrass].x = sz/2+sz*i;
				grasses[nGrass].y = sz/2+sz*nLine;
				grasses[nGrass].p = 0;
				nGrass++;
			}
		}
		nLine++;
	}
	fclose(f);		// ��ȡ��Ϲر��ļ�
}
// ��Ϸ��ʼ��
void Init()
{
	// ���ȶ�ȡ�����ļ��еĲ������ȫ�ֱ���
	ReadIni();

	//��Ӳ������ͼƬ
	tank1[0] = (HBITMAP)LoadImage( NULL, L"Resources\\TankBlue.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank2[0] = (HBITMAP)LoadImage( NULL, L"Resources\\TankYellow.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank3[0] = (HBITMAP)LoadImage( NULL, L"Resources\\TankLarge.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	bulletPic[0] = (HBITMAP)LoadImage( NULL, L"Resources\\bullet.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank1[1] = (HBITMAP)LoadImage( NULL, L"Resources\\TankBlue1.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank2[1] = (HBITMAP)LoadImage( NULL, L"Resources\\TankYellow1.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank3[1] = (HBITMAP)LoadImage( NULL, L"Resources\\TankLarge1.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	bulletPic[1] = (HBITMAP)LoadImage( NULL, L"Resources\\bullet1.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank1[2] = (HBITMAP)LoadImage( NULL, L"Resources\\TankBlue2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank2[2] = (HBITMAP)LoadImage( NULL, L"Resources\\TankYellow2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank3[2] = (HBITMAP)LoadImage( NULL, L"Resources\\TankLarge2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	bulletPic[2] = (HBITMAP)LoadImage( NULL, L"Resources\\bullet2.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank1[3] = (HBITMAP)LoadImage( NULL, L"Resources\\TankBlue3.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank2[3] = (HBITMAP)LoadImage( NULL, L"Resources\\TankYellow3.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	tank3[3] = (HBITMAP)LoadImage( NULL, L"Resources\\TankLarge3.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	bulletPic[3] = (HBITMAP)LoadImage( NULL, L"Resources\\bullet3.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );
	// ����ͼƬ
	background = (HBITMAP)LoadImage( NULL, L"Resources\\Back.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE );

	//����Դ�ļ�������ͼƬ(��Ҫ����Դ�����н�λͼ����)
	grass=LoadBitmap (hInst,MAKEINTRESOURCE(IDB_GRASS)); 

	// ��ʼ������
	for(nEnemy = 0; nEnemy < MAX_ENEMY; nEnemy++)
	{
		enemys[nEnemy].s = sz;
		enemys[nEnemy].b = 0;
		enemys[nEnemy].e = 1;
		enemys[nEnemy].dir = Dir(UP+rand()%4);
		enemys[nEnemy].v = rand()%2==0?velf:vels;
		enemys[nEnemy].v == velf?	memcpy(enemys[nEnemy].a, tank3, 4*sizeof(Dir)):memcpy(enemys[nEnemy].a, tank2, 4*sizeof(Dir));
		enemys[nEnemy].x = (rand()%3)*(wndWidth-sz)/2 + sz/2;
		enemys[nEnemy].y = sz;
		enemys[nEnemy].p = 0;
	}

	// ��ʼ�����
	ResetPlayer();

	// ��ʼ����ͼ
	InitMap();
}
// ���ض���Ϸʵ������ƶ�
void Move(Entity *ent, int ts)
{
	if (ent->p)
		return;
	switch(ent->dir)
	{
	case UP:
		ent->y -= ent->v * ts;
		break;
	case DOWN:
		ent->y += ent->v * ts;
		break;
	case LEFT:
		ent->x -= ent->v * ts;
		break;
	case RIGHT:
		ent->x += ent->v * ts;
		break;
	}
}
// �ض�ʵ������������
void Fire(const Entity* ent)
{
	Entity *pBulletes = (ent->e)?enemyBullets:bullets;
	int nB = (ent->e)?nEnemyBullet:nBullet;
	if (nB >= MAX_BULLETS)
		return;
	(pBulletes+nB)->s = szb;
	(pBulletes+nB)->b = 1;
	(pBulletes+nB)->e = 0;
	memcpy((pBulletes+nB)->a, bulletPic, 4*sizeof(Dir));
	(pBulletes+nB)->dir = ent->dir;
	(pBulletes+nB)->v = velb;
	(pBulletes+nB)->x = ent->x;
	(pBulletes+nB)->p = 0;
	(pBulletes+nB)->y = ent->y;
	switch(ent->dir)
	{
	case UP:
		(pBulletes+nB)->y -= ent->s;
		break;
	case DOWN:
		(pBulletes+nB)->y += ent->s;
		break;
	case LEFT:
		(pBulletes+nB)->x -= ent->s;
		break;
	case RIGHT:
		(pBulletes+nB)->x += ent->s;
		break;
	}
	if (ent->e)
		nEnemyBullet++;
	else
		nBullet++;
}
// ���ض���ʵ���������ɾ��,����Ԫ����ǰ�ƶ�
void Destroy(Entity ents[], int n, int *num)
{
	memcpy(ents+n, ents+n+1, sizeof(Entity)*((*num)-1-n));
	(*num)--;
}
// �ж�����ʵ���Ƿ�����ײ,��������֮�䷢����ײ���ж�
int IsCollide(const Entity *ent1, const Entity *ent2)
{

	if (ent1->x+ent1->s/2 <= ent2->x-ent2->s/2 || ent1->x-ent1->s/2 >= ent2->x + ent2->s/2)
		return 0;
	if (ent1->y+ent1->s/2 <= ent2->y-ent2->s/2 || ent1->y-ent1->s/2 >= ent2->y + ent2->s/2)
		return 0;
	return 1;
}
// �ж��ض�ʵ���Ƿ�ͱ߽緢����ײ
int WallCollide(Entity *ent)
{
	int bC = 0;
	switch(ent->dir)
	{
	case UP:
		if ((ent->y - ent->s/2) < 0)			// �ϱ߽�
		{
			bC = 1;
			ent->y = ent->s/2;
		}
		break;
	case DOWN:
		if ((ent->y + ent->s/2) > wndHeight)	// �±߽�
		{
			bC = 1;
			ent->y = wndHeight - ent->s/2;
		}
		break;
	case LEFT:
		if((ent->x - ent->s/2) < 0)				// ��߽�
		{
			bC = 1;
			ent->x = ent->s/2;
		}
		break;
	case RIGHT:
		if((ent->x + ent->s/2) > wndWidth)		// �ұ߽�
		{
			bC = 1;
			ent->x = wndWidth - ent->s/2;
		}
		break;
	}
	if (bC)
	{
		if (ent->e)
			ent->dir = Dir((ent->dir+1+rand()%3)%4);
		else
			ent->p = 1;
	}
	return bC;
}
// ���¸�����Ϸ��Ϣ,��ʱ����Ϣ�л�����������
void Update(int ts)
{
	// ���ֿ��ƶ��������λ�ø���
	Entity* ent = NULL;
	for (int i = 0; i < nEnemy; i++)
	{
		ent = enemys+i;
		Move(ent, ts);
		if ((rand()%enemyFirePer) == 0)
			Fire(ent);
	}
	for (int i = 0; i < nBullet; i++)
	{
		ent = bullets+i;
		Move(ent, ts);
	}
	for (int i = 0; i < nEnemyBullet; i++)
	{
		ent = enemyBullets+i;
		Move(ent, ts);
	}
	Move(&player, ts);

	// ��Ҵ��ڿ���״̬�Ļ�,�����ӵ�
	if (bFire)
	{
		Fire(&player);
		bFire = 0;
	}

	// �ж��ӵ��Ƿ�͵�����ײ
	for(int i = 0; i < nBullet; i++)
	{
		for (int j = 0; j < nEnemy; j++)
		{
			if (IsCollide(&bullets[i], &enemys[j]))
			{
				Destroy(bullets, i, &nBullet);
				Destroy(enemys, j, &nEnemy);
				nScore++;
				i--;
				j--;
				break;
			}
		}
	}
	// �жϵ��˵��ӵ��Ƿ�������ײ
	for(int i = 0; i < nEnemyBullet; i++)
	{
		if (IsCollide(&enemyBullets[i], &player))
		{
			Destroy(enemyBullets, i, &nEnemyBullet);
			ResetPlayer();
			nLife--;
			i--;
			break;
		}
	}
	// �жϵ����Ƿ�������ײ
	for (int i = 0; i < nEnemy; i++)
	{
		if (IsCollide(&player, &enemys[i]))
		{
			ResetPlayer();
			nLife--;
		}
	}
	// �жϸ���ʵ���Ƿ����Ϸ�߽緢����ײ
	for (int i = 0; i < nEnemy; i++)
	{
		ent = enemys+i;
		if (!WallCollide(ent))		// ��һ�����ʸı䷽��
		{
			int cg = 0;
			for (int j = 0; j < nGrass; j++)	// �жϵ����Ƿ�ͳ������ϰ��﷢����ײ
			{
				if (IsCollide(ent, grasses+j))
				{
					cg = 1;

					Move(ent, -ts);
					break;
				}
			}
			if (rand()%enemyDirPer == 0 || cg)
				ent->dir = Dir((ent->dir+1+rand()%3)%4);
		}
	}
	// �ж���ҽ�ɫ�Ƿ���ϰ��﷢����ײ,�����,��ֹͣ
	for (int i = 0; i < nGrass; i++)
	{
		ent = grasses+i;
		if (IsCollide(ent, &player))
		{
			switch(player.dir)
			{
			case UP:
				player.y = ent->y+ent->s;
				break;
			case DOWN:
				player.y = ent->y-ent->s;
				break;
			case LEFT:
				player.x = ent->x+ent->s;
				break;
			case RIGHT:
				player.x = ent->x-ent->s;
				break;
			}
			player.p = 1;
			break;
		}
	}
	// �ж��ӵ��ͱ߽����ײ
	for (int i = 0; i < nBullet; i++)
	{
		ent = bullets+i;
		if (WallCollide(ent))
		{
			Destroy(bullets, i, &nBullet);
			i--;
		}
	}
	for (int i = 0; i < nEnemyBullet; i++)
	{
		ent = enemyBullets+i;
		if (WallCollide(ent))
		{
			Destroy(enemyBullets, i, &nEnemyBullet);
			i--;
		}
	}
	// ��Һͱ߽����ײ
	WallCollide(&player);
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TANKPLUS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TANKPLUS));

	srand(time(NULL));			// �������
	Init();						// ��ʼ����Ϸ��Ϣ

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TANKPLUS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;//MAKEINTRESOURCE(IDC_TANKPLUS);		// ȥ���˵���
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }
   SetWindowLong(hWnd, GWL_STYLE,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU);	// ������ı䴰�ڴ�С,�Ա�׼ȷ�趨�����еĸ�������λ��
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_CREATE:			// ����������,��ʼ����һ����ʱ��
		SetTimer(hWnd,1,timeStep,NULL);
		break;
	case WM_TIMER:			// ��ʱ����Ӧ
		if (wParam == 1)	// ����Ϸ���и���
		{
			if (nLife > 0)
				Update(timeStep/10);
			InvalidateRect(hWnd, NULL, TRUE);	// �ô��ڱ�Ϊ��Ч,�Ӷ������ػ���Ϣ
		}
		break;
	case WM_SIZE:			// ��ȡ���ڵĳߴ�
		wndWidth = LOWORD(lParam);
		wndHeight = HIWORD(lParam);
		break;
	case WM_KEYDOWN: 
		{
			InvalidateRect(hWnd, NULL, TRUE);
			switch (wParam)	// ��������������Ϣ������ҿ��Ƶ�̹��״̬
			{
			case VK_LEFT:
				player.dir = LEFT;
				player.p = 0;
				break;
			case VK_RIGHT:
				player.dir = RIGHT;
				player.p = 0;
				break;
			case VK_UP:
				player.dir = UP;
				player.p = 0;
				break;
			case VK_DOWN:
				player.dir = DOWN;
				player.p = 0;
				break;
			case VK_SPACE:
				bFire = 1;
				break;
			}
			break;
		}
	case WM_ERASEBKGND:		// ����������,������˸
		break;
	case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			// ���µĲ�����Ϊ�˱��������Ļ��˸,��������Ƶ��ڴ���,һ���Կ�������Ļ��
			//�����ڴ�HDC
			HDC memHDC = CreateCompatibleDC(hdc);

			//��ȡ�ͻ�����С
			RECT rectClient;
			GetClientRect(hWnd, &rectClient);

			//����λͼ
			HBITMAP bmpBuff = CreateCompatibleBitmap(hdc,wndWidth,wndHeight);
			HBITMAP pOldBMP = (HBITMAP)SelectObject(memHDC, bmpBuff);
			PatBlt(memHDC,0,0,wndWidth,wndHeight,WHITENESS);	// ���ñ���Ϊ��ɫ

			// ���������Ļ���
			DrawScene(memHDC);

			//�����ڴ�HDC���ݵ�ʵ��HDC
			BOOL tt = BitBlt(hdc, rectClient.left, rectClient.top, wndWidth,
				wndHeight, memHDC, rectClient.left, rectClient.top, SRCCOPY);

			//�ڴ����
			SelectObject(memHDC, pOldBMP);
			DeleteObject(bmpBuff);
			DeleteDC(memHDC);

			EndPaint(hWnd, &ps);
			break;
		}
	case WM_DESTROY:
		KillTimer(hWnd,1);		// �����˳�ʱ������ʱ��ɾ��
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
