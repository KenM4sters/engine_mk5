#include "vector3.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

vector3 vector3_create(float x, float y, float z) 
{
    vector3 ret;
    ret.x = x;
    ret.y = y;
    ret.z = z;

    return ret;
}


float* vector3_value_ptr(vector3 vec) 
{
    float* ret = malloc(sizeof(float) * VECTOR3_LENGTH);

    ret[0] = vec.x;
    ret[1] = vec.y;
    ret[2] = vec.z;

    return ret;
}

//vec3 combinations
void vector3_addv(vector3* source, vector3 add) 
{
    source->x += add.x;
    source->y += add.y;
    source->z += add.z;
}

vector3 vector3_addition(vector3 vec1, vector3 vec2) 
{
    vector3 ret = vector3_create(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
    return ret;
}

void vector3_subv(vector3* source, vector3 sub)
{
    source->x -= sub.x;
    source->y -= sub.y;
    source->z -= sub.z;
}

vector3 vector3_subtraction(vector3 vec1, vector3 vec2)
{
    vector3 ret = vector3_create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
    return ret;
}

void vector3_multv(vector3* source, vector3 mult)
{
    source->x *= mult.x;
    source->y *= mult.y;
    source->z *= mult.z;
}

vector3 vector3_multiplication(vector3 vec1, vector3 vec2)
{
    vector3 ret = vector3_create(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
    return ret;
}

void vector3_divv(vector3* source, vector3 div)
{
    source->x /= div.x;
    source->y /= div.y;
    source->z /= div.z;
}

vector3 vector3_division(vector3 vec1, vector3 vec2)
{
    vector3 ret = vector3_create(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
    return ret;  
}

//vec3 scalars
void vector3_scale_addv(vector3* source, float k)
{
    source->x += k;
    source->y += k;
    source->z += k;
}

vector3 vector3_scale_addition(vector3 vec, float k)
{
    vector3 ret = vector3_create(vec.x + k, vec.y + k, vec.z + k);
    return ret;
}

void vector3_scale_subv(vector3* source, float k)
{
    source->x -= k;
    source->y -= k;
    source->z -= k;
}

vector3 vector3_scale_subtraction(vector3 vec, float k)
{
    vector3 ret = vector3_create(vec.x - k, vec.y - k, vec.z - k);
    return ret;
}

void vector3_scale_multv(vector3* source, float k)
{
    source->x *= k;
    source->y *= k;
    source->z *= k;
}

vector3 vector3_scale_multiplication(vector3 vec, float k)
{
    vector3 ret = vector3_create(vec.x * k, vec.y * k, vec.z * k);
    return ret;
}

void vector3_scale_divv(vector3* source, float k)
{
    source->x /= k;
    source->y /= k;
    source->z /= k;
}

vector3 vector3_scale_division(vector3 vec, float k)
{
    vector3 ret = vector3_create(vec.x / k, vec.y / k, vec.z / k);
    return ret;
}

float vector3_dot(vector3 vec1, vector3 vec2) 
{
    float ret = (vec1.x * vec2.x) + (vec1.y * vec2.y) + (vec1.z * vec2.z);
    return ret;
}

float vector3_magnitude(vector3 vec) 
{  
    float ret = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
    return ret;
}

void vector3_normalizev(vector3* vec) 
{
    float magnitude = vector3_magnitude(*vec);
    vec->x /= magnitude;
    vec->y /= magnitude;
    vec->z /= magnitude;

}

vector3 vector3_normalize(vector3 vec) 
{
    float magnitude = vector3_magnitude(vec);
    vector3 ret;

    ret.x = vec.x / magnitude;
    ret.y = vec.y / magnitude;
    ret.z = vec.z / magnitude;

    return ret;

}

bool vector3_is_perpendicular(vector3 vec1, vector3 vec2) 
{
    return vector3_dot(vec1, vec2) == 0;
}

bool vector3_compare(vector3 vec1, vector3 vec2) 
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

vector3 vector3_cross(vector3 vec1, vector3 vec2) 
{
    vector3 ret = vector3_create(1.0f, 1.0f, 1.0f);
    
    ret.x = ((vec1.y * vec2.z) - (vec1.z * vec2.y));
    ret.y = ((vec1.z * vec2.x) - (vec1.x * vec2.z));
    ret.z = ((vec1.x * vec2.y) - (vec1.y * vec2.x));

    return ret;
    
}

void vector3_log(vector3 vec) 
{
    printf("\n x: %4f y: %4f z: %4f \n", vec.x, vec.y, vec.z);
}
