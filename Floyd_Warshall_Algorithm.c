#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>


void main(){

	int n=0;
	int fcc;
	int tc;
	int fs=1;
	int cc;
	int w[10][10];
	int a[10][10];
	int d[10];
	int dmax=0;
	int W_bar[10][10];
	int M;
	int W[10][10];
	int D[10][10];
	int i,j;
	int r[10][10];
	int rv[1][10];
	int mem[100];
	int k;
	char input_file_name [100];

//read file to matrix

	i=0;
	FILE * inputFile;

	printf("Enter the ascii file name: ");
	scanf("%s",input_file_name);	

	inputFile = fopen(input_file_name,"r");
	
	FILE * output_file;
	output_file = fopen("Out.txt", "w");
	
	if (inputFile == NULL)	{
		printf("Error opening Input file\n");
		}	
	if (output_file == NULL)	{
		printf("Error opening Output file\n");
		}

	while((i<100)){
	fscanf(inputFile,"%d ",&mem[i]);

	i++;

	if(feof(inputFile)){
		break;
		}	
	}


	n=mem[0];

	printf("Number of Nodes is %d",n);


	printf("\n\n");

//Reading path delays
k=1;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{
				w[i][j] = mem[k];
				k++;
			}
	}



//Print w

	printf("\n\n::::::Path Delay Matrix is::::::\n\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{
				printf("%d \t",w[i][j]);
			}
			printf("\n\n");
	}


	
//reading node delays

	for(i=1;i<=n;i++)
	{
		d[i] = mem[k];
		k++;
	}

	
//print d	
		
	printf(":::::::Node Delays are::::::\n");	
	for(i=1;i<=n;i++)
	{
		printf("%d \t",d[i]);
	}
	
	printf("\n");
	

//finding inequalities initially

	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{
				r[i][j] = w[i][j];
			}
	}

	

//print inequalities	
	printf("\n\n::::::The inequalities are::::::\n\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{   if(r[i][j] != 9999 &&  (i != j))
				printf("r(%d) - r(%d) <= %d \n",i,j,r[i][j]);
			}
	}
	
printf("\n\n ");	
	
	
// finding dmax
	
	for(i=1;i<=n;i++)
		if(d[i] > dmax)
			dmax = d[i];
			

printf("Enter desired clock cycle value(value should be atleast greater than maximum combinational delay (%d)): ",dmax);
	scanf("%d",&fcc);


	printf("dmax value is %d\n",dmax);
	
	M = dmax*n;
	
	printf("M value is %d\n",M);

//  W_bar = cal_W_bar();
	
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{	
				if(i==j)
				W_bar[i][j] = 9999;
				else if(w[i][j] != 9999)
				W_bar[i][j] = M * w[i][j] - d[i];
				else
				W_bar[i][j] = 9999;
			}
	}
	
//print W_bar matrix	
	printf("\n\n::::::W_bar matrix::::::\n\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{
				printf("%d \t",W_bar[i][j]);
			}
			printf("\n\n");
	}

	
	
//S_bar finding logic

//Using Flyod Marshall algorithm



        for(k=1;k<=n;k++)/*n is the no.of vertices of the graph and k represents table no.*/
            {
                for(i=1;i<=n;i++)/*i represents row no. within a table*/
                    {
                        for(j=1;j<=n;j++)/*j represents column no. within a row*/
                            {
                                if(W_bar[i][j]>(W_bar[i][k]+W_bar[k][j]))/*Minimum is to be selected*/
                                /*W_bar[i][j] denotes distance between ith vertex and jth vertex*/
                                W_bar[i][j]=(W_bar[i][k]+W_bar[k][j]);
                            }
                    }
            }



    printf("\nS_bar matrix:\n");
    
        for(i=1;i<=n;i++)
            {
                for(j=1;j<=n;j++)	
                    {
                        printf("%5d",W_bar[i][j]);
                    }
                printf("\n");
            }


//W finding logic

	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{	
				if(i==j)
					W[i][j] = 0;
				else
					W[i][j] = ((W_bar[i][j] % M) >0 ) ? (W_bar[i][j] / M) + 1 : (W_bar[i][j] / M);
			}
	}



//print W matrix	
	printf("\n\n::::::W matrix::::::\n\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{
				printf("%d \t",W[i][j]);
			}
			printf("\n\n");
	}

	

