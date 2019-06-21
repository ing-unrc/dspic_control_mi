#ifndef USERPARMS_H
#define USERPARMS_H

#include "general.h"

//Definiciones de funcionamiento
  
//A: Seleccionar 1 opcion
//#define MOTOR_BICI_1
// #define MOTOR_BICI_2

//B:
//#define ARRANQUE_LAZO_ABIERTO
 
//C:
//#define    ACELERADOR_BICI
    
//-------------------------------------------------------------------------

#undef BIDIRECTIONAL_SPEED


/* definition for tuning - if active the speed reference is a ramp with a 
 constant slope. The slope is determined by TUNING_DELAY_RAMPUP constant.
 */ 
/* the software ramp implementing the speed increase has a constant slope, */
/* adjusted by the delay TUNING_DELAY_RAMPUP when the speed is incremented.*/
/* The potentiometer speed reference is overwritten. The speed is          */
/* increased from 0 up to the END_SPEED_RPM in open loop � with the speed  */
/* increase typical to open loop, the transition to closed loop is done    */
/* and the software speed ramp reference is continued up to MAXIMUM_SPEED_RPM. */
/* define the follwing TUNING for slow acceleration ramp instead POT */
#undef TUNING

/* if TUNING was define, then the ramp speed is needed: */
#ifdef TUNING
    #define TUNING_DELAY_RAMPUP   0xF      /* the smaller the value, the quicker the ramp */
#endif


/* open loop continuous functioning */
/* closed loop transition disabled  */
#undef OPEN_LOOP_FUNCTIONING


/* definition for torque mode - for a separate tuning of the current PI
 controllers, tuning mode will disable the speed PI controller */
#undef TORQUE_MODE



/* static snapshots can be taken activating the SNAPSHOT definition */
/* this feature is available only in DEBUG mode of the project */
/* load DMCI GUI from MPLAB - Tools tab 
Please consult DMCI help by pressing Help button on DMCI window for a
complete description of DMCI tool.
Using dedicated open button in DMCI window load dmci_snapshot.dmci 
setup file from the AN1292 project�s folder.
It contains in the Dynamic data view tab the proper variables setup */
/* static snapshots are captured running the code, and, when halt button
from the Debug toolbar is pressed, the DMCI graph windows are updated with
the captured data */
/* consult debug.c API for calling the specific SNAPSHOT debug functions:
   DBG_Init(void)	- debug initialization
   DBG_SnapStart(void) - start of SNAPSHOT trigger
   DBG_SnapUpdate(void) - SNAPSHOT variables update 
   These functions are called in pmsm.c */
/* 
For captured data setup please check: 
"DEFINITIONS FOR SNAP and RTDM captured variables"
section in this file 
*/
/* to enable static snapshot, uncomment the folowing line */  
#undef SNAPSHOT

#undef RTDM_DEMO

/* Real Time Debug Monitor enable - if activated, RTDM will allow real time
 control and monitoring of the embedded side from host DMCI interface */
