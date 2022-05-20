#include "structs.h"
#include <graphics.h>
#include <winbgim.h>


bool handle_key(char c, Graph &g)
{
    switch(c)
    {
        case 'z':
            g.x1 += 0.5;
            g.x2 -= 0.5;
            g.y1 -= 0.25;
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
            return true;
        case 'u':
            g.x1 -= 0.5;
            g.x2 += 0.5;
            g.y1 += 0.25;
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
            return true;
        case 'd':
            g.x1 += 0.5;
            g.x2 += 0.5;
            return true;
        case 'a':
            g.x1 -= 0.5;
            g.x2 -= 0.5;
            return true;
        case 'w':
            g.y1 += 0.5;
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
            return true;
        case 's':
            g.y1 -= 0.5;
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
            return true;
        case 'p':
            writeimagefile();
        default:
            return false;
    }

}

void handle_mouse(Graph& g, bool& d, int& prevx,int& prevy,int& curx,int& cury, bool& isup)
{
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        getmouseclick(WM_LBUTTONDOWN, prevx, prevy);
        isup = false;
    }
    if(ismouseclick(WM_LBUTTONUP))
    {
        isup = true;
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_LBUTTONUP);
    }
    if(!isup)
    {
        curx = mousex();
        cury = mousey();

        Point current;
        current.x = curx * 100;
        current.y = cury * 100;
        current = translate_back(current, g);

        Point previous;
        previous.x = prevx * 100;
        previous.y = prevy * 100;
        previous = translate_back(previous, g);

        //cout << "Previous: "<< prevx << ' ' << prevy << " Current: " << curx << ' ' << cury << '\n';

        int diffx=current.x-previous.x, diffy=current.y-previous.y;

        //cout << diffx << " " << diffy << "\n";

        if(diffx>0)
        {
            d = true;
            g.x1 -= (0.01*diffx);
            g.x2 -= (0.01*diffx);
        }
        if(diffx<0)
        {
            d = true;
            g.x1 -= (0.01*diffx);
            g.x2 -= (0.01*diffx);
        }
        if(diffy>0)
        {
            d = true;
            g.y1 -= (0.01*diffy);
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
        }
        if(diffy<0)
        {
            d = true;
            g.y1 -= (0.01*diffy);
            g.y2 = g.y1 - (g.x2 - g.x1)*(g.screen_y2 - g.screen_y1)/(g.screen_x2 - g.screen_x1);
        }
        prevx = curx;
        prevy = cury;
    }
}
