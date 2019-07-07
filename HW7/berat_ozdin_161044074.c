#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 250
#define MAX_CH 10
void string_clear(char a[]){/*Clear the string*/

	int i=0;
	for(i=0; a[i]!=0; i++){
		a[i]=0;
	}
}
void clear_newline(char line[]){/*Clear newline character in string*/

	int i;
	for(i=0; (line[i]!=0 && line[i]!='\n'); i++);
	line[i]=0;
}
int gate_type(char a[]){/*Finds gate type*/

	int result=0;

	result=strcmp(a,"AND");
	if(result==0){return 1;}

	result=strcmp(a,"OR");	
	if(result==0){return 2;}

	result=strcmp(a,"NOT");	
	if(result==0){return 3;}

	result=strcmp(a,"FLIPFLOP");	
	if(result==0){return 4;}
}
typedef struct gate{/*Gate struct*/

	char gate_name[MAX_CH];
	int gate_type;
	int output;
	struct gate *left;
	struct gate *right;

}gate;

int tree_output(gate *head){/*Find output by using tree*/
	
	int output;
	if(head->gate_type==0){/*Number or flip flop memory*/

		return head->output;
	}
	else if(head->gate_type==1){/*And gate*/

		output=(tree_output(head->left) && tree_output(head->right));
	}
	else if(head->gate_type==2){/*Or gate*/

		output=(tree_output(head->left) || tree_output(head->right));
	}
	else if(head->gate_type==3){/*Not gate*/

		if(head->left==0){
			output=!(tree_output(head->right));
		}
		else{
			output=!(tree_output(head->left));
		}
	}
	else if(head->gate_type==4){/*Flipflop gate*/
		output=(!(tree_output(head->right)==tree_output(head->left)));
		head->right->output=output;/*Value is assigned to memory of flipflop*/
	}
	return output;
}

