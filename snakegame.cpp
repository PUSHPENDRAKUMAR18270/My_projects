#include<bits/stdc++.h>
//#include<conio>
using namespace std;
const int height=10;
const int width=10;
int score;
int x;
int y;
int fruitx;
int fruity;
bool gameover;
enum directions{STOP=0,UP,DOWN,LEFT,RIGHT};
directions dir;
void setup()
{
  gameover=false;
  score=0;
  fruitx=rand()%width;
  fruity=rand()%height;
  x=width/2;
  y=height/2;
}
void draw()
{
	//clrs;
  int i,j;
  for(i=1;i<=height;i++)
  {
  	for(j=1;j<=width;j++)
  	{
  	    if(j==fruitx&&i==fruity)
  			{cout<<"F";continue;}
  		if(j==x&&i==y)
  			{cout<<"o";
  		continue;}
  		if(i==1)
  		{
           cout<<"#";
  		}
  		else if(i==height)
  			cout<<"#";
  		else if(j==1)
  			cout<<"#";
  		else if(j==width)
  			cout<<"#";
  		
  		else cout<<" ";
  		
  	}
  	cout<<endl;
  }
  cout<<"score="<<score;
}
void input()
{
	char inp;
	cout<<"enter the move a/s/d/w/q\n";
	cin>>inp;
	cout<<endl;
	//if(_khbit())
	
	  switch(inp)//_getch()
	   {
		case 'a':
			  dir=LEFT;
			  break;
		case 'w':
			  dir=UP;
			  break;
		case 's':
			  dir=DOWN;
			  break;
		case 'd':
			  dir=RIGHT;
			  break; 
		case 'q':
		     dir=STOP;
			 //gameover=true;
			 break;
		}
	
}
void logic()
{
   switch(dir)
   {
   	 case UP:
   	  y--;
   	  break;
   	  case DOWN:
   	  y++;
   	  break;
   	  case RIGHT:
   	  x++;
   	  break;
   	  case LEFT:
   	  x--;
   	  break;
   	  case STOP:
   	  gameover=true;
   	  break;
   }
   if(x>width||x<=0||y>height||y<=0)
   {
   	gameover=true;
   	return;
   }
   if(x==fruitx&&y==fruity)
   {
   	score+=10;
   	fruitx=rand()%width;
   	fruity=rand()%height;
   }
}

int main()
{
	setup();
	while(!gameover)
	{
      draw();
      input();
      logic();
   //system('clear');
   clrscr;
  }
}
