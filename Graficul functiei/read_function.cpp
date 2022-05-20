#include "define.h"
#include "math_logic.h"
#include "structs.h"

#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <iostream>

using namespace std;

char Alfabet[200]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char OperatiiBinare[200]="+-*/^";
char OperatiiUnare[200]="sctbdfghnarel";
char Operatii[200]="+-*/^sctbdfghnarel";
char Cifre[13]="0123456789qx";
char Caractere_Nepermise[300]="!@#$%&;'_[]{},~`\|""abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


const float pi=3.1415926;
int vf_Op,vf_Opd;
const int max_stiva=100;
double Opd[100]; /// stiva operanzilor
char Op[100]; /// stiva operatorilor

char a[100][100];///matrice de erori
int poz;

extern char language;

bool ENumar(char s[100]) ///verific daca sirul de caractere este numar
{
    return (strchr("-+0123456789",s[0]) && atof(s)!=0.0);
}

int Prioritate(char ch) ///stabilirea ordinii de prioritate a operatorilor
{
    if(ch=='(' || ch==')')
        return 0;
    if(ch=='+' || ch=='-')
        return 1;
    if(ch=='*' || ch=='/')
        return 2;
    if(ch=='^')
        return 3;
    if(ch=='s' || ch=='c' || ch=='a' || ch=='t' || ch=='b' || ch=='d' || ch=='f' || ch=='g'  || ch=='h' || ch=='e' || ch=='r' || ch=='l')
        return 4;
}

int ok_i, ok_t, ok_c, ok_r, ok_l, ok_lz;


double Valoare_Functie(Functie F, double x) ///valoarea functiei in x
{

    ok_i=1,ok_t=1,ok_c=1,ok_r=1,ok_l=1,ok_lz=1;
    int i;
    double val,x1,x2;
    for (i=1; i<=max_stiva; i++)
    {
        Opd[i]=0;
        Op[i]='@';
    }
    vf_Opd=0;
    vf_Op=1;
    Op[vf_Op]='(';
    i=0;
    while(i<=F.lung_v && vf_Op>0)
    {
        i++;
        if(ENumar(F.v[i]))///daca e numar -> pun in stiva operanzilor
        {
            vf_Opd++;
            val=atof(F.v[i]);
            Opd[vf_Opd]=val;
        }
        else
            switch (F.v[i][0])///daca numarul e reprezentat de unul din
                              ///caracterele q:=(pi=3.1415926) sau X -> pun in stiva operanzilor
            {
                case 'q': vf_Opd++;
                          Opd[vf_Opd]=pi;
                          break;
                case 'x': vf_Opd++;
                          Opd[vf_Opd]=x;
                          break;
                case '(': vf_Op++;      /// paranteza de inceput a expresiei -> pun in stiva operatorilor
                          Op[vf_Op]='(';
                          break;
                default: ///daca in varful stivei operatorilor se afla un operator binar sau unar (altfel spus, nu e '(' sau ')' )
                   while( (vf_Op>0) && !(strchr("()",Op[vf_Op])) &&
                           Prioritate(Op[vf_Op]) >= Prioritate(F.v[i][0]) )
                    {
                        if (vf_Opd>1) ///daca am un operator ce implica doi operanzi
                            x1=Opd[vf_Opd-1]; ///primul operand
                        x2=Opd[vf_Opd]; ///al doilea operand
                        switch (Op[vf_Op]) ///Operatii[200]="+-*/^sctarel"
                        {
                            case '=': val=Egal(x1,x2); break;
                            case '#': val=Diferit(x1,x2); break;
                            case '<': val=MaiMic(x1,x2); break;
                            case '>': val=MaiMare(x1,x2); break;
                            case '+': val=Plus(x1,x2); break;
                            case '-': val=Minus(x1,x2); break;
                            case '*': val=Inmultit(x1,x2); break;
                            case '/': {
                                            if(x2!=0)
                                                val=Impartit(x1,x2);
                                            else
                                                ok_i=0;
                                            break;
                                      }

                            case '^': val=Putere(x1,x2); break;
                            case 's': val=Sinus(x2);break;
                            case 'c': val=Cosinus(x2);break;
                            case 't': {

                                            if(Cosinus(x2)>epsilon || Cosinus(x2)<0.0)
                                                val=Tangenta(x2);
                                            else
                                                ok_t=0;
                                            break;
                                        }

                            case 'b': {

                                            if(Sinus(x2)>epsilon || Sinus(x2)<0.0)
                                                val=Cotangenta(x2);
                                            else
                                                ok_c=0;
                                            break;
                                        }
                            case 'd': val=Arc_Sinus(x2); break;
                            case 'f': val=Arc_Cosinus(x2); break;
                            case 'g': val=Arc_Tangenta(x2); break;
                            case 'h': val=Arc_Cotangenta(x2); break;
                            case 'a': val=Modul(x2); break;
                            case 'r': {
                                            if(x2==0)
                                                val=0;
                                            else
                                            if(x2>0)
                                                val=Radical(x2);
                                            else
                                                ok_r=0;
                                            break;
                                      }

                            case 'e': val=Exponential(x2); break;
                            case 'l': {
                                            if(x2==0)
                                                ok_lz=0;
                                            else
                                            if(x2<0)
                                                ok_l=0;
                                            else
                                            if(x2>0)
                                                val=Logaritm(x2);

                                            break;
                                      }

                        }
                        if (strchr(OperatiiBinare,Op[vf_Op]))///daca in varful stivei operatorilor este un operator binar
                            vf_Opd--; ///varful operanzilor scade (au fost folositi)
                        if (strchr(Operatii,Op[vf_Op]))
                            Opd[vf_Opd]=val;///rezultatul calculului este pus in stiva operanzilor
                        vf_Op--;///varful operatorilor scade (a fost folosit)
                    }

                if (vf_Op>0)

                    if ((Op[vf_Op]!='(') || (strcmp(F.v[i],")")))///daca in vf stivei operatorilor nu e '(' sau
                                                                 ///pe pozitia initiala i a vectorului corespunzator expresiei este ')'
                    {
                        vf_Op++;
                        Op[vf_Op]=F.v[i][0];///este adaugat in stiva operatorilot
                    }
                    else
                        vf_Op--;
            }
    }
    if(ok_i==1 && ok_t==1 && ok_c==1 && ok_r==1 && ok_l==1)
        if (vf_Op==0) ///daca s-a golit cu succes stiva operatorilor
            return Opd[1]; ///se returneaza rezultatul expresiei, acesta aflandu-se la baza stivei operanzilor
        else
            return infinit;///se returneaza infinit daca au mai ramas operatori in stiva operatorilor
}

