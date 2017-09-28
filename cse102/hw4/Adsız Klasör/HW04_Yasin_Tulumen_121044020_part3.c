/*##########################################################*/
/*HW04_Yasin_Tulumen_121044020_part3.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on March 16,2015  				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*soguk savas esnasinda ucaga gonderilecek bilginin			*/
/*sifresinin cozulmesi programi								*/
/*Inputs:													*/
/*	-crypted dosya (CryptedInput.txt)						*/
/*Outputs:													*/
/*	-bilginin sayilarla sifrelenmis versiyonu (Encoded) 	*/
/*	-sayilarla sifrelenmis bilginin yaziya dokulmesi		*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/
#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define CHARACTERFILE "Files/Q3/CharacterList.txt"
#define SAMPLEFILE "Files/Q3/Sample.txt"
#define ENCODEDFILE "Files/Q3/XUniversityEncoded.txt"
#define PLAINTEXTFILE "Files/Q3/XUniversityMessage.txt"

void 
swap_int(int *a, int *b);
void 
swap_char(char *a, char *b);
void
sort(char *a, int a_num, char *b, int b_num, char *c, int c_num);
int 
is_letter(char c);
int 
read_character_list(FILE* f_in_ptr, char *c1, char *c2, char *c3);
void 
count_letters(FILE *f_in_ptr, char *c1, char *c2, char *c3);
void 
decode(FILE *f_in_ptr, FILE *f_out_ptr, char c1, char c2, char c3);

int 
main(int argc, char* argv[])
{
	FILE *f_character_list_ptr, *f_sample_file_ptr, *f_encoded_ptr,
		*f_plain_text_ptr;
	int character_number;
	char c1, c2, c3;

	/*dosya acma*/
	f_character_list_ptr = fopen(CHARACTERFILE,"r");
	f_sample_file_ptr = fopen(SAMPLEFILE, "r");
	f_encoded_ptr = fopen(ENCODEDFILE, "r");
	f_plain_text_ptr = fopen(PLAINTEXTFILE, "w");
	/*eger dosya hatasi tespit edilirse program sonlandirilacak*/
	if(f_character_list_ptr == NULL)
	{
		printf("File error.Program terminating!\n");
		return 0;
	}
	character_number = read_character_list(f_character_list_ptr, &c1, &c2, &c3);
	/*eger dosya hatasi tespit edilirse program sonlandirilacak*/
	if(character_number < 3)
	{
		printf("insufficient input.Program terminating !\n");
		return 0;
	}
	/*dosya kapama*/
	fclose(f_character_list_ptr);
	/*eger dosya hatasi tespit edilirse program sonlandirilacak*/
	if(f_sample_file_ptr == NULL)
	{
		printf("File error.Program terminating!\n");
		return 0;
	}

	count_letters(f_sample_file_ptr, &c1, &c2, &c3);

	/*dosya kapama*/
	fclose(f_sample_file_ptr);
	/*eger dosya hatasi tespit edilirse program sonlandirilacak*/
	if(f_encoded_ptr == NULL)
	{
		printf("File error.Program terminating!\n");
		return 0;
	}
	/*eger dosya hatasi tespit edilirse program sonlandirilacak*/
	if(f_plain_text_ptr == NULL)
	{
		printf("File error.Program terminating!\n");
		return 0;
	}
	decode(f_encoded_ptr, f_plain_text_ptr, c1, c2, c3);
	/*dosya kapama*/
	fclose(f_encoded_ptr);
	fclose(f_plain_text_ptr);
	return 0;
}

void 
swap_int(int *a, int *b)
{
	int temp;

	/*a ve b'nin yerini degistirme*/
	temp = *a;
	*a = *b;
	*b = temp;
}
void 
swap_char(char *a, char *b)
{
	char c;

	/*a ve b'nin yerini degistirme*/
	c = *a;
	*a = *b;
	*b = c;
}
void
sort(char *a, int a_num, char *b, int b_num, char *c, int c_num)
{
	/*her uc durumu da kontrol ederek dogru siralamayi elde ediyoruz*/
	if(a_num < b_num)
	{
		swap_int(&a_num, &b_num);
		swap_char(a, b);
	}
	if(a_num < c_num)
	{
		swap_int(&a_num, &c_num);
		swap_char(a, c);
	}
	if(b_num < c_num)
	{
		swap_int(&b_num, &c_num);
		swap_char(b, c);
	}
}
int 
is_letter(char c)
{
	/*eger buyuk harf ise 'TRUE' return edilecek*/
	if(c > 64 && c < 91)
		return TRUE;
	return FALSE;
}
int 
read_character_list(FILE* f_in_ptr, char *c1, char *c2, char *c3)
{	
	int counter = 0, get;

	/*ilk karakter icin dosya bitene kadar veya counter artana kadar*/
	/*okuma yapilacak*/
	while(counter != 1 && (fscanf(f_in_ptr," %c", c1) != EOF))
	{
		if(is_letter(*c1)== TRUE)
			++counter;
	}	
	/*ikinci karakter icin dosya bitene kadar veya counter artana kadar*/
	/*okuma yapilacak*/
	while(counter != 2 && (fscanf(f_in_ptr," %c", c2) != EOF))
	{
		if(is_letter(*c2)== TRUE)
			++counter;
	}
	/*ucuncu karakter icin dosya bitene kadar veya counter artana kadar*/
	/*okuma yapilacak*/
	while(counter != 3 && (fscanf(f_in_ptr," %c", c3) != EOF))
	{
		if(is_letter(*c3)== TRUE)
			++counter;
	}
	return counter;
}
void 
count_letters(FILE *f_in_ptr, char *c1, char *c2, char *c3)
{
	 int a_num = 0, b_num = 0, c_num = 0;
	 char ch;

	 /*dosyadan okuma islemleri yapilirken hangi karakterden*/
	 /*kac tane oldugu tespit edilecek*/
	 while(fscanf(f_in_ptr," %c", &ch) != EOF)
	 {
	 	if(ch == *c1)
	 		++a_num;
	 	else if(ch == *c2)
	 		++b_num;
	 	else if(ch == *c3)
	 		++c_num;
	 }
	 /*daha sonra bunlar siralamaya gonderilecek*/
	 sort(c1, a_num, c2, b_num, c3, c_num);
}
void 
decode(FILE *f_in_ptr, FILE *f_out_ptr, char c1, char c2, char c3)
{
	int count_one, get=1;
	char ch;
	/*dosya bitene kadar okuma islemi yapilacak*/
	while(fscanf(f_in_ptr, "%c", &ch) != EOF)
	{
		/*eger okunan karakter '1' ise ya c2 ya da c3 basilacak*/
		if(ch == '1')
		{
			/*tekrar input alinacak ve yine '1' ise c3 basilacak (110)*/
			fscanf(f_in_ptr, "%c", &ch);
			
			if(ch == '1')
			{
				fprintf(f_out_ptr, "%c", c3);
				/*buradaki fscanf'in amaci iki defa '1' okuduktan sonra*/
				/*okunmasi gereken '0'i okumak icin*/
				fscanf(f_in_ptr, "%c", &ch);
			}
			/*'0' c2 basilacak. (10)*/
			else
				fprintf(f_out_ptr, "%c", c2);	
		}
		/*okunan karakter '1' degilse '0' demektir.c1 basilacak*/
		else
			fprintf(f_out_ptr, "%c", c1);
	}
}
/*##########################################################*/
/*		End of HW04_Yasin_Tulumen_121044020_part3.c			*/
/*##########################################################*/