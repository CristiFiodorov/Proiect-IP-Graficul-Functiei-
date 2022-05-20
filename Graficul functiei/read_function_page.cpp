#include <graphics.h>
#include <winbgim.h>
#include <windows.h>
#include <stdlib.h>
#include <cstring>

#include "structs.h"

using namespace std;

struct coordinates_field
{
    int x1, y1;
    int x2, y2;
};

void draw_pageII(coordinates_field& functie, coordinates_field& a_field, coordinates_field& b_field, coordinates_field& button_field)
{
    int screen_width = GetSystemMetrics(SM_CXSCREEN);

    setbkcolor(15);
    cleardevice();
    setcolor(4);
    settextstyle(3, HORIZ_DIR, 5);
    int width = textwidth("Scrieti expresia functiei!");
    int height = textheight("Scrieti expresia functiei!");
    outtextxy((screen_width-width)/2, 100, "Scrieti expresia functiei!");

    // Partea pentru introducerea functiei
    setcolor(0);
    int width2 = textwidth("F(x)= ");
    height += textheight("F(x)= ");
    outtextxy((screen_width-width - width2)/2 - 200, 150+height, "F(x)= " );
    rectangle((screen_width-width)/2 - 200 + width2/2, 140+height, (screen_width+width)/2 + 200, 200+height);

    functie = {(screen_width-width)/2 - 200 + width2/2, 140+height, (screen_width+width)/2 + 200, 200+height};

    // Partea pentru afisarea mesajului despre interval
    setcolor(4);
    int width3 = textwidth("Fixati intervalul de reprezentare: [a,b]");
    height += textheight("Fixati intervalul de reprezentare: [a,b]");
    outtextxy((screen_width-width3)/2, 250+height, "Fixati intervalul de reprezentare: [a,b]");

    //Partea cu introducerea valorii lui a
    setcolor(0);
    int width4 = textwidth("a= ");
    height += textheight("a= ");
    outtextxy((screen_width-100 - width4)/2, 300+height, "a= ");
    rectangle((screen_width-100)/2 + width4/2, 290+height, (screen_width+100)/2 + width4/2, 350+height);

    a_field = {(screen_width-100)/2 + width4/2, 290+height, (screen_width+100)/2 + width4/2, 350+height};

    //Partea cu introducerea valorii lui a
    int width5 = textwidth("b= ");
    height += textheight("b= ");
    outtextxy((screen_width-100 - width5)/2, 350+height, "b= ");
    rectangle((screen_width-100)/2 + width5/2, 340+height, (screen_width+100)/2 + width5/2, 400+height);

    b_field = {(screen_width-100)/2 + width5/2, 340+height, (screen_width+100)/2 + width5/2, 400+height};

    //Butonul de desenare
    setfillstyle(SOLID_FILL, 4);
    bar((screen_width-150)/2, 450+height, (screen_width+150)/2, 500+height);

    button_field = {(screen_width-150)/2, 450+height, (screen_width+150)/2, 500+height};

    setbkcolor(4);
    setcolor(15);
    settextstyle(3, 0, 2);
    int width6 = textwidth("Deseneaza");
    outtextxy((screen_width-width6)/2, 460+height, "Deseneaza");

    setbkcolor(15);
}

bool is_field_pressed(coordinates_field field, int x, int y)
{
    if(x > field.x1 && x < field.x2 && y > field.y1 && y < field.y2)
        return true;
    return false;
}

void read_pageII(Functie& f)
{
    char c;
    char a[4] = " ";
    char b[4] = " ";
    int i_func = 0;
    int i_a = 0;
    int i_b = 0;

    int x;
    int y;

    bool func_pressed = false;
    bool a_pressed = false;
    bool b_pressed = false;

    coordinates_field functie, a_field, b_field, button_field;

    draw_pageII(functie, a_field, b_field, button_field);

    int page = 1;
    bool d = false;

    while(true)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if(is_field_pressed(functie, x, y))
            {
                func_pressed = true;
                a_pressed = false;
                b_pressed = false;
            }
            else if(is_field_pressed(a_field, x, y))
            {
                func_pressed = false;
                a_pressed = true;
                b_pressed = false;
            }
            else if(is_field_pressed(b_field, x, y))
            {
                func_pressed = false;
                a_pressed = false;
                b_pressed = true;
            }
            else if(is_field_pressed(button_field, x, y))
            {
                int ai;
                int bi;
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
                break;
            }
            else
            {
                func_pressed = false;
                a_pressed = false;
                b_pressed = false;
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
                            f.Expresie[i_func-1] = '\0';
                            --i_func;
                            d = true;
                        }
                    }
                    else
                    {
                        if(i_func < 25)
                        {
                            f.Expresie[i_func] = c;
                            ++i_func;
                            d = true;

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
                        if(i_a < 3)
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
                        if(i_b < 3)
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
                setvisualpage(1-page);
                page = 1-page;

                draw_pageII(functie, a_field, b_field, button_field);

                setcolor(4);
                settextstyle(3, 0, 5);
                outtextxy( functie.x1 + 5, functie.y1 + 10, func);
                outtextxy( a_field.x1 + 5, a_field.y1 + 10, a);
                outtextxy( b_field.x1 + 5, b_field.y1 + 10, b);

                setactivepage(page);
                setvisualpage(1-page);
                page = 1-page;
                d = false;
            }
            if(!(func_pressed || a_pressed || b_pressed))
                if(kbhit())
                    c = getch();
    }
}
