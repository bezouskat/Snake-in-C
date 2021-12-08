#ifndef POINT_H
#define POINT_H

#include <stdbool.h>

typedef struct
{
    int x;
    int y;
} point;

bool equal(point a, point b);

#endif // POINT_H
