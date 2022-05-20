#include "translate_point.h"
#include "draw_graph_buttons.h"

#include "structs.h"
#include <graphics.h>
#include <winbgim.h>


bool handle_key(char c, Graph &g)
{
    switch(c)
    {
        case 'z':
            if(g.x1 + 3 < g.x2)
            {
                g.x1 += 0.5;
                g.x2 -= 0.5;
                g.y1 -= 0.25;
                g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
                return true;
            }
            return false;
        case 'u':
            if((g.x2 - g.x1) <= 250 && g.x2 <= 200 && g.x1 >= -200 && g.y1 <= 150 && g.y2 >= -150)
            {
                g.x1 -= 0.5;
                g.x2 += 0.5;
                g.y1 += 0.25;
                g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
                return true;
            }
            return false;
        case 'd':
            if(g.x2 <= 200)
            {
                g.x1 += 0.5;
                g.x2 += 0.5;
                return true;
            }
            return false;
        case 'a':
            if(g.x1 >= -200)
            {
                g.x1 -= 0.5;
                g.x2 -= 0.5;
                return true;
            }
            return false;
        case 'w':
            if(g.y1 <= 150)
            {
                g.y1 += 0.5;
                g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
                return true;
            }
            return false;
        case 's':
            if(g.y2 >= -150)
            {
                g.y1 -= 0.5;
                g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
                return true;
            }
            return false;
        default:
            return false;
    }

}

void handle_mouse(Graph& g, bool& d, is_pressed& is_pressed)
{
    float precizie = 100;
    static int prevx, prevy, curx, cury;
    static bool isup = true, pressed = false;

    if(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN, prevx, prevy);
        isup = false;
        pressed = is_button_pressed(g, prevx, prevy, d, is_pressed); //din draw_graph_buttons
    }
    if(ismouseclick(WM_LBUTTONUP))
    {
        isup = true;
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_LBUTTONUP);
    }
    if(!isup && !pressed) // daca nu este nici un buton apasat si butonul din stanga nu este apasat
    {
        curx = mousex();
        cury = mousey();

        Point current;
        current.x = curx * precizie; // imultim cu precizia, deoarece cand traduceam aveam probleme
        current.y = cury * precizie;
        current = translate_back(current, g);

        Point previous;
        previous.x = prevx * precizie;
        previous.y = prevy * precizie;
        previous = translate_back(previous, g);


        float diffx=current.x-previous.x, diffy=current.y-previous.y;

        if(diffx > 0 && g.x1 >= -200)
        {
            if(g.x1 - diffx/precizie < -200)
                diffx = (g.x1 + 200) * precizie; // calculam cat ne trebuie pana sa ajungem la limita care este -200
            d = true;
            g.x1 -= (diffx/precizie);
            g.x2 -= (diffx/precizie);
        }
        if(diffx < 0 && g.x2 <= 200)
        {
            if(g.x2 - diffx/precizie > 200)
                diffx = (g.x2 - 200) * precizie; // calculam cat ne trebuie pana sa ajungem la limita care este 200
            d = true;
            g.x1 -= (diffx/precizie);
            g.x2 -= (diffx/precizie);
        }
        if(diffy > 0 && g.y2 >= -150)
        {
            if(g.y2 - diffy/precizie < -150)
                diffy = (g.y2 + 150) * precizie; // calculam cat ne trebuie pana sa ajungem la limita care este -150
            d = true;
            g.y1 -= (diffy/precizie);
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
        }
        if(diffy < 0 && g.y1 <= 150)
        {
            if(g.y1 - diffy/precizie > 150)
                diffy = (g.y1 - 150) * precizie; // calculam cat ne trebuie pana sa ajungem la limita care este 150
            d = true;
            g.y1 -= (diffy/precizie);
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
        }
        prevx = curx;
        prevy = cury;
    }
}
