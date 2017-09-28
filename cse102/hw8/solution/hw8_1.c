/*##########################################################################*/
/*                                                                          */
/* HW08_1.c                                                                 */
/* ---------                                                                */
/* Created on 06/05/2015 by Evren Cifci                                     */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*    Sample solution for part1 of hw8                                      */
/*    Solves the max rectangular sum problem with brute-force approach      */
/*                                                                          */
/* Inputs                                                                   */
/* ------                                                                   */
/* Table1.txt: Text file holding the table                                  */
/*                                                                          */
/* Outputs                                                                  */
/* -------                                                                  */
/* Terminal output: Solution                                                */
/*                                                                          */
/* Notes                                                                    */
/* -----                                                                    */
/*##########################################################################*/

#include <stdio.h>


#define COL_COUNT 8
#define ROW_CAP 10

/*Holds the coordinates of a point on the table*/
typedef struct{
    int x;  /*x-coordinate of the point*/
    int y;  /*y-coordinate of the point*/
} Point_t;

/*Defines a rectangle on the table*/
typedef struct{
    Point_t left_up;    /*left up corner*/
    Point_t right_down; /*right down corner*/
    double sum;         /*rectangular sum*/
} Rectangle_t;


Point_t construct_point(int x, int y);
Rectangle_t construct_rectangle(Point_t left_up, Point_t right_down);
void print_rectangle(const Rectangle_t *rectangle);
void getArray(FILE* inFile, double table[][COL_COUNT], int* nRow);
void getSum(double table[][COL_COUNT], Rectangle_t *rectangle);
Rectangle_t maxSumConstPoint(double table[][COL_COUNT], int nRow, Point_t left_up);
Rectangle_t maxSumRec(double table[][COL_COUNT], int nRow);

int main() {

    double table[ROW_CAP][COL_COUNT];
    FILE* inFile;
    int nRow;
    Rectangle_t max_rec;
    const Point_t ORIGIN = construct_point(0, 0);

    inFile=fopen("Table1.txt", "r");
    getArray(inFile, table, &nRow);

    max_rec = maxSumConstPoint(table, nRow, ORIGIN);
    printf("Max Rectangular starting from origin:\n");
    print_rectangle(&max_rec);

    max_rec=maxSumRec(table, nRow);
    printf("\nMaxSum Rectangular:\n");
    print_rectangle(&max_rec);

    fclose(inFile);
    return 0;
}


Point_t construct_point(int x, int y){
    Point_t p;
    
    p.x = x;
    p.y = y;
    
    return p;
}

Rectangle_t construct_rectangle(Point_t left_up, Point_t right_down){
    Rectangle_t r;
    
    r.left_up = left_up;
    r.right_down = right_down;
    
    return r;
}

void print_point(const Point_t* p){
    printf("y:%d\t x:%d\n", p->y, p->x);
}

void print_rectangle(const Rectangle_t *rectangle){
    printf("Left-up point: ");
    print_point(&rectangle->left_up);
    printf("Right-down point: ");
    print_point(&rectangle->right_down);
    printf("Rectangular sum:%f\n", rectangle->sum);
}

/*Reads the table from a file into a 2D array*/
void getArray(FILE* inFile, double table[][COL_COUNT], int* nRow){
	int row=0;
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

void getSum(double table[][COL_COUNT], Rectangle_t *rectangle){
    int row, col;
    double sum=0;

    for(row=rectangle->left_up.y; row<=rectangle->right_down.y; ++row)
            for(col=rectangle->left_up.x; col<=rectangle->right_down.x; ++col)
                    sum+=table[row][col];

    rectangle->sum = sum;
}


Rectangle_t maxSumConstPoint(double table[][COL_COUNT], int nRow, Point_t left_up){
    Rectangle_t rec_try;    /*rectangle to be tested for best*/
    
    /*rectangle to be returned: initialize it to represent 1 point only*/
    Rectangle_t rec_best_so_far = construct_rectangle(left_up, left_up);    
    getSum(table, &rec_best_so_far);
    
    /*Try all feasible rectangles by changing the right down corner*/
    rec_try.left_up = left_up;
    for(rec_try.right_down.y=left_up.y; rec_try.right_down.y<nRow; ++rec_try.right_down.y){
        for(rec_try.right_down.x=left_up.x; rec_try.right_down.x<COL_COUNT; ++rec_try.right_down.x){
            getSum(table, &rec_try);
            if(rec_try.sum > rec_best_so_far.sum)
                /*a better rectangular is found, perform an update */
                rec_best_so_far = rec_try;
        }
    }
    
    return rec_best_so_far;
}


Rectangle_t maxSumRec(double table[][COL_COUNT], int nRow){
    Point_t left_up;
    Rectangle_t rec_try;    /*rectangle to be tested for best*/
    /*rectangle to be returned: initialize with origin only*/
    Rectangle_t rec_best_so_far={{0, 0}, {0, 0}, table[0][0]};  
    
    for(left_up.y=0; left_up.y<nRow; ++left_up.y)
        for(left_up.x=0; left_up.x<COL_COUNT; ++left_up.x){
            rec_try = maxSumConstPoint(table, nRow, left_up);
            if(rec_try.sum > rec_best_so_far.sum)
                /*a better rectangular is found, perform an update */
                rec_best_so_far = rec_try;
        }
    
    return rec_best_so_far;
}
