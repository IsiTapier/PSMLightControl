/*
  Util.h - Util-Library for Airduino.
*/

#ifndef Util_h
#define Util_h

#include "debug/_Debug.h"
#include "statistics/Statistics.h"
#include "templates/Templates.h"
#include "timeCode/TimeCode.h"
// #include "math/Math.h"
#include "macros/Macros.h"

/**************************************************************************/
/*!
    @brief              log() to certain base --
                        calculates log(x) to the base n
    @param  base        the base of log()
    @param  x           the x value of which to calculate the logn()
    @returns            logn(x)
*/
/**************************************************************************/
double logn(double base, double x);

#endif