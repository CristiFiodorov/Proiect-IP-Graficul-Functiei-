#include <graphics.h>
#include <winbgim.h>
#include <windows.h>
#include <string.h>

#include <iostream>

#include "structs.h"
#include "working_with_files.h"

extern char path_dir[255];
extern int screen_width;
extern int screen_height;
extern char language;

using namespace std;

char f_expresie_salvat[31] = "";
char a_salvat[5] = "";
char b_salvat[5] = "";

extern char a[100][100];///matrice de erori
extern int poz;

coordinates_field functie, a_field, b_field, button_field, info_field, file_field, backbutton_field;
bool func_pressed, a_pressed, b_pressed, info_pressed;

void draw_pageII()
{
    setbkcolor(15);
    cleardevice();
    setcolor(4);
    setlinestyle(0, USERBIT_LINE, 1);

    char text[100] = " ";

    //backgroud image
    char bk_image[255] = "";
    strcpy(bk_image, path_dir);
    strcat(bk_image, "\\images\\bk2.gif");

    //info sign image
    char info_sign_image[255] = "";
    strcpy(info_sign_image, path_dir);
    strcat(info_sign_image, "\\images\\info_sign.gif");

    //info box image
    char info_box[255] = "";
    strcpy(info_box, path_dir);
    strcat(info_box, "\\images\\info_box.gif");

    //backbutton image
    char backbutton_image[255] = "";
    strcpy(backbutton_image, path_dir);
    strcat(backbutton_image, "\\images\\backbutton.gif");


    readimagefile( bk_image, -30, 0, screen_width + 60, screen_height);

    //backbutton
    setfillstyle(SOLID_FILL, 4);
    setbkcolor(4);
    settextstyle(3, HORIZ_DIR, 3);
    settextjustify( 1, 2);
    setcolor(15);

    if(language == 'r')
        strcpy(text, "Inapoi");
    else if(language == 'e')
        strcpy(text, "Back");

    readimagefile( backbutton_image, 80, 110, 170, 180);
    outtextxy(135, 130, text);

    backbutton_field = {80, 110, 170, 180};

    // info sign
    readimagefile( info_sign_image, screen_width - 120, 120, screen_width - 80, 160);
    info_field = {screen_width - 120, 120, screen_width - 80, 160};

    if(info_pressed)
    {
        settextjustify(CENTER_TEXT, TOP_TEXT);

        readimagefile( info_box, screen_width - 300, 165, screen_width - 20, 530);

        setbkcolor(4);
        setcolor(15);

        if(language == 'r')
            strcpy(text, "Operatori");
        else if(language == 'e')
            strcpy(text, "Operators");

        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 230, text);
        settextstyle(3, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 260, "+        -        *        /        ^");

        if(language == 'r')
            strcpy(text, "Variabile");
        else if(language == 'e')
            strcpy(text, "Variables");

        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 310, text);
        settextstyle(3, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 340, "x");

        if(language == 'r')
            strcpy(text, "Functii");
        else if(language == 'e')
            strcpy(text, "Functions");

        settextstyle(10, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 390, text);
        settextstyle(3, HORIZ_DIR, 3);
        outtextxy(screen_width - 160, 420, "sin    cos    arcsin    arccos");
        outtextxy(screen_width - 160, 450, "tg     ctg    arctg     arcctg");
        outtextxy(screen_width - 160, 480, "      rad    abs    ln        ");

    }

    setbkcolor(15);
    setcolor(4);

    settextjustify(LEFT_TEXT, TOP_TEXT);
    settextstyle(10, HORIZ_DIR, 5);

    if(language == 'r')
        strcpy(text, "Scrieti expresia functiei!");
    else if(language == 'e')
        strcpy(text, "Write the function expression!");

    int width = textwidth(text);
    int height = textheight(text);
    outtextxy((screen_width-width)/2, 120, text);

    // Partea pentru introducerea functiei
    setcolor(0);
    if(func_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);

    int width2 = textwidth("F(x)= ");
    outtextxy((screen_width - 500 - width2)/2 - 200, 160 + height, "F(x)= " );
    rectangle((screen_width - 500)/2 - 200 + width2/2, 150 + height, (screen_width + 500)/2 + 200, 210 + height);

    functie = {(screen_width - 500)/2 - 200 + width2/2, 150 + height, (screen_width + 500)/2 + 200, 210 + height};

    height += textheight("F(x)= ");

    // Partea pentru afisarea mesajului despre interval
    settextstyle(10, HORIZ_DIR, 4);
    setcolor(4);

    if(language == 'r')
        strcpy(text, "Fixati intervalul de reprezentare: [a,b]");
    else if(language == 'e')
        strcpy(text, "Set the representation range: [a,b]");

    int width3 = textwidth(text);
    outtextxy((screen_width-width3)/2, 210+height, text);
    height += textheight(text);


    settextstyle(10, HORIZ_DIR, 5);

    //Partea cu introducerea valorii lui a
    setcolor(0);
    if(a_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);

    int width4 = textwidth("a= ");
    outtextxy( (screen_width - width3)/2 + 100, 250+height, "a= ");
    rectangle( (screen_width - width3)/2 + width4 + 100, 240+height, (screen_width - width3)/2 + width4 + 220, 300+height);

    a_field = {(screen_width - width3)/2 + width4 + 100, 240+height, (screen_width - width3)/2 + width4 + 220, 300+height};

    //Partea cu introducerea valorii lui b
    if(b_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);

    int width5 = textwidth("b= ");
    outtextxy( (screen_width + width3)/2 - 220 - width5, 250+height, "b= ");
    rectangle((screen_width + width3)/2 - 220, 240+height, (screen_width + width3)/2 - 100, 300+height);

    b_field = {(screen_width + width3)/2 - 220, 240+height, (screen_width + width3)/2 - 100, 300+height};

    //Erori
    setcolor(4);
    setlinestyle(0, USERBIT_LINE, 1);

    if(language == 'r')
        strcpy(text, "Erori:");
    else if(language == 'e')
        strcpy(text, "Errors:");

    int width6 = textwidth(text);
    int height6 = textheight(text);

    outtextxy( (screen_width - width6)/2, 330+height, text);

    rectangle(screen_width/2 - 435, 340 + height + height6, screen_width/2 + 435, 515+height);

    settextstyle(10, HORIZ_DIR, 1);
    setcolor(COLOR(255, 0, 0));
    settextjustify(0, 2);

    if(poz > 6)
        poz = 6;

    for(int i=0;i<=poz;i++)
    {
        if(strcmp(a[0],"Expresie corecta!") && strcmp(a[0],"The expression is correct!"))
        {
            int h = textheight(a[i]);
            outtextxy(screen_width/2 - 430, 345 + height + height6 + i * h, a[i]);
        }
    }


    setbkcolor(4);
    setcolor(15);
    settextstyle(10, 0, 3);
    setlinestyle(0, USERBIT_LINE, 1);
    setfillstyle(SOLID_FILL, 4);

    //Butonul de introducere din fisier

    bar((screen_width-310), 525+height, (screen_width-140), 575+height);
    outtextxy((screen_width-304), 538+height, "functie.txt");

    file_field = {(screen_width-310), 525+height, (screen_width-140), 575+height};

    //Butonul de desenare
    bar((screen_width-150)/2, 525+height, (screen_width+150)/2, 575+height);

    button_field = {(screen_width-150)/2, 525+height, (screen_width+150)/2, 575+height};

    if(language == 'r')
        strcpy(text, "Deseneaza");
    else if(language == 'e')
        strcpy(text, "Draw");

    int width7 = textwidth(text);
    outtextxy((screen_width-width7)/2, 538+height, text);

    setbkcolor(15);
}

