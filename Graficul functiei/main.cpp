#include "draw_function_graph.h"
#include "draw_graph_buttons.h"
#include "structs.h"
#include "read_function.h"
#include "interaction.h"
#include "start_page.h"
#include "read_function_pageII.h"
#include "working_with_files.h"

#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <windows.h>
#include <stdlib.h>
#include <cstring>
#include <math.h>
#include <unistd.h>
#include <MMsystem.h>

char path_dir[255] = "";

char language;

int screen_width;
int screen_height;

int color_graph, color_min, color_max, color_asym;

extern char a[100][100];///matrice de erori
extern int poz;

using namespace std;

int main()
{
    screen_width = GetSystemMetrics(SM_CXSCREEN);
    screen_height = GetSystemMetrics(SM_CYSCREEN)-65;

    initwindow(screen_width, screen_height, "Graphs of Functions");

    //pregatirea drumului spre imagini
    getcwd(path_dir, sizeof(path_dir));

    //setarea limbii
    char lan[2] = " ";
    read_file(lan, "language.txt");
    lan[1] = '\0';
    language = lan[0];

    if(!strchr("re", language))
    {
        language = 'r';
    }


    //culorile
    char s[100] = "";
    read_file(s, "color.txt");

    int i = 0;
    int nr;
    char* p = strtok(s , ".");
    while(p != NULL)
    {
        nr = atoi(p);
        if(i == 0)
            color_graph = nr;
        else if(i == 1)
            color_min = nr;
        else if(i == 2)
            color_max = nr;
        else if(i == 3)
            color_asym = nr;
        p = strtok(NULL , ".");
        ++i;
    }


    //coordonate graficului pe ecran
    Graph g;
    g.screen_x1 = 0;
    g.screen_x2 = screen_width;
    g.screen_y1 = 0;
    g.screen_y2 = screen_height;

    //                read_page  min    max  save graph
    is_pressed pressed = {true, false, false, false}; // pentru butoanele de pe grafic
    bool start_page = true;

    Point min_g, max_g;

    int page = 0;

    Functie F = {" "};

    char c = ' ';

    bool d = true;

    bool f_ok = true;

    while(true)
    {
        if(start_page)
        {
            read_start_page();
            start_page = false;
            pressed.read_page = true;
        }
        if(pressed.read_page)
        {
            pressed.read_page = false;
            read_pageII(F, start_page, f_ok);

            if(start_page)
                continue;

            Elimin_Spatii(F.Expresie);

            Cuvinte(F.Expresie);
            Adaugare_Vector(F);


            Codificare_Fct_Trigonometrice(F);

            Tip(F);

            poz=0;

            float x = 201.1;

            if(!Expresie_Corecta(F,x))
            {
                pressed.read_page = true;
                f_ok = false;
                continue;
            }

            //pregatire coordonate grafic
            g.x1 = F.a;
            g.x2 = F.b;

            float dif = (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);

            g.y1 = dif/2;
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);


            min_g.x = g.x1;
            min_g.y = Valoare_Functie(F, min_g.x);

            max_g.x = g.x1;
            max_g.y = Valoare_Functie(F, max_g.x);

            setactivepage(page);
            setvisualpage(1-page);
            page = 1-page;

            draw_graph(g, F, min_g, max_g);
            draw_min_max(g, min_g, max_g, pressed.min_d, pressed.max_d);
            draw_buttons(g, pressed, path_dir);

            setactivepage(page);
            setvisualpage(1-page);
            page = 1-page;

            d = true;
        }


        if(kbhit())
        {
            c = getch();
            if (handle_key(c, g))
                d = true;
        }

        handle_mouse(g, d, pressed);

        if(d)
        {

            draw_graph(g, F, min_g, max_g);
            draw_min_max(g, min_g, max_g, pressed.min_d, pressed.max_d);

            if(pressed.save_b)
            {
                writeimagefile();
                pressed.save_b = false;
            }

            draw_buttons(g, pressed, path_dir);

            setactivepage(1-page);
            setvisualpage(page);
            page = 1-page;

            d = false;
        }
    }
    closegraph(); return 0;
}
