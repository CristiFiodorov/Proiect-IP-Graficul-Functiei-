#include "structs.h"
#include "read_function.h"
#include "translate_point.h"
#include "define.h"

#include <graphics.h>
#include <winbgim.h>
#include <iostream>
#include <stdio.h>
#include <math.h>

extern bool draw_asymptotes;
extern bool d_asy;
extern char language;
extern int color_graph, color_min, color_max, color_asym;

void draw_axis(Graph g)
{
    setlinestyle(0, USERBIT_LINE, 1);

    Point orig;
    orig.x = 0;
    orig.y = 0;
    orig = translate(orig, g);

    if(orig.x > g.screen_x1 && orig.x < g.screen_x2)
        line(orig.x, g.screen_y2, orig.x, g.screen_y1);

    if(orig.y > g.screen_y1 && orig.y < g.screen_y2)
        line(g.screen_x1, orig.y, g.screen_x2, orig.y);

    Point bars;
    setfillstyle(1, 0);
    settextjustify( 1, 2);

    char str[20];

    if(orig.y > g.screen_y1 && orig.y < g.screen_y2)
    {
        for (int i = g.x1; i < g.x2; ++i)
        {
            bars.x = i;
            bars.y = 0;
            if(bars.x != 0)
            {
                if( (abs(g.x1-g.x2) < 30) ||(abs(g.x1-g.x2) >= 30 && abs(g.x1-g.x2) < 100 && i%5 == 0) || (abs(g.x1-g.x2) >= 100 && i%10 == 0))
                {

                bars = translate(bars, g);
                bar(bars.x - 1, orig.y + 6, bars.x + 1, orig.y - 6);

                ltoa(i,str,10);
                outtextxy(bars.x, orig.y + 10, str);
                }
            }
        }
    }


    if(orig.x > g.screen_x1 && orig.x < g.screen_x2)
    {
        for (int i = g.y2; i < g.y1; ++i)
        {
            bars.x = 0;
            bars.y = i;
            if(bars.y != 0)
            {
                if( (abs(g.x1-g.x2) < 30) ||(abs(g.x1-g.x2) >= 30 && abs(g.x1-g.x2) < 100 && i%5 == 0) || (abs(g.x1-g.x2) >= 100 && i%10 == 0))
                {
                bars = translate(bars, g);
                bar(orig.x - 6, bars.y + 1, orig.x + 6, bars.y - 1);

                ltoa(i,str,10);
                outtextxy(orig.x - 20, bars.y - 8, str);
                }
            }
        }
    }
}

