#include "matrix4.h"
#include <stdlib.h>
#include <stdio.h>


matrix4 matrix4_create(vector4 row1, vector4 row2, vector4 row3, vector4 row4) 
{
    matrix4 ret;

    ret.row1 = row1;
    ret.row2 = row2;
    ret.row3 = row3;
    ret.row4 = row4;

    return ret;
}

matrix4 matrix4_identity() 
{
    matrix4 ret;

    ret.row1 = vector4_create(1.0f, 0.0f, 0.0f, 0.0f);
    ret.row2 = vector4_create(0.0f, 1.0f, 0.0f, 0.0f);
    ret.row3 = vector4_create(0.0f, 0.0f, 1.0f, 0.0f);
    ret.row4 = vector4_create(0.0f, 0.0f, 0.0f, 1.0f);

    return ret;
}

float* matrix4_value_ptr(matrix4 m) 
{
    float* ret = malloc(sizeof(matrix4));

    for(int i = 0; i < vector4_LENGTH; i++ ) 
    {
        ret[i] = vector4_value_ptr(m.row1)[i];
    }
    for(int i = 0; i < vector4_LENGTH; i++ ) 
    {
        ret[i + 4] = vector4_value_ptr(m.row2)[i];
    }
    for(int i = 0; i < vector4_LENGTH; i++ ) 
    {
        ret[i + 8] = vector4_value_ptr(m.row3)[i];
    }
    for(int i = 0; i < vector4_LENGTH; i++ ) 
    {
        ret[i + 12] = vector4_value_ptr(m.row4)[i];
    }

    return ret;
}

bool matrix4_compare(matrix4 m1, matrix4 m2) 
{
    return vector4_compare(m1.row1, m2.row1) &&
           vector4_compare(m1.row2, m2.row2) &&
           vector4_compare(m1.row3, m2.row3) &&
           vector4_compare(m1.row4, m2.row4);
}

matrix4 matrix4_scalar_addition(matrix4 m, float k) 
{
    matrix4 ret = matrix4_create(m.row1, m.row2, m.row3, m.row4);
    
    vector4_scale_addv(&ret.row1, k);
    vector4_scale_addv(&ret.row2, k);
    vector4_scale_addv(&ret.row3, k);
    vector4_scale_addv(&ret.row4, k);

    return ret;
}

matrix4 matrix4_scalar_subtraction(matrix4 m, float k) 
{
    matrix4 ret = matrix4_create(m.row1, m.row2, m.row3, m.row4);
    
    vector4_scale_subv(&ret.row1, k);
    vector4_scale_subv(&ret.row2, k);
    vector4_scale_subv(&ret.row3, k);
    vector4_scale_subv(&ret.row4, k);

    return ret;
}

matrix4 matrix4_scalar_multiplication(matrix4 m, float k) 
{
    matrix4 ret = matrix4_create(m.row1, m.row2, m.row3, m.row4);
    
    vector4_scale_multv(&ret.row1, k);
    vector4_scale_multv(&ret.row2, k);
    vector4_scale_multv(&ret.row3, k);
    vector4_scale_multv(&ret.row4, k);

    return ret;
}

matrix4 matrix4_scalar_division(matrix4 m, float k) 
{
    matrix4 ret = matrix4_create(m.row1, m.row2, m.row3, m.row4);
    
    vector4_scale_divv(&ret.row1, k);
    vector4_scale_divv(&ret.row2, k);
    vector4_scale_divv(&ret.row3, k);
    vector4_scale_divv(&ret.row4, k);

    return ret;
}

void matrix4_scale_addv(matrix4* m, float k) 
{
   vector4_scale_addv(&m->row1, k);
   vector4_scale_addv(&m->row2, k);
   vector4_scale_addv(&m->row3, k);
   vector4_scale_addv(&m->row4, k);
}

void matrix4_scale_subv(matrix4* m, float k) 
{
   vector4_scale_subv(&m->row1, k);
   vector4_scale_subv(&m->row2, k);
   vector4_scale_subv(&m->row3, k);
   vector4_scale_subv(&m->row4, k);
}

void matrix4_scale_multv(matrix4* m, float k) 
{
   vector4_scale_multv(&m->row1, k);
   vector4_scale_multv(&m->row2, k);
   vector4_scale_multv(&m->row3, k);
   vector4_scale_multv(&m->row4, k);
}

void matrix4_scale_divv(matrix4* m, float k) 
{
   vector4_scale_divv(&m->row1, k);
   vector4_scale_divv(&m->row2, k);
   vector4_scale_divv(&m->row3, k);
   vector4_scale_divv(&m->row4, k);
}

