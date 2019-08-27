#include<bits/stdc++.h>
using namespace std;
void merge(int arr[],int lsubarray[],int rsubarray[],int llength,int rlength)
{
   int i=0,j=0,k=0;
    while(i<llength&&j<rlength)
    {
    	if(lsubarray[i]<rsubarray[j])
    		{
    			arr[k]=lsubarray[i];i++;k++;
    		}
    		else if(lsubarray[i]>rsubarray[j])
    		{
    			arr[k]=rsubarray[j];k++;j++;
    		}
    		else {
    			arr[k]=lsubarray[i];i++;k++;
    			arr[k]=rsubarray[j];k++;j++;
    		}
    }
    while(i<llength)
    {
    	arr[k]=lsubarray[i];k++;i++;
    }
    while(j<rlength)
    {
    	arr[k]=rsubarray[j];k++;j++;
    }
}
void mergesort(int arr[],int sizearray)
{
	if(sizearray==1)
		return;
	int mid=(sizearray)/2;
	int lsubarray[mid];
	for(int i=0;i<mid;i++)
	{
		lsubarray[i]=arr[i];
	}
	mergesort(lsubarray,mid);
	int rsubarray[sizearray-mid];
	for(int i=mid;i<sizearray;i++)
	{
		rsubarray[i-mid]=arr[i];
	}
	mergesort(rsubarray,sizearray-mid);
	merge(arr,lsubarray,rsubarray,mid,sizearray-mid);
}
int main()
{
	int sizearray,i;
	cin>>sizearray;
	int arr[sizearray];
	for(i=0;i<sizearray;i++)
	{
		cin>>arr[i];
	}
	mergesort(arr,sizearray);
	for(i=0;i<sizearray;i++)
	{
		cout<<arr[i]<<" ";
	}
}