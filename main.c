#include <stdio.h>
#include <string.h>
#define N 127      //Ҷ�ӽ����
#define M 2*N-1       //���н������
int hsz[N];
char zhenw[100000];
int weida[N][2];
char faze[127];
char faze2[127][50];
typedef struct//���������Ľڵ�
{
    char data;    //���洢�ĵ���
    int weight;        //Ȩ��(�õ��ʳ��ִ���)
    int parent;        //˫�׽��
    int lchild;        //���ӽ��
    int rchild;        //�Һ��ӽ��
} HTNode;
typedef struct//����������
{
    char cd[N];    //Ҷ�ӽڵ��Ӧ�Ĺ���������
    int start; //ָ�����������cd[]���ʼ�ַ�(���±�start��ʼ��nΪ��Ч�Ĺ���������)
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
void CreateHT(HTNode ht[],int n);//����
void CreateHCode(HTNode ht[],HCode hcd[],int n);//����
void DispHCode(HTNode ht[],HCode hcd[],int n);//�������
void main()
{
    printf("���ڸ�Ŀ¼�½���TXT�ļ�����#��β\n");
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
    ////��ʼ��
    char str[u];
    int fnum[u];
    for(i=0;i<u;i++)
    {
        str[i]=(char *)weida[i][0];
        fnum[i]=weida[i][1];
    }
    HTNode ht[M];//�ڵ�
    HCode hcd[N];//����
    for (i=0;i<n;i++)
    {
        ht[i].data=str[i];
        ht[i].weight=fnum[i];
    }
    CreateHT(ht,u);//�����������
    CreateHCode(ht,hcd,u);//���ݹ���������������������
    DispHCode(ht,hcd,u);//�������������
    printf("\n");
    shuchuzhengwen(it,u);
    printf("#");
}


void CreateHT(HTNode ht[],int n)
{
    int i,k,lnode,rnode;
    int min1,min2;
    for (i=0;i<2*n-1;i++)//ht[]��ʼ��---���н���������ó�ֵ-1
        ht[i].parent=ht[i].lchild=ht[i].rchild=-1;
    //�����������///////////////////////////////
    for (i=n;i<2*n-1;i++)
    {
        min1=min2=32767;//��СȨ�غʹ�СȨ��
        lnode=rnode=-1;//��С����Ȩ��λ��(�ڵ��±�)
        //�����еĽڵ���δ����������Ľڵ���ѡȡȨ����С�������ڵ�
        for (k=0;k<=i-1;k++)//��������i���ڵ�
            if (ht[k].parent==-1)//��δ����������Ľ��
            {
                if (ht[k].weight<min1)//k�Žڵ�Ȩ�ر���СȨ��min1��С
                {
                    min2=min1;rnode=lnode;//��СȨ��min2ȡ��СȨ��min1
                    min1=ht[k].weight;lnode=k;//��СȨ��min1ȡk�Žڵ��Ӧ��Ȩ��
                }
                else if (ht[k].weight<min2)//k�Žڵ�Ȩ�ش�����СȨ�أ�С�ڴ�СȨ��min2
                {
                    min2=ht[k].weight;rnode=k;//��СȨ��min2ȡk�Žڵ�Ȩ��
                }
            }
        ht[lnode].parent=i;ht[rnode].parent=i;//Ȩ����С�������ڵ㹹����i�Žڵ�Ϊ���ڵ�Ķ�����
        //����i�Žڵ�(�����ڵ�û��data��)
        ht[i].weight=ht[lnode].weight+ht[rnode].weight;
        ht[i].lchild=lnode;ht[i].rchild=rnode;
    }
}
void CreateHCode(HTNode ht[],HCode hcd[],int n)
{
    int i,f,temp;
    HCode hc;
    for (i=0;i<n;i++)    /*���ݹ������������������*/
    {
        //////��Ҷ�ڵ�i��Ӧ����---���б���////
        hc.start=n;//hc.cd[]�б����ŵ���ʼλ��(��start��ʼ��nΪ����洢��)(�����±귶Χ��0~N-1)
        temp=i;//��ǰ�ڵ�cȡҶ�ڵ�i
        f=ht[temp].parent;
        while (f!=-1)//��ǰ�ڵ�c���ڸ��ڵ�
        {
            if (ht[f].lchild==temp)//��ǰc�ڵ����丸�ڵ�����ӽڵ�
                hc.cd[hc.start--]='0';//����
            else hc.cd[hc.start--]='1';//��ǰc�ڵ����丸�ڵ���Һ��ӽڵ�

            temp=f;//ȡc�ĸ��ڵ�Ϊ�µĵ�ǰ�ڵ�c
            f=ht[temp].parent;//ȡ���µĵ�ǰ�ڵ�c�ĸ��ڵ�f
        }
        hc.start++;//(���±�hc.start��ʼ�洢��hc.start=n����)---startָ������������ʼ�ַ�
        ////////////////////////////////////////
        hcd[i]=hc;//Ҷ�ڵ�i��Ӧ���ʵĹ���������hc��������hcd[i]
    }
}
void DispHCode(HTNode ht[],HCode hcd[],int n)//�������������
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
        for (k=hcd[i].start;k<=n;k++)//�������(Ҷ�ڵ�)����
        {
            printf("%c",hcd[i].cd[k]);
            faze2[i][t++]=hcd[i].cd[k];
        }
        printf(" ");

    }

}
