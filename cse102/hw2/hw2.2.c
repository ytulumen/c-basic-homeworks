/*##########################################################*/
/*HW02_Yasin_Tulumen_121044020_part2.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on February 27,2015				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*kullanici tarafindan .txt dosyasindan ogrencinin ismi,	*/
/*2 vize ve final notunun okunmasi, ortalamasinin ve		*/
/*agirlikli notunun hesaplanip dosyaya ve ekrana yazilmasi	*/
/*Inputs:													*/
/*	-ogrenci adi, soyadi, iki vize ve bir final notu		*/
/*Outputs:													*/
/*	-ogrenci adi, soyadi, gpa'yi ve not ortalamasinin		*/
/*	-dosyaya ve ekrana yazilmasi							*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>

/*kullanilacak sabit degiskenlerin tanimlanmasi*/
/*midtermler icin kullanilacak constant*/
#define MIDHEI 0.3
/*finaller icin kullanilacak constant*/
#define FINHEI 0.4
/*harf notlarinin belirlenmesinde kullanilacak constantlar*/
#define AGR 85
#define BGR 70
#define CGR 65
#define DGR 40
/*max ogrenci sayisi*/
#define STU 5
/*min ve max alinabilecek notlar*/
#define	MIN 0
#define MAX 100
/*dersin agirligi*/
#define CONTR 0.15

/*ortalama notun hesaplanmasi*/
double CalculateGrade(int midterm1, int midterm2, int final);
/*elde edilen not bilgisine gore harf notunun hesaplanmasi*/
char LetGrade(double total);
/*harf notuna gore agirlikli notun hesaplanmasi*/
double gpaGrade(char letter);

