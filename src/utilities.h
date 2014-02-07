#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>

static char buf[]="    "; // for Double2Chars conversion

char* Double2Chars(double num);
int LimitValueBetween(int value, int min, int max);

#endif

