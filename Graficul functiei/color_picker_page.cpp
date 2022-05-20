#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <stdio.h>

#include "structs.h"
#include "read_function_pageII.h"
#include "working_with_files.h"

extern int screen_width;
extern int screen_height;
extern char path_dir[];
extern char language;


bool graph_line_pressed, min_pressed, max_pressed, asym_pressed;

coordinates_field graph_field, min_field, max_field, asym_field, color_picker_field, save_field, bkbutton_field;

extern int color_graph, color_min, color_max, color_asym;


void draw_color_page()
{
    setbkcolor(15);
    cleardevice();

    char text[100] = " ";

    // background
    char bk_image[255] = "";
    strcpy(bk_image, path_dir);
    strcat(bk_image, "\\images\\bk2.gif");

    readimagefile( bk_image, -30, 0, screen_width + 60, screen_height);


    //imaginea cu color picker-ul
    char colormap_image[255] = "";
    strcpy(colormap_image, path_dir);
    strcat(colormap_image, "\\images\\img_colormap.gif");

    readimagefile(colormap_image, 160, 150, 760, 650);
    color_picker_field = {160, 150, 760, 650};


    //backbutton
    char backbutton_image[255] = "";
    strcpy(backbutton_image, path_dir);
    strcat(backbutton_image, "\\images\\backbutton.gif");

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

    bkbutton_field = {80, 110, 170, 180};



    // scris
    settextstyle(10, HORIZ_DIR, 5);
    settextjustify( 1, 2);
    setcolor(4);
    setbkcolor(15);

    if(language == 'r')
        strcpy(text, "Alege o culoare pentru:");
    else if(language == 'e')
        strcpy(text, "Choose a color for:");

    int height = textheight(text);
    outtextxy(1110, 150, text);


    //linia graficului
    setlinestyle(0, USERBIT_LINE, 1);
    settextjustify( 0, 2);
    settextstyle(10, HORIZ_DIR, 4);

    if(language == 'r')
        strcpy(text, "Linia graficului:");
    else if(language == 'e')
        strcpy(text, "Graph's line:");

    outtextxy(830, 200 + height, text);

    setfillstyle(1, COLOR(RED_VALUE(color_graph), GREEN_VALUE(color_graph), BLUE_VALUE(color_graph)));
    bar(1180, 190 + height, 1300, 240 + height);

    setcolor(0);
    if(graph_line_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);


    rectangle(1180, 190 + height, 1300, 240 + height);

    graph_field = {1180, 190 + height, 1300, 240 + height};

    height += textheight("Linia graficului:");


    //minim
    if(language == 'r')
        strcpy(text, "Minim:");
    else if(language == 'e')
        strcpy(text, "Minimum:");

    setcolor(4);
    outtextxy(830, 250 + height, text);

    setfillstyle(1, COLOR(RED_VALUE(color_min), GREEN_VALUE(color_min), BLUE_VALUE(color_min)));
    bar(1180, 240 + height, 1300, 290 + height);

    setcolor(0);
    if(min_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);

    rectangle(1180, 240 + height, 1300, 290 + height);

    min_field = {1180, 240 + height, 1300, 290 + height};

    height += textheight("Minim:");


    //maxim
    if(language == 'r')
        strcpy(text, "Maxim:");
    else if(language == 'e')
        strcpy(text, "Maximum:");

    setcolor(4);
    outtextxy(830, 300 + height, text);

    setfillstyle(1, COLOR(RED_VALUE(color_max), GREEN_VALUE(color_max), BLUE_VALUE(color_max)));
    bar(1180, 290 + height, 1300, 340 + height);

    setcolor(0);
    if(max_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);

    rectangle(1180, 290 + height, 1300, 340 + height);

    max_field = {1180, 290 + height, 1300, 340 + height};

    height += textheight("Maxim:");


    //asimptote
    if(language == 'r')
        strcpy(text, "Asimptote:");
    else if(language == 'e')
        strcpy(text, "Asymptotes:");

    setcolor(4);
    outtextxy(830, 350 + height, text);

    setfillstyle(1, COLOR(RED_VALUE(color_asym), GREEN_VALUE(color_asym), BLUE_VALUE(color_asym)));
    bar(1180, 340 + height, 1300, 390 + height);

    setcolor(0);
    if(asym_pressed)
        setlinestyle(0, USERBIT_LINE, 3);
    else
        setlinestyle(0, USERBIT_LINE, 1);

    rectangle(1180, 340 + height, 1300, 390 + height);

    asym_field = {1180, 340 + height, 1300, 390 + height};

    height += textheight("Asimptote:");


    // butonul de salvare
    setfillstyle(1, COLOR(127, 0, 0));
    settextstyle(10, HORIZ_DIR, 3);
    settextjustify( 1, 2);
    setcolor(15);
    setbkcolor(COLOR(127, 0, 0));

    if(language == 'r')
        strcpy(text, "Salveaza");
    else if(language == 'e')
        strcpy(text, "Save");

    bar(1045, 420 + height, 1175, 460 + height);
    outtextxy(1110, 425 + height, text);

    save_field = {1045, 420 + height, 1175, 460 + height};

}

