
#include "pi.h"

void InitPI(tPIParm *pParm)
{
    pParm->qdSum = 0;
    pParm->qOut = 0;
}

void CalcPI( tPIParm *pParm)
{
 /*   
    ;void CalcPI( tPIParm *pParm)
;{
;    Err  = InRef - InMeas
;    U  = Sum + Kp * Err
;    if( U > Outmax )
;        Out = Outmax
;    else if( U < Outmin )
;        Out = Outmin
;    else        
;        Out = U 
;    Exc = U - Out
;    Sum = Sum + Ki * Err - Kc * Exc
;}
;
*/
	int16_t currentError;
    int32_t U;
    int16_t outTemp;
    
    currentError = pParm->qInRef - pParm->qInMeas;
    
    
    if(currentError > 255)
        currentError = 255;

    if(currentError < -255)
        currentError = -255;
    
    
    U = (currentError * pParm->qKp)<<4;
    U = U + pParm->qdSum;
    
    outTemp = (int)(U>>15);
	if(outTemp >  pParm->qOutMax)
		pParm->qOut=  pParm->qOutMax;
	else if(outTemp < pParm->qOutMin)
		pParm->qOut =  pParm->qOutMin;
	else
		pParm->qOut = outTemp;
		
	U = (currentError * pParm->qKi);
	
	currentError = outTemp - pParm->qOut;
	U -= (currentError *  pParm->qKc);

	pParm->qdSum = pParm->qdSum + U;
}


 void CalcPI_ang( tPIParm *pParm)
{
 /*   
    ;void CalcPI( tPIParm *pParm)
;{
;    Err  = InRef - InMeas
;    U  = Sum + Kp * Err
;    if( U > Outmax )
;        Out = Outmax
;    else if( U < Outmin )
;        Out = Outmin
;    else        
;        Out = U 
;    Exc = U - Out
;    Sum = Sum + Ki * Err - Kc * Exc
;}
;
*/
	int16_t currentError;
    int32_t U;
    int16_t outTemp;
    
    currentError = pParm->qInRef - pParm->qInMeas;
    
    /*
        if(currentError > 255)
        currentError = 255;
    
     if(currentError < -255)
        currentError = -255;
    */
    
    U = (currentError * pParm->qKp)<<4;
    U = U + pParm->qdSum;
    
    outTemp = (int)(U>>15);
	if(outTemp >  pParm->qOutMax)
		pParm->qOut=  pParm->qOutMax;
	else if(outTemp < pParm->qOutMin)
		pParm->qOut =  pParm->qOutMin;
	else
		pParm->qOut = outTemp;
		
	U = (currentError * pParm->qKi);
	
	currentError = outTemp - pParm->qOut;
	U -= (currentError *  pParm->qKc);

	pParm->qdSum = pParm->qdSum + U;
}


