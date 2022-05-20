#ifndef READ_FUNCTION_PAGE_H_INCLUDED
#define READ_FUNCTION_PAGE_H_INCLUDED

#include "structs.h"

void read_pageII(Functie& f, bool& start_page, bool& f_ok);
bool is_field_pressed(coordinates_field field, int x, int y);

#endif // READ_FUNCTION_PAGE_H_INCLUDED
