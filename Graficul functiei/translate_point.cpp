#include "structs.h"


Point translate(Point p, Graph g)
{
    Point res;
    res.x = (p.x - g.x1) / (g.x2 - g.x1) * (g.screen_x2 - g.screen_x1) + g.screen_x1;
    res.y = (p.y - g.y1) / (g.y2 - g.y1) * (g.screen_y2 - g.screen_y1) + g.screen_y1;
    return res;
};

Point translate_back(Point p, Graph g)
{
    Point res;
    res.x = (p.x - g.screen_x1) / (g.screen_x2 - g.screen_x1) * (g.x2 - g.x1) + g.x1;
    res.y = (p.y - g.screen_y1) / (g.screen_y2 - g.screen_y1) * (g.y2 - g.y1) + g.y1;
    return res;

}
