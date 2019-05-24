
//version 5: 2019/02/05. Se ingresa con una Ed constante para el arranque, de forma de enganchar al PLL a una baja frecuencia 

#include "Estim.h"
#include "EstimDef.h"
#include "park.h"
#include "control.h"
#include "UserParms.h"
//#include <libq.h> /* q15 abs function use */

short int frec_arranque;
      
extern   tParkParm              ParkParm;
extern   tSincosParm    		SincosParm;
//extern   tCtrlParm              CtrlParm;

extern tPIParm     PIEst_rho;        //PI estimador
extern tPIParm     PIEst_rho; 
extern volatile short int ref_iq;

    long error;
    int32_t temp_int;
    int16_t signo = 1;
    int16_t tmpa, tmpb;
    int16_t qEsAbsPrev;
    
volatile  int16_t modo_acel = 0;    
    
    
extern  short int  etapa_arranque;    
    

void Estim(void)
{

    

    short int aux_abs_int;
    
    //*******************************
    // dIalpha = Ialpha-oldIalpha,  dIbeta  = Ibeta-oldIbeta
    // for lower speed the granularity of differnce is higher - the 
    // difference is made between 2 sampled values @ 8 ADC ISR cycles//
    

    aux_abs_int = abs_iq(EstimParm.qVelEstim);
    
//    if (aux_abs_int < NOMINAL_SPEED_RPM*NOPOLESPAIRS)
    //if (_Q15abs(EstimParm.qVelEstim)<NOMINAL_SPEED_RPM*NOPOLESPAIRS)
    if(1)
    { 
    
    	EstimParm.qDIalpha	=	(ParkParm.qIalpha-EstimParm.qLastIalphaHS[(EstimParm.qDiCounter-7)&0x0007]);
    	/* the current difference can exceed the maximum value per 8 ADC ISR cycle */
    	/* the following limitation assures a limitation per low speed - up to the nominal speed */
    	if (EstimParm.qDIalpha>EstimParm.qDIlimitLS) 
            EstimParm.qDIalpha=EstimParm.qDIlimitLS;
        
        if (EstimParm.qDIalpha<-EstimParm.qDIlimitLS) 
            EstimParm.qDIalpha=-EstimParm.qDIlimitLS;
        
        EstimParm.qVIndalpha = (int)((MotorEstimParm.qLsDt * EstimParm.qDIalpha)>>10);
        //EstimParm.qVIndalpha = (int)(__builtin_mulss(MotorEstimParm.qLsDt, EstimParm.qDIalpha)>>10);
     
    	EstimParm.qDIbeta	=	(ParkParm.qIbeta-EstimParm.qLastIbetaHS[(EstimParm.qDiCounter-7)&0x0007]);
    	/* the current difference can exceed the maximum value per 8 ADC ISR cycle */
    	/* the following limitation assures a limitation per low speed - up to the nominal speed */
    	if (EstimParm.qDIbeta>EstimParm.qDIlimitLS) 
            EstimParm.qDIbeta=EstimParm.qDIlimitLS;
        
        if (EstimParm.qDIbeta<-EstimParm.qDIlimitLS) 
            EstimParm.qDIbeta=-EstimParm.qDIlimitLS;
        
        EstimParm.qVIndbeta = (int)((MotorEstimParm.qLsDt * EstimParm.qDIbeta)>>10);
        //EstimParm.qVIndbeta = (int)(__builtin_mulss(MotorEstimParm.qLsDt, EstimParm.qDIbeta)>>10);
    
    }
     else
    {
    
    	EstimParm.qDIalpha	=	(ParkParm.qIalpha-EstimParm.qLastIalphaHS[(EstimParm.qDiCounter)]);
    	/* the current difference can exceed the maximum value per 1 ADC ISR cycle */
    	/* the following limitation assures a limitation per high speed - up to the maximum speed */
    	if (EstimParm.qDIalpha>EstimParm.qDIlimitHS) EstimParm.qDIalpha=EstimParm.qDIlimitHS;
            if (EstimParm.qDIalpha<-EstimParm.qDIlimitHS) EstimParm.qDIalpha=-EstimParm.qDIlimitHS;
                EstimParm.qVIndalpha = (int)((MotorEstimParm.qLsDt * EstimParm.qDIalpha)>>7);
//          EstimParm.qVIndalpha = (int)(__builtin_mulss(MotorEstimParm.qLsDt, EstimParm.qDIalpha)>>7);
    
    	EstimParm.qDIbeta	=	(ParkParm.qIbeta-EstimParm.qLastIbetaHS[(EstimParm.qDiCounter)]);
    	/* the current difference can exceed the maximum value per 1 ADC ISR cycle */
    	/* the following limitation assures a limitation per high speed - up to the maximum speed */
    	if (EstimParm.qDIbeta>EstimParm.qDIlimitHS) EstimParm.qDIbeta=EstimParm.qDIlimitHS;
            if (EstimParm.qDIbeta<-EstimParm.qDIlimitHS) EstimParm.qDIbeta=-EstimParm.qDIlimitHS;
                EstimParm.qVIndbeta= (int)((MotorEstimParm.qLsDt * EstimParm.qDIbeta)>>7);
//    	EstimParm.qVIndbeta= (int)(__builtin_mulss(MotorEstimParm.qLsDt, EstimParm.qDIbeta)>>7);
    
    }


    //*******************************
    // update  LastIalpha and LastIbeta
    EstimParm.qDiCounter=(EstimParm.qDiCounter+1) & 0x0007;
    EstimParm.qLastIalphaHS[EstimParm.qDiCounter]	=	ParkParm.qIalpha;
    EstimParm.qLastIbetaHS[EstimParm.qDiCounter] 	=	ParkParm.qIbeta;
    
    //*******************************
    // Stator voltage eqations
    // Ualpha = Rs * Ialpha + Ls dIalpha/dt + BEMF
    // BEMF = Ualpha - Rs Ialpha - Ls dIalpha/dt   
    
    EstimParm.qEsa		= 	EstimParm.qLastValpha -	((int)( MotorEstimParm.qRs * ParkParm.qIalpha)	>>11) - EstimParm.qVIndalpha;
//	EstimParm.qEsa		= 	EstimParm.qLastValpha -	(int)(__builtin_mulss( MotorEstimParm.qRs, ParkParm.qIalpha)	>>11)			- EstimParm.qVIndalpha;
    
    /* the multiplication between the Rs and Ialpha was shifted by 11 instead of 15 */
    /* because the Rs value normalized exceeded Q15 range, so it was divided by 16 */
    /* immediatelky after the normalization - in userparms.h */

    // Ubeta = Rs * Ibeta + Ls dIbeta/dt + BEMF
    // BEMF = Ubeta - Rs Ibeta - Ls dIbeta/dt   
    
	EstimParm.qEsb		= 	EstimParm.qLastVbeta -	((int)( MotorEstimParm.qRs * ParkParm.qIbeta )	>>11)	- EstimParm.qVIndbeta;
    //	EstimParm.qEsb		= 	EstimParm.qLastVbeta -			(int)(__builtin_mulss( MotorEstimParm.qRs, ParkParm.qIbeta )	>>11)							- EstimParm.qVIndbeta;
							
    /* the multiplication between the Rs and Ibeta was shifted by 11 instead of 15 */
    /* because the Rs value normalized exceeded Q15 range, so it was divided by 16 */
    /* immediatelky after the normalization - in userparms.h */
    
    //*******************************0.16
    // update  LastValpha and LastVbeta
	EstimParm.qLastValpha = ParkParm.qValpha;
	EstimParm.qLastVbeta  = ParkParm.qVbeta;
	

    
    
    //lazo abierto para prueba
    //  SincosParm.qCos = (short)(cos(  ((float)ParkParm.qAngle)/10416 ) * 32767);
    // SincosParm.qSin = (short)(sin(  ((float)ParkParm.qAngle)/10416 ) * 32767);
    
   
    
    // Cálculo del valor absoluto
    
    // qEsAbs = (qEsqf^2 + qEsdf^2   )^(1/2);
    tmpa = abs_iq(EstimParm.qEsa);
    tmpb = abs_iq(EstimParm.qEsb);
    
    if (tmpa >= tmpb)
        EstimParm.qEsAbs =  tmpa + 3*(tmpb>>3);
    else 
        EstimParm.qEsAbs =  tmpb + 3*(tmpa>>3);
    
    
    //filtros pasa bajos EsAbs
            
    /* y(n)=1./(1+k).( x(n) + x(n-1) + y(n-1).(k-1))
     * k = fm / (pi*fc)
     * K1 = 1/(1+k)
     * K2 = (1-k)
     **   Copiar en MATLAB: 
        fm = 18000; fc=50; nfrac = 14;
        k = fm / (pi*fc);
        K1 = round(1/(1+k)*2^nfrac);
        K2 = round((k-1)/(1+k)*2^nfrac);
        fprintf("#define K1FILT_FEM %d \n",K1)
        fprintf("#define K2FILT_FEM %d \n",K2)
     *
     *
     */

    /*
    #define K1FILT_FEM 142 
    #define K2FILT_FEM 16101 
    temp_int =  (int32_t)EstimParm.qEsAbs;
    temp_int += (int32_t)qEsAbsPrev;
    temp_int = temp_int*K1FILT_FEM;
    temp_int += (K2FILT_FEM*(int32_t)EstimParm.qEsAbsf);

    EstimParm.qEsAbsf = (int16_t)((temp_int) >> 14);
    qEsAbsPrev = EstimParm.qEsAbs;
     */

    
    // Calculate Sin(Rho) and Cos(Rho)
    // SincosParm.qAngle  = EstimParm.qRho;
    // SinCos();
    
    //estimador lazo cerrado
    SincosParm.qCos = (int16_t)(cos(  ((float)EstimParm.qRho)/10416  ) * 32767);
    SincosParm.qSin = (int16_t)(sin(  ((float)EstimParm.qRho)/10416  ) * 32767);
    
    //*******************************
    //    Esd =  Esa*cos(Angle) + Esb*sin(Rho)
    EstimParm.qEsd	= (int)( (int)EstimParm.qEsa * (int)SincosParm.qCos +	(int)EstimParm.qEsb * (int)SincosParm.qSin)>>15;
    //	EstimParm.qEsd		=	(int)((__builtin_mulss(EstimParm.qEsa, SincosParm.qCos)>>15) +	builtin_mulss(EstimParm.qEsb, SincosParm.qSin)>>15));
    //*******************************
    //   Esq = -Esa*sin(Angle) + Esb*cos(Rho)
    EstimParm.qEsq	= (int)( (int)EstimParm.qEsb * (int)SincosParm.qCos -	(int)EstimParm.qEsa * (int)SincosParm.qSin)>>15;
    //	EstimParm.qEsq		=	(int)((__builtin_mulss(EstimParm.qEsb, SincosParm.qCos)>>15) -	(__builtin_mulss(EstimParm.qEsa, SincosParm.qSin)>>15));

    
    
    //*******************************
    //*******************************
    // Filter first order for Esd and Esq
    // EsdFilter = 1/TFilterd * Intergal{ (Esd-EsdFilter).dt }
        
        // Test sin filtro
    
	temp_int = (int)(EstimParm.qEsd - EstimParm.qEsdf);
    EstimParm.qEsdStateVar			+= (temp_int * EstimParm.qKfilterdq);
//	EstimParm.qEsdStateVar			+= __builtin_mulss(temp_int, EstimParm.qKfilterdq);
	EstimParm.qEsdf					= (int)(EstimParm.qEsdStateVar>>15);
    
    
    //EstimParm.qEsdf=EstimParm.qEsdf;

	temp_int = (int)(EstimParm.qEsq - EstimParm.qEsqf);
    EstimParm.qEsqStateVar			+= (temp_int*EstimParm.qKfilterdq);
//	EstimParm.qEsqStateVar			+= __builtin_mulss(temp_int,EstimParm.qKfilterdq);
	EstimParm.qEsqf					= (int)(EstimParm.qEsqStateVar>>15);
     
    
    //EstimParm.qEsdf = EstimParm.qEsd;
    //EstimParm.qEsqf = EstimParm.qEsq;
    
    // OmegaMr= (1+SigmaR)/PsiMr * Esq -sgn(Uhqf) * Uhdf
     
   
    
    // Cálculo del valor absoluto
    
    // qEsAbs = (qEsqf^2 + qEsdf^2   )^(1/2);
    tmpa = abs_iq(EstimParm.qEsdf);
    tmpb = abs_iq(EstimParm.qEsqf);
    
    if (tmpa >= tmpb)
        EstimParm.qEsAbs =  tmpa + 3*(tmpb>>3);
    else 
        EstimParm.qEsAbs =  tmpb + 3*(tmpa>>3);
    
    
    
    
     if(EstimParm.qOmegaMr > 0)
        signo = 1;
     else 
        signo = -1;  
    
    
            PIEst_rho.qInRef =  0;  
        PIEst_rho.qInMeas =   (EstimParm.qEsdf*signo);

        CalcPI_ang(&PIEst_rho);
    
    
       // if (ref_iq > 0 )
       // {
            if (modo_acel == 0)
            {
                if (EstimParm.qEsAbs < 1000)  //EstimParm.qEsAbs < 1000
                {
                    PIEst_rho.qdSum = ( (((int32_t)EstimParm.qOmegaMr) << 15) + (((int32_t)EstimParm.qEsdf	 * (int32_t)PIEst_rho.qKp)<<4)  );
                    EstimParm.qOmegaMr = 250;
                    
                    
                    modo_acel = 0;
                }
                else
                    modo_acel = 1;
            }
            else
            {
                if (EstimParm.qEsAbs > 100)
                {
                    //if (EstimParm.qEsqf > 0)
                    //    temp_int = (int)(EstimParm.qEsAbs- EstimParm.qEsdf);
                    //else
                     //   temp_int = (int)(EstimParm.qEsqf+ EstimParm.qEsdf>>4);
                   
                    //EstimParm.qOmegaMr	=	(int)((MotorEstimParm.qInvPsi * temp_int)>>5);
                    // temp_int =  (int)(EstimParm.qEsqf- EstimParm.qEsdf);//  PIEst_rho.qOut*signo -(EstimParm.qEsqf);//*signo;
                    // EstimParm.qOmegaMr	=	(int)((MotorEstimParm.qInvPsi * temp_int)>>15);
                    //EstimParm.qOmegaMr = PIEst_rho.qOut*signo - ((MotorEstimParm.qInvPsi *EstimParm.qEsqf)>>10);// + (EstimParm.qEsqf*MotorEstimParm.qInvPsi)>>15;//*signo;
                    EstimParm.qOmegaMr = PIEst_rho.qOut + ((EstimParm.qEsAbsf*5570)*0>>15) ;// + (EstimParm.qEsqf*MotorEstimParm.qInvPsi)>>15;//*signo;
                    modo_acel = 1;
                }
                //else
                    //modo_acel = 0;
            } 
        //}
        //else
        //{
        /*
            if (modo_acel == -1)
            {
                if (EstimParm.qEsAbs > 100)
                {
                    EstimParm.qOmegaMr = PIEst_rho.qOut + ((EstimParm.qEsAbsf*Q15(0.54))*0>>15);//*signo;
                    modo_acel = -1;
                }
                else  
                    modo_acel = 0;
            }
            else
            {
                if (EstimParm.qEsAbs < 400)
                {
                     PIEst_rho.qdSum = ( (((int32_t)EstimParm.qOmegaMr) << 15) + (((int32_t)EstimParm.qEsdf	 * (int32_t)PIEst_rho.qKp)<<4)  );
                     EstimParm.qOmegaMr = 250;
                     modo_acel = 0;
                }
                else
                    modo_acel = -1;
                
            }

        } 
         ran*/          
        
        //modificaci�n versi�n 2
        /*
        if( (etapa_arranque == 0) || (etapa_arranque == 1) )
        {

             //EstimParm.qOmegaMr = frec_arranque*0;  //frecuencia de arranque
             //EstimParm.qOmegaMr = PIEst_rho.qOut;//+frec_arranque;      
             //EstimParm.qOmegaMr = PIEst_rho.qOut+frec_arranque;  
             PIEst_rho.qdSum = ( (((int32_t)EstimParm.qOmegaMr) << 15) + (((int32_t)EstimParm.qEsdf	 * (int32_t)PIEst_rho.qKp)<<4)  );     //ajusto el termino de suma del PI para que cuando se haga la transicion la salida del PI no cambie
             
             //PIEst_rho.qOut = frec_arranque;
             PIEst_rho.qOut = 500;
             EstimParm.qOmegaMr = PIEst_rho.qOut;//+frec_arranque;  

        }
        else
   

            EstimParm.qOmegaMr = PIEst_rho.qOut;//+frec_arranque;       
        }
          */  
    
    
    /*
    aux_abs_int = abs_iq(EstimParm.qVelEstim);
    
    if (aux_abs_int > (NOMINAL_SPEED_RPM*NOPOLESPAIRS/10))

//if (_Q15abs(EstimParm.qVelEstim)>(NOMINAL_SPEED_RPM*NOPOLESPAIRS/10))
    //if(1)
    {
        
    	if(EstimParm.qEsqf>0)
    	{
    		temp_int = (int)(EstimParm.qEsqf- EstimParm.qEsdf);
            error = temp_int;
            EstimParm.qOmegaMr	=	(int)((MotorEstimParm.qInvPsi * temp_int)>>15);
            modo_estim = 1;
//    		EstimParm.qOmegaMr	=	(int)(__builtin_mulss(MotorEstimParm.qInvPsi, temp_int)>>15);
    	} else
    	{
    		temp_int = (int)(EstimParm.qEsqf+ EstimParm.qEsdf);
            error = temp_int;
            EstimParm.qOmegaMr	=	(int)((MotorEstimParm.qInvPsi * temp_int)>>15);
             modo_estim = 2;
//    		EstimParm.qOmegaMr	=	(int)(__builtin_mulss(MotorEstimParm.qInvPsi, temp_int)>>15);
    	}
    } else // if est speed<10% => condition VelRef<>0
    {
    	if(EstimParm.qVelEstim>0)
    	{
    		temp_int = (int)(EstimParm.qEsqf - EstimParm.qEsdf);
            error = temp_int;
            EstimParm.qOmegaMr	=	(int)((MotorEstimParm.qInvPsi *temp_int)>>15);
             modo_estim = 3;
  //      	EstimParm.qOmegaMr	=	(int)(__builtin_mulss(MotorEstimParm.qInvPsi,temp_int)>>15);
    	} else
    	{
    		temp_int = (int)(EstimParm.qEsqf + EstimParm.qEsdf);
            error = temp_int;
            EstimParm.qOmegaMr	=	(int)((MotorEstimParm.qInvPsi * temp_int)>>15);
             modo_estim = 4;
   //     	EstimParm.qOmegaMr	=	(int)(__builtin_mulss(MotorEstimParm.qInvPsi,temp_int)>>15);
    
    	}
    }
     
     */
    
    //	EstimParm.qOmegaMr=EstimParm.qOmegaMr<<1;

    /* the integral of the angle is the estimated angle */
        EstimParm.qRhoStateVar	+= (long)(EstimParm.qOmegaMr*EstimParm.qDeltaT);//* EstimParm.qDeltaT);
//  	EstimParm.qRhoStateVar	+= __builtin_mulss(EstimParm.qOmegaMr, EstimParm.qDeltaT);
    	EstimParm.qRho 		= 	(int) (EstimParm.qRhoStateVar>>15);

        #define USEIMRREF
        
        
#ifdef USEIMRREF	
        // Omeg2Estim=Iq/Imr/Tr when Reference Value of magnatising current is used
        
        
        EstimParm.qOmeg2Estim= (int)((ParkParm.qIq, MotorEstimParm.qRrInvTr)>>15);
        
//		EstimParm.qOmeg2Estim= (int)(__builtin_mulss(ParkParm.qIq, MotorEstimParm.qRrInvTr)>>15);
#else

//*******************************
// Current Model
// Imr = 1/Tr * Intergal{ (Id-Imr).dt } when real value of magnetising current is used

        temp_int = (int)(ParkParm.qId - EstimParm.qImr);
        EstimParm.qImrStateVar += (temp_int * MotorEstimParm.qInvTr) ;
//		EstimParm.qImrStateVar += __builtin_mulss(temp_int,MotorEstimParm.qInvTr) ;
		EstimParm.qImr      	= (int)(EstimParm.qImrStateVar>>15);

        EstimParm.qIqInvTr2= (ParkParm.qIq * MotorEstimParm.qInvTr2);
//		EstimParm.qIqInvTr2=__builtin_mulss(ParkParm.qIq, MotorEstimParm.qInvTr2);

		/* limit the magnetizing current to guarantee stability */
		if (EstimParm.qImr<2000)
        {
			EstimParm.qImr=2000;
		}

		EstimParm.qOmeg2Estim = EstimParm.qIqInvTr2/EstimParm.qImr;

#endif

    /* the estiamted speed is a filter value of the above calculated OmegaMr. The filter implementation */
    /* is the same as for BEMF d-q components filtering */
    temp_int = (int)(EstimParm.qOmegaMr-EstimParm.qOmeg2Estim-EstimParm.qVelEstim);
    EstimParm.qVelEstimStateVar+=(temp_int * EstimParm.qVelEstimFilterK);
//	EstimParm.qVelEstimStateVar+=__builtin_mulss(temp_int, EstimParm.qVelEstimFilterK);
	EstimParm.qVelEstim=	(int)(EstimParm.qVelEstimStateVar>>15);
    // Mechanical speed

    EstimParm.qVelEstimMech= (int)((EstimParm.qVelEstim * EstimParm.qInvPol)>>15);
//	EstimParm.qVelEstimMech= (int)(__builtin_mulss(EstimParm.qVelEstim, EstimParm.qInvPol)>>15);
}   // End of Estim()
        
    
    
    
    