void Cuvinte(char expr[MAX])
{
    char s[MAX];
    int k,i,ok;
    k=0;
    i=0;
    ok=0;
    while(i<strlen(expr))
    {
       ///daca exista caracter
        if(expr[i+1]!=NULL)
        {
            /*numerele care incep cu '-' sau '+' sunt considerate operatii unare cand: 1) este primul caracter
                                                                                       2) in fata nu exista o cifra
                                                                                       3) in fata nu se afla ')'     */

            if((expr[i]=='-' || expr[i]=='+') && strchr(Cifre,expr[i+1]) && (i==0 || (strchr(Cifre,expr[i-1])==NULL || strchr(Alfabet,expr[i-1])!=NULL) && strchr("xq",expr[i-1])==NULL) && expr[i-1]!=')')
            {
                    s[k++]=expr[i++];
                    s[k++]='1';
                    s[k++]=' ';
                    s[k++]='*';
                    s[k++]=' ';
                    if((strchr(Cifre,expr[i]) != NULL && strchr("xq",expr[i+1])==NULL || expr[i]=='.' ) &&
                            strchr(OperatiiBinare,expr[i+1])==NULL && expr[i+1]!=')' && expr[i+1]!=NULL)
                    {
                        while((strchr(Cifre,expr[i]) != NULL && strchr("xq",expr[i+1])==NULL || expr[i]=='.') &&
                            strchr(OperatiiBinare,expr[i+1])==NULL && expr[i+1]!=')' && expr[i+1]!=NULL)
                        s[k++]=expr[i++];

                        s[k++]=expr[i++];
                        s[k++]=' ';
                    }
                    else
                    {
                        s[k++]=expr[i++];
                        s[k++]=' ';
                    }

            }

            else ///Cifre[13]="0123456789qx";
                 /*este cifra daca 1) in fata ei a fost '('
                                   2) este prima din sir
                                   3) in fata ei este un operator */ ///sin(2x)
            if( strchr(Cifre,expr[i]) != NULL &&
                     (i==0 || strchr(OperatiiBinare,expr[i-1]) != NULL || expr[i-1]=='(' || strchr(Alfabet,expr[i-1])!=NULL) )
            {
                if( strchr(OperatiiBinare,expr[i+1]) == NULL &&
                        strchr(Alfabet,expr[i+1]) == NULL &&
                        expr[i+1] != ')' &&
                        expr[i+1] != '(' &&
                        expr[i+1] != NULL &&
                        (strchr(Cifre,expr[i]) != NULL && strchr("xq",expr[i+1])==NULL || expr[i]=='.' ) )
                {
                    while ( strchr(OperatiiBinare,expr[i+1]) == NULL &&
                            strchr(Alfabet,expr[i+1]) == NULL &&
                            expr[i+1] != ')' &&
                            expr[i+1] != '(' &&
                            expr[i+1] != NULL &&
                            (strchr(Cifre,expr[i]) != NULL && strchr("xq",expr[i+1])==NULL || expr[i]=='.' ) )
                        s[k++]=expr[i++];

                    s[k++]=expr[i++];
                    s[k++]=' ';
                }
                else
                {
                    s[k++]=expr[i++];
                    s[k++]=' ';
                }
            }
            else

            if(strchr("xq",expr[i])!=NULL)
            {
                s[k++]=expr[i++];
                s[k++]=' ';
            }


            else ///OperatiiUnare: ln/sin/cos/tg/ctg/arcsin/arccos/arctg/arcctg/abs/exp/rad care incep cu '-' sau '+'
                if( (expr[i]=='-' || expr[i]=='+') && (i==0 ) && expr[i-1]!=')' &&
                  ( (expr[i+1]=='l' && expr[i+2]=='n')                     ||
                    (expr[i+1]=='s' && expr[i+2]=='i' && expr[i+3]=='n')  ||
                    (expr[i+1]=='c' && expr[i+2]=='o' && expr[i+3]=='s')  ||
                    (expr[i+1]=='t' && expr[i+2]=='g')                    ||
                    (expr[i+1]=='c' && expr[i+2]=='t' && expr[i+3]=='g')  ||
                    (expr[i+1]=='a' && expr[i+2]=='r' && expr[i+3]=='c' && expr[i+4]=='s' && expr[i+5]=='i' && expr[i+6]=='n')  ||
                    (expr[i+1]=='a' && expr[i+2]=='r' && expr[i+3]=='c' && expr[i+4]=='c' && expr[i+5]=='o' && expr[i+6]=='s')  ||
                    (expr[i+1]=='a' && expr[i+2]=='r' && expr[i+3]=='c' && expr[i+4]=='t' && expr[i+5]=='g')  ||
                    (expr[i+1]=='a' && expr[i+2]=='r' && expr[i+3]=='c' && expr[i+4]=='c' && expr[i+5]=='t' && expr[i+6]=='g')  ||
                    (expr[i+1]=='a' && expr[i+2]=='b' && expr[i+3]=='s')  ||
                    (expr[i+1]=='e' && expr[i+2]=='x' && expr[i+3]=='p')  ||
                    (expr[i+1]=='r' && expr[i+2]=='a' && expr[i+3]=='d') ) )
                   {
                        ok=1;
                        s[k++]=expr[i++];
                        s[k++]='1';
                        s[k++]=' ';
                        s[k++]='*';
                        s[k++]=' ';
                   }
            else ///OperatiiUnare: ln/tg
                if( expr[i]=='l' && expr[i+1]=='n' ||
                    expr[i]=='t' && expr[i+1]=='g' )
                    {
                        ok=1;
                        s[k++]=expr[i];
                        s[k++]=expr[i+1];
                        s[k++]=' ';
                        i=i+2;
                    }
            else ///OperatiiUnare: sin/cos/ctg/abs/exp/rad
                if( (expr[i]=='s' && expr[i+1]=='i' && expr[i+2]=='n') ||
                    (expr[i]=='c' && expr[i+1]=='o' && expr[i+2]=='s') ||
                    (expr[i]=='c' && expr[i+1]=='t' && expr[i+2]=='g') ||
                    (expr[i]=='a' && expr[i+1]=='b' && expr[i+2]=='s') ||
                    (expr[i]=='e' && expr[i+1]=='x' && expr[i+2]=='p') ||
                    (expr[i]=='r' && expr[i+1]=='a' && expr[i+2]=='d')  )

                {
                    ok=1;
                    s[k++]=expr[i];
                    s[k++]=expr[i+1];
                    s[k++]=expr[i+2];
                    s[k++]=' ';
                    i=i+3;
                }
            else///arctg
                if(expr[i]=='a' && expr[i+1]=='r' && expr[i+2]=='c' && expr[i+3]=='t' && expr[i+4]=='g')
                {
                    ok=1;
                    s[k++]=expr[i];
                    s[k++]=expr[i+1];
                    s[k++]=expr[i+2];
                    s[k++]=expr[i+3];
                    s[k++]=expr[i+4];
                    s[k++]=' ';
                    i=i+5;
                }
            else///arcsin/arccos/arcctg
                if((expr[i]=='a' && expr[i+1]=='r' && expr[i+2]=='c' && expr[i+3]=='s' && expr[i+4]=='i' && expr[i+5]=='n') ||
                   (expr[i]=='a' && expr[i+1]=='r' && expr[i+2]=='c' && expr[i+3]=='c' && expr[i+4]=='o' && expr[i+5]=='s') ||
                   (expr[i]=='a' && expr[i+1]=='r' && expr[i+2]=='c' && expr[i+3]=='c' && expr[i+4]=='t' && expr[i+5]=='g') )
                {
                    ok=1;
                    s[k++]=expr[i];
                    s[k++]=expr[i+1];
                    s[k++]=expr[i+2];
                    s[k++]=expr[i+3];
                    s[k++]=expr[i+4];
                    s[k++]=expr[i+5];
                    s[k++]=' ';
                    i=i+6;
                }
            else
                ///pun in sir Operatiile Binare sau '(' , ')' urmate de spatiu
                if( expr[i]=='(' && strchr(Cifre,expr[i-1]) && i!=0)
                {
                    s[k++]=' ';
                    s[k++]='*';
                    s[k++]=' ';
                    s[k++]=expr[i++];
                    s[k++]=' ';
                }


            else
                if(strchr(OperatiiBinare,expr[i]) || expr[i]=='(' || expr[i]==')')
                {
                    s[k++]=expr[i++];
                    s[k++]=' ';
                }
            else
                if(strchr("!@#$%&;'_[]{},~`\|""",expr[i]) || ok==0 && strchr(Alfabet,expr[i]))
                {

                    s[k++]=expr[i++];
                    s[k++]=' ';

                }
        }
        else
        ///daca nu exista caracter
        if(expr[i+1]==NULL)
            s[k++]=expr[i++];
    }
    s[k]=NULL;
    strcpy(expr,s);
}

