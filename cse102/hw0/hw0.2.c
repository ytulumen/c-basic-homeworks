/*##########################################################*/
/*HW00_Yasin_Tulumen_121044020.c              				*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on February 12,2015				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*Takes the Integral of a given 2st degree polynomial		*/
/*Inputs:													*/
/*	-Coefficients of the 2st degree polynomial				*/
/*	-Zero input value of the resulting polynomial			*/
/*Outputs:													*/
/*	-Resulting 2nd degree polynomial						*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>

int
main(){
	
	double ia0, ia1, ia2;		/*coefficients of the input poly*/
	double p0;					/*P(0) value of the resulting poly*/
	double ra0, ra1, ra2, ra3;	/*coeffients of the resulting poly*/

	/*Get the 1st degree input polynomial*/
	printf("Enter the coefficients of the polynomial (from higher to lower order)>\n");
	scanf("%lf%lf%lf",&ia2, &ia1, &ia0);

	/*Get the zero input value of the resulting poly*/
	printf("Enter P(0) value for the resulting polynomial>\n");
	scanf("%lf", &p0);

	/*Calculate the resulting poly*/
	ra3 = ia2/3;
	ra2 = ia1/2;
	ra1 = ia0;
	ra0 = p0;

	/*Output the resulting poly*/
	printf("The resulting polynomial is %5.3f x^3 %5.3f x^2 %5.3f x %5.3f.\n", ra3, ra2, ra1, ra0 );

	return 0;
}

/*##########################################################*/
/*		End of HW00_Yasin_Tulumen_121044020					*/
/*##########################################################*/
