#include<stdio.h>
#define SIZE 512

void island_marker(char matrix[][SIZE],int i,int j,char terrain,char flag_value){

	if(j+1<SIZE && matrix[i][j+1]==terrain && matrix[i][j+1]!=flag_value){/*Right*/
		matrix[i][j]=flag_value;
		island_marker(matrix,i,j+1,terrain,flag_value);
	}
	if(0<=j-1 && matrix[i][j-1]==terrain && matrix[i][j-1]!=flag_value){/*Left*/
		matrix[i][j]=flag_value;
		island_marker(matrix,i,j-1,terrain,flag_value);
	}
	if(i+1<SIZE && matrix[i+1][j]==terrain && matrix[i+1][j]!=flag_value){/*Down*/
		matrix[i][j]=flag_value;
		island_marker(matrix,i+1,j,terrain,flag_value);
	}
	if(0<=i-1 && matrix[i-1][j]==terrain && matrix[i-1][j]!=flag_value){/*Up*/
		matrix[i][j]=flag_value;
		island_marker(matrix,i-1,j,terrain,flag_value);
	}
	if(1){
		matrix[i][j]=flag_value;
	}
}

int main(){

	FILE *input,*output;
	int i,j,island_counter=0;
	char matrix[SIZE][SIZE];
	char flag_value_ch=0,terrain=0;
	int water_level;
	int temp;

	input=fopen("input.txt","r");
	output=fopen("output.txt","w");
	fscanf(input,"%d",&water_level);//water level value(L) is read

	for(i=0; i<SIZE; i++){/*input.txt file is read and the values assigned to matrix*/
		for(j=0; j<SIZE; j++){
			
			fscanf(input,"%d",&temp);
			if(temp>water_level){
				matrix[i][j]=120;
			}
			else{
				matrix[i][j]=0;
			}
		}
	}
	terrain=120;
	flag_value_ch=1;
	for (i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++){

			if(matrix[i][j]!=0 && matrix[i][j]==120){/*If the coordinat is terrain and not read,this condition is true*/
				island_marker(matrix,i,j,terrain,flag_value_ch);/*This function marks island by using flag value*/
				island_counter++;
				flag_value_ch++;/*Every island has different flag value*/
			}
		}
	}

	fprintf(output,"%d\n",island_counter);
	flag_value_ch=125;
	terrain=125;

	for (i=0; i<SIZE; i++)
	{
		for(j=0; j<SIZE; j++){

			if(matrix[i][j]!=0 && matrix[i][j]!=125){
				terrain=matrix[i][j];
				island_marker(matrix,i,j,terrain,flag_value_ch);/*This function marks island by flag value(125).
				Finally finds every island coordinates is written to file*/
				fprintf(output,"%d %d\n",j,-i);
			}
		}
	}

	fclose(input);
	fclose(output);
	return 0;
}

