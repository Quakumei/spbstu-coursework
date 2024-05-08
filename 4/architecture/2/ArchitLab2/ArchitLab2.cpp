#include <stdio.h>
#include <conio.h>

#include <immintrin.h>
#include <emmintrin.h> // for SSE2

int main(void) {
	//// pcmpeqb - SUM
	//char qw1[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
	//char qw2[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
	//_asm { //mmx
	//	movq mm0, qw1
	//	movq mm1, qw2
	//	pcmpeqb mm0, mm1
	//	movq qw1, mm0
	//}
	//printf("%s\n", "Summing elements of vectors qw1 + qw2 :");
	//for (int i = 0; i < 8; i++)
	//{
	//	printf("%d ", qw1[i]);
	//}
	//printf("\n");


	// addps - SUM
	float c[4] = { 1, 2, 3, 4 };
	float d[4] = { 5, 6, 7, 8 };
	_asm { //sse
		movups xmm0, c
		movups xmm1, d
		addps xmm0, xmm1
		movups c, xmm0
	}
	printf("%s\n", "Summing elements of vectors c + d :");
	for (int i = 0; i < 4; i++)
	{
		printf("%f ", c[i]);
	}

	
	double f[2] = { 16, 4 }; 
	_asm { //sse2
		movups xmm1, f
		sqrtpd xmm0, xmm1
		movups f, xmm0
	}
	printf("\n\n%s %f %s %f\n", "Square of ", f[0], "is", f[1]);
	

	char a128[16] = { 1, 18, 3, 19, 5, 21, 7, 23, 9, 25, 11, 27, 13, 29, 15, 31 };
	char b128[16] = { 17, 2, 19, 4, 21, 6, 23, 8, 25, 10, 27, 12, 29, 14, 31, 16 };
	_asm {
		movups xmm0, a128
		movups xmm1, b128
		pminub xmm0, xmm1
		movups a128, xmm0
	}

	printf("\n%s\n", "Comparing elements :");
	for (int i = 0; i < 16; i++)
	{
		printf("( %d , %d) ; ", a128[i], b128[i]);
	}
	printf("\n%s\n", "Minimum elements :");
	for (int i = 0; i < 16; i++)
	{
		printf("%d ", a128[i]);
	}


	printf("\n\n====NEW=CODE============================\n");
	

	// 1. SSE3: ADDSUBPD
	double a[2] = { 1.0, 2.0 };
	double b[2] = { 3.0, 4.0 };
	double result[2];

	__m128d xmm_a, xmm_b, xmm_res; // Declare xmm registers for vectors a and b

	xmm_a = _mm_loadu_pd(a); // Load values of a and b into xmm registers
	xmm_b = _mm_loadu_pd(b);
	xmm_res = _mm_addsub_pd(xmm_a, xmm_b); // perform the add-subtract operation

	_mm_storeu_pd(result, xmm_res);
	printf("SSE3\tADDSUBPD\ta[0]-b[0], a[1]+b[1]:\t%f, %f\n", result[0], result[1]);


	// 2. SSE2 - PADDSB - добавление с насыщением
	__m128i a_sse = _mm_set_epi8(127, 100, -50, -75, 10, -20, 127, -128, -50, 50, 0, 1, 2, 3, 4, 5);
	__m128i b_sse = _mm_set_epi8(-128, -100, 50, 75, -10, 20, -127, 127, 50, -50, 0, -1, -2, -3, -4, -5);
	__m128i result = _mm_paddsb_epi8(a, b);

	// Print the result as signed integers
	for (int i = 0; i < 16; i++) {
		printf("%d ", (int8_t)_mm_extract_epi8(result, i));
	}


	// 3. AVX: fmsub multiply and subtract two 256-bit vectors of doubles
	double e[4] = { 1.0, 2.0, 3.0, 4.0 };
	double k[4] = { 5.0, 6.0, 7.0, 8.0 };
	double t[4] = { 1.0, 2.0, 3.0, 4.0   };
	__m256d z = _mm256_fmsub_pd(
		_mm256_set_pd(e[0], e[1], e[2], e[3]),
		_mm256_set_pd(k[0], k[1], k[2], k[3]),
		_mm256_set_pd(t[0], t[1], t[2], t[3])
	);
	printf("AVX\tFMSUB\te*k-t:\t%lf %lf %lf %lf\n",
		((double*)&z)[3], ((double*)&z)[2], ((double*)&z)[1], ((double*)&z)[0]);
	
	
	
	

	_getch();
	return 0;
}