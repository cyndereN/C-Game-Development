#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{	
	int n1,n2,n3,n4;
	int year1,month1,day1,days1=0;
	int year,month,day,days=0;
	int i,j,h,tianshu,xiaoshishu=0;
	int sum=0;
	int leap(int year);
	int monthA[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
	int daysums[20000];
	
	printf("“人生漫漫，我们其实一直在太空旅行；”\n");
	system("pause");
	printf("“不存在未来，那只是一场虚幻的梦境；”\n");
	system("pause");
	printf("“不存在当下，因为那只有矛盾的苦情；”\n");
	system("pause");
	printf("“不存在过去，那都是一些顽固的记忆——”\n");
	system("pause");
	printf("走着走着，你遇到了一位衣着怪异的外乡人。\n");
	system("pause");
	printf("去打个招呼吗？\n");
	system("pause");
	printf("1.向他走去\n");
	printf("0.算了\n");

		while((n1==0)||(n1==1))
		{
			scanf("%d",&n1);
			
			if(n1==1)
				{
					break;
				}
				
			else if(n1==0)
				{	
					printf("Farewell.\n");
					system("pause");
					return 0;
				}
				
			else
				{
					printf("Error! Wrong number.\n");
				}
		}
		
		printf("你好。我在这里孑身一人，徘徊一世，只为等待你的出现。在我把所有事讲给你听之前，可否先告诉我，今天的日期？...\n");
		printf("今天的日期是（格式：yyyy,mm(m),dd(d)）："); 
		scanf("%d,%d,%d",&year,&month,&day);
		printf("“看来我们都在这世上游荡已久。我说，生活是场永无止境的奔跑，但似乎你已气喘吁吁。”\n");
		system("pause");
		printf("1.我太累了，已经不能再坚持\n");
		printf("0.我不能停下来，我必须继续前进\n");
				
			while((n2==0)||(n2==1))
				{	
					scanf("%d",&n2);
					
					if(n2==1)
						{
							system("pause");
							return 0;
						} 
						
					else if(n2==0)
						{
							break; 
						}
						
					else
						{
							printf("Error! Wrong number.\n");
						}
				}
			
			printf("这场奔跑的终点是何方？目的又何在？\n");
			system("pause");
			printf("1.知识\n");
			printf("2.金钱\n");
			printf("3.荣誉\n");
			printf("4.成功\n");
			printf("5.创作\n");
			printf("6.成功\n\n");
			printf("0.Life means n0thing!\n");
					
				while((n3==1)||(n3==2)||(n3==3)||(n3==4)||(n3==5)||(n3==6)||(n3==0)) 
					{
						scanf("%d",&n3);			
						
						if((n3==1)||(n3==2)||(n3==3)||(n3==4)||(n3==5)||(n3==6)) 
							{
								system("cls");
								printf("不！你错了。Life means nothing.\n");
								break;
							}
								
						else if(n3==0)
							{
								system("cls");
								printf("恭喜，你答对了。\n");
								break; 
							}
						else
							{
								printf("Error! Wrong number.\n");
							}
						}
		printf("既然你愿意听我唠叨，我就再来分享一些东西吧。\n");
		system("pause");		
		printf("人生毫无意义。时间在一分一秒的流逝。而你却任由它从指缝间溜走，仍在进行着这款无意义的游戏。\n");
		system("pause");
		printf("这个游戏本身毫无意义，但你却依然选择玩这款游戏。这样的行为充满了意义。\n");
		system("pause");
		printf("并非生命中的所有东西都拥有何种意义，但是生命之所以美好，在于我们可以选择赋予它的意义。\n");
		system("我们的过去，是最重要的。它决定了我们是谁，也留下了我们曾经来过的印记。\n");
		system("pause");
		printf("1.你说的没错。\n");
		printf("0.我不能苟同。\n");
			
			while((n3==0)||(n3==1))
				{
					scanf("%d",&n3);
			
					if((n3==0)||(n3==1))
						{
							break;
						}
				
					else
						{
							printf("Error! Wrong number.\n");
						}
				}
							
			system("cls");
			printf("先听我说。从哪一天起，你来到了这个世界？（格式：yyyy,mm(m),dd(d)）");
			scanf("%d,%d,%d",&year1,&month1,&day1);
				
			h=year1;
	for(i=1;i<=month1-1;i++)
		{
			days1+=monthA[i];
		}
	
	if (leap(year1)&&month1>=3)
		{
			days1=day1+1+days1;
		}
	else
		{
			days1=day1+days1;
		}
	
	for(j=1;j<=month-1;j++)
		{
			days+=monthA[j];
		}
	if (leap(year)&&month>=3)
		{
			days=day+1+days;
		}
	else
		{
			days=day+days;
		}
	
	if(h==year)
		{
			sum=0;
		}
	else
	{
		for(h=year1;h<year;h++)
			{
				if((h%4==0&&h%100!=0)||h%400==0)
				{	
					daysums[h]=366;
				}
				else
				{	
					daysums[h]=365;
				}
			}
	for(h=year1;h<year;h++)
		{	
			sum=daysums[h]+sum;
		}	
	}
	tianshu=sum+days-days1;
	xiaoshishu=tianshu*24;
	
	system("cls");
	printf("哦，恭喜你，你已经在这个混沌时代里，你已经活过了 %d 天\n",tianshu);
	system("pause");
	printf("在这欢声与泣语交错，酸甜和苦辣并存的 %d 小时里，你又有多少时间平白无故的浪费了呢？\n",xiaoshishu);
	system("pause");
	printf("我们把握当下，就是为了不让将来沦为不堪回首的过去。\n");
	system("pause");	
	printf("希望你对这次游戏的选择能为你敞开一扇门。你能够选择并改变你的人生。\n");
	system("pause");
	printf("不论前方有怎样的恐惧与障碍，我们都能够克服。\n");
	system("pause");	
	printf("——以不尽的热忱回应没有温度的独行。\n");
	system("pause");
	system("cls");
	
	printf("“再见，旅人\n");					
	system("pause");
	printf("请你铭记：\n");					
	system("pause");	
	printf("我们的征途是星辰大海。”\n");					
	system("pause");
	
	system("cls");
	printf("游戏结束，请连按任意键退出游戏.\n");
	printf("Thank u for playing !”\n");
	system("pause");
	
	return 0;
	
}

int leap(int year)
{
	int leap;
	leap=year%4==0&year%100!=0||year%400==0;
	return leap;
	
}
