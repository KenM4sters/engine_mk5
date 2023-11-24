#ifndef VECTOR_4
#define VECTOR_4
#define vector4_LENGTH 4
#include <stdbool.h>

//vec4 structure
typedef struct vector4{

    float x, y, z, w;

} vector4;


//vec4 creation
vector4 vector4_create(float x, float y, float z, float w); 
float* vector4_value_ptr(vector4 vec);

//vec4 combinations
void vector4_addv(vector4* source, vector4 add);
vector4 vector4_addition(vector4 vec1, vector4 vec2);
void vector4_subv(vector4* source, vector4 sub);
vector4 vector4_subtraction(vector4 vec1, vector4 vec2);
void vector4_multv(vector4* source, vector4 mult);
vector4 vector4_multiplication(vector4 vec1, vector4 vec2);
void vector4_divv(vector4* source, vector4 div);
vector4 vector4_division(vector4 vec1, vector4 vec2);

//scaling a single vec3 with a float value
void vector4_scale_addv(vector4* source, float k);
vector4 vector4_scale_addition(vector4 vec1, float k);
void vector4_scale_subv(vector4* source, float k);
vector4 vector4_scale_substraction(vector4 vec1, float k);
void vector4_scale_multv(vector4* source, float k);
vector4 vector4_scale_multiplication(vector4 vec1, float k);
void vector4_scale_divv(vector4* source, float k);
vector4 vector4_scale_division(vector4 vec1, float k);

//usesful utility functions for vector geometry 
float vector4_dot(vector4 vec1, vector4 vec2);
float vector4_magnitude(vector4 vec);
void vector4_normalizev(vector4* vec);
vector4 vector4_normalize(vector4 vec);
bool vector4_is_perpendicular(vector4 vec1, vector4 vec2);
bool vector4_compare(vector4 vec1, vector4 vec2);
// vector4 vector4_cross(vector4 vec1, vector4 vec2);

//logging function to print the x,y,z values of any vec3
void vector4_log(vector4 vec);
void vector4_ptr_log(vector4* vec);

#endif
