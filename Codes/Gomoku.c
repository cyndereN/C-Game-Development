#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>			

#define MAX 15 //定义棋盘大小

int p[MAX][MAX];//存储对局信息
char buff[MAX*2+1][MAX*4+3];//输出缓冲器
int cx,cy;//当前光标位置
int now;//当前走子的玩家，1代表黑，2代表白
int wl,wp;//当前写入缓冲器的列数和行数位置
char* showText;//在棋盘中央显示的文字信息
int count;//回合数
void explation();
void gotoxy(int x,int y);
int color(int c);

/*
  设置光标位置
 */
void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
 /*
  文字颜色函数     
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}
/*
  开始界面
 */
void welcome_menu()
{
	int n;
	int i,j = 1;
	gotoxy(23,2);
	color(13);
	printf("五 子 棋 游 戏");
	color(15);          			//白色边框
	for (i =6; i <= 12; i++)   	//输出上下边框┅
	{
		for (j = 7; j <= 54; j++)  //输出左右边框┇
		{
			gotoxy(j, i);
			if (i == 6 || i == 12)
			{
				printf("-");
            }
			else if (j == 7 || j == 54)
            {
				printf("|");
            }
		}
	}
	color(14);
	gotoxy(15, 8);
	printf("1.开始游戏");
	gotoxy(35, 8);
	printf("2.游戏说明");
	gotoxy(15, 10);
	printf("3.退出游戏");
	gotoxy(19,13);
	color(12);
	printf("请选择[1 2 3]:[ ]\b\b");        //\b为退格，使得光标处于[]中间
	color(14);
    scanf("%d", &n);    		//输入选项
    switch (n)
    {
    	case 1:
    		system("cls");
			RunGame();
        	break;
    	case 2:
            explation();
            break;
    	case 3:
        	exit(0);     		//退出游戏
        	break;
        
    }
}

//修改过的字符串复制函数，会忽略末端的\0
char* Copy(char* strDest,const char* strSrc)
{
    char* strDestCopy = strDest;
    while (*strSrc!='\0')
    {
        *strDest++ = *strSrc++;
    }
    return strDestCopy;
}
    
//初始化一个对局函数
void Initialize()
{
    int i,j;//循环变量
    showText = "";//重置显示信息
    count = 0; //回合数归零
    for(i=0; i<MAX; i++)//重置对局数据
    {
        for(j=0;j<MAX;j++)
        {
            p[i][j]=0;
        }
    }
    cx = cy= MAX/2;//重置光标到中央
    now = 1;//重置当前为黑方
}

//获得棋盘中指定坐标交点位置的字符，通过制表符拼成棋盘
char* getStyle(int i,int j)
{
    if(p[i][j]==1)//1为黑子
        return "●";
    else if(p[i][j]==2)//2为白子
        return "○";
    else if(i==0&&j==0)//以下为边缘棋盘样式
        return "┏";
    else if(i==MAX-1&&j==0)
        return "┓";
    else if(i==MAX-1&&j==MAX-1)
        return "┛";
    else if(i==0&&j==MAX-1)
        return "┗";
    else if(i==0)
        return "┠";
    else if(i==MAX-1)
        return "┨";
    else if(j==0)
        return "┯";
    else if(j==MAX-1)
        return "┷";
    return "┼";//中间的空位
}

//获得指定坐标交点位置左上格的样式，通过制表符来模拟光标的显示
char* getCurse(int i,int j)
{
    if(i==cx)
    {
        if(j==cy)
            return "┏";
        else if (j==cy+1)
            return "┗";
    }
    else if(i==cx+1)
    {
        if(j==cy)
            return "┓";
        else if (j==cy+1)
            return "┛";
    }
    return "　";//如果不在光标附近则为空
}

//向缓冲器写入字符串
void write(char* c)
{
    Copy(buff[wl]+wp,c);
    wp+=strlen(c);
}

//缓冲器写入位置提行
void ln()
{
    wl+=1;
    wp=0;
}
    
