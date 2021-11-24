#include<iostream>
using namespace std;


void display(int A[],int n);
void InsertSort1(int A[],int n)//直接插入排序
{
    for(int i=1;i<n;i++)
    {
        int temp=A[i];
        int j;
        for(j=i-1;j>=0&&temp<A[j];j--)
        {
            A[j+1]=A[j];
        }
        A[j+1]=temp;
        display(A,n);
    }
}
// 1 3 4 5 6 7 2


void InsertSort2(int A[],int n)//折半插入排序
{
    for(int i=1;i<n;i++)
    {
        int temp=A[i];
        int j,low=1,high=i-1,mid;
        while(low<=high)
        {
            mid=low+(high-low)/2;
            if(temp<A[mid])
            {
                high=mid-1;
            }
            else
            {
                low=mid+1;
            }
        }
        for(j=i-1;j>high;j--)
        {
            A[j+1]=A[j];
        }
        A[high+1]=temp;
        display(A,n);
    }
}


void ShellSort(int A[],int n)//希尔插入排序(不稳定)
{
    int gap=n/2;
    while(gap>0)
    {
        for(int i=0;i<gap;i++)//进行分组
        {
            for(int j=i+gap;j<n;j+=gap)//初始时，假定第0个元素是排序完的,则取第一个元素开始
            {
                //与已经排好序的进行比较
                //如果小于已经排好序的序列最后一个元素，则交换，否则，不交换（相当于将本元素插到排好序的数列末端）
                int temp=A[j];
                int k;
                for(k=j-gap;k>=0&&temp<A[k];k-=gap)
                {                 
                    A[k+gap]=A[k];
                }
                A[k+gap]=temp;    
            }
        }
        gap/=2;
    }
}


void BubbleSort(int A[],int n)//冒泡交换排序
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(A[j]>A[j+1])
            {
                int temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
            }
        }
    }
}


int Partition(int A[],int low,int high)
{
    int pivot=A[low];
    while(low<high)
    {
        while(low<high&&A[high]>=pivot)
        {
            high--;
        }
        A[low]=A[high];
        while (low<high&&A[low]<=pivot)
        {
            low++;
        }
        A[high]=A[low];
    }
    A[low]=pivot;
    return low;
}


void QuickSort(int A[],int low,int high)//快排(不稳定)
{
    if(low<high)
    {
        int pivotpos=Partition(A,low,high);
        QuickSort(A,low,pivotpos-1);
        QuickSort(A,pivotpos+1,high);
    }
}


void SelectSort(int A[],int n)//简单选择排序(不稳定)
{
    for(int i=0;i<n;i++)
    {
        int index=i;
        for(int j=i+1;j<n;j++)
        {
            if(A[j]<A[index])
            {
                index=j;
            }
        }
        swap(A[i],A[index]);
    }
}

//堆排序(不稳定)
void HeapAdjust(int A[],int parent,int n)
{
    int temp=A[parent];
    int child=2*parent+1;
    while(child<n)
    {
        if(child+1<n&&A[child]<A[child+1])//确保有右孩子
        {
            child++;
        }
        if(temp>=A[child])
        {
            break;
        }       
        else
        {
            A[parent]=A[child];
            parent=child;
        }
        child=2*parent+1;   
    }
    A[parent]=temp;
}


void BuildmaxHeap(int A[],int n)//建立大根堆
{
    for(int i=n/2;i>=0;i--)
    {
        HeapAdjust(A,i,n);
    }
}


void HeapSort(int A[],int n)//大根堆排序(从小到大)
{
    BuildmaxHeap(A,n);
    for(int i=n-1;i>0;i--)
    {
        swap(A[0],A[i]);
        HeapAdjust(A,0,i);
    }
}




//归并排序的合并函数
void Merge(int* A,int low,int mid,int high)
{
    //第一部分是low-->mid
    //第二部分是mid+1-->high
    //要归并的部分是low-->high

    int length=high-low+1;
    int* temp=new int[length];
    for(int index=0;index<length;index++)
    {
        temp[index]=A[low+index];
    }
    int i=0,j=mid-low+1;
    int k=low;
    while(i<mid-low+1&&j<high-low+1)
    {
        if(temp[i]<=temp[j])
        {
            A[k++]=temp[i++];
        }
        else
        {
            A[k++]=temp[j++];
        }
    }
    while(i<mid-low+1)
    {
        A[k++]=temp[i++];
    }
    while(j<high-low+1)
    {
        A[k++]=temp[j++];
    }

    delete[] temp;
       
}

//归并排序
void MergeSort(int A[],int low,int high)
{
    if(low<high)
    {
        int mid=low+(high-low)/2;
        MergeSort(A,low,mid);
        MergeSort(A,mid+1,high);
        Merge(A,low,mid,high);
    }
}


//基数排序
void RadixSort(int* A,int n)
{
    int max=A[0],base=1;
    for(int i=1;i<n;i++)
    {
        if(A[i]>max)
        {
            max=A[i];
        }
    }
    int* temp=new int[n];
    while(max/base>0)
    {
        int buckets[10]={0};
        for(int j=0;j<n;j++)
        {
            buckets[A[j]/base%10]++;
        }
        for(int j=1;j<n;j++)
        {
            buckets[j]+=buckets[j-1];
        }
        /*for(int k=n-1;k>=0;k--)
        {
            temp[buckets[A[k]/base%10]-1]=A[k];
            buckets[A[k]/base%10]--;
        }*/
        for(int k=0;k<n;k++)
        {
            temp[buckets[A[k]/base%10]-1]=A[k];
        }
        for(int k=0;k<n;k++)
        {
            A[k]=temp[k];
        }
        base=base*10;
    }
    delete[] temp;
}



void display(int A[],int n)
{
    for(int i=0;i<n;i++)
    {
        cout<<A[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    /*int A[6]={1,7,5,6,3,2};
    int B[6]={1,7,5,6,3,2};
    InsertSort1(A,6);
    cout<<endl;
    InsertSort2(B,6);
    int m[10]={19,29,30,1,20,0,2,5,87,6};
    ShellSort(m,10);
    display(m,10);

    int C[9]={10,70,50,60,30,20,40,40,45};
    BubbleSort(C,9);
    display(C,9);*/


    int D[10]={22,7,10,29,13,1,4,11,8,9};
    QuickSort(D,0,9);
    display(D,10);


    /*int E[11]={1,22,7,10,29,13,1,4,11,8,9};
    SelectSort(E,11);
    display(E,11);


    int G[12]={2,4,5,6,66,78,29,7,10,28,20,20};
    HeapSort(G,12);
    display(G,12);

    int F[15]={2,4,5,6,66,78,29,7,10,28,20,20,1,-1,-3};
    MergeSort(F,0,14);
    display(F,15);*/

    //int H[10]={1,99999,14,768,2345,10000,3,32,156,12};
    //RadixSort(H,10);
    //display(H,10);

    
    
}