int number_of_node(){/*Finds number of node of tree*/

	FILE *input;
	char line[MAX_LINE+1];
	int i,counter_node=0;

	input=fopen("circuit.txt","r");
	fgets(line,MAX_LINE+1,input);
	clear_newline(line);

	for(i=0; line[i]!=0; i++){/*First line is scanned*/
		if(line[i]==' '){
			counter_node++;
		}
	}

	while(fgets(line,MAX_LINE+1,input)!=0){
		counter_node++;
	}

	fclose(input);
	return counter_node;
}
gate **circuit_tree(){/*This function creates the tree*/

	FILE *input;
	gate **circuit_p;/*Array includes adresses of structs*/
	gate *temp_struct;
	char line[MAX_LINE+1],gate_name[MAX_CH+1],gate_type_str[MAX_LINE+1];
	int i=0,j=0,k=0,struct_index=0,arr_index=0,gate_type_value,control_gate_name=10,left_rigt_control=0,name_index=0;

	circuit_p=(gate**)malloc((number_of_node())*sizeof(gate*));
	input=fopen("circuit.txt","r");
	fgets(line,MAX_LINE+1,input);
	clear_newline(line);

	for(i=0; line[i]!=' '; i++){/*Skips INPUT word*/
		j++;
	}
	j++;

	for(i=j; line[i]!=0; i++){/*Input names are assigned*/

		if(line[i]==' '){
			circuit_p[struct_index]=(gate*)malloc(sizeof(gate));
			strcpy(circuit_p[struct_index]->gate_name,gate_name);
			struct_index++;
			arr_index=0;
			string_clear(gate_name);
		}

		else{
			gate_name[arr_index]=line[i];
			arr_index++;
		}

		if (line[i+1]==0)
		{
			circuit_p[struct_index]=(gate*)malloc(sizeof(gate));
			strcpy(circuit_p[struct_index]->gate_name,gate_name);
			struct_index++;
			arr_index=0;
			string_clear(gate_name);
		}
	}

	for (i=0; i<struct_index; i++)/*Gate names and left-right adress data is assigned to input structs*/
	{
		circuit_p[i]->gate_type=0;
		circuit_p[i]->left=0;
		circuit_p[i]->right=0;
	}
	
	string_clear(line);

	while(fgets(line,MAX_LINE+1,input)!=NULL){/*Other lines are scanned*/
		
		clear_newline(line);
		circuit_p[struct_index]=(gate*)malloc(sizeof(gate));
		circuit_p[struct_index]->left=0;/*Starting left and right pointer is zero*/
		circuit_p[struct_index]->right=0;
	
		j=0;
		string_clear(gate_type_str);

		for(i=0; line[i]!=' '; i++){
			gate_type_str[i]=line[i];
			j++;
		}
		gate_type_str[i]=0;
		j++;

		circuit_p[struct_index]->gate_type=gate_type(gate_type_str);/*Gate type is assigned.1-AND,2-OR,3-NOT,4-FLIPFLOP*/
		string_clear(gate_name);

		name_index=0;
		for(i=j; line[i]!=' '; i++){
			gate_name[name_index]=line[i];
			name_index++;
		}
		i++;
		j=i;

		strcpy(circuit_p[struct_index]->gate_name,gate_name);/*Gate name is assigned*/
		string_clear(gate_name);

		arr_index=0;
		control_gate_name=10;
		left_rigt_control=0;

		for(i=j; line[i]!=0; i++){


			if(line[i]==' '){

				for(k=0; k<struct_index; k++){/*This loop search gate name and connects the current gate*/

					control_gate_name=strcmp(circuit_p[k]->gate_name,gate_name);
					if(control_gate_name==0){
						circuit_p[struct_index]->left=circuit_p[k];/*Node is added left side of current gate*/
						left_rigt_control=1;
						control_gate_name=10;
					}
				}

				arr_index=0;
				string_clear(gate_name);
			}

			else{
				gate_name[arr_index]=line[i];
				arr_index++;
			}

			if(line[i+1]==0){

				if(left_rigt_control==1){/*If left side isn't empty, gate is added right side*/

					for(k=0; k<struct_index; k++){

						control_gate_name=strcmp(circuit_p[k]->gate_name,gate_name);
						if(control_gate_name==0){
							circuit_p[struct_index]->right=circuit_p[k];
							control_gate_name=10;
						}
					}
				}

				else{/*If left side is empty, gate is added left side*/
					for(k=0; k<struct_index; k++){

						control_gate_name=strcmp(circuit_p[k]->gate_name,gate_name);
						if(control_gate_name==0){
							circuit_p[struct_index]->left=circuit_p[k];
							control_gate_name=10;
						}
					}
				}

				string_clear(gate_name);
			}
		}

		if(circuit_p[struct_index]->gate_type==4){/*This node is memory of flipflop*/

			circuit_p[struct_index]->right=(gate*)malloc(sizeof(gate));
			circuit_p[struct_index]->right->left=0;
			circuit_p[struct_index]->right->right=0;
			circuit_p[struct_index]->right->output=0;
			circuit_p[struct_index]->right->gate_type=0;
		}
		struct_index++;
		string_clear(line);
	}

	return circuit_p;
}
int main(){
	
	/*File opening*/
	FILE *input,*output;
	input=fopen("input.txt","r");
	output=fopen("output.txt","w");
	/*--------*/
	gate **p;
	gate *head;
	char input_line[MAX_LINE],input_data[MAX_CH+1];
	int i,struct_index=0,result=0;

	p=circuit_tree();/*Tree is created*/
	head=p[number_of_node()-1];/*Element which is root of tree is assigned to head*/
		
	while(fgets(input_line,MAX_LINE+1,input)!=0){/*This loop reads input.txt and assigns values to structs(input struct)*/
		
		clear_newline(input_line);
		struct_index=0;
		for(i=0; input_line[i]!=0; i++){

			if(input_line[i]!=' '){

				input_data[0]=input_line[i];
				sscanf(input_data,"%d",&p[struct_index]->output);
				struct_index++;
			}
		}
		fprintf(output,"%d\n",tree_output(head));
	}

	free(p);
	fclose(input);
	fclose(output);
	return 0;
}


