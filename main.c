#include <stdio.h>
#include <string.h>
#define N 127      //叶子结点数
#define M 2*N-1       //树中结点总数
int hsz[N];
char zhenw[100000];
int weida[N][2];
char faze[127];
char faze2[127][50];
typedef struct//哈夫曼树的节点
{
    char data;    //结点存储的单词
    int weight;        //权重(该单词出现次数)
    int parent;        //双亲结点
    int lchild;        //左孩子结点
    int rchild;        //右孩子结点
} HTNode;
typedef struct//哈夫曼编码
{
    char cd[N];    //叶子节点对应的哈夫曼编码
    int start; //指向哈夫曼编码cd[]的最开始字符(从下标start开始到n为有效的哈夫曼编码)
} HCode;
void shuchuzhengwen(int m,int u)
{
    int i,j,k;
    for(i=0;i<m;i++)
    {
        for(j=0;j<u;j++)
        {
            if(faze[j]==zhenw[i])
            {
                for(k=0;k<50;k++)
                    if(faze2[j][k]!='\0') printf("%c",faze2[j][k]);
                printf(" ");
            }
        }
    }
}
void CreateHT(HTNode ht[],int n);//构造
void CreateHCode(HTNode ht[],HCode hcd[],int n);//编码
void DispHCode(HTNode ht[],HCode hcd[],int n);//输出编码
void main()
{
    printf("请在根目录下建立TXT文件，以#结尾\n");
    freopen("in.txt","r",stdin);
        freopen("out.txt","w",stdout);
    memset(hsz,0,sizeof(hsz));
    memset(zhenw,'\0',sizeof(zhenw));
    memset(weida,0,sizeof(weida));
    memset(faze,'\0',sizeof(faze));
    memset(faze2,'\0',sizeof(faze2));
    int a;
    char b;
    b=getchar();
    a=(int*)b;
    int i=0,it=0;
    hsz[a]++;
    zhenw[it++]=b;
    while(b!='#')
    {
        b=getchar();
        zhenw[it]=b;
        a=(int *)b;
        hsz[a]++;
        it++;
    }
    int u=0;
    for(i=0;i<N;i++)
    {
        if(hsz[i]!=0)
        {
            weida[u][0]=i;
            weida[u][1]=hsz[i];
            u++;
        }
    }
    int n=127;
    ////初始化
    char str[u];
    int fnum[u];
    for(i=0;i<u;i++)
    {
        str[i]=(char *)weida[i][0];
        fnum[i]=weida[i][1];
    }
    HTNode ht[M];//节点
    HCode hcd[N];//编码
    for (i=0;i<n;i++)
    {
        ht[i].data=str[i];
        ht[i].weight=fnum[i];
    }
    CreateHT(ht,u);//构造哈夫曼树
    CreateHCode(ht,hcd,u);//根据哈夫曼树建立哈夫曼编码
    DispHCode(ht,hcd,u);//输出哈夫曼编码
    printf("\n");
    shuchuzhengwen(it,u);
    printf("#");
}


void CreateHT(HTNode ht[],int n)
{
    int i,k,lnode,rnode;
    int min1,min2;
    for (i=0;i<2*n-1;i++)//ht[]初始化---所有结点的相关域置初值-1
        ht[i].parent=ht[i].lchild=ht[i].rchild=-1;
    //构造哈夫曼树///////////////////////////////
    for (i=n;i<2*n-1;i++)
    {
        min1=min2=32767;//最小权重和次小权重
        lnode=rnode=-1;//最小两个权重位置(节点下标)
        //从已有的节点且未构造二叉树的节点中选取权重最小的两个节点
        for (k=0;k<=i-1;k++)//树中现有i个节点
            if (ht[k].parent==-1)//尚未构造二叉树的结点
            {
                if (ht[k].weight<min1)//k号节点权重比最小权重min1还小
                {
                    min2=min1;rnode=lnode;//次小权重min2取最小权重min1
                    min1=ht[k].weight;lnode=k;//最小权重min1取k号节点对应的权重
                }
                else if (ht[k].weight<min2)//k号节点权重大于最小权重，小于次小权重min2
                {
                    min2=ht[k].weight;rnode=k;//次小权重min2取k号节点权重
                }
            }
        ht[lnode].parent=i;ht[rnode].parent=i;//权重最小的两个节点构造以i号节点为父节点的二叉树
        //新增i号节点(新增节点没有data域)
        ht[i].weight=ht[lnode].weight+ht[rnode].weight;
        ht[i].lchild=lnode;ht[i].rchild=rnode;
    }
}
void CreateHCode(HTNode ht[],HCode hcd[],int n)
{
    int i,f,temp;
    HCode hc;
    for (i=0;i<n;i++)    /*根据哈夫曼树求哈夫曼编码*/
    {
        //////对叶节点i对应单词---进行编码////
        hc.start=n;//hc.cd[]中编码存放的起始位置(从start开始到n为编码存储区)(编码下标范围是0~N-1)
        temp=i;//当前节点c取叶节点i
        f=ht[temp].parent;
        while (f!=-1)//当前节点c存在父节点
        {
            if (ht[f].lchild==temp)//当前c节点是其父节点的左孩子节点
                hc.cd[hc.start--]='0';//编码
            else hc.cd[hc.start--]='1';//当前c节点是其父节点的右孩子节点

            temp=f;//取c的父节点为新的当前节点c
            f=ht[temp].parent;//取当新的当前节点c的父节点f
        }
        hc.start++;//(从下标hc.start开始存储到hc.start=n结束)---start指向哈夫曼编码最开始字符
        ////////////////////////////////////////
        hcd[i]=hc;//叶节点i对应单词的哈夫曼编码hc存入编码表hcd[i]
    }
}
void DispHCode(HTNode ht[],HCode hcd[],int n)//输出哈夫曼编码
{
    int t=0;
    int i,k;
    int CodeSum=0,WeightAdd=0;
    for (i=0;i<n;i++)
    {
        t=0;
        int CountLen=0;
        faze[i]=ht[i].data;
        printf("(%c) ",ht[i].data);
        for (k=hcd[i].start;k<=n;k++)//输出单词(叶节点)编码
        {
            printf("%c",hcd[i].cd[k]);
            faze2[i][t++]=hcd[i].cd[k];
        }
        printf(" ");

    }

}
