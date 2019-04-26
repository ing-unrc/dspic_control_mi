#ifndef GENERAL_H
#define GENERAL_H


//--------------------- Common stuff for C routines ---------------------

//#include <p33Exxxx.h>
typedef unsigned short WORD;
typedef signed int SFRAC16;
typedef unsigned char  BYTE;
typedef unsigned char  bool;
#define False  0
#define True   1
#ifdef INITIALIZE
    // allocate storage
    #define EXTERN
#else
    #define EXTERN extern
#endif

#define Q15(Float_Value)	\
        ((Float_Value < 0.0) ? (SFRAC16)(32768 * (Float_Value) - 0.5) \
        : (SFRAC16)(32767 * (Float_Value) + 0.5))

signed int Q15SQRT(signed int);

#endif      // end of general_H
