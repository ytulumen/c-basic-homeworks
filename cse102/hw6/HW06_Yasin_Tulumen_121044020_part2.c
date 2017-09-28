/*##########################################################*/
/*HW06_Yasin_Tulumen_121044020_part2.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on April 07,2015					*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*dosyadan okunan kelimenin buyuk ve kucuk unlu uyumuna		*/
/*uyup uymadiginin kontrol edilmesi ve sonuna cogul eki		*/
/*eklenmesi													*/
/*Inputs:													*/
/*	-dosyadan okunan kelimeler ve sesli harfler				*/
/*Outputs:													*/
/*	-buyuk ve kucuk unlu uyumuna uyma durumu				*/
/*	-kelimenin cogullastirilmis hali						*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

#include <stdio.h>
#include <string.h>
#include <wchar.h>
#define MAX 102


typedef enum
	{HARD, SOFT, JCONSONANT} major_type;
typedef enum
	{FLAT, ROUND, NCONSONANT} minor_type;
typedef enum
	{FALSE, TRUE} BOOL;

BOOL is_major_vh_word(const char* word, const char* v_hard, const char* v_soft);
major_type major(const char ch1, const char* v_hard, const char* v_soft);
BOOL is_minor_vh_word(const char* word, const char* v_flat, const char* v_round);
minor_type minor(const char ch1, const char* v_flat, const char* v_round);
major_type find_last_type(const char* word, const char* v_hard, const char* v_soft);
char* make_plural(const char* noun, char* plural_noun, const char* v_hard, const char* v_soft);


int
main()
{
	int i, j, k;
	char vowel[MAX][MAX], noun[MAX][MAX];
	char plural_noun[MAX];

	FILE *vo_file, *no_file, *pl_file;
	vo_file = fopen("Vowels.txt","r");
	no_file = fopen("Nouns.txt","r");
	pl_file = fopen("Plural.txt","w");

	/*eger dosya bulunamassa hata mesaji ve cikis yapacak*/
	if(vo_file == NULL || no_file == NULL)
	{
		printf("File error.program terminating\n");
		return -1;
	}
	/*kelimenin ve sesli harflerin uzunlugunun bulunmasi*/
	printf("Reading the nouns...\n\n");
	for(i=0 ; EOF != fscanf(no_file," %s", noun[i]) ; ++i);
	printf("Reading the vowels...\n\n");
	for(j=0 ; EOF != fscanf(vo_file," %s", vowel[j]) ; ++j);

	printf("The maintaince of the harmonies \n\n");

	printf("		Major 		Minor\n" );

	/*her kelime icin tek tek donecek*/
	for(k=0 ; k<i ; ++k)
	{
		/*kelimeyi ve buyuk-kucuk unlu uyumuna uyma durumunu kontrol edecek*/
		printf("%s 		", noun[k]);
		if(is_major_vh_word(noun[k], vowel[0], vowel[1]))
			printf("T");
		else
			printf("F");
		printf("		");
		if(is_minor_vh_word(noun[k], vowel[2], vowel[3]))
			printf("T");
		else
			printf("F");
		printf("\n");

	}
	printf("Writing the plurals of the nouns\n");
	/*kelimeleri cogul yapacak*/
	for(k=0 ; k<i-1 ; ++k)
	{
		fprintf(pl_file,"%s\n",make_plural(noun[k], plural_noun, vowel[0], vowel[1]));
	}
}
BOOL 
is_major_vh_word(const char* word, const char* v_hard, const char* v_soft)
{
	int i, j=0, k=0;
	major_type a;

	for(i=0 ; i<strlen(word) ; ++i)
	{
		/*harf harf sertlik yumusaklik kontol edilecek*/
		a=major(word[i], v_hard, v_soft);
		if(a==HARD)
			++j;
		else if(a==SOFT)
			++k;
	}
	if((k==0 && j!=0) || (j==0 && k!=0))
		return TRUE;
	else
		return FALSE;


}
major_type 
major(const char ch1, const char* v_hard, const char* v_soft)
{
	int i;
	/*iki farklı dongude sert veya yumusak unlu harflerden birine esitlik durumu kontrol edilecek*/
	for(i=0 ; i<strlen(v_hard) ; ++i)
	{
		if(v_hard[i] == ch1)
			return HARD;
	}
	for(i=0 ; i<strlen(v_soft) ; ++i)
	{
		if(v_soft[i] == ch1)
			return SOFT;
	}
	return JCONSONANT;

}
BOOL 
is_minor_vh_word(const char* word, const char* v_flat, const char* v_round)
{
	int i, j=0, k=0;
	minor_type a;

	for(i=0 ; i<strlen(word) ; ++i)
	{
		/*harf harf duzluk yuvarlaklık kontol edilecek*/
		a=minor(word[i], v_flat, v_round);
		if(a==FLAT)
			++j;
		else if(a==ROUND)
			++k;
	}
	if((k==0 && j!=0) || (j==0 && k!=0))
		return TRUE;
	else
		return FALSE;


}
minor_type 
minor(const char ch1, const char* v_flat, const char* v_round)
{
	int i;
	/*iki farklı dongude duz veya yumusak unlu harflerden birine esitlik durumu kontrol edilecek*/
	for(i=0 ; i<strlen(v_flat) ; ++i)
	{
		if(v_flat[i] == ch1)
			return FLAT;
	}
	for(i=0 ; i<strlen(v_round) ; ++i)
	{
		if(v_round[i] == ch1)
			return ROUND;
	}
	return NCONSONANT;

}
major_type
find_last_type(const char* word, const char* v_hard, const char* v_soft)
{
	int i, j;
	major_type a;
	for(i=0 ; word[i] != '\0' ; ++i);
	/*kelimenin uzunlugu bulunacak*/
	/*sonra sondan baslayarak ilk unlu harf bulunma durumunda return edilecek*/
	for(j=0 ; j<i ; --i)
	{
		a=major(word[i], v_hard, v_soft);
	
		if(a==HARD)
			return HARD;
		else if(a==SOFT)
			return SOFT;
	}
	return JCONSONANT;
}
char*
make_plural(const char* noun, char* plural_noun, const char* v_hard, const char* v_soft)
{
	major_type a;
	int i;

	for(i=0 ; noun[i] != '\0' ; ++i);
	a=find_last_type(noun, v_hard, v_soft);
	/*a'nin degerine gore yumusak ise '-ler' sert ise '-lar' eklenicek*/
	if(a==HARD)
	{
		strcpy(plural_noun, noun);
		plural_noun[i]='l';
		plural_noun[i+1]='a';
		plural_noun[i+2]='r';
		plural_noun[i+3]='\0';
	}
	else if(a==SOFT)
	{
		strcpy(plural_noun, noun);
		plural_noun[i]='l';
		plural_noun[i+1]='e';
		plural_noun[i+2]='r';
		plural_noun[i+3]='\0';
	}
	return plural_noun;
}
/*##########################################################*/
/*		End of HW06_Yasin_Tulumen_121044020_part2			*/
/*##########################################################*/
















