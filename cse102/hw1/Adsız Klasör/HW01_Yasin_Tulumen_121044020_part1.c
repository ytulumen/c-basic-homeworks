/*##########################################################*/
/*HW01_Yasin_Tulumen_121044020_part1.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on February 22,2015				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*tanimlanmis fog(x) ve gof(x)'in dosyadan elde edilen		*/
/*degerlere gore cozumu										*/
/*Inputs:													*/
/*	-dosyadan x degerleri									*/
/*Outputs:													*/
/*	-fog(x) ve gof(x)'in cozumu								*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/
#include <stdio.h>
#include <math.h>

/*sabit degerin tanimi*/
#define Y 8

/*fonksiyonlarin tanimlamalari*/
double gx(double x);
double fx(double x);

int 
main()
{
	/*kullanilacak degiskenlerin tanimlanmasi		*/
	int x;
	double turn, result;

	/*dosyadan okuma ve dosyaya yazma yapilmasi icin*/
	/*dosya pointerlarinin tanimlanmasi				*/
	FILE *infile1, *infile2;
	FILE *infile;
	FILE *outfile;
	infile = fopen("Variables.txt", "r");
	outfile = fopen("Results1.txt", "w");

	/*dosyadan x degerinin okunmasi*/
	fscanf(infile, "%d", &x);

	/*fog(x)'in cozumu icin once g(x)'in bulunmasi*/
	/*ardindan elde edilen degerle f(x)'in cagirilip*/
	/*fog(x)'in sonucu*/
	turn = gx(x);
	result = fx(turn);

	/*dosyaya ve konsola sonucun yazdirilmasi*/
	fprintf(outfile, "%f\n", result );
	printf("fog(x)'in sonucu: \n %f \n", result);

	/*gof(x)'in cozumu icin once f(x)'in bulunmasi*/
	/*ardindan elde edilen degerle g(x)'in cagirilip*/
	/*gof(x)'in sonucu*/
	turn = fx(x);
	result = gx(turn);

	/*dosyaya ve konsola sonucun yazdirilmasi*/
	fprintf(outfile, "%f\n", result );
	printf("gof(x)'in sonucu: \n %f \n", result);

	/*dosyalarin kapatilmasi*/
	fclose(infile);
	fclose(outfile);

	return 0;

}
double
fx(double x)
{
	double fx;

	fx = sin(pow ( ( ( x + Y ) / x ) + sqrt ( log ( pow(3.0,x) / (2.0 * x + 1.0 ) ) ) ,2.5) );
	return fx;
}
double
gx(double x)
{
	double gx;

	gx = x + ( 1.0 / ( x + ( Y / ( 2.0 * x ) ) ) );
	return gx;
}
/*##########################################################*/
/*		End of HW01_Yasin_Tulumen_121044020_part2			*/
/*##########################################################*/