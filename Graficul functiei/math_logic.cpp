#include <iostream>
#include <math.h>

#include "define.h"

const float pi=3.1415926;

bool EInfinit(float a)
{
    return a==plus_infinit || a==minus_infinit;
}

float Plus(float a, float b)
{
    if(EInfinit(a) || EInfinit(b))
        return infinit;
    else
        return a+b;
}

float Minus(float a, float b)
{
    if(EInfinit(a) || EInfinit(b))
        return infinit;
    else
        return a-b;
}

float Inmultit(float a, float b)
{
    if(fabs(a)<epsilon || fabs(b)<epsilon )
        return 0;
    else
    if(EInfinit(a) || EInfinit(b))
        return infinit;
    else
        return a*b;
}

float Impartit(float a, float b)
{
    if(fabs(b)>epsilon)
        return a/b;
    else
        return infinit;///daca b depaseste val. 0.0001 este considerat 0, iar a/0=infinit
}

float Putere(float a, float b)
{
    if(a==0)
        return 0;
    else
    if(b==0)
        return 1;
    else
        if(EInfinit(a) || EInfinit(b))
            return infinit;
        else
            return pow(a,b);
}

float Sinus(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return sin(a);
}

float Arc_Sinus(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return asin(a);
}

float Cosinus(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return cos(a);
}

float Arc_Cosinus(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return acos(a);
}

float Tangenta(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return tan(a);
}

float Arc_Tangenta(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return atan(a);
}

float Cotangenta(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return 1/tan(a);
}

float Arc_Cotangenta(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return pi/2 - atan(a);
}

float Modul(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return fabs(a);
}

float Radical(float a)
{
    if(!EInfinit(a) && a>epsilon)
        return sqrt(a);
    else
        return infinit;
}

float Exponential(float a)
{
    if(EInfinit(a))
        return infinit;
    else
        return exp(a);
}

float Logaritm(float a)
{
    if (a>epsilon && !EInfinit(a))
        return log(a);
    else
        return infinit;
}

float Egal(float a, float b)
{
    return a==b;
}

float Diferit(float a, float b)
{
    return a!=b;
}

bool MaiMic(float a, float b)
{
    return a < b;
}

bool MaiMare(float a, float b)
{
    return a > b;
}