/*
IMPORTANT:
___________________--__________--_____________________________________
Communication between the host computer and the target device (dsPIC33FJ64MC204)
may fail due to noisy environment, real time specificity of the system 
or other unpredictable causes. 
Since the host computer is used to completely control the target device,
in such failure cases, use the RESET button on MCHV module to stop the 
execution and stop the motor.
___________________--__________--_____________________________________

Short usage guide 
(please consult the http://ww1.microchip.com/downloads/en/DeviceDoc/70567A.pdf
for detailed information on RTDM and its usage):
Open DMCI- Data Monitor and Control Interface window from the 
MPLAB�s Tools tab. Using afferent open pictogram, load dmci_rtdm.dmci
setup file from the AN1292 project�s folder. Within the DMCI window�s
frame, the following controls are available:
1/Boolean DMCIFlags.StartStop � used for start/stop  the motor
2/ Slider SpeedReference � used for reference speed modification
3/ Boolean DMCIFlags.Recorder � used for triggering a new sample of 
measured variables
4/ Slider SnapShotDelay � used for sample rate modification of 
the measured variables
5/ Graph 1-4 � Graphs of the measured variables: A phase current, 
q-axis current, estimated speed, estimated angle 
Running the application note software will connect the target
MCHV board to the host DMCI application as specified in above indicated 
User�s Guide.  
Suggested usage guide: 
1/ Run the program using Run button in Dynamic Data Input DMCI child window
� allow few seconds for communication protocol to be established without
issuing any other command
2/ Run DMCI tab � Remote communication menu, which should indicate 
connection status as DETECTED (if it doesn�t, please refer to the 
above indicated User guide for troubleshooting). Close the DMCI Remote 
Communication Properties window by pressing OK acknowledging the 
detected communication.
3/ Press Run Time Update button in Dynamic Data Input DMCI child window � 
this will update the host DMCI GUI with the initial setup already existing 
on target device
4/ Adjust the speed reference using the afferent Slider SpeedReference 
to a value of roughly 5000 (please note that both positive and negative 
speed references can be set, so bidirectional functioning is selected 
by default with RTDM_DEMO)
5/ Press Start/Stop button, switching it from OFF state to ON state 
using afferent Boolean DMCIFlags.StartStop button in Dynamic Data Input 
DMCI child window �  immediately the motor will start running
6/ Press Boolean DMCIFlags.Recorder in in Dynamic Data Input DMCI child 
window in order to trigger a sample of the measured variables(the button 
should be in ON state)
7/ Press Run Time Update button in Dynamic Data Input DMCI child window 
� this will update the host DMCI GUI with the snapped data in target device.
8/ Use Automated Event Control button to have steps 6/, 7/ executed 
automatically at 1 second period 
9/ Vary the reference speed, vary the snap shot delay, etc.
10/ Press Start/Stop button, switching it from ON state to OFF state 
using afferent Boolean DMCIFlags.StartStop button in Dynamic Data Input 
DMCI child window �  immediately the motor will stop running
*/
/* consult debug.c API for calling the specific RTDM_DEMO functions:
   DBG_Init(void)	- RTDM initialization
   DBG_SyncComm(void) - RTDM syncrho target and host in pooling mode
   DBG_SnapUpdate(void) - RTDM variables update 
   These functions are called in pmsm.c */
/* 
For captured data setup please check: 
"DEFINITIONS FOR SNAP and RTDM captured variables"
section in this file 
*/
/* unefine the line below for RTDM control demo */
#undef DMCI_DEMO		


/****************************************************/
/* DEFINITIONS FOR SNAP and RTDM captured variables */
/****************************************************/

    #include "park.h"
    #include "Estim.h"
    #include "control.h"

    extern tParkParm   ParkParm;       /* park transform params */
    //extern tEstimParm 	EstimParm;     /* estim params */
    extern tCtrlParm CtrlParm;
    #define DATA_BUFFER_SIZE 200  //Size in 16-bit Words of the snap */
                                  // the value depends on the dsPIC memory
    #define SNAPDELAY	10 // Initial delay in capture given in number of PWM Interrupts
    
    
    #define	SNAP1		ParkPar m.qIa     // snap captures
    #define	SNAP2		ParkParm.qIq 
 //   #define SNAP3		EstimParm.qVelEstim
  //  #define SNAP4		EstimParm.qRho

/****************************************************/



#define LOOPTIME_SEC  0.000054           // PWM Period - 50 uSec, 20Khz PWM
#define	DISPLOOPTIME_SEC	0.100		// button polling loop period in sec

#define DEADTIME_SEC  0.000001         // Dead time in seconds - 700ns el original era 0.000001 
 
#define PWM_DT_ERRATA

#define DDEADTIME      (unsigned int)(DEADTIME_SEC*FCY_HZ)	// Dead time in dTcys

#ifdef PWM_DT_ERRATA
    #define MIN_DUTY  (unsigned int)(DDEADTIME/2 + 1)        // Should be >= DDEADTIME/2 for PWM Errata workaround
