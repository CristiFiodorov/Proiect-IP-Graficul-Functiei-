#include <graphics.h>
#include <winbgim.h>
#include <windows.h>
#include <string.h>

#include "structs.h"
#include "read_function_pageII.h"
#include "working_with_files.h"
#include "color_picker_page.h"

extern char path_dir[255];
extern int screen_width;
extern int screen_height;

extern char language;

coordinates_field start_field, about_field, settings_field, back_field, flag_field, music_field;

bool music_on = false;

void draw_start_page()
{
    int middle_width = screen_width/2;

    setbkcolor(15);
    cleardevice();
    setcolor(4);
    setlinestyle(0, USERBIT_LINE, 1);

    //backgroud image
    char bk_image[255] = "";
    strcpy(bk_image, path_dir);
    strcat(bk_image, "\\images\\bk2.gif");

    readimagefile( bk_image, -30, 0, screen_width + 60, screen_height);

    //logo image
    char logo_image[255] = "";
    strcpy(logo_image, path_dir);

    if(language == 'r')
        strcat(logo_image, "\\images\\logo.gif");
    else if(language == 'e')
        strcat(logo_image, "\\images\\logo_eng.gif");

    readimagefile( logo_image, middle_width - 360, 110, middle_width + 360, 240);


    //language
    char flag_image[255] = "";
    strcpy(flag_image, path_dir);

    if(language == 'r')
        strcat(flag_image, "\\images\\romanian_flag.gif");
    else if(language == 'e')
        strcat(flag_image, "\\images\\british_flag.gif");

    setcolor(1);
    readimagefile(flag_image, screen_width - 180, 110, screen_width - 100, 150);
    rectangle(screen_width - 180, 110, screen_width - 100, 150);

    flag_field = {screen_width - 180, 110, screen_width - 100, 150};


    // music icon

    char sound_image[255] = "";
    strcpy(sound_image, path_dir);

    if(music_on)
        strcat(sound_image, "\\images\\volume.gif");
    else if(!music_on)
        strcat(sound_image, "\\images\\mute.gif");

    readimagefile(sound_image, 150, 110, 200, 160);

    music_field = {150, 110, 200, 160};


    setbkcolor(4);
    setcolor(15);
    settextstyle(10, 0, 6);
    setfillstyle(SOLID_FILL, 4);
    settextjustify( LEFT_TEXT, TOP_TEXT);

    char text[100] = " ";

    // butonul de incepere
    bar((screen_width-350)/2, 280, (screen_width+350)/2, 360);

    start_field = {(screen_width-350)/2, 280, (screen_width+350)/2, 360};

    if(language == 'r')
        strcpy(text, "Incepe");
    else if(language == 'e')
        strcpy(text, "Start");

    int width = textwidth(text);
    outtextxy((screen_width-width)/2, 290, text);


    // butonul despre
    bar((screen_width-350)/2, 400, (screen_width+350)/2, 480);

    settings_field = {(screen_width-350)/2, 400, (screen_width+350)/2, 480};

    if(language == 'r')
        strcpy(text, "Setari");
    else if(language == 'e')
        strcpy(text, "Settings");

    width = textwidth(text);
    outtextxy((screen_width-width)/2, 410, text);


    // butonul de setari
    bar((screen_width-350)/2, 520, (screen_width+350)/2, 600);

    about_field = {(screen_width-350)/2, 520, (screen_width+350)/2, 600};


    if(language == 'r')
        strcpy(text, "Despre");
    else if(language == 'e')
        strcpy(text, "About");

    width = textwidth(text);
    outtextxy((screen_width-width)/2, 530, text);

}

