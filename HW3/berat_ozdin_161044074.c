#include<stdio.h>
#define ROW 100
#define COLUMN 250
#define WORD_CH 10
int main(){
	/*Variables and open file processes */
	FILE *input1,*input2,*output;
	
	input1=fopen("input1.txt","r");
	input2=fopen("input2.txt","r");
	output=fopen("output.txt","w");
	
	char word[WORD_CH+1],search_matrix[ROW][COLUMN]={0};/*Word array and matris (2d-array of input2.txt file)*/
	char ch;
	int return_value=10,i=0,j=0,a,b,length_of_str=0,status=10,max_row_len=0;
	int row,column,control=0,control_vert=0,temp,temp_vert,k,m,c,d,n;
	/*-----------*/
	while(return_value!=EOF){/*Input2.txt is read. Characters in file are takes a matrix*/
	
		return_value=fscanf(input2,"%c",&ch);
		
		if(return_value==EOF){
			if(max_row_len<j){/*This condition finds row which is the longest*/
			max_row_len=j;
			}
			break;
		}
	
		if(ch=='\n'){/*If fscanf reads '\n' character,values start to take under row by increasing j value*/
			i++;
			if(max_row_len<j){/*This condition finds row which is the longest*/
			max_row_len=j;
			}
			j=0;
		}
	
		if(ch!='\n'){
			search_matrix[i][j]=ch;
			j++;
		}	
	}
	i=i+1;/*i  value is number of row*/
	while(status!=EOF){/*The loop continues until all of word in file is read*/
	
		status=fscanf(input1,"%s",word);
		
		if(status==EOF){
			break;
		}
		
		for(a=0; word[a]!=0; a++){/*This loop finds the length of word*/
			length_of_str++;
		}
		
		/*This part is horizantal searching*/
		for(a=0; a<i; a++){/*Row value is increased*/
			
			for(k=0; search_matrix[a][k+(length_of_str-1)]!=0; k++){
			
			temp=k;
				for(m=0; m<length_of_str; m++){/*Loop checks the word array and matris*/
				
				if(search_matrix[a][k]==word[m]){/*This condition checks for each character*/
					control++;
				}
				k++;
				}	
			if(control==length_of_str){/*If all checkings is success,the coordinate is writed to file */
				fprintf(output,"%s (%d,%d) %s\n",word,a+1,temp+1,"Horizantal");
			}
				
			k=temp;	
			control=0;
			}
		}
		/*-----------*/
		
		/*This part is vertical searching*/
		for(c=0; c<max_row_len; c++){/*Column value is increased*/
		
			for(d=0; d<i+length_of_str-1; d++){
			
			temp_vert=d;
			
				for(n=0; n<length_of_str; n++){/*Loop checks the word array and matris*/
				
				if(search_matrix[d][c]==word[n]){/*This condition checks for each character*/
				
				control_vert++;
				
				}
				d++;
			}
				if(control_vert==length_of_str){/*If all checkings is success,the coordinate is writed to file */
				fprintf(output,"%s (%d,%d) %s\n",word,temp_vert+1,c+1,"Vertical");
			}
			d=temp_vert;
			control_vert=0;		
			}
		}
		/*------------*/
		length_of_str=0;
		
		for(b=0; word[b]!=0; b++){/*Clearing the word array*/
			word[b]=0;
		}
	}
		
	return 0;
}