int
main()
{
	char name, surname;
	int midterm1, midterm2, final, count, match;
	double total, gpa;
	char letter;

	/*dosya acma islemleri*/
	FILE *infile;
	FILE *outfile; 
	infile = fopen("Students.txt","r");
	outfile = fopen("Grades.txt","w");


	/*match degiskeninin olusturulma sebebi dosyadan dogru sekilde okuma yapip yapmadigimizi kontrol etmek*/
	match = fscanf(infile," %c%c %d %d %d", &name, &surname, &midterm1, &midterm2, &final);
	/*eger dosya bitmediyse (-1) ve 5 data okunmadiysa bu hatali input oldugu anlamina gelir*/
	/*bunun icin bu if yapisini kullanicaz*/
	if(match != 5 && match != -1)
	{
		printf("file do not have enough information\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*eger girilen inputlardan birisi max veya min notundan fazla veya eksikse hata mesaji basilacak*/
	/*program sonlandiralacak*/
	if(midterm1 < MIN || midterm2 < MIN || final < MIN || midterm1 > MAX || midterm2 > MAX || final > MAX)
	{
		printf("\nFile have unacceptable points.\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*sinav ortalamalarinin hesaplanmasi*/
	total = CalculateGrade(midterm1, midterm2, final);
	/*sinav ortalamalarina gore harf notunun hesaplanmasi*/
	letter = LetGrade(total);
	/*harf notuna gore dersin agirlik katkisinin hesaplanmasi*/
	gpa = gpaGrade(letter);

	/*dosyaya ve ekrana yazilma islemleri*/
	fprintf(outfile, "%c%c %.2f %.2f \n", name, surname, gpa, total );
	printf("%c%c isimli ogrencinin:\nGPA: %.2f\nNot ortalamasi: %.2f \n\n", name, surname, gpa, total);

	/*match degiskeninin olusturulma sebebi dosyadan dogru sekilde okuma yapip yapmadigimizi kontrol etmek*/
	match = fscanf(infile," %c%c %d %d %d", &name, &surname, &midterm1, &midterm2, &final);
	/*eger dosya bitmediyse (-1) ve 5 data okunmadiysa bu hatali input oldugu anlamina gelir*/
	/*bunun icin bu if yapisini kullanicaz*/
	if(match != 5 && match != -1)
	{
		printf("file do not have enough information\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*eger girilen inputlardan birisi max veya min notundan fazla veya eksikse hata mesaji basilacak*/
	/*program sonlandiralacak*/
	if(midterm1 < MIN || midterm2 < MIN || final < MIN || midterm1 > MAX || midterm2 > MAX || final > MAX)
	{
		printf("\nFile have unacceptable points.\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*sinav ortalamalarinin hesaplanmasi*/
	total = CalculateGrade(midterm1, midterm2, final);
	/*sinav ortalamalarina gore harf notunun hesaplanmasi*/
	letter = LetGrade(total);
	/*harf notuna gore dersin agirlik katkisinin hesaplanmasi*/
	gpa = gpaGrade(letter);

	/*dosyaya ve ekrana yazilma islemleri*/
	fprintf(outfile, "%c%c %.2f %.2f \n", name, surname, gpa, total );
	printf("%c%c isimli ogrencinin:\nGPA: %.2f\nNot ortalamasi: %.2f \n\n", name, surname, gpa, total);

	/*match degiskeninin olusturulma sebebi dosyadan dogru sekilde okuma yapip yapmadigimizi kontrol etmek*/
	match = fscanf(infile," %c%c %d %d %d", &name, &surname, &midterm1, &midterm2, &final);
	/*eger dosya bitmediyse (-1) ve 5 data okunmadiysa bu hatali input oldugu anlamina gelir*/
	/*bunun icin bu if yapisini kullanicaz*/
	if(match != 5 && match != -1)
	{
		printf("file do not have enough information\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*eger girilen inputlardan birisi max veya min notundan fazla veya eksikse hata mesaji basilacak*/
	/*program sonlandiralacak*/
	if(midterm1 < MIN || midterm2 < MIN || final < MIN || midterm1 > MAX || midterm2 > MAX || final > MAX)
	{
		printf("\nFile have unacceptable points.\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*sinav ortalamalarinin hesaplanmasi*/
	total = CalculateGrade(midterm1, midterm2, final);
	/*sinav ortalamalarina gore harf notunun hesaplanmasi*/
	letter = LetGrade(total);
	/*harf notuna gore dersin agirlik katkisinin hesaplanmasi*/
	gpa = gpaGrade(letter);

	/*dosyaya ve ekrana yazilma islemleri*/
	fprintf(outfile, "%c%c %.2f %.2f \n", name, surname, gpa, total );
	printf("%c%c isimli ogrencinin:\nGPA: %.2f\nNot ortalamasi: %.2f \n\n", name, surname, gpa, total);

	/*match degiskeninin olusturulma sebebi dosyadan dogru sekilde okuma yapip yapmadigimizi kontrol etmek*/
	match = fscanf(infile," %c%c %d %d %d", &name, &surname, &midterm1, &midterm2, &final);
	/*eger dosya bitmediyse (-1) ve 5 data okunmadiysa bu hatali input oldugu anlamina gelir*/
	/*bunun icin bu if yapisini kullanicaz*/
	if(match != 5 && match != -1)
	{
		printf("file do not have enough information\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*eger girilen inputlardan birisi max veya min notundan fazla veya eksikse hata mesaji basilacak*/
	/*program sonlandiralacak*/
	if(midterm1 < MIN || midterm2 < MIN || final < MIN || midterm1 > MAX || midterm2 > MAX || final > MAX)
	{
		printf("\nFile have unacceptable points.\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*sinav ortalamalarinin hesaplanmasi*/
	total = CalculateGrade(midterm1, midterm2, final);
	/*sinav ortalamalarina gore harf notunun hesaplanmasi*/
	letter = LetGrade(total);
	/*harf notuna gore dersin agirlik katkisinin hesaplanmasi*/
	gpa = gpaGrade(letter);

	/*dosyaya ve ekrana yazilma islemleri*/
	fprintf(outfile, "%c%c %.2f %.2f \n", name, surname, gpa, total );
	printf("%c%c isimli ogrencinin:\nGPA: %.2f\nNot ortalamasi: %.2f \n\n", name, surname, gpa, total);

	/*match degiskeninin olusturulma sebebi dosyadan dogru sekilde okuma yapip yapmadigimizi kontrol etmek*/
	match = fscanf(infile," %c%c %d %d %d", &name, &surname, &midterm1, &midterm2, &final);
	/*eger dosya bitmediyse (-1) ve 5 data okunmadiysa bu hatali input oldugu anlamina gelir*/
	/*bunun icin bu if yapisini kullanicaz*/
	if(match != 5 && match != -1)
	{
		printf("file do not have enough information\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*eger girilen inputlardan birisi max veya min notundan fazla veya eksikse hata mesaji basilacak*/
	/*program sonlandiralacak*/
	if(midterm1 < MIN || midterm2 < MIN || final < MIN || midterm1 > MAX || midterm2 > MAX || final > MAX)
	{
		printf("\nFile have unacceptable points.\n");
		printf("Please fix it and try again\n");
		printf("Program terminating !\n\n");
		return 0;
	}
	/*sinav ortalamalarinin hesaplanmasi*/
	total = CalculateGrade(midterm1, midterm2, final);
	/*sinav ortalamalarina gore harf notunun hesaplanmasi*/
	letter = LetGrade(total);
	/*harf notuna gore dersin agirlik katkisinin hesaplanmasi*/
	gpa = gpaGrade(letter);

	/*dosyaya ve ekrana yazilma islemleri*/
	fprintf(outfile, "%c%c %.2f %.2f \n", name, surname, gpa, total );
	printf("%c%c isimli ogrencinin:\nGPA: %.2f\nNot ortalamasi: %.2f \n\n", name, surname, gpa, total);

	/*dosya kapama islemleri*/
	fclose(infile);
	fclose(outfile);

	return 0;
}
double CalculateGrade(int midterm1, int midterm2, int final)
{
	double total;

	/*totala notlarin hesaplanip atilmasi islemi*/
	total = (midterm1 * MIDHEI) + (midterm2 * MIDHEI) + (final * FINHEI);
	
	return total;
}
char LetGrade(double total)
{
	char letter;

	/*total notuna gore harf notlarinin hesaplanmasi*/
	if(total >= AGR)
		letter = 'A';

	else if(total >= BGR)
		letter = 'B';

	else if(total >= CGR)
		letter = 'C';
	
	else if(total >= DGR)
		letter = 'D';
	
	else
		letter = 'F';

	return letter;
}
double gpaGrade(char letter)
{
	double gpa;

	/*harf notuna gore dersin agirlik katkisinin hesaplanmasi*/
	switch(letter)
	{
		case 'A' :
			gpa = 4 * CONTR;
			break;
		case 'B' :
			gpa = 3 * CONTR;
			break;
		case 'C' :
			gpa = 2 * CONTR;
			break;
		case 'D' :
			gpa = 1 * CONTR;
			break;
		case 'F' :
			gpa = 0 * CONTR;
			break;
   }
   return gpa;

}
/*##########################################################*/
/*		End of HW02_Yasin_Tulumen_121044020_part2			*/
/*##########################################################*/