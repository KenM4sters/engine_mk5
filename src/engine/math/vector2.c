#include "vector2.h"
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

vector2 vector2_create(float x, float y) 
{
    vector2 ret;
    ret.x = x;
    ret.y = y;

    return ret;
}


float* vector2_value_ptr(vector2 vec) 
{
    float* ret = malloc(sizeof(float) * vector2_LENGTH);

    ret[0] = vec.x;
    ret[1] = vec.y;

    return ret;
}

//vec3 combinations
void vector2_addv(vector2* source, vector2 add) 
{
    source->x += add.x;
    source->y += add.y;
}

vector2 vector2_addition(vector2 vec1, vector2 vec2) 
{
    vector2 ret = vector2_create(vec1.x + vec2.x, vec1.y + vec2.y);
    return ret;
}

void vector2_subv(vector2* source, vector2 sub)
{
    source->x -= sub.x;
    source->y -= sub.y;
}

vector2 vector2_subtraction(vector2 vec1, vector2 vec2)
{
    vector2 ret = vector2_create(vec1.x - vec2.x, vec1.y - vec2.y);
    return ret;
}

void vector2_multv(vector2* source, vector2 mult)
{
    source->x *= mult.x;
    source->y *= mult.y;
}

vector2 vector2_multiplication(vector2 vec1, vector2 vec2)
{
    vector2 ret = vector2_create(vec1.x * vec2.x, vec1.y * vec2.y);
    return ret;
}

void vector2_divv(vector2* source, vector2 div)
{
    source->x /= div.x;
    source->y /= div.y;
}

vector2 vector2_division(vector2 vec1, vector2 vec2)
{
    vector2 ret = vector2_create(vec1.x / vec2.x, vec1.y / vec2.y);
    return ret;  
}

//vec3 scalars
void vector2_scale_addv(vector2* source, float k)
{
    source->x += k;
    source->y += k;
}

vector2 vector2_scale_addition(vector2 vec, float k)
{
    vector2 ret = vector2_create(vec.x + k, vec.y + k);
    return ret;
}

void vector2_scale_subv(vector2* source, float k)
{
    source->x -= k;
    source->y -= k;
}

vector2 vector2_scale_subtraction(vector2 vec, float k)
{
    vector2 ret = vector2_create(vec.x - k, vec.y - k);
    return ret;
}

void vector2_scale_multv(vector2* source, float k)
{
    source->x *= k;
    source->y *= k;
}

vector2 vector2_scale_multiplication(vector2 vec, float k)
{
    vector2 ret = vector2_create(vec.x * k, vec.y * k);
    return ret;
}

void vector2_scale_divv(vector2* source, float k)
{
    source->x /= k;
    source->y /= k;
}

vector2 vector2_scale_division(vector2 vec, float k)
{
    vector2 ret = vector2_create(vec.x / k, vec.y / k);
    return ret;
}

float vector2_dot(vector2 vec1, vector2 vec2) 
{
    float ret = (vec1.x * vec2.x) + (vec1.y * vec2.y);
    return ret;
}

float vector2_magnitude(vector2 vec) 
{  
    float ret = sqrt((vec.x * vec.x) + (vec.y * vec.y));
    return ret;
}

void vector2_normalizev(vector2* vec) 
{
    float magnitude = vector2_magnitude(*vec);
    vec->x /= magnitude;
    vec->y /= magnitude;

}

vector2 vector2_normalize(vector2 vec) 
{
    float magnitude = vector2_magnitude(vec);
    vector2 ret;

    ret.x = vec.x / magnitude;
    ret.y = vec.y / magnitude;

    return ret;

}

bool vector2_is_perpendicular(vector2 vec1, vector2 vec2) 
{
    return vector2_dot(vec1, vec2) == 0;
}

bool vector2_compare(vector2 vec1, vector2 vec2) 
{
    return vec1.x == vec2.x && vec1.y == vec2.y;
}

// vector2 vector2_cross(vector2 vec1, vector2 vec2) 
// {
//     vector2 ret = vector2_create(1.0f, 1.0f, 1.0f);
    
//     ret.x = ((vec1.y * vec2.z) - (vec1.z * vec2.y));
//     ret.y = ((vec1.z * vec2.x) - (vec1.x * vec2.z));
//     ret.z = ((vec1.x * vec2.y) - (vec1.y * vec2.x));

//     return ret;
    
// }

void vector2_log(vector2 vec) 
{
    printf("\n x: %4f y: %4f \n", vec.x, vec.y);
}