void read_color_page()
{
    int x, y;

    bool d = true;

    graph_line_pressed = false;
    min_pressed = false;
    max_pressed = false;
    asym_pressed = false;

    int pixel = 15; // 15 este culoarea interzisa

    int page = 3;

    setactivepage(page);
    setvisualpage(page);
    page = (page == 3? 4 : 3);

    draw_color_page();

    setactivepage(page);
    setvisualpage(page == 3? 4 : 3);
    page = (page == 3? 4 : 3);


    while(true)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if(is_field_pressed(color_picker_field, x, y))
            {
                setactivepage(page);
                setvisualpage(page == 3? 4 : 3);
                page = page == 3? 4 : 3;

                pixel = getpixel(x, y);

                setactivepage(page);
                setvisualpage(page == 3? 4 : 3);
                page = page == 3? 4 : 3;

                if(pixel != 15)
                {
                    if(graph_line_pressed)
                        color_graph = pixel;
                    else if(min_pressed)
                        color_min = pixel;
                    else if(max_pressed)
                        color_max = pixel;
                    else if(asym_pressed)
                        color_asym = pixel;

                    d = true;
                }
            }
            else if(is_field_pressed(graph_field, x, y))
            {
                graph_line_pressed = true;
                min_pressed = false;
                max_pressed = false;
                asym_pressed = false;
                d = true;
            }
            else if(is_field_pressed(min_field, x, y))
            {
                graph_line_pressed = false;
                min_pressed = true;
                max_pressed = false;
                asym_pressed = false;
                d = true;
            }
            else if(is_field_pressed(max_field, x, y))
            {
                graph_line_pressed = false;
                min_pressed = false;
                max_pressed = true;
                asym_pressed = false;
                d = true;
            }
            else if(is_field_pressed(asym_field, x, y))
            {
                graph_line_pressed = false;
                min_pressed = false;
                max_pressed = false;
                asym_pressed = true;
                d = true;
            }
            else if(is_field_pressed(save_field, x, y))
            {
                char str[100] = "";
                char tr[10] = " ";

                gcvt(color_graph, 10, tr);
                strcat(str,tr);

                gcvt(color_min, 10, tr);
                strcat(str,tr);

                gcvt(color_max, 10, tr);
                strcat(str,tr);

                gcvt(color_asym, 10, tr);
                strcat(str,tr);

                write_file(str, "color.txt");
            }
            else if(!is_field_pressed(color_picker_field, x, y))
            {
                graph_line_pressed = false;
                min_pressed = false;
                max_pressed = false;
                asym_pressed = false;
                d = true;
            }
            if(is_field_pressed(bkbutton_field, x, y))
            {
                break;
            }
        }
        if(d)
        {
            setactivepage(page);
            setvisualpage(page == 3? 4 : 3);
            page = page == 3? 4 : 3;

            draw_color_page();

            setactivepage(page);
            setvisualpage(page == 3? 4 : 3);
            page = page == 3? 4 : 3;

            d = false;
        }
    }
}
