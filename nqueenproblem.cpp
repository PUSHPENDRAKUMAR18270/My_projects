#include<iostream>
#include<string.h>
#include <bits/stdc++.h>
#include<time.h>
#define ll long long int
#define n 5
using namespace std;
int ld[30]={0};
int rd[30]={0};
int cl[30]={0};
bool solvequeenutil(int arr[n][n],int cols)
{

   int i,j;
  if(cols==n)
   return true;
for(i=0;i<n;i++)
 {
   if(ld[i-cols+n-1]!=1&&rd[i+cols]!=1&&cl[i]!=1)
      {
         arr[i][cols]=1;ld[i - cols + n - 1] =
                          rd[i + cols] = cl[i] = 1;
         if(solvequeenutil(arr,cols+1))
        {
            return true;
        }
       ld[i-cols+n-1]=0;rd[i+cols]=0;cl[i]=0;
       arr[i][cols]=0;
      }
 }
return false;
}
int main()
{
  int arr[n][n];
  int i,j;
  memset(arr,0,sizeof(arr));
  solvequeenutil(arr,0);
  for(i=0;i<n;i++)
  {
   for(j=0;j<n;j++)
   {
      cout<<arr[i][j]<<" ";
   }
   cout<<endl;
  }
}
