/*##########################################################*/
/*HW01_Yasin_Tulumen_121044020_part2.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on February 18,2015				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*iki bilinmeyenli iki denklemin cozumu						*/
/*f(x,y) fonksiyonunun cozumu								*/
/*Inputs:													*/
/*	-dosyadan iki bilinmeyenli denklemin katsayilari		*/
/*	-dosyadan f(x,y) denkleminin katsayilari				*/
/*Outputs:													*/
/*	-x ve y'nin bulunmasi									*/
/*	-fonksiyonun bulunan x ve y degerlerine gore cozumu		*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/
#include <stdio.h>

int
main(){

	/*kullanilacak degiskenlerin tanimlanmasi		*/
	double x, y, z, x1, y1, x2, y2, z1, z2;
	char ch;
	double a, b, totalx, totalz, totaly, totalFunc;

	/*dosyadan okuma ve dosyaya yazma yapilmasi icin*/
	/*dosya pointerlarinin tanimlanmasi				*/
	FILE *infile1, *infile2;
	FILE *outfile;
	infile1 = fopen("EqCoefficients.txt", "r");
	infile2 = fopen("FuncCoefficients.txt", "r");
	outfile = fopen("Results2.txt", "w");

	
	/*dosyadan okuma islemlerinin yapilmasi			*/
	fscanf(infile1, "%lf %lf %lf", &x1, &y1, &z1 );
	fscanf(infile1, "%lf %lf %lf", &x2, &y2, &z2 );
	fscanf(infile2, "%lf %lf", &a, &b);

	/*okunan katsayilara gore x ve y'nin cozulmesi	*/
	totalx = (x1 * y2) + (x2 * ((-1.0) * y1));
	totalz = (z1 * y2) + (z2 * ((-1.0) * y1));
	x = totalz / totalx;
	y = (z1 - (x1 * x)) / y1;

	/*okunan katsayilara gore f(x,y) fonksiyonun cozulmesi*/
	totalFunc = (a * x) + (b * y);

	/*son olarak dosyaya ve konsola outputlarin yazilmasi*/
	printf("solution of equations:\n x = %.2f \n y = %.2f \n", x, y);
	printf("solution of function \n f(x,y) = %.2f \n", totalFunc);
	fprintf(outfile, "%.2f %.2f %.2f \n", x, y, totalFunc );

	/*dosyalarin kapatilmasi*/
	fclose(infile1);
	fclose(infile2);
	fclose(outfile);

	return 0;

}

/*##########################################################*/
/*		End of HW01_Yasin_Tulumen_121044020_part2			*/
/*##########################################################*/