#else
    #define MIN_DUTY  0x00
#endif




//**************  support xls file definitions begin **************
/* the following values are given in the xls attached file */

//**************  Motor Parameters **************
/* motor's number of pole pairs */
//#define NOPOLESPAIRS 2
/* Nominal speed of the motor in RPM */
//#define NOMINAL_SPEED_RPM    2500 // Value in RPM
/* Maximum speed of the motor in RPM - given by the motor's manufacturer */
#define MAXIMUM_SPEED_RPM    4700 // Value in RPM  - maximum provided by manufact. is 5000RPM


#define NOPOLESPAIRS        2       // Number of pole pairs

/* nominal motor speed */
#define NOMINAL_SPEED_RPM 1500
    
/* normalized rs value */
#define NORM_RS  510  
    
/* normalized ls/dt value */
#define NORM_LSDT 1828
    
/* Magnetizing current reference value */
//#define	MAGNETIZING_CURRENT	5734	
    
/* inverse flux */
#define NORM_INVPSI  64
    
/* normalized Tsample/Tr */
#define NORM_INVTR 22
 
/* the calculation of InvKfi gives a value which not exceed the Q15 limit */
/* to assure that an increase of the term with 5 is possible in the lookup table */
/* for high flux weakening the normalized is initially divided by 2 */
/* this is taken care in the estim.c where the value is implied */
/* normalized dt value */
#define NORM_DELTAT  1805    
    
#define KFILTER_ESDQ 404 
    
   
/* normalized inverse RRTR */
#define NORM_RRINVTR 5
    
#define KFILTER_VELESTIM 1178

/* normalized inverse Tr */
#define NORM_INVTR2 128


    
//#define NORM_CURRENT_CONST     0.000488
/* normalized ls/dt value */
//#define NORM_LSDTBASE 7069

/* the calculation of Rs gives a value exceeding the Q15 range so,
the normalized value is further divided by 2 to fit the 32768 limit */
/* this is taken care in the estim.c where the value is implied */
/* normalized inv kfi at base speed */
//#define NORM_INVKFIBASE  5888


// Limitation constants 
/* di = i(t1)-i(t2) limitation */ 
/* high speed limitation, for dt 50us */
/* the value can be taken from attached xls file */
#define D_ILIMIT_HS 1500
/* low speed limitation, for dt 8*50us */
#define D_ILIMIT_LS 6000

//**************  support xls file definitions end **************


// Filters constants definitions  
/* BEMF filter for d-q components @ low speeds */
//#define KFILTER_ESDQ 749
/* BEMF filter for d-q components @ high speed - Flux Weakening case */
#define KFILTER_ESDQ_FW 404
    
/* estimated speed filter constatn */
/* a separate constant for field weakening could be defined */
//#define KFILTER_VELESTIM 1285


/* initial offset added to estimated value, */
/* when transitioning from open loop to closed loop */
/* the value represents 0deg and should satisfy both */
/* open loop functioning */
/* normally this value should be modified in */
/* case of fine tuning of the transition, depending on */
/* the load or the rotor moment of inertia */
/* ex: 0x2000 represents an offset of 45deg */
#define INITOFFSET_TRANS_OPEN_CLSD 0x0000

/* current transformation macro, used below */
#define NORM_CURRENT(current_real) (Q15(current_real/NORM_CURRENT_CONST/32768))

/* open loop startup constants */
/* the following values depends on the PWM frequency, */
/* lock time is the time needed for motor's poles alligniament 
 previous the open loop speed ramp up */
#define LOCK_TIME 8000 // This number is: 20,000 is 1 second.
/* open loop speed ramp up end value */
#define END_SPEED_RPM 500 // Value in RPM
/* open loop speed ramp up speed of increase */
#define OPENLOOP_RAMPSPEED_INCREASERATE 10
/* open loop q current setup - */
#define Q_CURRENT_REF_OPENLOOP NORM_CURRENT(0.5)

