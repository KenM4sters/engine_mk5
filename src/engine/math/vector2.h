#ifndef VECTOR_2
#define VECTOR_2
#define vector2_LENGTH 2
#include <stdbool.h>

//vec3 structure
typedef struct vector2{

    float x, y;

} vector2;


//vec3 creation
vector2 vector2_create(float x, float y); 
float* vector2_value_ptr(vector2 vec);

//vec3 combinations
void vector2_addv(vector2* source, vector2 add);
vector2 vector2_addition(vector2 vec1, vector2 vec2);
void vector2_subv(vector2* source, vector2 sub);
vector2 vector2_subtraction(vector2 vec1, vector2 vec2);
void vector2_multv(vector2* source, vector2 mult);
vector2 vector2_multiplication(vector2 vec1, vector2 vec2);
void vector2_divv(vector2* source, vector2 div);
vector2 vector2_division(vector2 vec1, vector2 vec2);

//scaling a single vec3 with a float value
void vector2_scale_addv(vector2* source, float k);
vector2 vector2_scale_addition(vector2 vec1, float k);
void vector2_scale_subv(vector2* source, float k);
vector2 vector2_scale_subtraction(vector2 vec1, float k);
void vector2_scale_multv(vector2* source, float k);
vector2 vector2_scale_multiplication(vector2 vec1, float k);
void vector2_scale_divv(vector2* source, float k);
vector2 vector2_scale_division(vector2 vec1, float k);

//usesful utility functions for vector geometry 
float vector2_dot(vector2 vec1, vector2 vec2);
float vector2_magnitude(vector2 vec);
void vector2_normalizev(vector2* vec);
vector2 vector2_normalize(vector2 vec);
bool vector2_is_perpendicular(vector2 vec1, vector2 vec2);
bool vector2_compare(vector2 vec1, vector2 vec2);
// vector2 vector2_cross(vector2 vec1, vector2 vec2);

//logging function to print the x,y,z values of any vec3
void vector2_log(vector2 vec);

#endif
