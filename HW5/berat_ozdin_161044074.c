#include <stdio.h>
#include <string.h>
#define MAX_TEXT 250
#define MAX_NAME 10

void tree_visualize(char *text,int num_paranthesis,FILE *p){
	
	int i,control,a,b,c,d,e,space=0,comma_space=0,control_bracket=0;
	char node[MAX_NAME+1];

	for(d=0; d<(MAX_NAME+1); d++){/*Clearing node array*/
		node[d]=0;
	}

	for(i=0; (text[i]!=',' &&  text[i]!=0); i++){/*This loop reads name of name*/

		node[i]=text[i];

		if(text[i+1]==')'){
			break;
		}	
		if(text[i]=='('){
			break;
		}

	}
	

	if(text[0]==','){/*If current char is comma character,only comma is assigned to node array*/
		node[0]=text[0];	
	}
	
	if(node[0]!='(' && node[0]!=')' && node[0]!=','){/*Writing the output file*/
	
	for(a=0; a<num_paranthesis; a++){

		fprintf(p,"-");/*Line is written by using num_paranthesis value*/
	}
	fprintf(p,"%s\n",node);/*Node is written*/
	}

	control=0;

	if(node[0]==','){
		control=1;
	}
	else{		

		for(c=0; node[c]!=0; c++){/*Finding lenght of node array*/
			control++;
		}
	}
	
	if(text[i]==0){
		/*Finishing state of recursive function*/		
	}	
	
	else if(node[0]==','){

		e=1;
		comma_space=0;
		while(text[e]==' '){/*Checking space*/
			comma_space++;
			e++;	
		}
		if (comma_space!=0 && text[e]=='(')
		{
			comma_space++;
		}
		else{
			comma_space=1;
		}
		tree_visualize(&text[comma_space],num_paranthesis,p);
	}

	else if(node[0]=='('){

		e=1;
		control_bracket=0;
		while(text[e]==' '){/*Checking space*/
			control_bracket++;
			e++;
		}

		if(text[e]=='('){
			control_bracket++;
		}
		else{
			control_bracket=1;
		}

		tree_visualize(&text[control_bracket],num_paranthesis+1,p);/*State which node includes '(' character */
	}

	else if(node[0]==')'){

		space=0;
		e=1;
		while(text[e]==' '){/*Checking space*/
			space++;
			e++;
		}
		tree_visualize(&text[space+1],num_paranthesis-1,p);/*State which node includes ')' character */
	}

	else {/*States which node is text or ',' */

		tree_visualize(&text[control],num_paranthesis,p);
	}
}

int main(){

	FILE *input,*output;

	char text[MAX_TEXT+1],nonspace[MAX_TEXT+1];
	int control=0,i,j,a,space_start;

	input=fopen("input.txt","r");
	output=fopen("output.txt","w");
	fgets(text,250,input);

	i=0;
	j=0;

	while(text[i]!='\n'){/*Removing the \n character in string*/

		text[j]=text[i];
		j++;
		i++;
	}

	text[i]=0;
	i=0;
	while(text[i]!=0){
		i++;
	}

	i--;
	while(text[i]==' '){
		i--;
	}

	for(a=0; a<=i; a++){
		nonspace[a]=text[a];
	}

	space_start=0;
	i=0;

	while(nonspace[i]==' '){

		space_start++;
		i++;
	}
	for(i=0; nonspace[i]!=0; i++){

	}
	

	tree_visualize(&nonspace[space_start],0,output);
	return 0;
}