void draw_graph(Graph g, Functie F, Point& min_g, Point& max_g)
{
    setbkcolor(15);
    cleardevice();

    settextstyle(0, HORIZ_DIR, 2);

    setcolor(0);
    draw_axis(g);

    Point p1, p2;
    p1.x = g.x1;
    p1.y = Valoare_Functie(F,p1.x);

    float diff_puncte = 0.05;


    d_asy = false;

    for(int i=0; i < F.lung_v; ++i)
    {
        if(strcmp(F.v[i],"btg")==0 || strcmp(F.v[i],"tg")==0 || F.v[i][0]=='/' || strcmp(F.v[i],"ln")==0)
        {
            d_asy = true;
            diff_puncte = 0.005;
        }
        if(strcmp(F.v[i],"drcsin")==0 || strcmp(F.v[i],"frccos")==0)
        {
            diff_puncte = 0.005;
        }
    }

    //min - max

    static bool alege_min = true, alege_max = true;

    if(min_g.x < g.x1 || min_g.x > g.x2 ||(min_g.y < g.y2 || min_g.y > g.y1) || isnan(min_g.y))
    {
        if(min_g.y < g.y2 || min_g.y > g.y1 || isnan(min_g.y))
        {
            min_g.x = g.x1;
            min_g.y = Valoare_Functie(F, min_g.x);
            while(min_g.y < g.y2 || min_g.y > g.y1 || isnan(min_g.y))
            {
                min_g.x += diff_puncte;
                min_g.y = Valoare_Functie(F, min_g.x);
                if(min_g.x > g.x2)
                    break;
            }
        }
        if(min_g.x < g.x1)
        {
            min_g.x = g.x1;
            min_g.y = Valoare_Functie(F, min_g.x);
            alege_min = true;
        }
        if(min_g.x > g.x2)
        {
            min_g.x = g.x2;
            min_g.y = Valoare_Functie(F, min_g.x);
            alege_min = true;
        }
    }


    if(max_g.x < g.x1 || max_g.x > g.x2 || (max_g.y < g.y2 || max_g.y > g.y1) || isnan(max_g.y))
    {
        if(max_g.y < g.y2 || max_g.y > g.y1 || isnan(max_g.y))
        {
            max_g.x = g.x1;
            max_g.y = Valoare_Functie(F, max_g.x);
            while(max_g.y < g.y2 || max_g.y > g.y1 || isnan(max_g.y))
            {
                max_g.x += diff_puncte;
                max_g.y = Valoare_Functie(F, max_g.x);
                if(max_g.x > g.x2)
                    break;
            }
        }
        if(max_g.x < g.x1)
        {
            max_g.x = g.x1;
            max_g.y = Valoare_Functie(F, max_g.x);
            alege_max = true;
        }
        if(max_g.x > g.x2)
        {
            max_g.x = g.x2;
            max_g.y = Valoare_Functie(F, max_g.x);
            alege_max = true;
        }
    }

    Point p1t, p2t;

    setlinestyle(0, USERBIT_LINE, 3);
    setcolor(COLOR(RED_VALUE(color_graph), GREEN_VALUE(color_graph), BLUE_VALUE(color_graph)));

    while(p1.x <= g.x2)
        {
        p2.x = p1.x;
        p2.y = p1.y;
        p1.x += diff_puncte;
        p1.y = Valoare_Functie(F,p1.x);

        p1t = translate(p1, g);
        p2t = translate(p2, g);

        if(p1.y > g.y2 && p1.y < g.y1)
        {
            if(min_g.y > p1.y)
            {
                min_g = p1;
            }
            else if(min_g.y == p1.y && alege_min)
            {
                min_g = p1;
                alege_min = false;
            }
            if(max_g.y < p1.y)
            {
                max_g = p1;
            }
            else if(max_g.y == p1.y && alege_max)
            {
                max_g = p1;
                alege_max = false;
            }
        }

            if(p1.y < g.y1 + 200 && p1.y > g.y2 - 200)
            {
                if(p1.y > g.y1)
                {
                    p1.y = g.y1 + 10;
                }

                if(p1.y < g.y2)
                {
                    p1.y = g.y2 - 10;
                }

                if(abs(p1.y - p2.y) < 200)
                    line(int(p1t.x), int(p1t.y), int(p2t.x), int(p2t.y));
                else if (draw_asymptotes && d_asy)
                {
                    setcolor(COLOR(RED_VALUE(color_asym), GREEN_VALUE(color_asym), BLUE_VALUE(color_asym)));
                    line(p1t.x - 2 , g.screen_y2, p1t.x - 2, g.screen_y1);
                    setcolor(COLOR(RED_VALUE(color_graph), GREEN_VALUE(color_graph), BLUE_VALUE(color_graph)));
                }
            }
        }

        //std::cout << min_g.y << " " << max_g.y << '\n';

    setcolor(0);
    setlinestyle(0, USERBIT_LINE, 1);
}

void draw_min_max(const Graph& g,Point min_g, Point max_g, bool draw_min, bool draw_max)
{
    setlinestyle(0, USERBIT_LINE, 3);
    settextjustify(LEFT_TEXT, TOP_TEXT);

    if(abs(min_g.y) < 0.1)
        min_g.y = 0;

    if(abs(max_g.y) < 0.1)
        max_g.y = 0;


    char str[15] = {""};

    // maxim
    char maxim[30];

    if(language == 'r')
        strcpy(maxim, "Maxim: ");
    else if(language == 'e')
        strcpy(maxim, "Maximum: ");

    if(max_g.y >= g.y2 && max_g.y <= g.y1)
    {
        gcvt(max_g.y, 7, str);
        strcat(maxim, str);
    }
    else
        strcat(maxim, "NAN");

    outtextxy(g.screen_x2 - 260, g.screen_y1 + 20, maxim);


    //minim
    char minim[30] = {"Minim: "};

    if(language == 'r')
        strcpy(minim, "Minim: ");
    else if(language == 'e')
        strcpy(minim, "Minimum: ");

    if(min_g.y >= g.y2 && min_g.y <= g.y1)
    {
        gcvt(min_g.y, 7, str);
        strcat(minim, str);
    }
    else
        strcat(minim, "NAN");

    outtextxy(g.screen_x2 - 260, g.screen_y1 + 50, minim);

    // desenare minim si maxim
    min_g = translate(min_g, g);
    max_g = translate(max_g, g);

    setcolor(COLOR(RED_VALUE(color_min), GREEN_VALUE(color_min), BLUE_VALUE(color_min)));
    if(draw_min && !isnan(min_g.y))
        circle(min_g.x, min_g.y , 20);

    setcolor(COLOR(RED_VALUE(color_max), GREEN_VALUE(color_max), BLUE_VALUE(color_max)));
    if(draw_max && !isnan(max_g.y))
        circle(max_g.x, max_g.y, 20);
}
