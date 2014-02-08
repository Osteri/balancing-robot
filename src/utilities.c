#include "utilities.h"

#include <stdio.h>
#include <string.h>

/**
 * @brief Convert double value to corresponding char array.
 *
 * Size of the buf defines how many digits we are converting from double
 * to char array (buf). If the buf size is 6, then M_PI becomes "3.141".
 * If the buf size is 4, then M_PI becomes "3.1" and so on.
 *
 * @param num Double value being converted to char array.
 *
 * @returns Pointer to converted char array.
 *
 * @example char* buf[6] = Double2Chars(M_PI); // buf is now "3.141"
 *
 * @author Oskari Teeri
 * @date 26.1.2014
 **/
char* Double2Chars(double num) {

    uint8_t size_of_buf = sizeof(buf) / sizeof(char);

    memset(buf, ' ', size_of_buf); // empty string
    snprintf(buf, size_of_buf, "%f", num);
    return buf;
}

/**
 * @brief Limit value between min and max.
 *
 * @param min Smallest possible output value.
 * @param value Input value.
 * @param max Greatest possible output value.
 *
 * @returns Value limited between min and max.
 *
 * @example int a = LimitValueBetween(-3, 0, 100); // returns 0
 *
 * @author Oskari Teeri
 * @date 1.2.2014
 **/

int LimitValueBetween(int value, int min, int max) {
    (value < min) ? value = min : value;
    (value > max) ? value = max : value;
    return value;
}