/* in case of the potentimeter speed reference, a reference ramp
 is needed for assuring the motor can follow the reference imposed */
#define    SPEEDREFRAMP   Q15(0.00003)  /*minimum value accepted */

/* PI controllers tuning values - */
//******** D Control Loop Coefficients *******


    
   
    #define     D_CURRCNTR_PTERM           Q15(0.2)  //Q15(0.2)
    #define     D_CURRCNTR_ITERM           Q15(0.05)
    #define     D_CURRCNTR_CTERM           Q15(0.999)      


 
#define     D_CURRCNTR_OUTMAX          20000    //diego: original 0x7FFF 
    
//******** Q Control Loop Coefficients *******

    #define     Q_CURRCNTR_PTERM           Q15(0.2)
    #define     Q_CURRCNTR_ITERM           Q15(0.05)
    #define     Q_CURRCNTR_CTERM           Q15(0.999) 
    
    
    

#define     Q_CURRCNTR_OUTMAX          21000    //sqrt( (32768*0.90)^2-16000^2)  

     
    
//parametros PI estimador
    
    #define     EST_PTERM           Q15(0.005)     //Q15(0.05)
    #define     EST_ITERM           Q15(0.0004) //Q15(0.0004)
    #define     EST_CTERM           Q15(0.999) 
    #define     EST_OUTMAX          0x7FFF
    #define     EST_OUTMIN          -0x7FFF

//parametros PI freno
    
    #define     FRENO_PTERM           Q15(0.005)     //Q15(0.05)
    #define     FRENO_ITERM           Q15(0.0004) //Q15(0.0004)
    #define     FRENO_CTERM           Q15(0.999) 
    #define     FRENO_OUTMAX          0x0000
    #define     FRENO_OUTMIN          -0x0000    
    
    
//*** Velocity Control Loop Coefficients *****
#define     SPEEDCNTR_PTERM        Q15(0.1)
#define     SPEEDCNTR_ITERM        Q15(0.003)
#define     SPEEDCNTR_CTERM        Q15(0.005)
#define     SPEEDCNTR_OUTMAX       0x5000


//************** Field Weakening **************

/// Field Weakening constant for constant torque range
#define     IDREF_BASESPEED            NORM_CURRENT(0.0)       // Flux reference value

/*-------------------------------------------------------------*/
/* IMPORTANT:--------------------------------------------------*/
/*-------------------------------------------------------------*/ 
/* In flux weakening of the surface mounted permanent magnets  */
/* PMSMs the mechanical damage of the rotor and the            */
/* demagnetization of the permanent magnets is possible if     */
/* cautions measures are not taken or the motor�s producer     */
/* specifications are not respected.                           */
/*-------------------------------------------------------------*/
/* IMPORTANT:--------------------------------------------------*/
/*-------------------------------------------------------------*/ 
/* In flux weakening regime implementation, if the FOC is lost */
/* at high speed above the nominal value, the possibility of   */
/* damaging the inverter is eminent. The reason is that the    */
/* BEMF will have a greater value than the one that would be   */
/* obtained for the nominal speed exceeding the DC bus voltage */
/* value and though the inverter�s power semiconductors and DC */
/* link capacitors would have to support it. Since the tuning  */
/* proposed implies iterative coefficient corrections until    */
/* the optimum functioning is achieved, the protection of the  */
/* inverter with corresponding circuitry should be assured in  */
/* case of stalling at high speeds.                            */
/*-------------------------------------------------------------*/ 
/*-------------------------------------------------------------*/ 

#define SPEED_INDEX_CONST 7 // speed index is increased every 2^(7-1)=64 RPM