void Tip(Functie &F)
{
    char tip_cifre[14]="0123456789";
    char tip_litere[3]="xq";
    for(int i=0; i<F.lung_v; i++)
    {
        if(F.v[i][0]=='(')
            F.Tip[i]=1;

        else
            if(F.v[i][0]==')')
                F.Tip[i]=2;

        else
            if(F.v[i][0]=='+' || F.v[i][0]=='-')
                F.Tip[i]=3;

        else

            if(F.v[i][0]=='*' || F.v[i][0]=='/' || F.v[i][0]=='^')
                F.Tip[i]=4;

        else
            if( strcmp(F.v[i],"sin")==0    ||
                strcmp(F.v[i],"cos")==0    ||
                strcmp(F.v[i],"tg")==0     ||
                strcmp(F.v[i],"btg")==0    || ///ctg
                strcmp(F.v[i],"drcsin")==0 || ///arcsin
                strcmp(F.v[i],"frccos")==0 || ///arccos
                strcmp(F.v[i],"grctg")==0  || ///arctg
                strcmp(F.v[i],"hrcctg")==0 || ///arcctg
                strcmp(F.v[i],"abs")==0    ||
                strcmp(F.v[i],"rad")==0    ||
                strcmp(F.v[i],"exp")==0    ||
                strcmp(F.v[i],"ln")==0      )
                    F.Tip[i]=5;

        else
            if(strchr(tip_cifre,F.v[i][0]) )
                F.Tip[i]=6;
        else
            if(strchr(tip_litere,F.v[i][0]) )
                F.Tip[i]=7;

        else
            if(strchr(Caractere_Nepermise,F.v[i][0]))
                F.Tip[i]=-1;
    }
}

