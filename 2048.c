#include <stdio.h>  
#include <stdlib.h>  
#include <windows.h>

#define bool int  //C里边没有布尔类型,就自己造
#define true 1   //bool的两种值
#define false 0
int MAP[4][4]= {0};  //地图,默认0认为是空位
typedef enum {   //定义一个方向类型的枚举变量
    UNKNOW,
    UP,
    DOWN,
    LEFT,
    RIGHT
} Dir;
  
void priMap();  //绘制图形
Dir getNextDirection(); //从键盘读入下一个用户操作
bool canMove(Dir direction); //判断是否可以进行指定方向的操作
void doAction();   //游戏事件
void move(Dir direction);  //移动数字
void New();    //放入一个新的数字

int main() //主函数
{    
    Dir nextStep;   //下一步
    int i,j;
    srand(time(0));
    New();    //游戏开始默认放两个数字
    New();
    priMap();    //打印格子
    while(1) 
    {
        if(!canMove(UP)&&!canMove(LEFT)&&!canMove(DOWN)&&!canMove(RIGHT)) break; //任意方向都不能移动,那么终止游戏
        nextStep=getNextDirection();  //获取下一个用户操作
        if(nextStep==UNKNOW) continue;  //如果不知道用户按了个什么键或者用户胡乱按的,那么进入新的循环
        if(!canMove(nextStep)) continue; //如果下一步不可继续操作,进入新的循环
        system("cls");    //对于Windows来说,执行命令行命令cls清屏
        doAction(nextStep);   //执行操作
        New();    //放新的数字
        priMap();    //打印格子
    }
    color(12);
    printf("游戏结束!");   //提示游戏结束
    while(1);     //等待游戏结束
}

/*
  文字颜色函数      此函数的局限性：1、只能Windows系统下使用   2、不能改变背景颜色
 */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}

void priMap() {
    int i,j;
    color(14);
    printf("-------------------------\n");
    for(i=0; i<4; i++) 
    {
        color(14);
        printf("|");
        for(j=0; j<4; j++) 
        {
            color(13);
            printf("  ");
            MAP[i][j] ? printf("%d",MAP[i][j]) : printf(" ");
            color(14);
            printf("  |");
            if(j>2)
                printf("\n");
        }
        color(14);
        printf("-------------------------\n");
    }
}

void doAction(Dir direction)
{
    int i,j,k;
    /*
      为了方便处理问题,将每个方向的运动操作简化为三步
      1.将数字归并到一个方向
      2.处理相同数字可消,并将消掉的数据定为0
      3.再次将数字归并到一个方向
    */

    //1.移动数字,取消数字之间的空位
    move(direction);

    //2.按照方向处理相同数字
    switch(direction)
    {
        case UP:        //按列枚举
            for(i=0;i<4;i++)        //对于每一行的每一个元素
            {
                for(j=0;j<3;j++)            //如果元素非零,并且当前和下一个相同,当前的翻倍,下一个置零
                {
                    if(MAP[j][i]&&MAP[j][i]==MAP[j+1][i])
                    {
                        MAP[j][i]+=MAP[j+1][i];
                        MAP[j+1][i]=0;
                    }
                }
            }
            break;

        case LEFT:
            for(i=0;i<4;i++)
            {
                for(j=0;j<3;j++)
                {
                    if(MAP[i][j]&&MAP[i][j]==MAP[i][j+1])
                    {
                        MAP[i][j]+=MAP[i][j+1];
                        MAP[i][j+1]=0;
                    }
                }
            }
            break;
        
        case DOWN://同上
            for(i=0;i<4;i++)
            {       
                for(j=3;j>0;j--)
                {
                    if(MAP[j][i]&&MAP[j][i]==MAP[j-1][i])
                    {
                        MAP[j][i]+=MAP[j-1][i];
                        MAP[j-1][i]=0;
                    }
                }
            }
            break;

        case RIGHT://同上
        for(i=0;i<4;i++)
        {        
            for(j=3;j>0;j--)
            {
                if(MAP[i][j]&&MAP[i][j]==MAP[i][j-1])
                {
                    MAP[i][j]+=MAP[i][j-1];
                    MAP[i][j-1]=0;
                }
            }
        }
        break;
        
    }
    //3.移动数字,取消因为上一步置零过程中新产生的空位
    move(direction);

}

