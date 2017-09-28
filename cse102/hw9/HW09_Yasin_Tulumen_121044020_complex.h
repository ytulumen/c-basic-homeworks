/*##########################################################*/
/*HW09_Yasin_Tulumen_121044020_complex.h              		*/
/*__________________________________________________________*/
/*Written by Yasin Tulumen on April 28,2015					*/
/*															*/
/*##########################################################*/
/*															*/
/*__________________________________________________________*/
/*						Includes							*/
/*__________________________________________________________*/

typedef struct {
	double real;
	double imag;
} complex_t;

int scan_complex (complex_t *c);
void print_complex (complex_t c);
complex_t add_complex (complex_t c1, complex_t c2);
complex_t subtract_complex (complex_t c1, complex_t c2);
complex_t multiply_complex (complex_t c1, complex_t c2);
complex_t divide_complex (complex_t c1, complex_t c2);
complex_t abs_complex (complex_t c);

/*##########################################################*/
/*		End of HW08_Yasin_Tulumen_121044020_complex.h		*/
/*##########################################################*/
