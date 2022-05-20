#include <graphics.h>
#include <winbgim.h>
#include <windows.h>

#include <iostream>

#include "structs.h"
#include "read_function_pageII.h"
#include "draw_function_graph.h"

bool draw_asymptotes = false;
bool d_asy;

extern char language;

void draw_buttons(const Graph& g, is_pressed& is_pressed, char path_dir[])
{
    char text[100] = " ";

    setfillstyle(SOLID_FILL, 4);
    setbkcolor(4);
    settextstyle(3, HORIZ_DIR, 3);
    settextjustify( 1, 2);
    setcolor(15);

    char backbutton[255] = "";
    strcpy(backbutton, path_dir);
    strcat(backbutton, "\\images\\backbutton.gif");


    if(language == 'r')
        strcpy(text, "Inapoi");
    else if(language == 'e')
        strcpy(text, "Back");

    readimagefile( backbutton, g.screen_x1 + 10, g.screen_y1 + 5, g.screen_x1 + 100, g.screen_y1 + 75);
    //bar(g.screen_x1 + 20, g.screen_y1 + 20, g.screen_x1 + 100, g.screen_y1 + 60);
    outtextxy(g.screen_x1 + 65, 25, text);

    if(language == 'r')
        strcpy(text, "Salveaza");
    else if(language == 'e')
        strcpy(text, "Save");

    bar(g.screen_x1 + 120, g.screen_y1 + 20, g.screen_x1 + 220, g.screen_y1 + 60);
    outtextxy(g.screen_x1 + 170, 25, text);

    settextstyle(10, HORIZ_DIR, 5);
    bar(g.screen_x2 - 150, g.screen_y2 - 80, g.screen_x2 - 108, g.screen_y2 - 38);
    outtextxy(g.screen_x2 - 129, g.screen_y2 - 79, "+");


    bar(g.screen_x2 - 90, g.screen_y2 - 80, g.screen_x2 - 48, g.screen_y2 - 38);
    outtextxy(g.screen_x2 - 69, g.screen_y2 - 79, "-");

    settextstyle(10, HORIZ_DIR, 3);

    if(is_pressed.min_d)
    {
        setfillstyle(SOLID_FILL, COLOR(255, 0, 0));
        setbkcolor(COLOR(255, 0, 0));
    }
    else
    {
        setfillstyle(SOLID_FILL, 4);
        setbkcolor(4);
    }

    bar(g.screen_x1 + 20, g.screen_y2 - 80, g.screen_x1 + 80, g.screen_y2 - 40);
    outtextxy(g.screen_x1 + 50, g.screen_y2 - 75, "MIN");

    if(is_pressed.max_d)
    {
        setfillstyle(SOLID_FILL, COLOR(255, 0, 0));
        setbkcolor(COLOR(255, 0, 0));
    }
    else
    {
        setfillstyle(SOLID_FILL, 4);
        setbkcolor(4);
    }

    bar(g.screen_x1 + 100, g.screen_y2 - 80, g.screen_x1 + 160, g.screen_y2 - 40);
    outtextxy(g.screen_x1 + 130, g.screen_y2 - 75, "MAX");

    if(d_asy)
    {
        if(draw_asymptotes)
        {
            setfillstyle(SOLID_FILL, COLOR(255, 0, 0));
            setbkcolor(COLOR(255, 0, 0));
        }
        else
        {
            setfillstyle(SOLID_FILL, 4);
            setbkcolor(4);
        }
    }
    else
    {
        setfillstyle(SOLID_FILL, COLOR( 153, 153, 153));
        setbkcolor(COLOR( 153, 153, 153));
    }

    if(language == 'r')
        strcpy(text, "ASIMPTOTE");
    else if(language == 'e')
        strcpy(text, "ASYMPTOTES");

    bar(g.screen_x1 + 180, g.screen_y2 - 80, g.screen_x1 + 340, g.screen_y2 - 40);
    outtextxy(g.screen_x1 + 260, g.screen_y2 - 75, text);

}

bool is_button_pressed(Graph& g, int x, int y, bool& d, is_pressed& is_pressed)
{
    static coordinates_field back_button = {g.screen_x1 + 10, g.screen_y1 + 5, g.screen_x1 + 100, g.screen_y1 + 75};
    static coordinates_field save_button = {g.screen_x1 + 120, g.screen_y1 + 20, g.screen_x1 + 220, g.screen_y1 + 60};
    static coordinates_field zoom = {g.screen_x2 - 150, g.screen_y2 - 80, g.screen_x2 - 108, g.screen_y2 - 38};
    static coordinates_field unzoom = {g.screen_x2 - 90, g.screen_y2 - 80, g.screen_x2 - 48, g.screen_y2 - 38};
    static coordinates_field min_field = {g.screen_x1 + 20, g.screen_y2 - 80, g.screen_x1 + 80, g.screen_y2 - 40};
    static coordinates_field max_field = {g.screen_x1 + 100, g.screen_y2 - 80, g.screen_x1 + 160, g.screen_y2 - 40};
    static coordinates_field asymptote_field = {g.screen_x1 + 180, g.screen_y2 - 80, g.screen_x1 + 340, g.screen_y2 - 40};

    if(is_field_pressed(back_button, x, y))
    {
        is_pressed.read_page = true;
        is_pressed.max_d = false;
        is_pressed.min_d = false;
        draw_asymptotes = false;
    }
    if(is_field_pressed(save_button, x, y))
    {
        is_pressed.save_b = true;
        d = true;
    }
    else if(is_field_pressed(zoom, x, y))
    {
        if(g.x1 + 3 < g.x2)
        {
            float n = ((g.x2 - g.x1) >= 30? ((g.x2 - g.x1) >= 60? 5 : 2 ): 1);
            g.x1 += n;
            g.x2 -= n;

            g.y1 -= n/2;
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
            d = true;
        }
        return true;
    }
    else if(is_field_pressed(unzoom, x, y))
    {
        if((g.x2 - g.x1) <= 250 && g.x2 <= 200 && g.x1 >= -200 && g.y1 <= 150 && g.y2 >= -150)
        {
            float n = ((g.x2 - g.x1) >= 30? ((g.x2 - g.x1) >= 60? 5 : 2 ): 1);
            g.x1 -= n;
            g.x2 += n;

            g.y1 += n/2;
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
            d = true;
        }
        return true;
    }
    else if(is_field_pressed(min_field, x, y))
    {
        if(!is_pressed.min_d)
            is_pressed.min_d = true;
        else
            is_pressed.min_d = false;
        d = true;
        return true;
    }
    else if(is_field_pressed(max_field, x, y))
    {
        if(!is_pressed.max_d)
            is_pressed.max_d = true;
        else
            is_pressed.max_d = false;
        d = true;
        return true;
    }
    else if(is_field_pressed(asymptote_field, x, y))
    {
        if(!draw_asymptotes)
            draw_asymptotes = true;
        else
            draw_asymptotes = false;
        d = true;
        return true;
    }
}
