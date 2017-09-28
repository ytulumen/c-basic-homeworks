#include <stdio.h>

int draw_hor_diag_of_bb(int first_height, int feet_height, char the_peak_point, char the_road_point);
int finish_diag(int length);



int
main()
{
	int first_height=4, feet_height=3, ch_no;
	char the_peak_point='o', the_road_point='x';
	printf("%d %d %c %c\n",first_height, feet_height, the_road_point, the_peak_point );
	ch_no = draw_hor_diag_of_bb(first_height, feet_height, the_peak_point, the_road_point);

	printf("%d char used\n\n",ch_no );

	return 0;



}
int 
draw_hor_diag_of_bb(int first_height, int feet_height, char the_peak_point, char the_road_point)
{
	int space_left = first_height, space_out = first_height * 2, space_in = -1, space_in_in;
	int i, j, k=1, l, m, total=0, length=0, n = (first_height * feet_height + 1);
	int first_height_2 = first_height, ch_no=0;
	printf("^\n");

	for(i = 1 ; i <= (first_height * feet_height +1) ; ++i)
	{
		printf("|");

		
		
		if(i == 2)
		{
			--space_left;
			space_out -= 2;
			space_in += 2;
		}
		
		else if(i % feet_height == 2)
		{
			--space_left;
			space_out -= 2;
			space_in += 2;
		}	

		for(j=0 ; j<space_left ; ++j)
			printf(" ");
	
		if(i > 1)
		{
			space_in_in = space_in;
			for(j=0 ; j<k ; ++j)
			{	
				printf("%c", the_road_point);
				++ch_no;

				for(l=0 ; l<space_in_in ; ++l)
				{
					printf(" ");
				}
				space_in_in -=2;

				printf("%c", the_road_point);
				++ch_no;

				for(m=0 ; m<space_out ; ++m)
					printf(" ");
			}
			if(i > feet_height)
				if(i % feet_height == 1)
					++k;
		}
		if(i == 1)
		{
			printf("%c", the_peak_point);
			++ch_no;
		}
		
		else if((i % feet_height == 1) && (i != n))
		{	
			printf("%c", the_peak_point);
			++ch_no;
		}
		printf("\n");
	}
	while(first_height_2 > 0)
	{
		total = first_height_2 * 2 + 1; 
		length += total;
		--first_height_2;
	}
	finish_diag(length);

	return ch_no;
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