void Codificare_Fct_Trigonometrice(Functie &F)
{
    for(int i=0;i<F.lung_v;i++)
    {
        if(strcmp("ctg",F.v[i])==0)
            F.v[i][0]='b';
        else
        if(strcmp("arcsin",F.v[i])==0)
            F.v[i][0]='d';
        else
        if(strcmp("arccos",F.v[i])==0)
            F.v[i][0]='f';
        else
        if(strcmp("arctg",F.v[i])==0)
            F.v[i][0]='g';
        else
        if(strcmp("arcctg",F.v[i])==0)
            F.v[i][0]='h';
    }
}

void Adaugare_Vector(Functie &F)
{
    char s[MAX];
    strcpy(s,F.Expresie);
    char *p;
    int k=1;
    strcpy(F.v[0],"(");
    p=strtok(s," ");
    while(p)
    {
        strcpy(F.v[k++],p);
        p=strtok(NULL," ");
    }
    strcpy(F.v[k++],")");
    F.lung_v=k;
}

void Elimin_Spatii(char *s)
{
    int lungime;
    lungime=strlen(s);
    for(int i=0;i<lungime;i++)
    {
        while(s[i]==' ')
            strcpy(s+i,s+i+1);
    }
}

void Verificare_Domeniu(Functie &F,float &x)
{
    Valoare_Functie(F,x);

    if(ok_i==0)
    {
        if(language == 'r')
        {
            strcpy(a[++poz],"EROARE: Nu se poate executa impartirea la 0!");
        }
        else if(language == 'e')
        {
            strcpy(a[++poz],"ERROR: Unable to divide by Zero!");
        }
    }

    if(ok_t==0)
    {
        if(language == 'r')
        {
            strcpy(a[++poz],"EROARE: Tangenta nu este definita in punctele de forma (2k+1)*(pi/2)!");
        }
        else if(language == 'e')
        {
            strcpy(a[++poz],"ERROR: The tangent is not defined in the points of the form (2k+1)*(pi/2)!");
        }
    }

    if(ok_c==0)
    {
        if(language == 'r')
        {
            strcpy(a[++poz],"EROARE: Cotangenta nu este definita in punctele de forma k*pi!");
        }
        else if(language == 'e')
        {
            strcpy(a[++poz],"ERROR: The cotangent is not defined in the points of the form k*pi!");
        }
    }

    if(ok_r==0)
    {
        if(language == 'r')
        {
            strcpy(a[++poz],"EROARE: Nu se poate extrage radicalul dintr-un numar negativ!");
        }
        else if(language == 'e')
        {
            strcpy(a[++poz],"ERROR: Unable to calculate the square root of a negative number!");
        }
    }

    if(ok_l==0)
    {
        if(language == 'r')
        {
            strcpy(a[++poz],"EROARE: Nu se poate calcula logaritmul natural dintr-un numar negativ!");
        }
        else if(language == 'e')
        {
            strcpy(a[++poz],"ERROR: Unable to evaluate natural logarithm for a negative number!");
        }
    }

    if(ok_lz==0)
    {
        if(language == 'r')
        {
            strcpy(a[++poz],"EROARE: Logaritmul natural nu este definit in 0!");
        }
        else if(language == 'e')
        {
            strcpy(a[++poz],"ERROR: Natural logarithm is not defined for 0!");
        }
    }
}