/* the follwing values indicate the d-current variation with speed */
/* please consult app note for details on tuning */
#define	IDREF_SPEED0	NORM_CURRENT(0)      
#define	IDREF_SPEED1	-10 
#define	IDREF_SPEED2	-50 
#define	IDREF_SPEED3	-100 
#define	IDREF_SPEED4	-200  
#define	IDREF_SPEED5	-300  
#define	IDREF_SPEED6	-400   
#define	IDREF_SPEED7	-500 
#define	IDREF_SPEED8	-600  
#define	IDREF_SPEED9	-700  
#define	IDREF_SPEED10	-800 
#define	IDREF_SPEED11	-950  
#define	IDREF_SPEED12	-1150 
#define	IDREF_SPEED13	-1350  
#define	IDREF_SPEED14	-1600
#define	IDREF_SPEED15	-1750 
#define	IDREF_SPEED16	-1950 
#define	IDREF_SPEED17	-2100 
#define	IDREF_SPEED18	-2200      
#define	IDREF_SPEED19	-2300 
#define	IDREF_SPEED20	-2400 
#define	IDREF_SPEED21	-2500 
#define	IDREF_SPEED22	-2650  
#define	IDREF_SPEED23	-2800  
#define	IDREF_SPEED24	-3000   
#define	IDREF_SPEED25	-3200 
#define	IDREF_SPEED26	-3400  
#define	IDREF_SPEED27	-3600  
#define	IDREF_SPEED28	-3800 
#define	IDREF_SPEED29	-4000 
#define	IDREF_SPEED30	-4200  
#define	IDREF_SPEED31	-4400  
#define	IDREF_SPEED32	-4600   
#define	IDREF_SPEED33	-4800 
#define	IDREF_SPEED34	-5000  
#define	IDREF_SPEED35	-5200  



/* the follwing values indicate the invKfi variation with speed */
/* please consult app note for details on tuning */
#define	INVKFI_SPEED0	NORM_INVKFIBASE    
#define	INVKFI_SPEED1	6100  
#define	INVKFI_SPEED2	6150  
#define	INVKFI_SPEED3	6200  
#define	INVKFI_SPEED4	6250   
#define	INVKFI_SPEED5	6300  
#define	INVKFI_SPEED6	6350  
#define	INVKFI_SPEED7	6400  
#define	INVKFI_SPEED8	6450  
#define	INVKFI_SPEED9	6500  
#define	INVKFI_SPEED10	6600   
#define	INVKFI_SPEED11	7000   
#define	INVKFI_SPEED12	7200 
#define	INVKFI_SPEED13	7400 
#define	INVKFI_SPEED14	7450  
#define	INVKFI_SPEED15	7500  
#define	INVKFI_SPEED16  7600   
#define	INVKFI_SPEED17	7700  
#define	INVKFI_SPEED18	7800    
#define	INVKFI_SPEED19	7900   
#define	INVKFI_SPEED20	8000   
#define	INVKFI_SPEED21	8200   
#define	INVKFI_SPEED22	8600   
#define	INVKFI_SPEED23	9000  
#define	INVKFI_SPEED24	9500  
#define	INVKFI_SPEED25	10000  
#define	INVKFI_SPEED26	10500  
#define	INVKFI_SPEED27	11000  
#define	INVKFI_SPEED28	11500   
#define	INVKFI_SPEED29	12000   
#define	INVKFI_SPEED30	12500   
#define	INVKFI_SPEED31	13000  
#define	INVKFI_SPEED32	13500  
#define	INVKFI_SPEED33	14000  
#define	INVKFI_SPEED34	14500  
#define	INVKFI_SPEED35	15000

