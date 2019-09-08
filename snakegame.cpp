#include<bits/stdc++.h>
//#include<conio>
#include<time.h>
using namespace std;
const int height=10;
const int width=10;
int score;
int x;
int y;
int fruitx;
int fruity;
bool gameover;
int tailX[100];
int tailY[100];
//int prevxy[2][2];
int taillength=1;
char grid[width+1][height+1];
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
        {
          cout<<"F";continue;
        }
      if(j==x&&i==y)
        {
          cout<<'O';
          continue;
         }
      if(i==1)
      {
           cout<<"#";
      }
       else if(i==height)
        {
          cout<<"#";
        }
       else if(j==1)
        {
          cout<<"#";
        }
       else if(j==width)
        {
          cout<<"#";
        }
        else
            {
                bool print = false;
                for (int k = 1; k < taillength; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
      
      
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
  int i;
    int prevX = tailX[0];
    int prevY = tailY[0];
    tailX[0] = x;
    tailY[0] = y;  
    int prev2X, prev2Y;
   for(i=1;i<taillength;i++)
   {
    //predecessor is following the successor in each move
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;

   }
  /* for (i = 1; i < taillength; i++)
        {
            if (tailX[i] == tailX[0] && tailY[i] == tailX[0])
                gameover = true;
            
        }*/
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
    score+=10;taillength++;
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
      system("clear");
   //clrscr();
  }
}