void draw_about_page()
{
    int middle_width = screen_width/2;

    setbkcolor(15);
    cleardevice();
    setcolor(4);

    //backgroud image
    char bk_image[255] = "";
    strcpy(bk_image, path_dir);
    strcat(bk_image, "\\images\\bk2.gif");

    readimagefile( bk_image, -30, 0, screen_width + 60, screen_height);

    //logo image
    char logo_image[255] = "";
    strcpy(logo_image, path_dir);
    strcat(logo_image, "\\images\\logo-fii.gif");

    if(language == 'r')
        readimagefile(logo_image, middle_width-55, 550, middle_width+45, 650);
    else if(language == 'e')
        readimagefile(logo_image, middle_width-70, 550, middle_width+30, 650);

    //about image
    char about_image[255] = "";
    strcpy(about_image, path_dir);

    if(language == 'r')
        strcat(about_image, "\\images\\about.gif");
    else if(language == 'e')
        strcat(about_image, "\\images\\about_eng.gif");

    readimagefile(about_image, middle_width - 450, 120, middle_width + 450, 530);


    //image character 1
    char ch1[255] = "";
    strcpy(ch1, path_dir);
    strcat(ch1, "\\images\\caracter1.gif");

    readimagefile(ch1, 250, 400, 370, 650);

    //image character 1
    char ch2[255] = "";
    strcpy(ch2, path_dir);
    strcat(ch2, "\\images\\caracter2.gif");

    readimagefile(ch2, screen_width - 370, 400, screen_width - 250, 650);


    //backbutton image
    char backbutton_image[255] = "";
    strcpy(backbutton_image, path_dir);
    strcat(backbutton_image, "\\images\\backbutton.gif");

    //backbutton
    setfillstyle(SOLID_FILL, 4);
    setbkcolor(4);
    settextstyle(3, HORIZ_DIR, 3);
    settextjustify( 1, 2);
    setcolor(15);

    readimagefile( backbutton_image, 80, 110, 170, 180);

    char text[100] = " ";

    if(language == 'r')
        strcpy(text, "Inapoi");
    else if(language == 'e')
        strcpy(text, "Back");

    outtextxy(135, 130, text);

    back_field = {80, 110, 170, 180};
}

void read_about_page()
{

    int ac_page = getactivepage();
    int vs_page = getvisualpage();

    setactivepage(vs_page);
    setvisualpage(ac_page);

    draw_about_page();

    setactivepage(ac_page);
    setvisualpage(vs_page);

    int x;
    int y;

    while(true)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if(is_field_pressed(back_field, x, y))
            {
                return;
            }
        }
    }


}

void read_start_page()
{
    //music
    char music_path[255] = "";
    strcpy(music_path, path_dir);
    strcat(music_path, "\\music\\music.wav");


    int ac_page = getactivepage();
    int vs_page = getvisualpage();

    setactivepage(vs_page);
    setvisualpage(ac_page);

    draw_start_page();

    setactivepage(ac_page);
    setvisualpage(vs_page);

    int x;
    int y;

    bool d = true;

    while(true)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if(is_field_pressed(start_field, x, y))
            {
                return;
            }
            else if(is_field_pressed(about_field, x, y))
            {
                read_about_page();
                d = true;
            }
            else if(is_field_pressed(settings_field, x, y))
            {
                read_color_page();
                d = true;
            }
            else if(is_field_pressed(music_field, x, y))
            {
                if(!music_on)
                {
                    PlaySound(TEXT(music_path), NULL, SND_LOOP | SND_ASYNC | SND_NODEFAULT);
                    music_on = true;
                }
                else
                {
                    PlaySound(NULL, 0, 0);
                    music_on = false;
                }
                d = true;
            }
            else if(is_field_pressed(flag_field, x, y))
            {
                if(language == 'r')
                {
                    language = 'e';
                    char l[] = "e";
                    write_file(l, "language.txt");
                }
                else if(language == 'e')
                {
                    language = 'r';
                    char l[] = "r";
                    write_file(l, "language.txt");
                }
                d = true;
            }
        }
        if(d)
        {
            setactivepage(vs_page);
            setvisualpage(ac_page);

            draw_start_page();

            setactivepage(ac_page);
            setvisualpage(vs_page);
            d = false;
        }
    }
}