///cout<<"EROARE la pozitia "<<i<<": Dupa "<<v[i]<<" nu poate urma "<<v[i+1]<<endl;
void Eroare_Tip(int pozitia, char tip_1[], char tip_2[])
{
    if(language == 'r')
    {
        char charValue[10] ="" ;
        char d[8]=": Dupa ";
        char n[16]=" nu poate urma ";
        strcpy(a[++poz],"EROARE la pozitia ");
        itoa(pozitia,charValue,10);
        for( int l=0 ;l<strlen(charValue);l++)
            a[poz][strlen("EROARE la pozitia")+ 1 + l]=charValue[l];

        for( int l=0 ;l<strlen(d);l++)
            a[poz][strlen("EROARE la pozitia")+ strlen(charValue)+1+l]=d[l];

        for( int l=0 ;l<strlen(tip_1);l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue)+strlen(d)+ l + 1]=tip_1[l];

        for( int l=0 ;l<strlen(n);l++)
            a[poz][strlen("EROARE la pozitia")+ strlen(charValue) + strlen(d) + strlen(tip_1) + l + 1]=n[l];

        for( int l=0 ;l<=strlen(tip_2);l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue) + strlen(d) + strlen(tip_1) + strlen(n) + l + 1]=tip_2[l];
    }
    else if(language == 'e')
    {
        char charValue[10] ="" ;
        char d[8]=": ";
        char n[]=" cannot be followed by ";
        strcpy(a[++poz],"ERROR at position ");
        itoa(pozitia,charValue,10);
        for( int l=0 ;l<strlen(charValue);l++)
            a[poz][strlen("ERROR at position")+ 1 + l]=charValue[l];

        for( int l=0 ;l<strlen(d);l++)
            a[poz][strlen("ERROR at position")+ strlen(charValue)+1+l]=d[l];

        for( int l=0 ;l<strlen(tip_1);l++)
            a[poz][strlen("ERROR at position") + strlen(charValue)+strlen(d)+ l + 1]=tip_1[l];

        for( int l=0 ;l<strlen(n);l++)
            a[poz][strlen("ERROR at position")+ strlen(charValue) + strlen(d) + strlen(tip_1) + l + 1]=n[l];

        for( int l=0 ;l<=strlen(tip_2);l++)
            a[poz][strlen("ERROR at position") + strlen(charValue) + strlen(d) + strlen(tip_1) + strlen(n) + l + 1]=tip_2[l];
    }

}
///cout<<"EROARE la pozitia "<<i<<": Dupa "<<v[i]<<" expresia se termina brusc"<<endl;
void Eroare_Brusc(int pozitia, char tip_1[])
{
    if(language == 'r')
    {
        char charValue[10] ="" ;
        char d[8]=": Dupa ";
        char n[30]=" expresia se termina brusc";
        strcpy(a[++poz],"EROARE la pozitia ");
        itoa(pozitia,charValue,10);
        for( int l=0 ;l<strlen(charValue);l++)
            a[poz][strlen("EROARE la pozitia")+ 1 + l]=charValue[l];
        for( int l=0 ;l<strlen(d);l++)
            a[poz][strlen("EROARE la pozitia")+ strlen(charValue)+1+l]=d[l];

        for( int l=0 ;l<strlen(tip_1);l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue)+strlen(d)+ l + 1]=tip_1[l];

        for( int l=0 ;l<=strlen(n);l++)
            a[poz][strlen("EROARE la pozitia")+ strlen(charValue) + strlen(d) + strlen(tip_1) + l + 1]=n[l];
    }
    else if(language == 'e')
    {
        char charValue[10] ="" ;
        char d[]=": After ";
        char n[30]=" the expression ends abruptly";
        strcpy(a[++poz],"ERROR at position ");
        itoa(pozitia,charValue,10);
        for( int l=0 ;l<strlen(charValue);l++)
            a[poz][strlen("ERROR at position")+ 1 + l]=charValue[l];
        for( int l=0 ;l<strlen(d);l++)
            a[poz][strlen("ERROR at position")+ strlen(charValue)+1+l]=d[l];

        for( int l=0 ;l<strlen(tip_1);l++)
            a[poz][strlen("ERROR at position") + strlen(charValue)+strlen(d)+ l + 1]=tip_1[l];

        for( int l=0 ;l<=strlen(n);l++)
            a[poz][strlen("ERROR at position")+ strlen(charValue) + strlen(d) + strlen(tip_1) + l + 1]=n[l];
    }
}

