#ifndef Estim_H
#define Estim_H


/**********************************************************************
* � 2011 Microchip Technology Inc.
*
* SOFTWARE LICENSE AGREEMENT:
* Microchip Technology Incorporated ("Microchip") retains all ownership and 
* intellectual property rights in the code accompanying this message and in all 
* derivatives hereto.  You may use this code, and any derivatives created by 
* any person or entity by or on your behalf, exclusively with Microchip's
* proprietary products.  Your acceptance and/or use of this code constitutes 
* agreement to the terms and conditions of this notice.
*
* CODE ACCOMPANYING THIS MESSAGE IS SUPPLIED BY MICROCHIP "AS IS".  NO 
* WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED 
* TO, IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A 
* PARTICULAR PURPOSE APPLY TO THIS CODE, ITS INTERACTION WITH MICROCHIP'S 
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
*
* YOU ACKNOWLEDGE AND AGREE THAT, IN NO EVENT, SHALL MICROCHIP BE LIABLE, WHETHER 
* IN CONTRACT, WARRANTY, TORT (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), 
* STRICT LIABILITY, INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, 
* PUNITIVE, EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF 
* ANY KIND WHATSOEVER RELATED TO THE CODE, HOWSOEVER CAUSED, EVEN IF MICROCHIP HAS BEEN 
* ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE FULLEST EXTENT 
* ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN ANY WAY RELATED TO 
* THIS CODE, SHALL NOT EXCEED THE PRICE YOU PAID DIRECTLY TO MICROCHIP SPECIFICALLY TO 
* HAVE THIS CODE DEVELOPED.
*
* You agree that you are solely responsible for testing the code and 
* determining its suitability.  Microchip has no obligation to modify, test, 
* certify, or support the code.
*
*******************************************************************************/

#include "UserParms.h"


	
//------------------  C API for Control routine ---------------------

typedef struct {
    int16_t   			  qDeltaT;      // int16_tegration constant
    int16_t   			  qRho;    	    // 
    long  			  qRhoStateVar; //     
    int16_t   			  qOmegaMr;     // 
    int16_t   			  qLastIalpha;  // 
    int16_t   			  qLastIbeta;   // 
    int16_t   			  qDIalpha;     // 
    int16_t   			  qDIbeta;      // 
	int16_t				  qEsa;			// 
	int16_t				  qEsb;			// 
	int16_t				  qEsd;			// 
	int16_t				  qEsq;			// 
	int16_t				  qImr;			// 
	long			  qImrStateVar;	// 
	int16_t				  qDiCounter;	// 
	int16_t				  qVIndalpha;
	int16_t				  qVIndbeta;
	int16_t				  qEsdf;
	long			  qEsdStateVar;
	int16_t				  qEsqf;
	long			  qEsqStateVar;
	int16_t				  qKfilterdq;
	int16_t   			  qVelEstim; 			// Estimated speed in 1.15
	int16_t   			  qVelEstimFilterK; 	// Filter Konstant for Estimated speed in 1.15
	long   			  qVelEstimStateVar; 	// State Variable for Estimated speed in 1.31
	int16_t   			  qOmeg2Estim; 			// Estimated speed in 1.15
	int16_t				  qVelEstimMech;// estimated mechanical speed
	int16_t				  qInvPol;		// 1/polpare numbare
    int16_t   			  qLastValpha;  // Value from last control step Ialpha 
    int16_t   			  qLastVbeta;   // Value from last control step Ibeta
	int16_t				  qDIalphaHS;			// dIalpha/dt
	int16_t				  qDIbetaHS;			// dIbeta/dt
	int16_t				  qLastIalphaHS[16];		//  last  value for Ialpha
	int16_t				  qLastIbetaHS[16];			// last  value for Ibeta
    int16_t				  qDIlimitLS;			// dIalphabeta/dt
	int16_t				  qDIlimitHS;			// dIalphabeta/dt
	long			  qIqInvTr2;
    int16_t				  qEsAbs;			// Valor absoluto de la FEM
    int16_t               qEsAbsf;          // Valor absoluto de la FEM filt



    } tEstimParm;


typedef struct {
	int16_t				   qRs;			//
	int16_t				   qLsDt;		//
	int16_t				   qInvPsi;		//
	int16_t				   qInvTr;		//
	int16_t				   qRrInvTr;	//
	int16_t				   qInvTr2;
    } tMotorEstimParm;

void	Estim(void);
void	InitEstimParm(void);
 int16_t Raiz_iq(int16_t );
  int16_t abs_iq( int16_t );
#endif
