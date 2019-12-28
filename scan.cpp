#include<iostream>
#include<stdio.h>
#include<ctype.h>
#define N 26

using namespace std;
class HNode{
	public:char data;
	int weight;
	int parent, lchild, rchild;
	int level;
};
typedef HNode* HuffTree;

void scan(int weight[],int n){
	
	for(int i=0;i<n;i++)
	*(weight+i)=0;
	
	FILE*fp=fopen("stdio.1.txt","r");
	for(;!feof(fp);)
	{
	   char ch;fscanf(fp,"%c",&ch);
	   if(islower(ch))
	   {	
	      weight[ch-97]++;
	   }
	           
	} 
	for(int i=0;i<n;i++)
	cout<<*(weight+i)<<' ';
	cout<<'\n';
	fclose(fp);
} 
void compress(char* code[],int n){
	FILE*fp1=fopen("stdio.1.txt","r");
	FILE*fp2=fopen("stdio.2.txt","w");
	for(;!feof(fp1);)
	{
	   char ch;
	   fscanf(fp1,"%c",&ch);
	   if(islower(ch))
	       fprintf(fp2,"%s",code[ch-97]); 
	   else if(ch=='\n'||ch==' ')
	       fprintf(fp2,"%c",ch);
	} 
	fclose(fp1);fclose(fp2);
}

