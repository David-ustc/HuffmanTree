

#include<ctype.h>
#define N 26
#define MAX_WEIGHT 500//估计最大权值 
#include "scan.cpp"
#include<iostream>
using namespace std; 
#include<string.h>

#define ElemType HNode

typedef struct {
  char *elem; // 基地址
  int stacksize;  // 当前分配内存大小，单位是sizeof(ElemType)
  int top;        // 栈顶位置，定义为表长初始-1
} SqStack;
void Push(SqStack &S, char e) {
  if (S.top == S.stacksize-1) cout<<"space error";
  S.elem[++S.top] = e;
}
bool Pop(SqStack &S, char &e) {
  if (S.top == -1) return false;
  e = S.elem[S.top--];
  return true;
}
void InitStack(SqStack &S, int msize=20) {
  S.elem = new char[msize];
  S.stacksize = msize;
  S.top = -1;
}
void coding(HuffTree HT, int root, char*HC[], SqStack&S){
	char ch='a';
	if(root!=-1){                
		if(HT[root].lchild==-1){
			Push(S,'\0');
			HC[root]=new char[7];
			strcpy(HC[root],S.elem);//strcpy不可以用？？？ 
			Pop(S,ch);//cout<<root<<' '<<HC[root]<<" - ";
		}
	Push(S,'0');
	coding(HT,HT[root].lchild,HC,S);
	Pop(S,ch);
	Push(S,'1');
	coding(HT,HT[root].rchild,HC,S);
	Pop(S,ch);
	}
}
void HuffmanCoding(HuffTree HT, char*HC[],int n){
	SqStack S;
	InitStack(S);
	coding(HT,2*n-2,HC,S);
	//for(int i=0;i<n;i++)cout<<HC[i]<<' ';
}
void Select(HuffTree HT, int s, int &l, int &r) {
  // 本函数的作用是从HT[0..s]中找到权值最小的两个结点
  int WL = MAX_WEIGHT, WR = MAX_WEIGHT;
  for (int i=0; i<=s; ++i) 
  {
    if (HT[i].parent == -1) {
	          if (HT[i].weight < WL) 
	             {WR = WL; WL = HT[i].weight; r=l; l=i;
				 }
	          else if (HT[i].weight < WR) 
	             {WR = HT[i].weight; r=i;}
	             
	}
  }
}//end Select
void CreateHuffmanTree(HuffTree &HT, int n,int weight[]) {
  int m = 2*n-1; // 最终将得到2n-1个结点  
  HT= new HNode[m];
  int i;
  for (i=0; i<n; ++i) 
  {
   // cin >> HT[i].data>> HT[i].weight;
   HT[i].data=i+97;
   HT[i].weight=weight[i];
    HT[i].lchild = HT[i].rchild = HT[i].parent = -1;
  }
  for (i=n; i<m; ++i) 
  {
    int s1,s2;
	Select(HT, i-1, s1, s2);            //i-2???
	HT[s1].parent=i;
	HT[s2].parent=i;
    HT[i].weight = HT[s1].weight + HT[s2].weight;
    HT[i].lchild=s1; HT[i].rchild=s2;
	HT[i].parent = -1;
	
    //if(i==50)cout<<i<<' '<<HT[i].weight<<' '<<HT[i].lchild<<' '<<HT[i].rchild<<endl;
  }
  //for (i=0; i<m; ++i)cout<<HT[i].weight<<' ';cout<<'\n'; 
}

void print(int n,int level){
	//if(level==1)
	cout<<'\n';
	for(int i=0;i<(n-2*level);i++)//(n+20-3*level);i++)
	cout<<' '; 

	return; 
	
	/*else {cout<<'\n';for(int i=0;i<2*(n-level);i++)	cout<<' ';return;//打印n个空格}*/	
} 
void PrintTree(HuffTree T,int n) {                            //n个叶子节点的二叉树 
   int sequence[20*n];
   int i=0,j=0;
   sequence[j]=2*n-2;j++;
   sequence[j]=-2/*'\n'*/;j++;
   int level=1;
   while (j!=i+1) 
   {
   	 if(sequence[i]==-2) 
		{
		sequence[j]=-2;j++;/*(int)'\n'*/
		}     //说明一层结束 
   	 else if(sequence[i]==-1/*#*/);                                            
     else if((T+sequence[i])->lchild!=-1)
	   {                     
	     int m=sequence[i];
	     sequence[j]=T[m].lchild;j++;
	     sequence[j]=T[m].rchild;j++;
	    }
     else 
	    {
	     sequence[j]=-1;j++;
	     sequence[j]=-1;j++;
	    }
     i++;
	}//层序遍历 
  
  //for(i=0;i<j-1;i++)cout<<sequence[i]<<' ';
  
    i=0;
    print(n,level);
    while(i!=j-1){
	if(sequence[i]==-2/*\n*/) {level++;cout<<'\n';print(n,level);}//print打印空格以及分叉符号 
	 else if(sequence[i]==-1/*#*/)cout<<"# ";
	 else if((T+sequence[i])->lchild!=-1)cout<<(T+sequence[i])->weight<<' ';//非叶子结点打印data
	 else if((T+sequence[i])->lchild==-1)cout<<(T+sequence[i])->data<<' ';//(char)(T+sequence[i])->data<<' '; 
     i++;
	}
	cout<<'\n';
}
void decode(HuffTree code,int n){
	FILE*fp2=fopen("stdio.2.txt","r");
	FILE*fp3=fopen("stdio.3.txt","w");
	for(int i=2*n-2;!feof(fp2);)
	{
		char ch;
		fscanf(fp2,"%c",&ch);
		
		if(ch=='0') i=code[i].lchild;
		else if(ch=='1') i=code[i].rchild;
		else fprintf(fp3,"%c",ch);
		
	    if(code[i].lchild==-1) 
		  {    fprintf(fp3,"%c",code[i].data);
		       cout<<code[i].data;
		      i=2*n-2;
		   }
	}
	fclose(fp2);
	fclose(fp3);
}
int main(){
	HuffTree alphabet;
	int num=26;
	int weight[num];
	char **Hcode=new char*[num];
	
	scan(weight,num);
	CreateHuffmanTree(alphabet,num,weight);

	PrintTree(alphabet,num);
	HuffmanCoding(alphabet,Hcode,num);
	//for(int i=0;i<num;i++)	cout<<alphabet[i].weight<<alphabet[i].data<<' '<<Hcode[i]<<endl;
    compress(Hcode,num);
    decode(alphabet,num);
}