/* the follwing values indicate the Ls variation with speed */
/* please consult app note for details on tuning */
#define     LS_OVER2LS0_SPEED0            Q15(0.5)   
#define     LS_OVER2LS0_SPEED1            Q15(0.0)  
#define     LS_OVER2LS0_SPEED2            Q15(0.0)  
#define     LS_OVER2LS0_SPEED3            Q15(0.0)  
#define     LS_OVER2LS0_SPEED4            Q15(0.0)   
#define     LS_OVER2LS0_SPEED5            Q15(0.0)  
#define     LS_OVER2LS0_SPEED6            Q15(0.0)  
#define     LS_OVER2LS0_SPEED7            Q15(0.0)  
#define     LS_OVER2LS0_SPEED8            Q15(0.0)  
#define     LS_OVER2LS0_SPEED9            Q15(0.0)  
#define     LS_OVER2LS0_SPEED10           Q15(0.0) 
#define     LS_OVER2LS0_SPEED11           Q15(0.0)  
#define     LS_OVER2LS0_SPEED12           Q15(0.0)  
#define     LS_OVER2LS0_SPEED13           Q15(0.0)  
#define     LS_OVER2LS0_SPEED14           Q15(0.0)  
#define     LS_OVER2LS0_SPEED15           Q15(0.0)  
#define     LS_OVER2LS0_SPEED16           Q15(0.0)  
#define     LS_OVER2LS0_SPEED17           Q15(0.0)  
#define     LS_OVER2LS0_SPEED18            Q15(0.0)   
#define     LS_OVER2LS0_SPEED19            Q15(0.0)  
#define     LS_OVER2LS0_SPEED20            Q15(0.0)  
#define     LS_OVER2LS0_SPEED21            Q15(0.0)  
#define     LS_OVER2LS0_SPEED22            Q15(0.0)   
#define     LS_OVER2LS0_SPEED23            Q15(0.0)  
#define     LS_OVER2LS0_SPEED24            Q15(0.0)  
#define     LS_OVER2LS0_SPEED25            Q15(0.0)  
#define     LS_OVER2LS0_SPEED26            Q15(0.0)  
#define     LS_OVER2LS0_SPEED27            Q15(0.0)  
#define     LS_OVER2LS0_SPEED28            Q15(0.0)  
#define     LS_OVER2LS0_SPEED29            Q15(0.0)  
#define     LS_OVER2LS0_SPEED30            Q15(0.0)   
#define     LS_OVER2LS0_SPEED31            Q15(0.0)  
#define     LS_OVER2LS0_SPEED32            Q15(0.0)  
#define     LS_OVER2LS0_SPEED33            Q15(0.0)  
#define     LS_OVER2LS0_SPEED34            Q15(0.0)  
#define     LS_OVER2LS0_SPEED35            Q15(0.0)  




#endif

   
    
      
#define BUFFER_REGISTRO 250

#define DAC_IDC              0    //corriente 
#define DAC_IA               1    //corriente
#define DAC_IB               2    //corriente 
#define DAC_IC               3    //corriente   
    
    
#define CMP_SALIDA_DAC_IQ     5     
#define CMP_SALIDA_DAC_ID     6  
    
#define SALIDA_DAC_SECTOR     10   
#define SALIDA_DAC_ANGULO     11  
    
#define SALIDA_DAC_VD         20  
#define SALIDA_DAC_VQ         21

#define IA_F_PS               30    //corriente filtrada pasa altos
#define IB_F_PS               31    //corriente filtrada pasa altos
#define IC_F_PS               32    //corriente filtrada pasa altos    
    
#define DAC_POTE              40    //pote acel
#define DAC_ter2              41
#define DAC_ter1              42   
#define DAC_POTE_FRENO         43  

    
#define CMP_ANG_EST_MI   50
//#define CMP_SLIDING_FEM_Q     51
//#define CMP_SLIDING_FEM_D     52
    
    
#define DAC_PWM1              60    
    
    
    
#define CTE_ANGULO            LOOPTIME_TCY*65536/2*16 
    
//------------------------------------------------------------------------    


#ifdef MOTOR_BICI_1
    
    //#define  I_ARRANQUE           450       //para shunt 2 mohm
   // #define  I_ARRANQUE           5750       //para bici 
#define  I_ARRANQUE           400       //para motor en vacio   
 

#elif defined(MOTOR_BICI_2)
        #define  I_ARRANQUE           225       //para shunt 1 mohm   (dos de 2 en paralelo)  
#else
    #define  I_ARRANQUE           800 
#endif
    
   #define  V_ARRANQUE           7000       //para shunt 1 mohm   (dos de 2 en paralelo) 
    
    
    
    