void    InitEstimParm(void)
{
            // Constants are defined in "EstimParameter_Oriental.xls" 
                
                EstimParm.qRhoStateVar=0;
                EstimParm.qOmegaMr=0;
                EstimParm.qDiCounter=0;
                EstimParm.qEsdStateVar=0;
                EstimParm.qEsqStateVar=0;
                
                EstimParm.qDIlimitLS = D_ILIMIT_LS;
                EstimParm.qDIlimitHS = D_ILIMIT_HS;
                EstimParm.qDeltaT=NORM_DELTAT;
                EstimParm.qKfilterdq=KFILTER_ESDQ;
                EstimParm.qInvPol=0x7FFF / NOPOLESPAIRS;
                EstimParm.qVelEstimFilterK=KFILTER_VELESTIM;

                MotorEstimParm.qInvTr=NORM_INVTR;
                MotorEstimParm.qRrInvTr=NORM_RRINVTR;
                MotorEstimParm.qInvTr2=NORM_INVTR2;


                MotorEstimParm.qLsDt=NORM_LSDT;
                MotorEstimParm.qInvPsi=NORM_INVPSI;
                MotorEstimParm.qRs=NORM_RS;
                
                frec_arranque = 0;

}
 int16_t abs_iq( int16_t param)
{
    if(param < 0)
        param = -param;
    
    return param;
            
    
}

 int16_t Raiz_iq(int16_t param)
 {
     float aux_float;
     int16_t aux_16bits;
 
     aux_float = ((double)(param))/32768;
     aux_16bits = (int16_t)((sqrt( aux_float ))*32768); 
            
      return aux_16bits;
            
 }

