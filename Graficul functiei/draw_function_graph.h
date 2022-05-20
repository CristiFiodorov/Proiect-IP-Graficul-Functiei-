#ifndef DRAW_GRAPH_H_INCLUDED
#define DRAW_GRAPH_H_INCLUDED

#include "structs.h"

void draw_graph(Graph g, Functie F, Point& min_g, Point& max_g);
void draw_min_max(const Graph& g,Point min_g, Point max_g, bool draw_min, bool draw_max);

#endif // DRAW_GRAPH_H_INCLUDED
