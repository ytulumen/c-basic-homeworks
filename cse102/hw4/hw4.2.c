/*##########################################################*/
/*HW04_Yasin_Tulumen_121044020_part2.c              		*/
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

#define PLAINTEXTFILE "Files/Q2/ReceivedMessage.txt"
#define ENCODEDFILE "Files/Q2/EncodedInput.txt"
#define CRYPTEDINPUT "Files/Q2/CryptedInput.txt"

void 
decode_and_write_to_file(FILE *f_out_ptr, int number_of_ones);

int 
decode_message(FILE *f_in_ptr, FILE *f_out_ptr);

int 
decrypt_message(FILE *f_in_ptr, FILE *f_out_ptr);

int 
main(int argc, char* argv[])
{
	FILE *f_plane_ptr, *f_encoded_ptr, *f_crypted_ptr;

	/*dosya acma*/
	f_crypted_ptr = fopen(CRYPTEDINPUT, "r");
	f_encoded_ptr = fopen(ENCODEDFILE, "w");

	/*eger dosya hatasi tespit edilirse program sonlandirilacak*/
	if((f_crypted_ptr == NULL) || (f_encoded_ptr == NULL))
	{
		printf("File error.Program terminating!\n");
		return 0;
	}
	decrypt_message(f_crypted_ptr, f_encoded_ptr);

	/*dosya kapama*/
	fclose(f_crypted_ptr);
	fclose(f_encoded_ptr);

	/*dosya acma*/
	f_encoded_ptr = fopen(ENCODEDFILE, "r");
	f_plane_ptr = fopen(PLAINTEXTFILE, "w");

	/*eger dosya hatasi tespit edilirse program sonlandirilacak*/
	if((f_plane_ptr == NULL) || (f_encoded_ptr == NULL))
	{
		printf("File error.Program terminating!\n");
		return 0;
	}
	decode_message(f_encoded_ptr, f_plane_ptr);

	/*dosya kapama*/
	fclose(f_encoded_ptr);
	fclose(f_plane_ptr);

	return 0;
}
int 
decrypt_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	int counter = 0, get;
	char c;
	while((get=fscanf(f_in_ptr,"%c",&c)) !=EOF)
	{
		if(c == '*')
			fprintf(f_out_ptr,"1");
		else if(c == '_')
			fprintf(f_out_ptr, "0");
		counter++;
	}
	return counter;
}
int 
decode_message(FILE *f_in_ptr, FILE *f_out_ptr)
{
	int counter = 0, get, i=0;
	char numb;
	
	/*dosyanin sonuna gelinene kadar okuma yapilacak*/
	/*ve her okumadan sonra decode islemi gerceklestirilecek*/
	/*i degiskeni kac tane bir tutuldugunu sayicak*/
	while((get = fscanf(f_in_ptr,"%c",&numb)) != EOF)
	{
		if(numb == '1')
			++i;
		else
		{
			decode_and_write_to_file(f_out_ptr, i);
			i=0;
		}	
	}
	return counter;
}
void 
decode_and_write_to_file(FILE *f_out_ptr, int number_of_ones)
{
	/*'1' adedi hangi harfe tekabul ediyorsa o harf dosyaya yazilacak*/
	switch (number_of_ones)
	{
		case 0:
			fprintf(f_out_ptr,"E");;
			break;
		case 1:
			fprintf(f_out_ptr,"I");
			break;
		case 2:
			fprintf(f_out_ptr," ");
			break;
		case 3:
			fprintf(f_out_ptr,"T");
			break;
		case 4:
			fprintf(f_out_ptr,"C");
			break;
		case 5:
			fprintf(f_out_ptr,"N");
			break;
		case 6:
			fprintf(f_out_ptr,"A");
			break;
		case 7:
			fprintf(f_out_ptr,"G");
			break;
		case 8:
			fprintf(f_out_ptr,"B");
			break;
		case 9:
			fprintf(f_out_ptr,"Z");
			break;
		case 10:
			fprintf(f_out_ptr,"H");
			break;
		case 11:
			fprintf(f_out_ptr,"L");
			break;
		case 12:
			fprintf(f_out_ptr,"U");
			break;
		case 13:
			fprintf(f_out_ptr,"V");
			break;
		case 14:
			fprintf(f_out_ptr,"R");
			break;
		case 15:
			fprintf(f_out_ptr,"S");
			break;
		case 16:
			fprintf(f_out_ptr,"Y");
			break;
		default:
			break;
	}
	
}
/*##########################################################*/
/*		End of HW04_Yasin_Tulumen_121044020_part2.c			*/
/*##########################################################*/