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
	
	printf("������������������ʵһֱ��̫�����У���\n");
	system("pause");
	printf("��������δ������ֻ��һ����õ��ξ�����\n");
	system("pause");
	printf("�������ڵ��£���Ϊ��ֻ��ì�ܵĿ��飻��\n");
	system("pause");
	printf("�������ڹ�ȥ���Ƕ���һЩ��̵ļ��䡪����\n");
	system("pause");
	printf("�������ţ���������һλ���Ź���������ˡ�\n");
	system("pause");
	printf("ȥ����к���\n");
	system("pause");
	printf("1.������ȥ\n");
	printf("0.����\n");

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
		
		printf("��á�������������һ�ˣ��ǻ�һ����ֻΪ�ȴ���ĳ��֡����Ұ������½�������֮ǰ���ɷ��ȸ����ң���������ڣ�...\n");
		printf("����������ǣ���ʽ��yyyy,mm(m),dd(d)����"); 
		scanf("%d,%d,%d",&year,&month,&day);
		printf("���������Ƕ����������ε��Ѿá���˵�������ǳ�����ֹ���ı��ܣ����ƺ�����������������\n");
		system("pause");
		printf("1.��̫���ˣ��Ѿ������ټ��\n");
		printf("0.�Ҳ���ͣ�������ұ������ǰ��\n");
				
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
			
			printf("�ⳡ���ܵ��յ��Ǻη���Ŀ���ֺ��ڣ�\n");
			system("pause");
			printf("1.֪ʶ\n");
			printf("2.��Ǯ\n");
			printf("3.����\n");
			printf("4.�ɹ�\n");
			printf("5.����\n");
			printf("6.�ɹ�\n\n");
			printf("0.Life means n0thing!\n");
					
				while((n3==1)||(n3==2)||(n3==3)||(n3==4)||(n3==5)||(n3==6)||(n3==0)) 
					{
						scanf("%d",&n3);			
						
						if((n3==1)||(n3==2)||(n3==3)||(n3==4)||(n3==5)||(n3==6)) 
							{
								system("cls");
								printf("��������ˡ�Life means nothing.\n");
								break;
							}
								
						else if(n3==0)
							{
								system("cls");
								printf("��ϲ�������ˡ�\n");
								break; 
							}
						else
							{
								printf("Error! Wrong number.\n");
							}
						}
		printf("��Ȼ��Ը��������߶���Ҿ���������һЩ�����ɡ�\n");
		system("pause");		
		printf("�����������塣ʱ����һ��һ������š�����ȴ��������ָ������ߣ����ڽ�����������������Ϸ��\n");
		system("pause");
		printf("�����Ϸ����������壬����ȴ��Ȼѡ���������Ϸ����������Ϊ���������塣\n");
		system("pause");
		printf("���������е����ж�����ӵ�к������壬��������֮�������ã��������ǿ���ѡ�����������塣\n");
		system("���ǵĹ�ȥ��������Ҫ�ġ���������������˭��Ҳ��������������������ӡ�ǡ�\n");
		system("pause");
		printf("1.��˵��û��\n");
		printf("0.�Ҳ��ܹ�ͬ��\n");
			
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
			printf("������˵������һ������������������磿����ʽ��yyyy,mm(m),dd(d)��");
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
	printf("Ŷ����ϲ�㣬���Ѿ����������ʱ������Ѿ������ %d ��\n",tianshu);
	system("pause");
	printf("���⻶�������ｻ������Ϳ�������� %d Сʱ������ж���ʱ��ƽ���޹ʵ��˷����أ�\n",xiaoshishu);
	system("pause");
	printf("���ǰ��յ��£�����Ϊ�˲��ý�����Ϊ�������׵Ĺ�ȥ��\n");
	system("pause");	
	printf("ϣ����������Ϸ��ѡ����Ϊ�㳨��һ���š����ܹ�ѡ�񲢸ı����������\n");
	system("pause");
	printf("����ǰ���������Ŀ־����ϰ������Ƕ��ܹ��˷���\n");
	system("pause");	
	printf("�����Բ������ȳ���Ӧû���¶ȵĶ��С�\n");
	system("pause");
	system("cls");
	
	printf("���ټ�������\n");					
	system("pause");
	printf("�������ǣ�\n");					
	system("pause");	
	printf("���ǵ���;���ǳ��󺣡���\n");					
	system("pause");
	
	system("cls");
	printf("��Ϸ������������������˳���Ϸ.\n");
	printf("Thank u for playing !��\n");
	system("pause");
	
	return 0;
	
}

int leap(int year)
{
	int leap;
	leap=year%4==0&year%100!=0||year%400==0;
	return leap;
	
}
