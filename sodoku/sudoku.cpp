#include<stdio.h>   
#include<iostream.h>
#include<cstdlib>
#include<ctime>
#include <string>
#include <sstream>
#include <string>
int a[10];
int m=3;
int n;
 FILE* file = fopen("sudoku.txt","w+");
int data[9][9]= {
	{1,2,3, 4,5,6, 7,8,9},
	{4,5,6, 7,8,9, 1,2,3},
	{7,8,9, 1,2,3, 4,5,6},

	{2,3,1, 5,6,4, 8,9,7},
	{5,6,4, 8,9,7, 2,3,1},
	{8,9,7, 2,3,1, 5,6,4},

	{3,1,2, 6,4,5, 9,7,8},
	{6,4,5, 9,7,8, 3,1,2},
	{9,7,8, 3,1,2, 6,4,5}
};



/*{8,7,0,2,6,0,0,0,0}, 
{3,0,5,0,0,8,0,0,7},  
{0,9,0,0,5,7,0,0,0}, 
{5,0,0,0,8,0,0,7,0}, 
{0,4,0,3,1,0,8,0,0},  
{0,8,0,5,0,0,6,0,1}, 
{1,0,0,8,2,0,0,4,0}, 
{7,0,0,6,0,0,9,0,2}, 
{6,0,4,0,3,9,0,8,5}*/
int getTimes(int argc,char *argv[]){
	if(argc==1){
		printf("Enter the amount of Sudoku you want to generate: ");
		scanf("%d",&n);
	}else if(argc==2){
		printf("This is a wrong format: %s %s\n", argv[0], argv[1]);
		printf("Input format: sudoku [ -c parameter ]\n");
		return -1;
	}else if(argc==3&&strcmp(argv[1],"-c")!=0){
		printf("This is a wrong parameter: %s\n",argv[1]);
		printf("Input format: sudoku [ -c parameter ]\n");
		return -1;
	}

	else{
		n = atoi(argv[2]);
	}

	return n;
}


void output() 
{ 
	int i,j;  
	for(i = 0;i < 9;i++) 
	{  
		for(j = 0;j < 9;j++){
	
			fprintf(file,"%d ",data[i][j]);
		}
	  	  
			fprintf(file,"\n");
	}

	fprintf(file,"\n");
}
 void suiji()
{
    int i,j;
    srand(time(0));
    for(i=0;i<9;i++)
    {
        a[i]=rand()%9+1;
        int flag=1;
        while(flag==1)
        {
            for(j=0;j<i;j++)
                if(a[i]==a[j])
                    break;
            if(j<i)
                a[i]=rand()%9+1;
            if(j==i)
                flag=0;
        };
     
    }
  
}
 /*
   对得到的棋盘进行全局任意数字的交换
 */
 void  turn()
 {
      int m=511,c;
   for(int k = 2;k <10;k++) 
   {  
        m=rand()%2+1;
	    c=rand()%8+2;
		if(m>>(c-1)%2>0)
		{
	      for(int i = 0;i < 9;i++) 
		  {  
		 
		   for(int j = 0;j < 9;j++) 
		   { 
			 if(data[i][j] ==k)
			  { 
				 data[i][j]=c;
			 }
             else if(data[i][j] ==c)
			  { 
				 data[i][j]=k;
			 }
		   }
		  }
		}

   }
   	
 }

void input() 
{ 
	int i,j;  
	for(i = 0;i <1;i++) 
		for(j = 0;j < 9;j++) 
			scanf("%d",&data[i][j]); 
}

/*
与该格所在行、列，九宫格进行查查比较
*/

 int CheckSquare(int line,int col,int num) 
 {  
	 int i = (line / 3) * 3; 
	 int j = (col / 3) * 3; 
	 int m,n;  
	 for(m = i;m < i + 3;m++) 
		 for(n = j;n < j + 3;n++)  
			 if((data[m][n] == num) && !(m == line && n == col))
				 return 0; 
			 return 1; 
 }
 
 int CheckLine(int line,int col,int num) 
 { 
	 int i = 9; 
	 while(i--)  
		 if((data[line][i] == num) && (i != col)) 
			 return 0;
		 return 1; 
 }

 
 int CheckColumn(int line,int col,int num) 
 { 
	 int i = 9; while(i--)  
		 if((data[i][col] == num) && (i != line))
			 return 0; 
		 return 1; 
 }
 
 int Check(int i,int j,int num) 
 { 
	 return  CheckSquare(i,j,num)  &&  CheckLine(i,j,num)  &&  CheckColumn(i,j,num); 
 }

 int IsDone() 
 { 
	
	 int i,j;  
     for(i = 0;i < 9;i++) 
		 for(j = 0;j < 9;j++)  
			 if(!Check(i,j,data[i][j]) || (data[i][j] == 0)){
				 return 0;}
	 return 1; 
 } 
/*
 搜索数值为0的空格
 */
 void Calc(int a[]) 
 { 
	
	 int i,j,k; 
	 
    
	 for(i = 0;i < 9;i++) 
	 {  
		 
		 for(j = 0;j < 9;j++) 
		 { 
			
              if(data[i][j] == 0)
			  {  
				  for(k = 0; k <9;k++)
				  { 
					  if(Check(i,j,a[k])) 
					  {   
						  data[i][j] = a[k]; 
						  Calc(a); 
						   
					  } 
				  } 
				  if(k == 9)
				  {  
					 
					  data[i][j] = 0;
					  return;
				  } 
			  } 
		 } 
	 } 
	 
 }

 int main(int argc, char* argv[]) { 

	 getTimes(argc, argv);
	  suiji();
   for(int i=0;i<n;i++){
	  turn();
	  	  output();
	  }
    fclose(file);
	 return 0;
 } 