///cout<<"EROARE la pozitia "<<i<<": "<<v[i]<<" Este un caracter nepermis"<<endl;
void Eroare_Nepermis(int pozitia, char tip_1[])
{
    if(language == 'r')
    {
        char charValue[10] ="" ;
        char e[30]=" este un caracter nepermis";
        strcpy(a[++poz],"EROARE la pozitia ");

        itoa(pozitia,charValue,10);

        for( int l=0 ;l<strlen(charValue);l++)
            a[poz][strlen("EROARE la pozitia")+ 1 + l]=charValue[l];

        a[poz][strlen("EROARE la pozitia")+ strlen(charValue) + 1]=':';
        a[poz][strlen("EROARE la pozitia")+ strlen(charValue) + 2]=' ';

        for( int l=0 ;l<strlen(tip_1);l++)
            a[poz][strlen("EROARE la pozitia") + strlen(charValue)+ 2 + l + 1]=tip_1[l];

        for( int l=0 ;l<=strlen(e);l++)
            a[poz][strlen("EROARE la pozitia")+ strlen(charValue) + 2+ strlen(tip_1) + l + 1]=e[l];
    }
    else if(language == 'e')
    {
        char charValue[10] ="" ;
        char e[30]=" is a forbidden character";
        strcpy(a[++poz],"ERROR at position ");

        itoa(pozitia,charValue,10);

        for( int l=0 ;l<strlen(charValue);l++)
            a[poz][strlen("ERROR at position")+ 1 + l]=charValue[l];

        a[poz][strlen("ERROR at position")+ strlen(charValue) + 1]=':';
        a[poz][strlen("ERROR at position")+ strlen(charValue) + 2]=' ';

        for( int l=0 ;l<strlen(tip_1);l++)
            a[poz][strlen("ERROR at position") + strlen(charValue)+ 2 + l + 1]=tip_1[l];

        for( int l=0 ;l<=strlen(e);l++)
            a[poz][strlen("ERROR at position")+ strlen(charValue) + 2+ strlen(tip_1) + l + 1]=e[l];
    }

}

