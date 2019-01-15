#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<conio.h>
#include<windows.h>
#include<Mmsystem.h>
#include<cstdlib>
using namespace std;
struct food{
	int x=-1,y=-1;
	char val='F';
}fo;
struct posion{
	int x=-1,y=-1;
	char val='p';
}po;
struct snake{
	int x=0,y=3;
	char val='#';
	struct snake *next;
}*head=NULL;
int points=0;
void print(struct snake *head)
{
	snake *ptr=head;
	while(ptr!=NULL)
	{
		cout<<ptr->x<<","<<ptr->y<<","<<ptr->val<<endl;
		ptr=ptr->next;
	}
	cout<<endl;
}
void SetBoard(char b[][50],struct food fo,struct posion po,struct snake *head)
{
	int i,j;
		for(int i=0;i<30;i++){
		for(int j=0;j<50;j++){
			b[i][j]=' ';
		}
	}
	b[fo.x][fo.y]=fo.val;
	b[po.x][po.y]=po.val;
	struct snake *ptr=head;
	while(ptr!=NULL)
	{
		b[ptr->x][ptr->y]=ptr->val;
		ptr=ptr->next;
	}
}
void PrintBoard(char b[][50],int points)
{
	for(int i=0;i<50;i++)
	{
		cout<<"!";
	}
	cout<<"         "<<"score = "<<points;
	cout<<endl;
	for(int i=0;i<30;i++)
	{
	cout<<"!";
		for(int j=0;j<50;j++)
		{
			cout<<b[i][j];
		}
		cout<<"!\n";
	}
	for(int i=0;i<50;i++){
		cout<<"!";
	}
	cout<<endl;
}
struct snake *InsertNewGame(struct snake *h)
{
  struct snake *p;
  p=new snake;
p->next=NULL;
    h=p;
    p->val='X';
    p->x=10;
    p->y=1;
  struct snake *q;
  q=new snake;
p->next=q;
  q->val='#';
  q->x=11;
  q->y=1;
  struct snake *t;
  t=new snake;
q->next=t;
  t->val='Y';
  t->x=12;
  t->y=1;
  t->next=NULL;

  return h;
}
struct snake *InsertFromSave(struct snake *head)
{
	FILE *fp=fopen("save.txt","r");
	if(fp!=NULL)
	{
	char s[500];
	int i,j; 
	fgets(s,500,fp);
	head=NULL;
	struct snake* ptr;
	int x,y;
	char del,ch;
	for(i=0;s[i]!='\0';i++)
 	{
     	del=s[i];
	     x=0;y=0;
		for(j=i+1;s[j]!=',';j++)
		{
		x=x*10+(s[j]-'0');	
		}
		
		for(j=j+1;s[j]!=',';j++)
		{
		y=y*10+(s[j]-'0');	
		}
		ch=s[j+1];
		
		if(del=='+')
		{	
		struct snake* temp;
		temp=(struct snake*)malloc(sizeof(struct snake));
		temp->x=x;
		temp->y=y;
		temp->val=ch;
		temp->next=NULL;
		if(head==NULL)
		{
			head=temp;
			ptr=head;
		}
		else
		{
		ptr->next=temp;	
		ptr=temp;
		}			
		}
		else if(del=='-')
		{
		fo.x=x;
		fo.y=y;
		fo.val=ch;
		}
		else if(del=='*')
		{
		po.x=x;
		po.y=y;
		po.val=ch;	
		}
		i=j+1;
	}
	}
   else
   {
   	head=InsertNewGame(head);	
   }
   return head;
}
int CheckValidMove(char m,struct snake *head)
{
	int d;
	char m1;
	int x1,x2,y1,y2;
	x1=head->x;
	y1=head->y;
	x2=head->next->x;
	y2=head->next->y;
	if(x1==x2)
	{
		d=abs(y1-y2);
		if(d==1)
		{
			if(y1<y2)
			m1='d';
			else
			m1='a';
		}
		else
		{
			if(y2<y1)
			m1='d';
			else
			m1='a';
		}
	}
	else
	{
		d=abs(x1-x2);
		if(d==1)
		{
			if(x1<x2)
			m1='s';
			else
			m1='w';
		}
		else
		{
			if(x2<x1)
			m1='s';
			else
			m1='w';
		}
	}
	if(m==m1)
	return 0;
	else 
	return 1;
}
struct snake *MoveRestPart(struct snake *head)
{
	
