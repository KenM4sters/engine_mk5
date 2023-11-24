#ifndef MATRIX4
#define MATRIX4

#include <stdlib.h>
#include "vector4.h"

typedef struct matrix4 
{
    vector4 row1, row2, row3, row4;

} matrix4;


matrix4 matrix4_create(vector4 row1, vector4 row2, vector4 row3, vector4 row4);
matrix4 matrix4_identity();

float* matrix4_value_ptr(matrix4 m);
bool matrix4_compare(matrix4 m1, matrix4 m2);
matrix4 matrix4_scalar_addition(matrix4 m, float k);
matrix4 matrix4_scalar_subtraction(matrix4 m, float k);
matrix4 matrix4_scalar_multiplication(matrix4 m, float k);
matrix4 matrix4_scalar_division(matrix4 m, float k);

matrix4 matrix4_matrix_addition(matrix4 m1, matrix4 m2);
matrix4 matrix4_matrix_subtraction(matrix4 m1, matrix4 m2);
matrix4 matrix4_matrix_multiplication(matrix4 m1, matrix4 m2);
matrix4 matrix4_matrix_division(matrix4 m1, matrix4 m2);

void matrix4_scale_addv(matrix4* m, float k);
void matrix4_scale_subv(matrix4* m, float k);
void matrix4_scale_multv(matrix4* m, float k);
void matrix4_scale_divv(matrix4* m, float k);

void matrix4_matrix_addv(matrix4* m1, matrix4 m2);
void matrix4_matrix_subv(matrix4* m1, matrix4 m2);
void matrix4_matrix_multv(matrix4* m1, matrix4 m2);
void matrix4_matrix_divv(matrix4* m1, matrix4 m2);

matrix4 matrix4_model();
vector4 matrix4_get_column(matrix4 m, int index);
matrix4 matrix4_transpose(matrix4 m);

void matrix4_log(float* m);


#endif