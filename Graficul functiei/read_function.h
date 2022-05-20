#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED

#include "define.h"
#include "structs.h"

bool ENumar(char s[100]);
int Prioritate(char ch);
double Valoare_Functie(Functie F, double x);
void Cuvinte(char expr[MAX]);
void Codificare_Fct_Trigonometrice(Functie &F);
void Adaugare_Vector(Functie &F);
void Elimin_Spatii(char *s);
void Tip(Functie &F);
bool Expresie_Corecta(Functie &F, float x);

#endif