	if(head->next==NULL)
	{
		return head;
	}
	else
	{
	MoveRestPart(head->next);
	head->next->x=head->x;
	head->next->y=head->y;	
	}
	return head;
}
struct snake *moveUp(struct snake *head)
{
	head->x--;
	if(head->x<0)
	head->x=29;
	return head;
}
struct snake *movedown(struct snake *head)
{
	head->x++;
	if(head->x>29)
	head->x=0;
	return head;
}
struct snake *moveleft(struct snake *head)
{
	head->y--;
	if(head->y<0)
	head->y=49;
	return head;
}struct snake *moveright(struct snake *head)
{
	head->y++;
	if(head->y>49)
	head->y=0;
	return head;
}
int cutitself(struct snake *head,struct food fo)
{
	struct snake *ptr=head->next;
	while(ptr!=NULL)
	{
		if(ptr->x==head->x && ptr->y==head->y)
		{
			return 1;
		}
		ptr=ptr->next;
	}
	return 0;
}
char GetTailDirection(struct snake *head,struct snake *ptr)
{
	char m;
	int x1,x2,y1,y2,d;
	x1=ptr->x;
	x2=ptr->next->x;
	y1=ptr->y;
	y2=ptr->next->y;
	if(x1==x2)
	{
		d=abs(y1-y2);
		if(d==1)
		{
			if(y1<y2)
				m='d';
			else
			m='a';
		}
		else
		{
			if(y1<y2)
			m='a';
			else
			m='d';
		}
	}
	else
	{
		d=abs(x1-x2);
		if(d==1)
		{
			if(x1<x2)
			{
				m='s';
			}
			else
			m='w';
		}
		else
		{
			if(y1<y2)
			m='s';
			else
			m='w';
		}
	}
	return m;
}
struct snake *InsertNew(struct snake *head)
{
	struct snake *ptr=head,*n=new snake;
	n->val='Y';
	n->next=NULL;
	while(ptr->next->next!=NULL)
	{
		ptr=ptr->next;
	}
	char m=GetTailDirection(head,ptr);
	ptr=ptr->next;
	ptr->val='#';
	if(m=='w')
	{
		n->y=ptr->y;
		n->x=ptr->x-1;
	}
    else if(m=='s')
	{
			n->x=ptr->x+1;
			n->y=ptr->y;
	}
	  else if(m=='a')
	{
		n->x=ptr->x;
		n->y=ptr->y-1;
	}
	  else if(m=='d')
	{
	n->x=ptr->x;
	n->y=ptr->y+1;
	}
	ptr->next=n;
	return head;
}
struct snake *DeleteHead(struct snake *head)
{
	struct snake *ptr=head;
	int c=1;
	while(ptr->next->next!=NULL)
	{
		ptr=ptr->next;
		c++;
	}
	if(c>=3)
	{
		ptr->val='Y';
		ptr->next=NULL;
	}
	return head;
}
int checkLiyOnSnakeBody(struct snake *head,struct food fo)
{
	struct snake *ptr=head;
	while(ptr!=NULL)
	{
		if(ptr->x==fo.x && ptr->y==fo.y)
		{
			return 1;
		}
		ptr=ptr->next;
	}
	return 0;
}
int checkposionOnSnakeBody(struct snake *head,struct posion po)
{
		struct snake *ptr=head;
	while(ptr!=NULL)
	{
		if(ptr->x==po.x && ptr->y==po.y)
		{
			return 1;
		}
		ptr=ptr->next;
	}
	return 0;
}
void SaveTheGame(struct snake *head,struct food fo,struct posion po)
{
	FILE *fp;
		fp=fopen("save.txt","w");
		if(fp!=NULL)
		{
	    	struct snake *ptr=head;
		    char ch;
		    int x,y;
		    while(ptr!=NULL)
	         	{
	        	x=ptr->x;
	         	y=ptr->y;
	        	ch=ptr->val;	
				fprintf(fp,"+%d,%d,%c",x,y,ch);	
		        ptr=ptr->next;	
		        }
		x=fo.x;
		y=fo.y;
		ch=fo.val;
		fprintf(fp,"-%d,%d,%c",x,y,ch);		
		x=po.x;
		y=po.y;
		ch=po.val;
		fprintf(fp,"*%d,%d,%c",x,y,ch);		
			fclose(fp);
		}
}
void game(struct snake *head,char b[][50],struct food fo,struct posion po)
{
	char m;
	do{
		if(head->x==fo.x && head->y==fo.y)
		{
			points=points+5;
			fo.x=rand()%28+1;
			fo.y=rand()%48+1;
		    head=InsertNew(head);
		}
		if(head->x==po.x && head->y==po.y)
		{
			points=points-5;
			po.x=rand()%28+1;
			po.y=rand()%48+1;
			head=DeleteHead(head);
		}
		while(1)
		{
			if(checkLiyOnSnakeBody(head,fo))
			{
			fo.x=rand()%28+1;
			fo.y=rand()%48+1;
			}
			else
			break;
		}
		while(1)
		{
			if(checkposionOnSnakeBody(head,po))
			{
			po.x=rand()%28+1;
			po.y=rand()%48+1;
			}
			else
			break;
		}
		cin>>m;
		system("cls");
		if(m=='q')
		{
			cout<<"Do You Wants To Save The Game\n";
			char ch;
			cin>>ch;
			if(ch=='y')
			{
				SaveTheGame(head,fo,po);
			}
			system("cls");
			cout<<"Game over\n";
			break;
		}
		if(CheckValidMove(m,head))
		{
			head=MoveRestPart(head);
			if(m=='w')
			head=moveUp(head);
			else if(m=='s')
			head=movedown(head);
			else if(m=='a')
			head=moveleft(head);
			else if(m=='d')
			head=moveright(head);
		}
		SetBoard(b,fo,po,head);
		PrintBoard(b,points);
		if(cutitself(head,fo))
		{
			system("cls");
	      cout<<"Gamr Over!\n";
			break;
		}
	}while(m=='w' || m=='s' || m=='a' || m=='d');
	cout<<"YOU SCORE "<<points<<" POINTS\n";
}
int main()
{
	char b[30][50];
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<50;j++)
		{
			b[i][j]=' ';
		}
	}
	cout<<"DO you Wants to continue the save game\n";
	char ch;
	cin>>ch;
	if(ch!='y')
	{
	  head=InsertNewGame(head);	
	}
	else
	{
		head=InsertFromSave(head);
	}
	system("cls");
			if(fo.x==-1 && fo.y==-1 && po.x==-1 && po.y==-1)
		{
			fo.x=rand()%28+1;
			fo.y=rand()%48+1;
			po.x=rand()%28+1;
			po.y=rand()%48+1;
		}
			SetBoard(b,fo,po,head);
		PrintBoard(b,points);
	game(head,b,fo,po);
}
