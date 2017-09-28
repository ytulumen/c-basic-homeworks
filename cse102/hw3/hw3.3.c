#include <stdio.h>

int draw_ver_diag_of_bb(int first_height, int feet_height, char the_peak_point, char the_road_point);
int draw_diag_step(int height, int feet_height, char the_peak_point, char the_road_point);
int finish_diag(int length);

int
main()
{
	int no;
	char sharp = '#', eks = 'x', plus = '+', star = '*', let = 'O', slash = '/' ;

	no = draw_ver_diag_of_bb(3, 3, let, star);
	printf("%d char used\n\n",no );

	no = draw_ver_diag_of_bb(5, 8, eks, plus);
	printf("%d char used\n\n",no );

	no = draw_ver_diag_of_bb(6, 1, sharp, slash);
	printf("%d char used\n\n",no );



	return 0;
}
int 
draw_ver_diag_of_bb(int first_height, int feet_height, char the_peak_point, char the_road_point)
{
	int new_height, ret = 0, total = 0, length = first_height * feet_height + 1;

	printf("^\n");
	for(new_height = 0 ; new_height < first_height ; first_height--)
	{
		ret = draw_diag_step(first_height, feet_height, the_peak_point, the_road_point);
		total += ret;
	}
	finish_diag(length);

	return total;
}
int 
draw_diag_step(int height, int feet_height, char the_peak_point, char the_road_point)
{
	int new_height, new_feet_height, space = 0, new_space, count = 0;

	for(new_height = 0 ; new_height < (height * 2 + 1) ; new_height++)
	{
		printf("|");

		for(new_space = 0 ; new_space < space ; new_space++)
		{
			printf(" ");
		}
		if(new_height < height)
		{
			space += feet_height;
			
			for(new_feet_height = 0 ; new_feet_height < feet_height ; new_feet_height++)
			{	
				printf("%c", the_road_point);
				++count;
			}
		}
		else if(new_height == height)
		{
			printf("%c", the_peak_point);
			space -= feet_height;
			++count;
		}
		
		else if(new_height > height)
		{
			space -= feet_height;
			for(new_feet_height = 0 ; new_feet_height < feet_height ; new_feet_height++)
			{
				printf("%c", the_road_point);
				++count;
			}
		}
		printf("\n");

	}
	return count;

}
int
finish_diag(int length)
{
	int count;

	printf("L");

	for(count = 0 ; count < length ; count++)
		printf("_");
	printf(">\n");
	return 1;
}




