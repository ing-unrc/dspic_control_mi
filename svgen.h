#ifndef SVGEN_H
#define SVGEN_H


typedef struct {
    short   iPWMPeriod;

    short   qVr1;
    short   qVr2;
    short   qVr3;

    } tSVGenParm;

extern tSVGenParm SVGenParm;    

//------------------  C ASVGen for SVGen routines ---------------------

void CalcRefVec( void );
void CalcSVGen( void );
void CorrectPhase( void );

EXTERN volatile int dPWM1Copy;
EXTERN volatile int dPWM2Copy;
EXTERN volatile int dPWM3Copy;

#endif



