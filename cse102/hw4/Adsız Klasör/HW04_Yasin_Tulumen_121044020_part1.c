/*##########################################################*/
/*HW04_Yasin_Tulumen_121044020_part1.c              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on March 16,2015  				*/
/*															*/
/*Description												*/
/*__________________________________________________________*/
/*soguk savas esnasinda ucak tarafindan gonderilen			*/
/*bilginin sifrelenmesi programi							*/
/*Inputs:													*/
/*	-ucaktan gelen bilgi (PlainMessagesToSent.txt)			*/
/*Outputs:													*/
/*	-bilginin sayilarla sifrelenmis versiyonu (Encoded) 	*/
/*	-sayilarla sifrelenmis bilginin karakterlerle			*/
/*	-sifrelenmesi(Crypted)									*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/
#include <stdio.h>

#define PLAINTEXTFILE "Files/Q1/PlainMessagesToSent.txt"
#define ENCODEDFILE "Files/Q1/EncodedMessages.txt"
#define CRYPTEDFILE "Files/Q1/CryptedMessages.txt"


void 
encode_and_write_to_file(FILE *f_out_ptr, char character);
int 
encode_message(FILE *f_in_ptr, FILE *f_out_ptr);
int 
crypt_message(FILE *f_in_ptr, FILE *f_out_ptr);

int 
main(int argc, char* argv[])
{
	/*dosya acma*/
	FILE *f_plane_ptr, *f_encoded_ptr, *f_crypted_ptr;
	f_plane_ptr = fopen(PLAINTEXTFILE,"r");
	f_encoded_ptr = fopen(ENCODEDFILE,"w");

	/*eger dosya hatasi tespit edilirse program sonlandirilacak*/
	if((f_plane_ptr == NULL) || (f_encoded_ptr == NULL))
	{
		printf("File error.Program terminating!\n");
		return 0;
	}

	encode_message(f_plane_ptr, f_encoded_ptr);
	/*dosya kapama*/
	
	fclose(f_plane_ptr);
	fclose(f_encoded_ptr);

	/*dosya acma*/
	f_encoded_ptr = fopen(ENCODEDFILE,"r");
	f_crypted_ptr = fopen(CRYPTEDFILE,"w");
	/*eger dosya hatasi tespit edilirse program sonlandirilacak*/
	if((f_crypted_ptr == NULL) || (f_encoded_ptr == NULL))
	{
		printf("File error.Program terminating!\n");
		return 0;
	}
	crypt_message(f_encoded_ptr, f_crypted_ptr);

	/*dosya kapama*/
	fclose(f_crypted_ptr);
	fclose(f_encoded_ptr);

	return 0;
}
int 
encode_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	int counter = 0, get;
	char c;
	/*dosyanin sonuna gelinene kadar okuma yapilacak*/
	/*ve her okumadan sonra encode islemi gerceklestirilecek*/
	while((get=fscanf(f_in_ptr,"%c",&c)) !=EOF)
	{
		encode_and_write_to_file(f_out_ptr, c);
		counter++;
	}
	return counter;
}
void 
encode_and_write_to_file(FILE *f_out_ptr, char character)
{
	/*switch-case yapisina gore hangi harf secilirse kac defa*/
	/*'1' basilacagi secilecek*/
	
	 int i, j;
	switch (character)
	{
		case 'E':
			i=0;
			break;
		case 'I':
			i=1;
			break;
		case ' ':
			i=2;
			break;
		case 'T':
			i=3;
			break;
		case 'C':
			i=4;
			break;
		case 'N':
			i=5;
			break;
		case 'A':
			i=6;
			break;
		case 'G':
			i=7;
			break;
		case 'B':
			i=8;
			break;
		case 'Z':
			i=9;
			break;
		case 'H':
			i=10;
			break;
		case 'L':
			i=11;
			break;
		case 'U':
			i=12;
			break;
		case 'V':
			i=13;
			break;
		case 'R':
			i=14;
			break;
		case 'S':
			i=15;
			break;
		case 'Y':
			i=16;
			break;
		default:
			break;
	}
	/*harfe karsilik gelen '1' sayisi kadar bir basilacak*/
	/*ve sonra '0' basilarak encode islemi bitirilecek*/
	for(j=0 ; j<i ; j++)
		fprintf(f_out_ptr, "1");
	fprintf(f_out_ptr, "0");
}
int 
crypt_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	int counter = 0, get, var=1,
		count1=0, count2=5; /*bu degiskenler '-' yazmak icin tutuldu*/
	char one = '*', zero = '_', tre = '-';
	/*encoode edilen dosya bitene kadar okuma ve crypt yapilacak*/
	while( (var = fscanf(f_in_ptr,"%1d",&get)) != EOF)
	{
		++counter;
		++count1;
		/*okunan degerin '0' veya '1' olma durumuna gore karakter basilacak*/
		if(get == 1)
			fprintf(f_out_ptr, "%c", one);
		else if(get == 0)
			fprintf(f_out_ptr, "%c", zero);
		/*her '-' basildiginda count1 sifirlanacak ve ayni anda count2*/
		/*bir azalacak.sirayla 5-4-3.. karakter araliklari ile '-' basilacak*/
		if(count1 == count2)
		{
			fprintf(f_out_ptr, "%c", tre);
			--count2;
			count1 = 0;
			
			/*ozel durum.count2 negatif olmamasi icin*/	
			if(count2==0)
				count2 = 5;
		}
	}
	return counter;
}
/*##########################################################*/
/*		End of HW04_Yasin_Tulumen_121044020_part1.c			*/
/*##########################################################*/