void Verificare_Tipuri(char v[MAX][MAX1+1], int tip[MAX], int lungime)
{
    char charValue;
    for(int i=1; i<=lungime-2; i++)
    {
        if(i!=lungime-2)
        {
            if( tip[i]==1 && (tip[i+1]==2 || tip[i+1]==4 || tip[i+1]==-1) ) /* '(' */
                    Eroare_Tip(i,v[i],v[i+1]);


            else

            if( tip[i]==2 && (tip[i+1]==1 || tip[i+1]==5 || tip[i+1]==6 || tip[i+1]==7 || tip[i+1]==-1)) /* ')' */
                Eroare_Tip(i,v[i],v[i+1]);

            else

            if( (tip[i]==3 && strlen(v[i])==1) && (tip[i+1]==2 || tip[i+1]==3  || tip[i+1]==4 || tip[i+1]==-1))  /* '+-' binar */
                    Eroare_Tip(i,v[i],v[i+1]);

            else

            if( tip[i]==4 && ( tip[i+1]==2 || (tip[i+1]==3 && strlen(v[i])==1) || tip[i+1]==4 || tip[i+1]==-1 ) ) /* '^/*' */
                    Eroare_Tip(i,v[i],v[i+1]);

            else
                /* ln/sin/cos/tg/ctg/arcsin/arccos/arctg/arcctg/abs/exp/rad */
            if (tip[i]==5 && (tip[i+1]==2 || tip[i+1]==3 || tip[i+1]==5 || tip[i+1]==-1)) ///daca nu urmeaza ( si nici un nr
            {
                    if(strcmp("btg",v[i])==0)
                        Eroare_Tip(i,"ctg",v[i+1]);
                    else
                    if(strcmp("drcsin",v[i])==0)
                        Eroare_Tip(i,"arcsin",v[i+1]);
                    else
                    if(strcmp("frccos",v[i])==0)
                         Eroare_Tip(i,"arccos",v[i+1]);
                    else
                    if(strcmp("grctg",v[i])==0)
                        Eroare_Tip(i,"arctg",v[i+1]);
                    else
                     if(strcmp("hrcctg",v[i])==0)
                        Eroare_Tip(i,"arcctg",v[i+1]);
                    else
                        Eroare_Tip(i,v[i],v[i+1]);
            }

            else

            if( tip[i]==6 && (tip[i+1]==1 || tip[i+1]==5 || tip[i+1]==7 || tip[i+1]==-1) ) /*tip_cifre[14]="0123456789"*/
                    Eroare_Tip(i,v[i],v[i+1]);

            else

            if( tip[i]==7 && (tip[i+1]==1 || tip[i+1]==5 || tip[i+1]==7 || tip[i+1]==-1) ) /*char tip_litere[3]="xq" */
                    Eroare_Tip(i,v[i],v[i+1]);

            else

            if(tip[i]==-1)
                Eroare_Nepermis(i,v[i]);
        }

        else

            if( i==lungime-2 )
            {

                if ( tip[i]==1 || tip[i]==3 || tip[i]==4 )
                        Eroare_Brusc(i,v[i]);

                else
                if( tip[i]==5 )

                        if(strcmp("btg",v[i])==0)
                            Eroare_Brusc(i,"ctg");
                        else
                        if(strcmp("drcsin",v[i])==0)
                            Eroare_Brusc(i,"arcsin");
                        else
                        if(strcmp("frccos",v[i])==0)
                            Eroare_Brusc(i,"arccos");
                        else
                        if(strcmp("grctg",v[i])==0)
                            Eroare_Brusc(i,"arctg");
                        else
                        if(strcmp("hrcctg",v[i])==0)
                            Eroare_Brusc(i,"arcctg");
                        else
                            Eroare_Brusc(i,v[i]);

                else

                if( tip[i]==-1 )
                        Eroare_Nepermis(i,v[i]);
            }
    }
}