bool is_field_pressed(coordinates_field field, int x, int y)
{
    if(x > field.x1 && x < field.x2 && y > field.y1 && y < field.y2)
        return true;
    return false;
}


void read_pageII(Functie& f, bool& start_page, bool& f_ok)
{
    //resetare f
    strcpy(f.Expresie, " ");
    f.lung_v = 0;
    f.a = 0;
    f.b = 0;

    char c = ' ';
    char f_expresie[31] = "";
    char a[5] = "-14";
    char b[5] = "14";
    int i_func = 0;
    int i_a = strlen(a);
    int i_b = strlen(b);

    if(!f_ok)
    {
        strcpy(f_expresie, f_expresie_salvat);
        i_func = strlen(f_expresie);

        strcpy(a, a_salvat);
        i_a = strlen(a);

        strcpy(b, b_salvat);
        i_b = strlen(b);

        f_ok = true;
    }

    int x;
    int y;

    func_pressed = true;
    a_pressed = false;
    b_pressed = false;
    info_pressed = false;

    int page = 3;

    setactivepage(page);
    setvisualpage(page);
    page = (page == 3? 4 : 3);

    draw_pageII();

    setactivepage(page);
    setvisualpage(page == 3? 4 : 3);
    page = (page == 3? 4 : 3);

    bool d = true;

    while(true)
    {
        if(ismouseclick(WM_LBUTTONDOWN) || c == 13)
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if(is_field_pressed(functie, x, y))
            {
                func_pressed = true;
                a_pressed = false;
                b_pressed = false;
                d = true;
            }
            else if(is_field_pressed(file_field, x, y))
            {
                func_pressed = true;
                a_pressed = false;
                b_pressed = false;
                d = true;

                read_file(f_expresie, "functie.txt");
                f_expresie[30] = '\0';
                i_func = strlen(f_expresie);

            }
            else if(is_field_pressed(a_field, x, y))
            {
                func_pressed = false;
                a_pressed = true;
                b_pressed = false;
                d = true;
            }
            else if(is_field_pressed(b_field, x, y))
            {
                func_pressed = false;
                a_pressed = false;
                b_pressed = true;
                d = true;
            }
            else if(is_field_pressed(info_field, x, y))
            {
                func_pressed = false;
                a_pressed = false;
                b_pressed = false;

                if(info_pressed)
                    info_pressed = false;
                else
                    info_pressed = true;

                d = true;
            }
            else if(is_field_pressed(backbutton_field, x, y))
            {
                start_page = true;
                poz = -1;
                return;
            }
            else if(is_field_pressed(button_field, x, y) || c == 13)
            {
                c = 0;
                if(strlen(f_expresie) == 0)
                {
                    d = true;
                    continue;
                }

                if(strlen(a) == 0)
                {
                    strcpy(a, "-14");
                    i_a = 3;
                }
                if(strlen(b) == 0)
                {
                    strcpy(b, "14");
                    i_b = 2;
                }

                if(a[0] == '-')
                {
                    char str[4];
                    strcpy(str, a +1);
                    f.a = stoi(str);
                    f.a *= -1;
                }
                else
                {
                    f.a = stoi(a);
                }
                if(b[0] == '-')
                {
                    char str[4];
                    strcpy(str, b +1);
                    f.b = stoi(str);
                    f.b *= -1;
                }
                else
                {
                    f.b = stoi(b);
                }

                if((f.a + 3 > f.b) || ((f.b - f.a) >= 250) || f.a < -200 || f.b < -200 || f.a > 200 || f.b > 200)
                {
                    continue;
                }

                strcpy(f.Expresie, f_expresie);
                f.lung_v=strlen(f.Expresie);

                strcpy(f_expresie_salvat, f_expresie);
                strcpy(a_salvat, a);
                strcpy(b_salvat, b);

                // reset styles
                settextstyle(0, HORIZ_DIR, 2);
                break;
            }
            else
            {
                func_pressed = false;
                a_pressed = false;
                b_pressed = false;
                d = true;
            }
        }

            if(func_pressed)
            {
                if(kbhit())
                {
                    c = getch();

                    if (c == 8)
                    {
                        if(i_func > 0)
                        {
                            f_expresie[i_func-1] = '\0';
                            --i_func;
                            d = true;
                        }
                    }
                    else if(strchr("+-*/^x1234567890sincoartgdblq()." , c))
                    {
                        if(!(f_expresie[i_func-1] == '/' && c == '0') && !(f_expresie[i_func-2] == '/' && f_expresie[i_func-1] == '(' && c == '0'))
                        {
                            if(i_func < 30 && c != 13)
                            {
                                f_expresie[i_func] = c;
                                ++i_func;
                                d = true;
                            }
                        }
                    }
                }
            }
            if(a_pressed)
            {
                if(kbhit())
                {
                c = getch();

                    if (c == 8)
                    {
                        if(i_a > 0)
                        {
                            a[i_a-1] = '\0';
                            --i_a;
                            d = true;
                        }
                    }
                    else if(strchr("-1234567890" , c))
                    {
                        if((i_a < 4 && c != '-') || (i_a < 1))
                        {
                            a[i_a] = c;
                            ++i_a;
                            d = true;

                        }
                    }
                }
            }
            if(b_pressed)
            {
                if(kbhit())
                {
                c = getch();

                    if (c == 8)
                    {
                        if(i_b > 0)
                        {
                            b[i_b-1] = '\0';
                            --i_b;
                            d = true;
                        }
                    }
                    else if(strchr("-1234567890" , c))
                    {
                        if((i_b < 4 && c != '-') || (i_b < 1))
                        {
                            b[i_b] = c;
                            ++i_b;
                            d = true;

                        }
                    }
                }
            }
            if(d)
            {
                setactivepage(page);
                setvisualpage(page == 3? 4 : 3);
                page = page == 3? 4 : 3;

                draw_pageII();

                setcolor(4);
                settextstyle(3, 0, 5);
                outtextxy( functie.x1 + 5, functie.y1 + 10, f_expresie);
                outtextxy( a_field.x1 + 5, a_field.y1 + 10, a);
                outtextxy( b_field.x1 + 5, b_field.y1 + 10, b);

                setactivepage(page);
                setvisualpage(page == 3? 4 : 3);
                page = page == 3? 4 : 3;
                d = false;
            }
            if(!(func_pressed || a_pressed || b_pressed))
                if(kbhit())
                    c = getch();
    }
}
