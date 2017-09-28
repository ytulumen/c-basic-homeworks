/*##########################################################*/
/*HW07_Yasin_Tulumen_121044020_part2.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on April 14,2015					*/
/*															*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>


int
combination(int n, int k);
int
ways_rec(int n, int k);
int
ways(int n);

int
main()
{
	int n;
	scanf("%d", &n);
	ways(n);

}

int
combination(int n, int k)
{
	printf("%d n %d k\n", n, k);
	if(n==k || n==0 || k==0)
		return 1;
	else
		return (combination(n-1, k-1) + combination(n-1, k));


}

int
ways_rec(int n, int k)
{
	if(n >= k)
		return (combination(n, k) + ways_rec(n-1, k+1));
	else
		return 0;
}

int
ways(int n)
{
	printf("n=%d you can climb in %d different ways\n", n, ways_rec(n, 0));
}