//将缓冲器内容输出到屏幕
void Display()
{
    int i,l = strlen(showText);//循环变量，中间文字信息的长度
    int Offset = MAX*2+2-l/2;//算出中间文字信息居中显示所在的横坐标位置
    if(Offset%2==1)//如果位置为奇数，则移动到偶数，避免混乱
    {
        Offset--;
    }
    Copy(buff[MAX]+Offset,showText);//讲中间文字信息复制到缓冲器
    if(l%2==1)//如果中间文字长度为半角奇数，则补上空格，避免混乱
    {
        *(buff[MAX]+Offset+l)=0x20;
    }
    system("cls");//清理屏幕，准备写入
    for(i=0;i<MAX*2+1;i++){//循环写入每一行
        printf("%s",buff[i]);
    if(i<MAX*2)//写入完每一行需要换行
        printf("\n");
    }
}

//将整个棋盘算出并储存到缓冲器，然后调用Display函数显示出来
void Print()
{
    int i,j;//循环变量
    wl=0;
    wp=0;
    for(j=0;j<=MAX;j++)//写入出交点左上角的字符，因为需要打印棋盘右下角，所以很以横纵各多一次循环
    {
        for(i=0;i<=MAX;i++)
        {
            write(getCurse(i,j));//写入左上角字符
            if(j==0||j==MAX)//如果是棋上下盘边缘则没有连接的竖线，用空格填充位置
            {
                if(i!=MAX)
                write("　");
            }
            else//如果在棋盘中间则用竖线承接上下
            {
                if(i==0||i==MAX-1)//左右边缘的竖线更粗
                    write("┃");
                else if(i!=MAX)//中间的竖线
                    write("│");
            }
        }

        if(j==MAX)//如果是最后一次循环，则只需要处理边侧字符，交点要少一排
        {
            break;
        }
        ln();//提行开始打印交点内容
        write("　");//用空位补齐位置
        for(i=0;i<MAX;i++)//按横坐标循环正常的次数
        {
            write(getStyle(i,j));//写入交点字符
            if(i!=MAX-1)//如果不在最右侧则补充一个横线承接左右
            {
                if(j==0||j==MAX-1)
                {
                    write("━");//上下边缘的横线更粗
                }
                else
                {
                    write("—");//中间的横线
                }
            }
        }
        ln();  //写完一行后提行
    }
    Display();  //将缓冲器内容输出到屏幕
}

int Put()   //在当前光标位置走子，如果非空，则返回0表示失败
{
    if(p[cx][cy]==0)
    {
        p[cx][cy]=now;//改变该位置数据
        return 1;//返回1表示成功
    }
    else
    {
        return 0;
    }
}

//胜负检查，即判断当前走子位置有没有造成五连珠的情况
int Check()
{
    int w=1,x=1,y=1,z=1,i;//累计横竖正斜反邪四个方向的连续相同棋子数目
    for(i=1;i<5;i++)
        if(cy+i<MAX&&p[cx][cy+i]==now)
            w++;
        else 
            break;//向下检查
    for(i=1;i<5;i++)
        if(cy-i>0&&p[cx][cy-i]==now)
            w++;
        else 
            break;//向上检查
    if(w>=5)
        return now;//若果达到5个则判断当前走子玩家为赢家
    for(i=1;i<5;i++)
        if(cx+i<MAX&&p[cx+i][cy]==now)
            x++;
        else 
            break;//向右检查
    for(i=1;i<5;i++)
        if(cx-i>0&&p[cx-i][cy]==now)
            x++;
        else 
            break;//向左检查
    if(x>=5)
        return now;//若果达到5个则判断当前走子玩家为赢家
    for(i=1;i<5;i++)
        if(cx+i<MAX&&cy+i<MAX&&p[cx+i][cy+i]==now)
            y++;
        else
            break;//向右下检查
    for(i=1;i<5;i++)
        if(cx-i>0&&cy-i>0&&p[cx-i][cy-i]==now)
            y++;
        else 
            break;//向左上检查
    if(y>=5)
        return now;//若果达到5个则判断当前走子玩家为赢家
    for(i=1;i<5;i++)
        if(cx+i<MAX&&cy-i>0&&p[cx+i][cy-i]==now)
            z++;
        else 
            break;//向右上检查
    for(i=1;i<5;i++)
        if(cx-i>0&&cy+i<MAX&&p[cx-i][cy+i]==now)
            z++;
        else
            break;//向左下检查 if(z>=5)return now;//若果达到5个则判断当前走子玩家为赢家
    return 0;//若没有检查到五连珠，则返回0表示还没有玩家达成胜利
}


