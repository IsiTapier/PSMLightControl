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
double logns(double base, double x) {
    return log(x) / log(base);
}
//double logn(double base, double x);

#endif