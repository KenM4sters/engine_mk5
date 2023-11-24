#ifndef VECTOR_3
#define VECTOR_3
#define VECTOR3_LENGTH 3
#include <stdbool.h>

//vec3 structure
typedef struct vector3{

    float x, y, z;

} vector3;


//vec3 creation
vector3 vector3_create(float x, float y, float z); 
float* vector3_value_ptr(vector3 vec);

//vec3 combinations
void vector3_addv(vector3* source, vector3 add);
vector3 vector3_addition(vector3 vec1, vector3 vec2);
void vector3_subv(vector3* source, vector3 sub);
vector3 vector3_subtraction(vector3 vec1, vector3 vec2);
void vector3_multv(vector3* source, vector3 mult);
vector3 vector3_multiplication(vector3 vec1, vector3 vec2);
void vector3_divv(vector3* source, vector3 div);
vector3 vector3_division(vector3 vec1, vector3 vec2);

//scaling a single vec3 with a float value
void vector3_scale_addv(vector3* source, float k);
vector3 vector3_scale_addition(vector3 vec1, float k);
void vector3_scale_subv(vector3* source, float k);
vector3 vector3_scale_subtraction(vector3 vec1, float k);
void vector3_scale_multv(vector3* source, float k);
vector3 vector3_scale_multiplication(vector3 vec1, float k);
void vector3_scale_divv(vector3* source, float k);
vector3 vector3_scale_division(vector3 vec1, float k);

//usesful utility functions for vector geometry 
float vector3_dot(vector3 vec1, vector3 vec2);
float vector3_magnitude(vector3 vec);
void vector3_normalizev(vector3* vec);
vector3 vector3_normalize(vector3 vec);
bool vector3_is_perpendicular(vector3 vec1, vector3 vec2);
bool vector3_compare(vector3 vec1, vector3 vec2);
vector3 vector3_cross(vector3 vec1, vector3 vec2);

//logging function to print the x,y,z values of any vec3
void vector3_log(vector3 vec);

#endif