void move(Dir direction)  //移动数字
{ 
    int i,j,k;
    switch(direction) 
    {
        case UP://按列枚举
            for(i=0;i<4;i++)//对于每一行的每一个元素
                for(j=0;j<4;j++) //如果非零,那么应当取消当前位置,后边元素向前移动
                    if(!MAP[j][i])
                    {
                        for(k=j;k<3;k++)
                        {
                            MAP[k][i]=MAP[k+1][i];
                        }
                        MAP[k][i]=0;  //新产生的空位置零
                    }
            break;

        case LEFT://同上
            for(i=0;i<4;i++)
                for(j=0;j<4;j++)
                    if(!MAP[i][j])
                    {
                        for(k=j;k<3;k++)
                        {
                            MAP[i][k]=MAP[i][k+1];
                        }
                        MAP[i][k]=0;
                    }
            break;

        case DOWN://同上
            for(i=0;i<4;i++)
                for(j=3;j>=0;j--)
                    if(!MAP[j][i])
                    {
                        for(k=j;k>0;k--)
                        {
                            MAP[k][i]=MAP[k-1][i];
                        }
                        MAP[k][i]=0;
                    }
            break;

        case RIGHT://同上
        for(i=0;i<4;i++)
            for(j=3;j>=0;j--)
                if(!MAP[i][j])
                {      
                    for(k=j;k>0;k--)
                    {
                        MAP[i][k]=MAP[i][k-1];
                    }
                    MAP[i][k]=0;
                }
            break;
    }
}

bool canMove(Dir direction)   //判断是否可以进行指定方向的操作
{ 
    int i,j;

    switch(direction) 
    {
        case UP:  //依次检查每一列
            for(i=0;i<4;i++)
            {
                for(j=3;j>=0;j--)         //首先排除在远端的一串空位,直接将j指向第一个非零元素
                    if(MAP[j][i])
                        break;
                
                if(j>0)   //j>0代表这一列并非全部为0
                    for(;j>=0;j--)   //依次检查每一个剩余元素,遇见空位直接返回true
                        if(!MAP[j][i]) 
                            return true;
                
                for(j=3;j>0;j--)//依次检查相邻的元素是否存在相同的非零数字
                    if(MAP[j][i]&&MAP[j][i]==MAP[j-1][i])
                        return true;
            }
            break;

        case DOWN://同上
            for(i=0;i<4;i++)
            {
                for(j=0;j<4;j++)
                    if(MAP[j][i]) break;
                if(j<4)
                    for(;j<4;j++)
                        if(!MAP[j][i]) return true;
                for(j=0;j<3;j++)
                    if(MAP[j][i]&&MAP[j][i]==MAP[j+1][i])
                        return true;
            }
            break;
        case LEFT://同上
            for(i=0; i<4; i++)
            {
                for(j=3;j>=0;j--)
                    if(MAP[i][j]) break;
                if(j>=0)
                    for(;j>=0;j--)
                        if(!MAP[i][j]) return true;

                for(j=0;j<3;j++)
                    if(MAP[i][j]&&MAP[i][j]==MAP[i][j+1]) 
                        return true;
            }
            break;

        case RIGHT://同上
            for(i=0; i<4; i++)
            {
                for(j=0;j<4;j++)
                    if(MAP[i][j]) break;
                if(j<4)
                    for(;j<4;j++)
                        if(!MAP[i][j]) return true;
                for(j=0;j<3;j++){
                    if(MAP[i][j]&&MAP[i][j]==MAP[i][j+1]) 
                        return true;
                }
            }
            break;
    }

    return false;   //当允许条件都被检查过后,返回不可执行的结果
}


Dir getNextDirection() 
{
   
    if(getch()!=224) return UNKNOW;  //第一个字节必须是224,否则判定输入的不是功能键
    
    switch(getch()) //根据第二字节对应出来用户的操作
    {
        case 72:
            return UP;
        case 80:
            return DOWN;
        case 75:
            return LEFT;
        case 77:
            return RIGHT;
        default:
            return UNKNOW;
    }
}


void New() 
{
    int* boxes[16]={NULL};  //为了方便操作,临时存储一下所有空闲格子的指针,这样可以用一个线性的内存随机访问实现对所有空位中任一空位的随机访问.
    int* target;   //用来临时保存目标格子的地址
    int count=0;   //统计一共有多少个有效空格
    int i,j;
    // color(2);
    //统计空位,发现空位即保存地址并累加计数器

    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(!MAP[i][j])
            {
                boxes[count]=&MAP[i][j];
                count++;
            }

    if(count)    //如果有空位,那么对这一位进行随机赋值操作,对于每一位可能性是相同的
    {
        target=boxes[rand()%count];
        *target=rand()%2?2:4;  //50%可能出现2 50% 可能出现4
    }
}