#include<stdio.h>
#define NUM_OF_POINT 10/*Number of point which in a class*/
#define SMALL_VALUE 0.00001/*Small value for divide zero*/
int main(){

	/*Variables*/
	int i,up,down;
	double sum_of_class1_x=0.0,sum_of_class1_y=0.0,sum_of_class2_x=0.0,sum_of_class2_y=0.0,point_x=0.0,point_y=0.0;
	double class1_x,class1_y,class2_x,class2_y,midpoint_x,midpoint_y,user_point_x,user_point_y,line_y;
	double slope_of_connecting_line,slope_of_seperating_line;
	
	for(i=0; i<NUM_OF_POINT; i++){  

		scanf("%lf %lf",&point_x,&point_y);
		
		sum_of_class1_x=sum_of_class1_x+point_x;
		sum_of_class1_y=sum_of_class1_y+point_y;
	}

	class1_x=sum_of_class1_x/NUM_OF_POINT;
	class1_y=sum_of_class1_y/NUM_OF_POINT;

	point_x=0.0;
	point_y=0.0;

	for(i=0; i<NUM_OF_POINT; i++){ 

		scanf("%lf %lf",&point_x,&point_y);

		sum_of_class2_x=sum_of_class2_x+point_x;
		sum_of_class2_y=sum_of_class2_y+point_y;
	}

	class2_x=sum_of_class2_x/NUM_OF_POINT;/*Finding coordinates of average point class 2*/
	class2_y=sum_of_class2_y/NUM_OF_POINT;
	
	midpoint_x=(class1_x+class2_x)/2.0;/*Calculating coordinates of midpoint*/
	midpoint_y=(class1_y+class2_y)/2.0;
	
	if(class2_x-class1_x==0)/*If coordinate x of first average point is same the coordinate x of second average point, the program uses macro value(0.00001)*/
	{
		slope_of_connecting_line=(class2_y-class1_y)/SMALL_VALUE;/*Calculating slope of connecting line*/
	}

	else
	{
		slope_of_connecting_line=(class2_y-class1_y)/(class2_x-class1_x);/*Calculating slope of connecting line by using average points*/
	}

	if(slope_of_connecting_line==0)
	{	
		slope_of_connecting_line=SMALL_VALUE;/*If slope of connecting line is zero, the program uses macro value*/
	}

	slope_of_seperating_line=(-1.0)/slope_of_connecting_line;
	
	line_y=midpoint_y+(slope_of_seperating_line*(class1_x-midpoint_x));/*Finds where class 1 point is */

	if(class1_y<line_y){ /*Class 1 is down, class 2 is up*/
		up=2;
		down=1;
	}

	else if(class1_y>line_y){ /*Class 1 is up, class 2 is down*/
		up=1;
		down=2;
	}

	i=2;

	while(i==2){

		i=scanf("%lf %lf",&user_point_x,&user_point_y);/*If user enters something not expected,scanf return zero and loop is finished */

		if(i==2){

		
		line_y=midpoint_y+(slope_of_seperating_line*(user_point_x-midpoint_x));

		if(user_point_y>line_y){/*Test point is up to seperating line*/
			printf("class %d\n",up);
		}
		else if(user_point_y<line_y){/*Test point is under the seperating line*/
			printf("class %d\n",down);
		}
		}	
	}

	return 0;

}