matrix4 matrix4_matrix_addition(matrix4 m1, matrix4 m2) 
{
    matrix4 ret = matrix4_create(m1.row1, m1.row2, m1.row3, m1.row4);

    vector4_addv(&ret.row1, m2.row1);
    vector4_addv(&ret.row2, m2.row2);
    vector4_addv(&ret.row3, m2.row3);
    vector4_addv(&ret.row4, m2.row4);

    return ret;
}

matrix4 matrix4_matrix_subtraction(matrix4 m1, matrix4 m2) 
{
    matrix4 ret = matrix4_create(m1.row1, m1.row2, m1.row3, m1.row4);

    vector4_subv(&ret.row1, m2.row1);
    vector4_subv(&ret.row2, m2.row2);
    vector4_subv(&ret.row3, m2.row3);
    vector4_subv(&ret.row4, m2.row4);

    return ret;
}

matrix4 matrix4_matrix_multiplication(matrix4 m1, matrix4 m2) 
{
    matrix4 ret = matrix4_create(m1.row1, m1.row2, m1.row3, m1.row4);

    vector4_multv(&ret.row1, m2.row1);
    vector4_multv(&ret.row2, m2.row2);
    vector4_multv(&ret.row3, m2.row3);
    vector4_multv(&ret.row4, m2.row4);

    return ret;
}

matrix4 matrix4_matrix_division(matrix4 m1, matrix4 m2) 
{
    matrix4 ret = matrix4_create(m1.row1, m1.row2, m1.row3, m1.row4);

    vector4_divv(&ret.row1, m2.row1);
    vector4_divv(&ret.row2, m2.row2);
    vector4_divv(&ret.row3, m2.row3);
    vector4_divv(&ret.row4, m2.row4);

    return ret;
}

void matrix4_matrix_addv(matrix4* m1, matrix4 m2) 
{
   vector4_addv(&m1->row1, m2.row1);
   vector4_addv(&m1->row2, m2.row2);
   vector4_addv(&m1->row3, m2.row3);
   vector4_addv(&m1->row4, m2.row4);
}

void matrix4_matrix_subv(matrix4* m1, matrix4 m2) 
{
   vector4_subv(&m1->row1, m2.row1);
   vector4_subv(&m1->row2, m2.row2);
   vector4_subv(&m1->row3, m2.row3);
   vector4_subv(&m1->row4, m2.row4);
}

void matrix4_matrix_multv(matrix4* m1, matrix4 m2) 
{
   vector4_multv(&m1->row1, m2.row1);
   vector4_multv(&m1->row2, m2.row2);
   vector4_multv(&m1->row3, m2.row3);
   vector4_multv(&m1->row4, m2.row4);
}

void matrix4_matrix_divv(matrix4* m1, matrix4 m2) 
{
   vector4_divv(&m1->row1, m2.row1);
   vector4_divv(&m1->row2, m2.row2);
   vector4_divv(&m1->row3, m2.row3);
   vector4_divv(&m1->row4, m2.row4);
}

matrix4 matrix4_model()
{
    matrix4 ret;

    ret.row1 = vector4_create(0.00125f, 0.0f, 0.0f, 0.0f);
    ret.row2 = vector4_create(0.00167f, 0.0f, 0.0f, 0.0f);
    ret.row3 = vector4_create(0.0f, 0.0f, 0.0f, 0.0f);
    ret.row4 = vector4_create(0.0f, 0.0f, 0.0f, 0.0f);

    return ret;
    
}

vector4 matrix4_get_column(matrix4 m, int index) 
{
    float* matrix_values = matrix4_value_ptr(m);

    int x_index =  0 + index;
    int y_index = 4 + index;
    int z_index = 8 + index;
    int w_index = 12 + index;

    vector4 ret = vector4_create(matrix_values[x_index], matrix_values[y_index], 
                                matrix_values[z_index], matrix_values[w_index]);
    free(matrix_values);

    return ret;
}

matrix4 matrix4_transpose(matrix4 m) 
{
    matrix4 ret;
    ret.row1 = matrix4_get_column(m, 0);
    ret.row2 = matrix4_get_column(m, 1);
    ret.row3 = matrix4_get_column(m, 2);
    ret.row4 = matrix4_get_column(m, 3);

    return ret;

}


void matrix4_log(float* m) 
{
    for(int i = 0; i < sizeof(matrix4)/sizeof(float); i++) 
    {
        printf(" %4f ", m[i]);
        i == 3 || i == 7 || i == 11 || i == 15 ? printf("\n\n") : printf("|");
    }
}