//进行整个对局，返回赢家信息(虽然有用上)
int RunGame()
{
    int input;//输入变量
    int victor;//赢家信息
    Initialize();//初始化对局
    while(1) //开始无限回合的死循环，直到出现胜利跳出
    {
        Print();//打印棋盘
        input=getch();//等待键盘按下一个字符

        if(input==27)//如果是ESC则退出程序
        {
            exit(0);
        }
        else if(input == 0x20)//如果是空格则开始走子
        {
            if(Put())//如果走子成功则判断胜负
            {
                victor=Check();
                now=3-now;//轮换当前走子玩家
                count++;
                if(victor==1)//如果黑方达到胜利，显示提示文字并等待一次按键，返回胜利信息
                {
                    showText="黑方获得了胜利！";
                    Print();
                    if(getch()==0xE0)
                    {
                        getch();
                    }
                    return now;
                }
                else if(victor==2)//如果白方达到胜利，显示提示文字并等待一次按键，返回胜利信息
                {
                    showText="白方获得了胜利！";
                    Display();
                    if(getch()==0xE0)
                    {
                        getch();
                    }
                    return now;
                }
                else if(count==MAX*MAX)//如果回合数达到了棋盘总量，即棋盘充满，即为平局
                {
                    showText="平局！";
                    Display();
                    if(getch()==0xE0)
                    {
                        getch();
                    }
                    return 0;
                }
            }
        }
        else if(input==0xE0)//如果按下的是方向键，会填充两次输入，第一次为0xE0表示按下的是控制键
        {
            input=getch();//获得第二次输入信息
            switch(input)//判断方向键方向并移动光标位置
            {
                case 0x4B:cx--; break;
                case 0x48:cy--; break;
                case 0x4D:cx++; break;
                case 0x50:cy++; break;
            }
            if(cx<0)  cx=MAX-1;//如果光标位置越界则移动到对侧
            if(cy<0)  cy=MAX-1; 
            if(cx>MAX-1) cx=0;
            if(cy>MAX-1) cy=0;
        }
    }
}

/*
  游戏说明
*/
void explation()
{
	int i,j = 1;
    system("cls");
    color(13);
    gotoxy(27,3);
    printf("游戏说明");
    color(5);
    for (i = 6; i <= 22; i++)   //输出上下边框===
	{
		for (j = 3; j <= 58; j++)  //输出左右边框||
		{
			gotoxy(j, i);
			if (i == 6 || i == 22) printf("=");
			else if (j == 3 || j == 58) printf("||");
		}
	}
    color(15);
    gotoxy(10,8);
    printf("tip1: 用↑.↓.←.→控制光标的位置");
    color(14);
    gotoxy(10,11);
    printf("tip2: 用空格键确定下棋子");
    color(12);
    gotoxy(10,14);
    printf("tip3: 黑白棋哪个先上下左右5个连在一起，得胜利");
    color(11);
    gotoxy(10,17);
    printf("tip4: 按<Esc>退出游戏");
    getch();                //按任意键返回主界面
    system("cls");
    welcome_menu();
}

int main()//主函数
{
   // system("color 2E"); //设置颜色
    welcome_menu();
    while(1)  //循环执行游戏
    { 
        RunGame();
    }
	return 0;
}