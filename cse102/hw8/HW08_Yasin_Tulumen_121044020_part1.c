/*##########################################################*/
/*HW08_Yasin_Tulumen_121044020_part1.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on April 20,2015					*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*ps'de islenen en buyuk sayilari iceren dikdortgeni		*/
/*bulma programinin degistirilmis hali 						*/
/*Inputs:													*/
/*	-dosyadan okunan tablo									*/
/*Outputs:													*/
/*	-orijinden baslayarak elde edilen en buyuk dikdortgen	*/
/*	-ve butun tablodaki en buyuk dikdortgenin				*/
/*	-ekrana basilmasi										*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>

#define COL_COUNT 8
#define ROW_CAP 10

typedef struct 
{
	int x,y;
}Point_t;

typedef struct 
{
	Point_t left_up, right_down;
	double sum;
}Rectangle_t;

void
getArray(FILE* inFile, double table[][COL_COUNT], int* nRow);
Point_t
construct_point(int x, int y);
Rectangle_t
construct_rectangle(Point_t left_up, Point_t right_down);
void
print_rectangle(const Rectangle_t *rectangle);
void
getSum(double table[][COL_COUNT], Rectangle_t *rectangle);
Rectangle_t
maxSumConstPoint(double table[][COL_COUNT], int nRow, Point_t left_up);
Rectangle_t
maxSumRec(double table[][COL_COUNT], int nRow);


int
main()
{
	double table[ROW_CAP][COL_COUNT];
	FILE* inFile;
	int nRow;
	double maxSum;
	Rectangle_t rectangle;
	Point_t left_up, right_down;
	

	inFile=fopen("Table1.txt", "r");

	getArray(inFile, table, &nRow);
	left_up = construct_point(0, 0);
	rectangle = construct_rectangle (left_up , right_down);
	rectangle = maxSumConstPoint(table, nRow, left_up);
	printf("start from origin:\n");
	print_rectangle(&rectangle);
	rectangle=maxSumRec(table, nRow);
	printf("max sum rectangular:\n");
	print_rectangle(&rectangle);

	fclose(inFile);
	return 0;


}
void getArray(FILE* inFile, double table[][COL_COUNT], int* nRow){
	int row=0, i, j;
	int col;
	int status=EOF+1;/*Different from EOF*/

	/*one more row will be read but the values will not be recorded into the table
	therefore, it is safe to use a table having just enough capasity to hold the data*/
	while(status!=EOF){
		for(col=0; col<COL_COUNT; col++)
			status=fscanf(inFile, "%lf", &table[row][col]);
		++row;
	}

	*nRow=row-1;/*one more row read*/
}
Point_t
construct_point(int x, int y)
{
	Point_t po;
	po.x = x;
	po.y = y;

	return po;
}
Rectangle_t
construct_rectangle(Point_t left_up, Point_t right_down)
{
	Rectangle_t flag_rec;

	flag_rec.left_up = left_up;
	flag_rec.right_down = right_down;

	return flag_rec;
}
void
print_rectangle(const Rectangle_t *rectangle)
{
	printf("sum of rectangle is %.2f\n", rectangle->sum);
	printf("x start point is %d\n", rectangle->left_up.x);
	printf("y start point is %d\n", rectangle->left_up.y);
	printf("x finish point is %d\n", rectangle->right_down.x);
	printf("y finish point is %d\n", rectangle->right_down.y);
}
void
getSum(double table[][COL_COUNT], Rectangle_t *rectangle)
{
	int row, col;
	/*belirlenen araliktaki toplam sayilarin elde edilmesi icin*/
	/*sol ust koseden baslanarak sag alt koseye kadar sayilar toplanacak*/
	for(row=rectangle->left_up.y ; row<=rectangle->right_down.y; ++row)
		for(col=rectangle->left_up.x ; col<=rectangle->right_down.x; ++col)
			rectangle->sum += table[row][col];
}
Rectangle_t
maxSumConstPoint(double table[][COL_COUNT], int nRow, Point_t left_up)
{
	Rectangle_t rectangle, temp_rec;

	/*initialize the rectangular with the one including only one point*/
	rectangle.sum = table[left_up.y][left_up.x];
	rectangle.right_down.y = left_up.y;
	rectangle.right_down.x = left_up.x;
	rectangle.left_up.y = left_up.y;
	rectangle.left_up.x = left_up.x;
	temp_rec.left_up.y = left_up.y;
	temp_rec.left_up.x = left_up.x;
	

	/*Try all feasible rectangulars by changing the right down corner*/
	for(temp_rec.right_down.y=left_up.y; temp_rec.right_down.y<nRow; ++temp_rec.right_down.y)
	{
		for(temp_rec.right_down.x=left_up.x; temp_rec.right_down.x<COL_COUNT; ++temp_rec.right_down.x)
		{
			temp_rec.sum = 0;
			getSum(table, &temp_rec);
			if(temp_rec.sum > rectangle.sum)
			{
				/*a better rectangular is found, perform an update */
				rectangle.sum=temp_rec.sum;
				rectangle.right_down.y = temp_rec.right_down.y;
				rectangle.right_down.x = temp_rec.right_down.x;
			}
		}
	}

	return rectangle;
}
Rectangle_t
maxSumRec(double table[][COL_COUNT], int nRow)
{
	Rectangle_t rectangle, temp_rec;
	/*initialize the rectangular with the one including only origin point*/
	rectangle.sum = table[0][0];
	rectangle.left_up.y = rectangle.left_up.x = rectangle.right_down.y = rectangle.right_down.x = 0;

	/*For all feasible starting points call maxSumConstPoint*/
	for(temp_rec.left_up.y = 0; temp_rec.left_up.y < nRow; ++temp_rec.left_up.y)
	{
		for(temp_rec.left_up.x = 0; temp_rec.left_up.x < COL_COUNT; ++temp_rec.left_up.x)
		{
			temp_rec = maxSumConstPoint(table, nRow, temp_rec.left_up);
			if(temp_rec.sum > rectangle.sum)
			{
				/*a better rectangular found, perform an update*/
				rectangle.sum = temp_rec.sum;
				rectangle.left_up.y = temp_rec.left_up.y;
				rectangle.left_up.x = temp_rec.left_up.x;
				rectangle.right_down.y = temp_rec.right_down.y;
				rectangle.right_down.x = temp_rec.right_down.x;
			}
		}
	}
	return rectangle;
}
/*##########################################################*/
/*		End of HW08_Yasin_Tulumen_121044020_part1			*/
/*##########################################################*/