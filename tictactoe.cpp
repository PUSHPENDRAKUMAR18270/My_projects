#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class tictactoe
{
	static char m[3][3];
	char symbol;
	
public:
	string name;
	tictactoe(string name,char s){
		name=s;symbol=s;
	}
	int  display_board();
	int  playturn(int x,int y);
	//void update_board(int x,int y,char s); 
    int  check_winner();
    int  fullboard();
};
int  tictactoe::fullboard()
{
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(m[i][j]!='.'||m[i][j]!='x')
			{
				return 0;
			}
		}
	}
	return 1;
}
int  tictactoe::playturn(int x,int y)
{
	if(m[x][y]=='0'||m[x][y]=='x')
		return 0;
	else {
		m[x][y]=symbol;return 1; 
	}
}
int  tictactoe::check_winner()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(m[i][j]==symbol)
			{
				flag=1;
			}
			else {
				flag=0;break;
			}
		}
		if(flag==1)
			return 1;
	}
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(m[j][i]==symbol)
			{
				flag=1;
			}
			else {
				flag=0;break;
			}
		}
		if(flag==1)
			return 1;
	}
	return 0;
}
void tictactoe::display_board()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<m[i][j]<<" ";
		}
		cout<<endl;
	}
}
int main()
{
  tictactoe p1("Pkc",'.'),p2("kapil",'x');
  int curr=1,x,y;
  while(true)
  {
       if(curr==1)
       {
       	  cout<<"enter the cordinates for turn\n";
       	  cin>>x>>y;
           if(!p1.playturn(x,y))
           {
           	cout<<"enter valid choice\n";
           	continue;
           }
           p1.display_board();
           if(p1.check_winner())
           {
           	cout<<p1.name<<" wins"<<endl;flag=1;break;
           }
           else
           {
           	curr=2;flag=0;
           }
           if(fullboard())
           {
           	flag=0;break;
           }
       }
       else if(curr==2)
       {
       	  cout<<"enter the cordinates for turn\n";
       	  cin>>x>>y;
           if(!p2.playturn(x,y))
           {
           	cout<<"enter valid choice\n";
           	continue;
           }
           p2.display_board();
           if(p2.check_winner())
           {
           	cout<<p2.name<<" wins"<<endl;flag=1;break;
           }
           else
           {
           	curr=1;flag=0;
           }
            if(fullboard())
           {
           	flag=0;break;
           }
       }

  }
  if(flag==0)
  {
  	cout<<"match becomes draw\n";
  }
}