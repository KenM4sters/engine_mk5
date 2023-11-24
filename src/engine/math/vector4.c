#include "vector4.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

vector4 vector4_create(float x, float y, float z, float w) 
{
    vector4 ret;
    ret.x = x;
    ret.y = y;
    ret.z = z;
    ret.w = w;

    return ret;
}


float* vector4_value_ptr(vector4 vec) 
{
    float* ret = malloc(sizeof(float) * vector4_LENGTH);

    ret[0] = vec.x;
    ret[1] = vec.y;
    ret[2] = vec.z;
    ret[3] = vec.w;

    return ret;
}

//vec3 combinations
void vector4_addv(vector4* source, vector4 add) 
{
    source->x += add.x;
    source->y += add.y;
    source->z += add.z;
    source->w += add.w;
}

vector4 vector4_addition(vector4 vec1, vector4 vec2) 
{
    vector4 ret = vector4_create(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
    return ret;
}

void vector4_subv(vector4* source, vector4 sub)
{
    source->x -= sub.x;
    source->y -= sub.y;
    source->z -= sub.z;
    source->w -= sub.w;
}

vector4 vector4_subtraction(vector4 vec1, vector4 vec2)
{
    vector4 ret = vector4_create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
    return ret;
}

void vector4_multv(vector4* source, vector4 mult)
{
    source->x *= mult.x;
    source->y *= mult.y;
    source->z *= mult.z;
    source->w *= mult.w;
}

vector4 vector4_multiplication(vector4 vec1, vector4 vec2)
{
    vector4 ret = vector4_create(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
    return ret;
}

void vector4_divv(vector4* source, vector4 div)
{
    source->x /= div.x;
    source->y /= div.y;
    source->z /= div.z;
    source->w /= div.w;
}

vector4 vector4_division(vector4 vec1, vector4 vec2)
{
    vector4 ret = vector4_create(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
    return ret;  
}

//vec3 scalars
void vector4_scale_addv(vector4* source, float k)
{
    source->x += k;
    source->y += k;
    source->z += k;
    source->w += k;
}

vector4 vector4_scale_addition(vector4 vec, float k)
{
    vector4 ret = vector4_create(vec.x + k, vec.y + k, vec.z + k, vec.w + k);
    return ret;
}

void vector4_scale_subv(vector4* source, float k)
{
    source->x -= k;
    source->y -= k;
    source->z -= k;
    source->w -= k;
}

vector4 vector4_scale_subtraction(vector4 vec, float k)
{
    vector4 ret = vector4_create(vec.x - k, vec.y - k, vec.z - k, vec.w - k);
    return ret;
}

void vector4_scale_multv(vector4* source, float k)
{
    source->x *= k;
    source->y *= k;
    source->z *= k;
    source->w *= k;
}

vector4 vector4_scale_multiplication(vector4 vec, float k)
{
    vector4 ret = vector4_create(vec.x * k, vec.y * k, vec.z * k, vec.w * k);
    return ret;
}

void vector4_scale_divv(vector4* source, float k)
{
    source->x /= k;
    source->y /= k;
    source->z /= k;
    source->w /= k;
}

vector4 vector4_scale_division(vector4 vec, float k)
{
    vector4 ret = vector4_create(vec.x / k, vec.y / k, vec.z / k, vec.w / k);
    return ret;
}

float vector4_dot(vector4 vec1, vector4 vec2) 
{
    float ret = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z) + (vec1.w * vec2.w);
    return ret;
}

float vector4_magnitude(vector4 vec) 
{  
    float ret = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z) + (vec.w * vec.w));
    return ret;
}

void vector4_normalizev(vector4* vec) 
{
    float magnitude = vector4_magnitude(*vec);
    vec->x /= magnitude;
    vec->y /= magnitude;
    vec->z /= magnitude;
    vec->w /= magnitude;

}

vector4 vector4_normalize(vector4 vec) 
{
    float magnitude = vector4_magnitude(vec);
    vector4 ret;

    ret.x = vec.x / magnitude;
    ret.y = vec.y / magnitude;
    ret.z = vec.z / magnitude;
    ret.w = vec.w / magnitude;

    return ret;

}

bool vector4_is_perpendicular(vector4 vec1, vector4 vec2) 
{
    return vector4_dot(vec1, vec2) == 0;
}

bool vector4_compare(vector4 vec1, vector4 vec2) 
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z && vec1.w == vec2.w;
}

// Cannot get the cross product of vectors outside of 3 and 7 dimensions
// vector4 vector4_cross(vector4 vec1, vector4 vec2) 
// {
//     vector4 ret = vector4_create(1.0f, 1.0f, 1.0f);
    
//     ret.x = ((vec1.y * vec2.z) - (vec1.z * vec2.y));
//     ret.y = ((vec1.z * vec2.x) - (vec1.x * vec2.z));
//     ret.z = ((vec1.x * vec2.y) - (vec1.y * vec2.x));

//     return ret;
    
// }

void vector4_log(vector4 vec) 
{
    printf("\n x: %4f y: %4f z: %4f w: %4f \n", vec.x, vec.y, vec.z, vec.w);
}

void vector4_ptr_log(vector4* vec) 
{
    printf("\n x: %4f y: %4f z: %4f w: %4f \n", vec->x, vec->y, vec->z, vec->w);
}
