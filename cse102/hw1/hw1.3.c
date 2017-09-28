/*##########################################################*/
/*HW01_Yasin_Tulumen_121044020_part3.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on February 18,2015				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*bir aracin yakit harcamasinin tl ve kurus olarak			*/
/*hesaplanmasi												*/
/*Inputs:													*/
/*	-dosyadan aracin numarasi, kilometrede harcadigi yakit	*/
/*	-dosyadan yakitin 1 litresinin ucreti					*/
/*	-dosyadan aracin toplam katettigi mesafe km cinsinden	*/
/*Outputs:													*/
/*	-aracin yakit icin harcadigi toplam ucretin bulunmasi	*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>

int
main()
{
	/*kullanilacak degiskenlerin tanimlanmasi		*/
	int car1, car2, car3;
	double priceOfFuel1, priceOfFuel2, priceOfFuel3;
	double takenKm1, takenKm2, takenKm3;
	double consPerKm1, consPerKm2, consPerKm3;
	double TotalFuelCosts1, TotalFuelCosts2, TotalFuelCosts3;
	double krs1, krs2, krs3;

	/*dosyadan okuma ve dosyaya yazma yapilmasi icin*/
	/*dosya pointerlarinin tanimlanmasi				*/
	FILE *infile, *outfile;
	infile = fopen("Cars.txt", "r");
	outfile = fopen("TotalFuelCosts.txt", "w");

	
	/*dosyadan okuma islemlerinin yapilmasi			*/
	fscanf(infile, "%d %lf %lf %lf", &car1, &consPerKm1, &priceOfFuel1, &takenKm1);
	fscanf(infile, "%d %lf %lf %lf", &car2, &consPerKm2, &priceOfFuel2, &takenKm2);
	fscanf(infile, "%d %lf %lf %lf", &car3, &consPerKm3, &priceOfFuel3, &takenKm3);

	/*yakit icin toplam harcanan ucretin hesaplanmasi*/
	TotalFuelCosts1 = consPerKm1 * priceOfFuel1 * takenKm1;
	TotalFuelCosts2 = consPerKm2 * priceOfFuel2 * takenKm2;
	TotalFuelCosts3 = consPerKm3 * priceOfFuel3 * takenKm3;

	/*sadece kurus cinsinde harcanan yakit ucretinin bulunmasi*/
	/*integera cast etmemizin sebebi ondalik olmayan kismi atarak*/
	/*sadece ondalik kismi elde edip bunu konsola yazdirirken*/
	/*ayrica kurus olarak yazdirabilmemiz icin*/
	krs1 = 100 * (TotalFuelCosts1 - (int)TotalFuelCosts1);
	krs2 = 100 * (TotalFuelCosts2 - (int)TotalFuelCosts2);
	krs3 = 100 * (TotalFuelCosts3 - (int)TotalFuelCosts3);



	/*elde edilen sonuclarin dosyaya ve konsola yazilmasi*/
	/*konsola yazdirmada '%.0lf' seklinde kullanmamizin amaci*/
	/*ihtiyacimiz olmayan ondalik kisimlardan kurtularak*/
	/*goze hos gelen bir goruntu elde etmek*/
	fprintf(outfile, "1 	%.2f \n", TotalFuelCosts1 );
	fprintf(outfile, "2 	%.2f \n", TotalFuelCosts2 );
	fprintf(outfile, "3 	%.2f \n", TotalFuelCosts3 );

	/*fakat %.0 seklinde kullanirken yuvarlama yapicak*/
	/*dolayisiyla integera cast edip sonra yazdiriyoruz*/
	TotalFuelCosts1 = (int)TotalFuelCosts1;
	TotalFuelCosts2 = (int)TotalFuelCosts2;
	TotalFuelCosts3 = (int)TotalFuelCosts3;

	printf("The total fuel cost of the car 1 is %.0f TL and %.0f Kurus\n", TotalFuelCosts1, krs1 );
	printf("The total fuel cost of the car 2 is %.0f TL and %.0f Kurus\n", TotalFuelCosts2, krs2 );
	printf("The total fuel cost of the car 3 is %.0f TL and %.0f Kurus\n", TotalFuelCosts3, krs3 );

	/*dosyalarin kapatilmasi*/
	fclose(infile);
	fclose(outfile);

	return 0;
}

/*##########################################################*/
/*		End of HW01_Yasin_Tulumen_121044020_part3			*/
/*##########################################################*/