#include<iostream>
#include<string.h>
#include <bits/stdc++.h>
#include<time.h>
#define n  9
#define ll long long int
using namespace std;
bool issafe(int matrix[n][n],int row,int col,int num)
{
   bool inrow=false,incol=false,inbox=false;
   int box_start_row=row-row%3;
   int box_start_col=col-col%3;
   for(int i=0;i<n;i++)
   {
      if(matrix[row][i]==num)
      {
         inrow=true;break;
      }
   }
   for(int i=0;i<n;i++)
   {
      if(matrix[i][col]==num)
      {
         incol=true;break;
      }
   }
   for(int i=box_start_row;i<box_start_row+3;i++)
   {
      for(int j=box_start_col;j<box_start_col+3;j++)
      {
         if(matrix[i][j]==num)
         {
             inbox=true;break;
         }
      }
   }
   return !inrow&&!incol&&!inbox;
}
bool unassigned(int matrix[n][n],int &row,int &col)
{
   for(row=0;row<n;row++)
   {
      for(col=0;col<n;col++)
      {
         if(matrix[row][col]==0)
            return true;
      }
   }
   return false;
}
bool suduko_solver(int matrix[n][n])
{
   int row,col;
  if(!unassigned(matrix,row,col))
   return true;
 for(int num=1;num<=9;num++)
 {
   if(issafe(matrix,row,col,num))
   {
      matrix[row][col]=num;
      if(suduko_solver(matrix)==true)
      {
         return true;
      }
      matrix[row][col]=0;
   }
 }
 return false;
}

int main()
{
   int matrix[n][n]={{3, 0, 6, 5, 0, 8, 4, 0, 0},
                      {5, 2, 0, 0, 0, 0, 0, 0, 0},
                      {0, 8, 7, 0, 0, 0, 0, 3, 1},
                      {0, 0, 3, 0, 1, 0, 0, 8, 0},
                      {9, 0, 0, 8, 6, 3, 0, 0, 5},
                      {0, 5, 0, 0, 9, 0, 6, 0, 0},
                      {1, 3, 0, 0, 0, 0, 2, 5, 0},
                      {0, 0, 0, 0, 0, 0, 0, 7, 4},
                      {0, 0, 5, 2, 0, 6, 3, 0, 0}};
   suduko_solver(matrix);
   for(int i=0;i<n;i++)
   {
      for(int j=0;j<n;j++)
      {
         cout<<matrix[i][j]<<" ";
      }
      cout<<endl;
   }
}
