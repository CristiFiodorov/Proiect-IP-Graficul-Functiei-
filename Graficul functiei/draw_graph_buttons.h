#ifndef GRAPH_BUTTONS_H_INCLUDED
#define GRAPH_BUTTONS_H_INCLUDED

#include "structs.h"

void draw_buttons(const Graph& g, is_pressed& is_pressed, char path_dir[]);
bool is_button_pressed(Graph& g, int x, int y, bool& d, is_pressed& is_pressed);


#endif // GRAPH_BUTTONS_H_INCLUDED