int Verificare_Paranteze(char *s)
{
    int i,verif,k,j,lungime;
    lungime=strlen(s);
    k=0;
    verif=1;

    for(i=0;i<lungime;i++)
    {
        if(s[i]=='(')
            k++;

        else
        if(s[i]==')' && k==0)
        {
            if(verif==1)
            {
                if(language == 'r')
                    strcpy(a[++poz],"EROARE: Parantezele nu sunt inchise corect!");
                else if(language == 'e')
                    strcpy(a[++poz],"ERROR: The parentheses are not closed properly!");
                verif=0; ///pentru a afisa doar o data mesajul
            }
        }
        else
            if(s[i]==')')
                k--;
    }
    if(k!=0)
    {
        if(verif==1)
        {
            if(language == 'r')
                    strcpy(a[++poz],"EROARE: Parantezele nu sunt inchise corect!");
            else if(language == 'e')
                    strcpy(a[++poz],"ERROR: The parentheses are not closed properly!");
            verif=0; ///pentru a afisa doar o data mesajul
        }
    }
}

bool Expresie_Corecta(Functie &F, float x)
{
    bool corect;
    Verificare_Paranteze(F.Expresie);
    Verificare_Tipuri(F.v,F.Tip,F.lung_v);
    if(poz == 0)
    {
        Verificare_Domeniu(F,x);
        int p = poz;
        poz = 0;
        x = -201.1;
        Verificare_Domeniu(F,x);
        if(p != poz)
            poz = 0;
        else
        {
            if(p > poz)
                poz = p;
        }
    }

    if(poz==0)
    {
        if(language == 'r')
            strcpy(a[0],"Expresie corecta!");
        else if(language == 'e')
            strcpy(a[0],"The expression is correct!");
        corect = true;
    }
    else
    {
        if(language == 'r')
            strcpy(a[0],"Expresie gresita!");
        else if(language == 'e')
            strcpy(a[0],"The expression is not correct!");
        corect = false;
    }

    for(int i=0;i<=poz;i++)
        cout<<a[i]<<endl;

    return corect;
}
