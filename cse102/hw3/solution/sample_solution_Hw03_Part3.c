/*##########################################################################*/
/*                 sample_code_Hw03_part3.c                                 */
/*_________________________________                                         */
/*                  Author ; Meltem Çetiner                                 */
/*                                                                          */
/*Descriptions:                                                             */
/*___________                                                               */
/*    A program which draw a vertical diagram of a bouncing ball. We will   */
/* assume that each step of bounce the ball will lose one feet (ft). The    */
/* function will be tested by calling  three times with the different       */
/* arguments on main.                                                       */
/*									    */
/*Inputs:                                                                   */
/*  first_height   : the first height of the ball			    */
/*  feet_height    : the height of one feet				    */
/*  the_peak_point : the character used to draw the peak points of the ball */
/*  the_path_point : the character used to draw the path points of the ball */
/* 									    */
/*Outputs:                                                                  */
/*  A graphic of the bouncing ball and the number of charachter             */
/*##########################################################################*/
/*                                                                          */
/*--------------------------------------------------------------------------*/
/*                         Includes                                         */
/*--------------------------------------------------------------------------*/
#include <stdio.h>

/*--------------------------------------------------------------------------*/
/*                        Prototypes                                        */
/*--------------------------------------------------------------------------*/
int draw_diag_step( int height, int feet_height, char the_peak_point,char the_road_point);
int draw_ver_diag_of_bb(int first_height, int feet_height, char the_peak_point, char the_road_point);
int finish_diag(int length);


/*--------------------------MAIN--------------------------------------------*/
int main()
{
        int first_height,feet_height,num_char;
	char the_peak_point, the_road_point;
        int count;
        for(count=1;count<4;count++)
        {	
		printf("\n---------------    %d. Diagram  ----------\n\n",count);
		
		printf("Enter first height : ");
		scanf("%d", &first_height);

		printf("Enter feet height : ");
		scanf("%d", &feet_height);

		printf("Enter the peak point charachter : ");
		scanf(" %c", &the_peak_point);

		printf("Enter the road point charachter : ");
		scanf(" %c", &the_road_point);

		num_char = draw_ver_diag_of_bb(first_height,feet_height,the_peak_point,the_road_point);
		
		printf("\n %d charachters are used for this diagram..\n\n\n", num_char);
        }

	

	return 0;
/*--------------------------END_OF_MAIN---------------------------------------*/
}

/*----------------------------------------------------------------------------*/
/*                        Implementations                                     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*A func which draw a vertical diagram of a bouncing ball. The return value is*/
/*the total number of the character used (both peaks and path points)         */
int draw_ver_diag_of_bb(int first_height, int feet_height, char the_peak_point, char the_road_point)
{
	int height, diag_count, length;
	height=first_height;
	length=height*feet_height;
        printf("^\n");
	while ( height>=1 )            
	{
		diag_count+=draw_diag_step( height, feet_height, the_peak_point,the_road_point);
		height--;                          /*We will assume that each step of bounce the ball will lose one feet (ft).*/
	}
	finish_diag(length);
	

	return diag_count;

}

/* This function will help you for printing just each bounce step, and returns  */
/*the number of the character used as peak points and path points for each step.*/
int draw_diag_step( int height, int feet_height, char the_peak_point,char the_road_point)
{
	int step=0,
            n_char=0, /* number of used char        */
            c_road,   /* counter of the road points */
            c_space,  /* space counter              */
            space=1;  /* space                      */
            
             
	/*ascending..............*/	
	while ( step < height )
	{
		printf("l");
		for(c_space=1;c_space<space;c_space++)             /*space block*/
			printf("%c", ' '); 
		for(c_road=0;c_road<feet_height;c_road++)         /*road of the ball*/
		{
			printf("%c",the_road_point); 
			n_char++;
		}		
		printf("\n");
		space+=feet_height;
		step++;	
	}
	
	step--;/* peak point line                           */
	printf("l");
	for(c_space=1;c_space<space;c_space++)
		printf("%c", ' ') ;
	printf("%c\n",the_peak_point);
        n_char++;
	space-=feet_height;	
	
	
	/*............descending*/
	while ( step !=-1 )
	{
		step--;
		printf("l");
		for(c_space=1;c_space<space;c_space++)                 /*space block*/
			printf("%c", ' '); 
		for(c_road=0;c_road<feet_height;c_road++)
		{
			printf("%c",the_road_point);                 /*road of the ball*/	
			n_char++;		
		}
                printf("\n");
		space-=feet_height;
	}

	return n_char;
}

/*print the end of the diagram by drawing the bottom axes.  */
/*The function returns 1 if it is successful or 0 otherwise.*/
int finish_diag(int length)
{
	int i=0;
	printf("L");
	for(i=0; i<length; ++i)
		printf("_ ");
			
	printf("> \n");

	if(length)
		return 1;
	else
		return 0;

}

/*##########################################################################*/
/*                   End of sample code part3                               */
/*##########################################################################*/
