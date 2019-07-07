#include<stdio.h>
#define P1 0.5
#define P2 20
#define MAX_INPUT 1000
double average(double array[],int first_index,int second_index){

	int i,size=0;/*This function calculates average of chunk by using index value*/
	double average_list=0.0;

	for(i=first_index; i<=second_index; i++){
		size++;
		average_list=array[i]+average_list;
	}
	average_list=average_list/size;
	
	return average_list;
}

void sort_average(double average[],int index[][2],int size){
	
	double temp_ort;/*This function sorts averages and index values.*/
	int i,j,small_value,temp_first_index,temp_second_index;
	
	for(i=0; i<size-1; i++){	
		small_value=i;
		
		for(j=i+1; j<size; j++){
		
			if(average[j]<average[small_value]){
				small_value=j;
			}
		}
		/*Sorts averages with indexes*/	
		temp_ort=average[i];
		average[i]=average[small_value];
		average[small_value]=temp_ort;
		
		temp_first_index=index[i][0];
		index[i][0]=index[small_value][0];
		index[small_value][0]=temp_first_index;
		
		temp_second_index=index[i][1];
		index[i][1]=index[small_value][1];
		index[small_value][1]=temp_second_index;
	}
}

int main(void){
	
	int i,j,size_of_content=1,index_print;
	double input_file[MAX_INPUT],average_of_chunk[100];
	
	int index_of_chunk[100][2],first_index,second_index;
	double a,b,n;
	int coordinate=0,return_value,condition;
	
	FILE *input,*output;
	
	input=fopen("input.txt","r");
	output=fopen("output.txt","w");

	return_value=fscanf(input,"%lf",&input_file[0]);
		
	i=1;
	while(return_value==1 && return_value!=EOF ){/*Reading file*/

		return_value=fscanf(input,"%lf",&input_file[i]);
		if(return_value!=1 || return_value==EOF ){
			break;
		}
		size_of_content++;
		i++;
	}	
	i=0;
	for(j=1; j<size_of_content+1; j++){/*This loop finds the indexes of chunks*/
	/*If condition is true, j value is continued to increase */
	
		if(j==size_of_content){/*If j value is non-index, the loop is finished*/
			index_of_chunk[coordinate][0]=i;
			index_of_chunk[coordinate][1]=j-1;
			coordinate=coordinate+1;
			break;		
		}
		
		n=input_file[j];/*j is index of n(added number)*/	
		a=average(input_file,i,j-1);/*average (not include n)*/
		b=average(input_file,i,j);/*average (include n) */
		condition=!((b>a*(1+P1)) || (b<a*(1-P1)) || (a>n*P2) || (a<n/P2));
		
		if(!condition){/*If condition is false, j-1 value is saved.*/
			index_of_chunk[coordinate][0]=i;
			index_of_chunk[coordinate][1]=j-1;
			coordinate=coordinate+1;
			i=j;
		}
		}
	
	j=0;
	for(i=0; i<coordinate; i=i+1){
		average_of_chunk[j]=average(input_file,index_of_chunk[i][0],index_of_chunk[i][1]);/*Finds array which includes averages of chunks by using average function*/	
		j++;
	}
	
	sort_average(average_of_chunk,index_of_chunk,coordinate);/*This function sorts the average and indexes of chunks*/
	
	for(j=0; j<coordinate; j++){/*This loop writes */	
		
		a=index_of_chunk[j][0];/*Starting index*/
		b=index_of_chunk[j][1];/*Finishing index*/
		for(index_print=a; index_print<=b; index_print++){			
			fprintf(output,"%.4lf ",input_file[index_print]);/*Writing the each number  to file*/

		}
		
		fprintf(output,"\n");		
	}	
	fclose(input);
	fclose(output);
	
	return 0;
}
