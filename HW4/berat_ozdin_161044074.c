#include<stdio.h>
#include<string.h>
#include<math.h>
#define POLY_MAX 1000
#define VALUES_MAX 100

int main(){

	/*Variables and file opening processes*/
	FILE *polynomial,*values,*evaluations;
	int status=1,i=0,j=0,control=0,k=0,control_x=0,a=0,c=0,d=0;
	double value,result=0,value_poly,result_pow;
	char ch;
	
	polynomial=fopen("polynomial.txt","r");
	values=fopen("values.txt","r");
	evaluations=fopen("evaluations.txt","w");
	
	char poly_arr[POLY_MAX+1]={0},power[10]={0};
	int power_poly,e;
	char nonspace_poly[POLY_MAX+1]={0},part[20]={0};
	int val_arr[VALUES_MAX];
	/*-----*/
	fgets(poly_arr,1000,polynomial);/*The polynomial is takes to string*/
	
	
	for(i=0; poly_arr[i]!='\n'; i++){
		/*The polynomial string can includes spaces so this loop removes spaces in polynomial. 
		Also \n is removed in string*/
		if(poly_arr[i]!=' '){
	
		nonspace_poly[j]=poly_arr[i];
		j++;	
		}
	}
	

	status=1;
	while(status!=EOF){/*This loop reads value to end of the file(values.txt)*/
	
		status=fscanf(values,"%lf",&value);/*Values are read in values.txt*/

		if(status==EOF){
		
			break;
		}

		i=0;
		while(nonspace_poly[i]!=0){/*This loop goes to end of polynomial */
	
			for(j=0; nonspace_poly[j]!=0; j++){/*This for loop partitions the polynomial*/
				
				part[j]=nonspace_poly[i];
				/*If the next index(next the actual index) is sign character,the loop is finished*/
				if(nonspace_poly[i+1]=='+' || nonspace_poly[i+1]=='-'){
				/* Partition process by using signs which front monomials*/
					i++;
					break;
				}

				i++;
				if(nonspace_poly[i]==0){/*If the end of the polynomial,the loop is finished*/
					break;
				}	
			}
			
			
			control=0;
			for(k=0; part[k]!=0; k++){/*This loop counts the number of '^' character*/
			
				if(part[k]=='^')
				{
					control++;
				}
			}
			
			
			control_x=0;
			for(k=0; part[k]!=0; k++){/*This loop counts the number of 'x' character*/

				if(part[k]=='x')
				{
					control_x++;
				}
			}
			
						
			/*This part controls type of monomial*/
			if(control==1 && control_x==1){/*x and power monomial*/

				for(k=0; part[k]!=0; k++){/*This loop finds the power of monomial*/

					if(part[k]=='^'){
						a=0;
						for(d=k+1; part[d]!=0; d++){

							power[a]=part[d];
							a++;
						
						}
						break;
					}
				}
				

				sscanf(power,"%d",&power_poly);
				result_pow=1;
				/*Find result of x^power process*/
				result_pow=pow(value,power_poly);
				
				if(part[0]=='x' || (part[0]=='-' && part[1]=='x') || (part[0]=='+' && part[1]=='x')){

					if(part[0]=='+' || part[0]=='x'){
						value_poly=1;
					}
					else if(part[0]=='-'){
						value_poly=-1;
					}

				}
				else{
					sscanf(part,"%lf",&value_poly);
				}	
				result=result+(result_pow*value_poly);
			}
		
			else if(control==0 && control_x==1){/*Only x monomial*/

				if(part[0]=='x'  || (part[0]=='-' && part[1]=='x') || (part[0]=='+' && part[1]=='x')){
		/*This condition controls that coefficient is 1*/

					if(part[0]=='+' || part[0]=='x'){
						value_poly=1;
					}
					else if(part[0]=='-'){
						value_poly=-1;
					}

				}
				else{
					sscanf(part,"%lf",&value_poly);
					
				}

				result=result+(value_poly*value);
				/*Multiplication of coefficient and x value is added to result*/
			}

			else if(control==0 && control_x==0){/*Only number monomial*/

				sscanf(part,"%lf",&value_poly);/*Only coefficient is added to result*/
				result=result+value_poly;
				

			}
			
			for (c=0; c<20;c++)/*Clearing the part array*/
			{
				part[c]=0;
			}
		}

		fprintf(evaluations,"%lf\n",result);/*Result of calculation for a value is written*/
		result=0;
	}

	return 0;
}
