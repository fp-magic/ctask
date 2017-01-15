#include "acllib.h"
#include<stdio.h>
#include<stdlib.h> 
#include<string.h>
#include<math.h>
int speed,endgame,length,head[1000][3],food[3],nowtime,dir,changedir;
void startview()
{
	clearDevice();
	setTextColor(BLUE);
	setTextSize(18); 
	char ch0[50]="press space to start";
	beginPaint();
	paintText(40,105,ch0);
	endPaint();
}
void refresh()
{
	clearDevice();
	memset(head,0,sizeof(head));
	head[1][0]=1;head[1][1]=150;head[1][2]=150;
	nowtime=0;
	length=1;
	dir=1;changedir=1;
	food[1]=(rand()%30)*10;
	food[2]=(rand()%30)*10;
	endgame=1;
	startview();
}
void gameview()
{
	setPenWidth(3);
	setPenColor(RED);
	setPenWidth(1);
	setPenStyle(PEN_STYLE_DASH);
	setBrushColor(GREEN);
	setBrushStyle(BRUSH_STYLE_SOLID); 
}
void addlength()
{
	length++;
	head[length][0]=head[length-1][0];
	if(head[length][0]==1)
	{
		head[length][1]=head[length-1][1];
		head[length][2]=head[length-1][2]+10;
	}
	if(head[length][0]==2)
	{
		head[length][1]=head[length-1][1]-10;
		head[length][2]=head[length-1][2];
	}
	if(head[length][0]==3)
	{
		head[length][1]=head[length-1][1];
		head[length][2]=head[length-1][2]-10;
	}
	if(head[length][0]==4)
	{
		head[length][1]=head[length-1][1]+10;
		head[length][2]=head[length-1][2];
	}
}
int getfood()
{
	if((head[1][1]==food[1])&&(head[1][2]==food[2]))
	{
		food[1]=(rand()%30)*10;
		food[2]=(rand()%30)*10;
		return 1;
	}
	return 0;
}
int collision()
{
	int i;
	for(i=2;i<=length;i++)
		if((head[i][1]==head[1][1])&&(head[i][2]==head[1][2]))
			return 1;
	if(head[1][1]<0||head[1][1]>=300||head[1][2]<0||head[1][2]>=300)
		return 1;	
	return 0;
}
void choiceview()
{
	clearDevice();
	setTextColor(BLUE);
	setTextSize(18); 
	char ch[60]="please choose speed(1~9)";
	char ch2[100]="you can also change it during the game";
	char ch3[100]="press space to pause";
	beginPaint();
	paintText(40,105,ch);
	setTextSize(12); 
	paintText(20,200,ch2);
	paintText(75,250,ch3);
	endPaint();
}
void time1(int id)
{
	if(endgame!=0)return;
	nowtime++;
	//printf("id=%d nowtime=%d\n",id,nowtime);
	beginPaint();
	clearDevice();
	if(getfood())addlength();
	if(abs(changedir-dir)==1||abs(changedir-dir)==3)
	{
		head[1][0]=changedir;
		dir=changedir;
	}
	int i; 
	rectangle(food[1],food[2],food[1]+10,food[2]+10);
	for(i=1;i<=length;i++)
	{//printf("%d:x=%d y=%d\n",i,head[i][1],head[i][2]);
		if(head[i][0]==1)
		{
			head[i][2]-=10;
			rectangle(head[i][1],head[i][2],head[i][1]+10,head[i][2]+10);
		}
		if(head[i][0]==2)
		{
			head[i][1]+=10;
			rectangle(head[i][1],head[i][2],head[i][1]+10,head[i][2]+10);
		}
		if(head[i][0]==3)
		{
			head[i][2]+=10;
			rectangle(head[i][1],head[i][2],head[i][1]+10,head[i][2]+10);
		}
		if(head[i][0]==4)
		{
			head[i][1]-=10;
			rectangle(head[i][1],head[i][2],head[i][1]+10,head[i][2]+10);
		}
	}
	for(i=length;i>=2;i--)head[i][0]=head[i-1][0];
	endPaint();
	if(collision())refresh();
}
void mouse1(int x,int y,int button,int event)
{
	if(endgame!=0)return;
	static int ox=0;
	static int oy=0;
	static int state=0;
	//printf("x=%d y=%d button=%d event=%d\n",x,y,button,event);
	beginPaint();
	if(button==1)state=1-state;
	if(state)line(ox,oy,x,y);
	endPaint();
	ox=x;oy=y;
}
void changespeed(int x)
{
	if(x==9)speed=50;
	if(x==8)speed=100;
	if(x==7)speed=200;
	if(x==6)speed=300;
	if(x==5)speed=500;
	if(x==4)speed=700;
	if(x==3)speed=900;
	if(x==2)speed=1100;
	if(x==1)speed=1500;
	if(x==0)speed=20;
	startTimer(0,speed);
	endgame=0;
}
void key1(int key,int event)
{
	if(key>=48&&key<=57)changespeed(key-48);
	if(key==32&&event==1)endgame=2;
	if(endgame==2){clearDevice();choiceview();}
	if(endgame!=0)return;
	//printf("key=%d event=%d\n",key,event);
	if(key==38)changedir=1;
	if(key==39)changedir=2;
	if(key==40)changedir=3;
	if(key==37)changedir=4;
}

int Setup()
{
	initConsole();
	initWindow("Ì°³ÔÉß0.9",DEFAULT,DEFAULT,300,300);
	registerMouseEvent(mouse1);
	registerKeyboardEvent(key1);
	registerTimerEvent(time1);
	refresh();
	//²Î¿¼´úÂë 
	//beginPaint();
	//arc(0,100,30,40,50,60,70,80); 
	//putPixel(100,150,RGB(255,0,0));
	//line(0,0,width,width);
	//rectangle(10,10,22,22);
	//endPaint();
	return 0;
}
