#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

#include "define.h"

struct Functie
{
    char Expresie[MAX];
    char v[MAX][MAX1+1];///vector de cuvinte
    int lung_v;///lungimea vectorului
    float a,b; ///intervalul de evaluare a functiei
    int Tip[MAX];///tipul fiecarui cuvant
};

struct Point{
    float x, y;
};

struct Graph{
    float x1, x2;
    float y1, y2;
    float screen_x1, screen_x2;
    float screen_y1, screen_y2;
};

struct coordinates_field
{
    int x1, y1;
    int x2, y2;
};

struct is_pressed
{
    bool read_page;
    bool min_d;
    bool max_d;
    bool save_b;
};

#endif // STRUCTS_H_INCLUDED
