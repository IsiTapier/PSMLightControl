/*
  Math.h - Math-Library for Airduino.
*/

#ifndef Maths_h
#define Maths_h

#include "cmath"

/**************************************************************************/
/*!
    @brief              log() to certain base --
                        calculates log(x) to the base n
    @param  base        the base of log()
    @param  x           the x value of which to calculate the logn()
    @returns            logn(x)
*/
/**************************************************************************/
// double logn(double base, double x);
double logn(double base, double x) {
    return log(x) / log(base);
}

#endif