//D finding logic

	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{	
				if(i==j)
					D[i][j] = d[i];
				else
					D[i][j] = M*W[i][j] - W_bar[i][j] + d[j];
			}
	}
	
//print D matrix	
	printf("\n\n::::::D matrix::::::\n\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{
				printf("%d \t",D[i][j]);
			}
			printf("\n\n");
	}
	
	
int rnew[10][10];	

	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{
				rnew[i][j]=r[i][j];
			}
	}

//finding inequalities different values of clock cycles

if(fs!=0)
{

   for(cc=fcc;cc>=dmax;cc--)
   
{
    printf("\n\n:::::::::For c = %d value:::::::::",cc);
	    for(i=1;i<=n;i++)
	        {
	        	for(j=1;j<=n;j++)
		        	{
		        		rnew[i][j]=r[i][j];
		        	}
	        }
	
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{	
				if( D[i][j] > cc)
					rnew[j][i] = W[i][j] -1 ;
			}
	}

	

	//print inequalities	
	printf("\n\n::::::The Inequalities are::::::\n\n");
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{
			    if(rnew[i][j]!=9999&&(i!=j))
				printf("r(%d) - r(%d) <= %d \n",j,i,rnew[i][j]);
			}
	}
	

	for(j=1;j<=n+1;j++)
	{	
	        rnew[n+1][j] = 0 ;
			if(i!=j)
			rnew[j][n+1] = 9999;
		}
	
	
	
for(k=1;k<=n+1;k++)/*n is the no.of vertices of the graph and k represents table no.*/
    {
        for(i=1;i<=n+1;i++)/*i represents row no. within a table*/
            {
                for(j=1;j<=n+1;j++)/*j represents column no. within a row*/
                {
                    if(rnew[i][j]>(rnew[i][k]+rnew[k][j]))/*Minimum is to be selected*/
                    rnew[i][j]=(rnew[i][k]+rnew[k][j]);
                }
            }
    }



printf("\nThe final matrix where we can find the shortest distance:\n");
    for(i=1;i<=n+1;i++)
        {
            for(j=1;j<=n+1;j++)	
                {
                    printf("%5d",rnew[i][j]);
                }
            printf("\n");
        }
	

for(i=1;i<=n+1;i++)
{
if(rnew[i][i]>=0)
    fs=1;
else
  {  fs=0;
    break;
    
  } 
}

if(fs==1)
{
    printf("\n\t Success: The graph does not contain any negative cycles. This is a feasible solution for a 'c' value of %d\n", cc);
    
    tc=cc;
    
    	for(i=1;i<=n;i++)
	{
	    rv[1][i]=rnew[n+1][i];
	}


	printf("\n::::::Retimed Vectors::::::\n\n");
	for(i=1;i<=n;i++)
	{
	    printf("rv[%d] = %d \t ",i,rv[1][i]);
	}


}

else if(fs==0)
{
    printf("\n\t Fail:The graph contains negative cycles. This cannot be a feasible solution for a 'c' value of %d\n", cc);
    break;
}
    
}

}

printf("\n\n ");

printf("\n\t The final values of the retimed vectors for a 'c' value of %d are as follows: \n", tc);
	for(i=1;i<=n;i++)
	{
	    printf("rv[%d] = %d \t ",i,rv[1][i]);
	}
	
		    printf("\n\n ");

int gnew[10][10];
	
	
	for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
				{
				    gnew[i][j]  =  w[i][j];				    
				}
		}
	
	
	
	for(i=1;i<=n;i++)
		{
			if(rv[1][i] != 0 )
			for(j=1;j<=n;j++)
				{
				    if(i != j )
				    {
					    if(gnew[j][i] != 9999)
					    gnew[j][i] = gnew[j][i] + rv[1][i]; 
                        else					
					    gnew[j][i] = 9999;
					
			    		if(gnew[i][j] !=9999)
				    	gnew[i][j] = gnew[i][j] - rv[1][i];
				    	else
				    	gnew[i][j] = 9999;
				    	
				
				    }    
				    else
				    gnew[i][j] = 0;
				}
		}
	

 
	printf("\n::::::Retimed Circuit Path Delay Matrix::::::\n\n");	
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
				{
					printf("%5d \t",gnew[i][j]);
				}
				printf("\n");
		}
	

	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
			{
				fprintf(output_file,"%d \n",gnew[i][j]);
			}	
	}



}

