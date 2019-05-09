#define S_FUNCTION_NAME  control_MI_dspic_main
#define S_FUNCTION_LEVEL 2

#define SVPWM 1



#include "simstruc.h"   
#include "math.h"
#include <stdint.h>

#include "park.h"
#include "pi.h"
#include "pi.c"
#include "Estim.h"
#include "Estim1.c"
#include "EstimDef.h"
#include "control.h"
#include "UserParms.h"
//#include <libq.h> /* 	 abs function use */

      



void Estim(void);
void InitControlParameters(void);
void CalcTimes(void);

 
 
tParkParm   ParkParm;

tPIParm     PIParmQ;        /* parms for PI controlers */
tPIParm     PIParmD;        /* parms for PI controlers */

tPIParm     PIEst_rho;        //PI estimador

tSincosParm   SincosParm;

extern tEstimParm   EstimParm;


static bool mivarbool = false;
static int contador   = 0;  
//static float Van_ref,Vbn_ref,Vcn_ref;
volatile short int Van_ref,Vbn_ref,Vcn_ref,rampa_iq=0,rampa_id=0,cont_rampa,ref_iq,ref_id;

static short int  Valfa1,Vbeta1,Valfa_fa,Vbeta_fa;

 short int  etapa_arranque;


//static float Vref1,Vref2, Vref3;
static  int Vr1,Vr2, Vr3,Vr1_aux,Vr2_aux, Vr3_aux;

static int cont_tiempo;


static  int t0,T1,T2;

static  int Ta, Tb, Tc; 
static  int Tpwm1, Tpwm2, Tpwm3; 
static int16_t auxIa,auxIb,auxIc;

static short int w, cont_arranque = 0,tita_real,delta_angulo, signo_esdf_ant, signo_esqf_ant,signo_esdf, signo_esqf;

static int aux_32bits,salida_auxiliar;

static short int tita_estimado=0,tension_vf,deltaf_vf;
 
static  short int frec_arranque_count;
extern short int frec_arranque;
extern volatile int16_t modo_acel;


 int16_t x_0[3],x_1[3],y_1[3];
   


static void mdlInitializeSizes(SimStruct *S)
{
    /* See sfuntmpl_doc.c for more details on the macros below */

    ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) 
    {
        /* Return if number of expected != number of actual parameters */
        return;
    }

    ssSetNumContStates(S, 0);
    ssSetNumDiscStates(S, 0);

    if (!ssSetNumInputPorts(S, 1)) return;

    ssSetInputPortWidth(S, 0, 10);//seteamos el ancho del puerto de entrada =4 ( Van_ref, Vbn_ref, Vcn_ref, triang)
    // ssSetInputPortWidth(S, 1, 1);//seteamos el ancho del puerto de entrada1 (es un escalar)=1

    ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    /*
    * Set direct feedthrough flag (1=yes, 0=no).
    * A port has direct feedthrough if the input is used in either
    * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
    * See matlabroot/simulink/src/sfuntmpl_directfeed.txt.
    */
    ssSetInputPortDirectFeedThrough(S, 0, 1); 
    //ssSetInputPortDirectFeedThrough(S, 1, 1);




    if (!ssSetNumOutputPorts(S, 1)) return;
    ssSetOutputPortWidth(S, 0, 30); //modificado para obtener un vector de 6 se�ales de salidas

    ssSetNumSampleTimes(S, 1);//era 1, lo modifique porque tenemos dos tiempos de sampling (el tiempo de simulacion y el de 10khz)
    ssSetNumRWork(S, 0);
    ssSetNumIWork(S, 0);
    ssSetNumPWork(S, 0);
    ssSetNumModes(S, 0);
    ssSetNumNonsampledZCs(S, 0);

    /* Specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S, 0);

    //inicializacion de los PI
    InitPI(&PIParmQ);
    InitPI(&PIParmD);
    InitPI(&PIEst_rho);
    InitControlParameters();
    InitEstimParm();

    cont_tiempo = 0;
    rampa_iq = 0;
    rampa_id = 0;
    cont_arranque = 0;

    signo_esdf_ant = 1;
    signo_esqf_ant = 1;
    etapa_arranque = 0;
    tita_estimado=0;
    deltaf_vf=20;
    tension_vf=100;


   
 }
 


/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
//    ssSetSampleTime(S, 0, 0.000054);
//    ssSetOffsetTime(S, 0, 0.0);
    
    ssSetSampleTime(S, 0, 0.000054); // tiempo de interrupcion 18,51 Khz
   ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);
    
     
}



#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
  /* Function: mdlInitializeConditions ========================================
   * Abstract:
   *    In this function, you should initialize the continuous and discrete
   *    states for your S-function block.  The initial states are placed
   *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
   *    You can also perform any other initialization activities that your
   *    S-function may require. Note, this routine will be called at the
   *    start of simulation and if it is present in an enabled subsystem
   *    configured to reset states, it will be call when the enabled subsystem
   *    restarts execution to reset the states.
   */
  static void mdlInitializeConditions(SimStruct *S)
  {
  }
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START) 
  /* Function: mdlStart =======================================================
   * Abstract:
   *    This function is called once at start of model execution. If you
   *    have states that should be initialized once, this is the place
   *    to do it.
   */
  static void mdlStart(SimStruct *S)
  {
  }
#endif /*  MDL_START */


#define MOD_VECTOR Q15(0.90)

    
#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
  /* Function: mdlUpdate ======================================================
   * Abstract:
   *    This function is called once for every major integration time step.
   *    Discrete states are typically updated here, but this function is useful
   *    for performing any tasks that should only take place once per
   *    integration step.
   */
  static void mdlUpdate(SimStruct *S, int_T tid)
  {
    const real_T *u = (const real_T*) ssGetInputPortSignal(S,0);
    real_T       *y = ssGetOutputPortSignal(S,0);
    
     
    unsigned char onebysqrt3 = 148;   // v5: se cambia 
                                        //onebysqrt = 148; //148 = 1/sqrt(3)*256
    int onebysqrt3q14 = 9459;   // v5: se cambia 

    short int sqrt3 = 222;		//sqrt(3)*128 = 222	
 
    
    int32_t aux_filtro,k1=1077,k2=30614;
    
    UNUSED_ARG(tid); /* not used in single tasking mode */

   
    //--------------------------------------------------------------
    //Si ocurri� un disparo del sampleo de 10khz ejecuta el c�digo -
    //--------------------------------------------------------------
    if (ssIsSampleHit(S, 0, tid)) {
        
        
            
            auxIa = (short int)(218*u[4]);        //150 A pico
            auxIb = (short int)(218*u[5]);
            auxIc = (short int)(218*u[6]); 
            
               
            //filtros pasa bajos de corriente
            
            /* y(n)=1./(1+k).( x(n) + x(n-1) + y(n-1).(k-1))
             * k = fm / (pi*fc)
             * K1 = 1/(1+k)
             * K2 = (1-k)
             **   Copiar en MATLAB: 
                 fm = 18000; fc=400; nfrac = 14;
                 k = fm / (pi*fc);
                 K1 = round(1/(1+k)*2^nfrac)
                 K2 = round((k-1)/(1+k)*2^nfrac)
             *
             *
             */
            
           x_0[0] = ((int16_t)(auxIa));
                    
    
           aux_filtro =  (int32_t)x_0[0];
           aux_filtro += (int32_t)x_1[0];
           aux_filtro = aux_filtro*1069;
           aux_filtro += (14246*(int32_t)y_1[0]);
          
                      
           y_1[0] = (int16_t)((aux_filtro) >> 14);
           x_1[0] = x_0[0];
           Van_ref = y_1[0];     
           
           //Van_ref  = auxIa;
           
           
           x_0[1] = ((int16_t)auxIb);
           
           aux_filtro =  (int32_t)x_0[1];
           aux_filtro += (int32_t)x_1[1];
           aux_filtro = aux_filtro*1069;
           aux_filtro += (14246*(int32_t)y_1[1]);
                  
                  
           y_1[1] = (int16_t)(aux_filtro >> 14);
           x_1[1] = x_0[1];
           Vbn_ref = y_1[1];            
                     
           //Vbn_ref = auxIb;
            
              
           //lazo cerrado 
            
           tita_real = (short)((u[0]*10416)-16384);       //correcion de 90�
           //tita_real = (short)((u[0]*10416));       //correcion de 90�
            
            
            delta_angulo = ParkParm.qAngle-tita_estimado;
            
                   
             
           if(etapa_arranque == 0)     //etapa de establecimiento de corrientes
            {
                cont_arranque++;
                frec_arranque = 0;
                if(cont_arranque == 1000)  // facu: comentado para pasar al smo
                //if(cont_arranque == 1)
                {
                    cont_arranque = 0;
                    //etapa_arranque = 1;
                    etapa_arranque = 1;   // facu: ERA 1
                    //frec_arranque_count = 0;
                }
                
                
            }
            else if(etapa_arranque == 1)          //se genera un ?ngulo para enganchar al PLL y arrancar al motor
             {
                 
                 cont_arranque++;
                 
                 frec_arranque_count++;
                 if(frec_arranque_count >= 20)
                 {
                    frec_arranque_count = 0;
                    if (frec_arranque < 250)
                        frec_arranque++;
                    else
                        etapa_arranque = 2;
                 }
                 
                 
                 if(cont_arranque == 1000)
                 {
                     cont_arranque = 0;
                     ///etapa_arranque = 2;
                 }
                 
                   
                 //  ParkParm.qAngle = u[7]*10430; //tita estimado 1 (desde el observador en diagrama en bloques)
                  
                  
                         
                          
             }
            
            else           //se genera un ?ngulo para enganchar al PLL y arrancar al motor
             {
                          
             }
                        
            
            ParkParm.qAngle = tita_estimado;
             
        
            
               
          //  delta_angulo = ParkParm.qAngle - tita_estimado;
          
         
            ParkParm.qCos = (short)(cos(  ((float)ParkParm.qAngle)/10430  ) * 32767);
            ParkParm.qSin = (short)(sin(  ((float)ParkParm.qAngle)/10430  ) * 32767);
       //     SincosParm.qAngle = ParkParm.qAngle;
            
            
         //   qSin
            
            
    
            
                                  //Transformada de clarke 
                //-----------------------------------------------------
                
          
                //Ialpha = Ia
                //Ibeta  = Ia*dOneBySq3 + 2*Ib*dOneBySq3;
                
                ParkParm.qIalpha = Van_ref;
                
                aux_32bits = (int)Van_ref * (int)9459 + 2 *(int)Vbn_ref * (int)9459;
                ParkParm.qIbeta = ( short )(aux_32bits >>14);
                
               
            //transformada de Park
          
            //Id =  Ialpha*cos(Angle) + Ibeta*sin(Angle)
            //Iq = -Ialpha*sin(Angle) + Ibeta*cos(Angle)
                
  
 
            ParkParm.qId = ( int)( (int)ParkParm.qIalpha * (int)ParkParm.qCos + (int)ParkParm.qIbeta * (int)ParkParm.qSin ) >> 15;
            
            ParkParm.qIq = ( int)( (int)ParkParm.qIbeta * (int)ParkParm.qCos - (int)ParkParm.qIalpha * (int)ParkParm.qSin ) >> 15;
            

            //estimador
            
            
            //tensiones para estimador tomadas de la medici�n de tensiones de fase
            //ParkParm.qValpha = u[7];
            //ParkParm.qVbeta = u[8];
              
            
            //tensiones para estimador tomadas del c�lculo
            ParkParm.qValpha = Valfa_fa;
            ParkParm.qVbeta = Vbeta_fa;                    

            
            
            //EstimParm.qRho = tita_real; //// BORRAR
            Estim();    

            tita_estimado =( EstimParm.qRho);
            //tita_estimado =   tita_real;
            tita_estimado = u[7]*10430;

            //tita_estimado = 0;
   
                
            //PIs
            
            ref_iq = u[1];
            ref_id = u[2];
            
            if( (etapa_arranque == 0) || (etapa_arranque == 1) ) 
            {
                ref_id = 3823;
                //ref_iq = ref_iq;// me.pote_acel;
            }
            else
            {
                 //ref_iq = me.pote_acel;
                //ref_iq= ref_iq; //me.pote_acel;
            }
            
  
            
            cont_rampa++;
            if(cont_rampa == 1)
            {
                cont_rampa = 0;
                
                if(rampa_iq < ref_iq)
               {
                   rampa_iq+=3;
               }
               if(rampa_iq > ref_iq)
               {
                   rampa_iq-=3;
               }

               if(rampa_id < ref_id)
               {
                   rampa_id+=2;
               }
               if(rampa_id > ref_id)
               {
                   rampa_id-=2;
               }               
            }
            
            PIParmQ.qInRef =  rampa_iq;  
            PIParmD.qInRef =  rampa_id; 
       
            PIParmQ.qInMeas = ParkParm.qIq;
            PIParmD.qInMeas = ParkParm.qId;
            
            CalcPI(&PIParmD);
         
            
            //saturacion 



            //    aux_32bits = (int)(((int)PIParmD.qOut * (int)PIParmD.qOut)>>15);

            //  aux_32bits = (int)(MOD_VECTOR) - aux_32bits;


            //aux_32bits = Raiz_iq(aux_32bits);  


            //    if(aux_32bits > Q_CURRCNTR_OUTMAX)
            //       aux_32bits = Q_CURRCNTR_OUTMAX;

            // PIParmQ.qOutMax = (short)aux_32bits;
            
            CalcPI(&PIParmQ);
            
            ParkParm.qVq = PIParmQ.qOut;
            ParkParm.qVd = PIParmD.qOut;

            //transformada inversa de Park


            //Valpha =  Vd*cos(Angle) - Vq*sin(Angle)
            //Vbeta  =  Vd*sin(Angle) + Vq*cos(Angle)
            
            ParkParm.qCos = (short)(cos(  ((float) (ParkParm.qAngle+5454))/10430  ) * 32767);
            ParkParm.qSin = (short)(sin(  ((float) (ParkParm.qAngle+5454))/10430  ) * 32767);              
            //ParkParm.qCos = (short)(cos(  ((float) (ParkParm.qAngle))/10416  ) * 32767);
            //ParkParm.qSin = (short)(sin(  ((float) (ParkParm.qAngle))/10416  ) * 32767);  


            aux_32bits = (  int)ParkParm.qVd*(  int)ParkParm.qCos - (  int)ParkParm.qVq*(int)ParkParm.qSin;
            ParkParm.qValpha = (short int)(aux_32bits>>15);

            
           // ParkParm.qCos = (short)(cos(  ((float) (ParkParm.qAngle+0))/10430  ) * 32767);
            //ParkParm.qSin = (short)(sin(  ((float) (ParkParm.qAngle+0))/10430  ) * 32767);
            
            aux_32bits = (  int)ParkParm.qVd*(  int)ParkParm.qSin + (  int)ParkParm.qVq*(int)ParkParm.qCos;
            ParkParm.qVbeta = (short int)(aux_32bits>>15);


     
            //-----------------------------------------------------

            //Transformada  inversa: en Microhip estaban invertidos Valfa y Vbeta

            // Vr1 = qValpha
            // Vr2 = (-qValpha/2 + sqrt(3)/2 * Vbeta)
            // Vr3 = (-qValpha/2 - sqrt(3/2) * Vbeta)


            Vr1_aux= (int)ParkParm.qValpha*2;		

            aux_32bits = ((int)ParkParm.qValpha) << 14; 
            aux_32bits = - aux_32bits + (( int)28378*( int)ParkParm.qVbeta);
            Vr2_aux	 = ( int)(aux_32bits >> 15)*2; 

            aux_32bits = ((int)ParkParm.qValpha) << 14; 
            aux_32bits = -aux_32bits  - (( int)28378*( int)ParkParm.qVbeta);
            Vr3_aux = ( int)(aux_32bits >> 15)*2; 

            //cambio de secuencia y fase para que Vr1, Vr2 y Vr3 est�n en fase y secuencia con la tensi�n generada por el inversor

            Vr1 = -Vr2_aux;
            Vr2 = -Vr1_aux; 
            Vr3 = -Vr3_aux; 

            //conversi�n de Valfa Vbeta de l�nea a Valfa Vbeta de fase para observador
            // ORIG
            //Valfa_fa = 1/sqrt(3)*[Valfa*sqrt(3)/2 + Vbeta / 2] = [Valfa + Vbeta / sqrt(3)]/2
            //Vbeta_fa = 1/sqrt(3)*[ -Valfa/2 + Vbeta * sqrt(3)/ 2 ] = [ -Valfa/sqrt(3) + Vbeta ]/2

            // CORRECC MAGNITUD
            //Valfa_fa = sqrt(3)/2 * 1/sqrt(3)*[Valfa*sqrt(3)/2 + Vbeta / 2] 
            //         = [Valfa*sqrt(3) + Vbeta ]* 1/4
            //Vbeta_fa = sqrt(3)/2 1/sqrt(3)*[ -Valfa/2 + Vbeta * sqrt(3)/ 2 ]
            //         = [- Valfa + Vbeta* sqrt(3)] * 1/4


            // CORRECC 2
            //Valfa_fa = [Valfa*1/2 + Vbeta  * sqrt(3)/ 2] 
            //         = [Valfa + Vbeta  * sqrt(3)] * 1/2
            //Vbeta_fa = [ -Valfa*sqrt(3)/ 2 + Vbeta *1/2 ]
            //         = [ -Valfa*sqrt(3) + Vbeta ] *1/2
 
            
            ParkParm.qCos = (short)(cos(  ((float) (ParkParm.qAngle))/10430  ) * 32767);
            ParkParm.qSin = (short)(sin(  ((float) (ParkParm.qAngle))/10430  ) * 32767); 
            

            aux_32bits = (  int)ParkParm.qVd*(  int)ParkParm.qCos - (  int)ParkParm.qVq*(int)ParkParm.qSin;
            aux_32bits = (aux_32bits>>15)*(int)9459;
            Valfa_fa = (short int)(aux_32bits>>14);
            

            aux_32bits = (  int)ParkParm.qVd*(  int)ParkParm.qSin + (  int)ParkParm.qVq*(int)ParkParm.qCos;
            aux_32bits = (aux_32bits>>15)*(int)9459;
            Vbeta_fa = (short int)(aux_32bits>>14);
            
            ParkParm.qCos = (short)(cos(  ((float) (ParkParm.qAngle-0))/10430  ) * 32767);
            ParkParm.qSin = (short)(sin(  ((float) (ParkParm.qAngle-0))/10430  ) * 32767); 
            
            
            // ParkParm.qCos = (short)(cos(  ((float) (ParkParm.qAngle))/10416  ) * 32767);
            // ParkParm.qSin = (short)(sin(  ((float) (ParkParm.qAngle))/10416  ) * 32767); 
            
            
            /*
            aux_32bits = (((int)ParkParm.qValpha)<<14)  + ((int)ParkParm.qVbeta*(int)9459);
            //aux_32bits = ( int )(aux_32bits >>10)*512; //  48/42*2^9
            Valfa_fa = ( short )(aux_32bits >>15);  // 1/2

            aux_32bits = -((int)ParkParm.qValpha*(int)9459)  + (((int)ParkParm.qVbeta)<<14);
            //aux_32bits = ( int )(aux_32bits >>10)*512;  //  48/42*2^9
            Vbeta_fa = ( short )(aux_32bits >>15   );  // 1/2  
            */




    
       
     if( Vr1 >= 0 )
        {       
        // (xx1)
        if( Vr2 >= 0 )
            {
            // (x11)
            // Must be Sector 3 since Sector 7 not allowed
            // Sector 3: (0,1,1)  0-60 degrees
            T2 = Vr2;
            T1 = Vr1;
            CalcTimes();
            Tpwm1 = Ta;
            Tpwm2 = Tb;
            Tpwm3 = Tc;

            }
        else
            {             
            // (x01)
            if( Vr3 >= 0 )
                {
                // Sector 5: (1,0,1)  120-180 degrees
                T2 = Vr1;
                T1 = Vr3;
                CalcTimes();
                Tpwm1 = Tc;
                Tpwm2 = Ta;
                Tpwm3 = Tb;
  

                }
            else
                {
                // Sector 1: (0,0,1)  60-120 degrees
                T2 = -Vr2;
                T1 = -Vr3;
                CalcTimes();
                Tpwm1 = Tb;
                Tpwm2 = Ta;
                Tpwm3 = Tc;
       
                }
            }
        }
    else
        {
        // (xx0)
        if( Vr2 >= 0 )
            {
            // (x10)
            if( Vr3 >= 0 )
                {
                // Sector 6: (1,1,0)  240-300 degrees
                T2 = Vr3;
                T1 = Vr2;
                CalcTimes();
                Tpwm1 = Tb;
                Tpwm2 = Tc;
                Tpwm3 = Ta;
       
                }
            else
                {
                // Sector 2: (0,1,0)  300-0 degrees
                T2 = -Vr3;
                T1 = -Vr1;
                CalcTimes();
                Tpwm1 = Ta;
                Tpwm2 = Tc;
                Tpwm3 = Tb;
      
                }
            }
        else
            {            
            // (x00)
            // Must be Sector 4 since Sector 0 not allowed
            // Sector 4: (1,0,0)  180-240 degrees
            T2 = -Vr1;
            T1 = -Vr2;
            CalcTimes();
            Tpwm1 = Tc;
            Tpwm2 = Tb;
            Tpwm3 = Ta;

            }
        } 
                 

                       
        
    }
    
  }
  
  
#define PWM 35000  
void CalcTimes(void)
{
    T1 = (T1*PWM)/65536 ;
    T2 = (T2*PWM)/65536 ;
    Tc = (PWM-T1-T2)/2;
    Tb = Tc + T1;
    Ta = Tb + T2;
}     
  
#endif /* MDL_UPDATE */





    
    



#define DT 5

/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{
    const real_T *u = (const real_T*) ssGetInputPortSignal(S,0);
    real_T       *y = ssGetOutputPortSignal(S,0);
    

    //-----------------------------------------
    //-     comparacion con la triangular    --
    //-----------------------------------------
    y[0] = (float)(EstimParm.qRho)/10430;
    y[1] = (float)(EstimParm.qEsAbs);

    y[2] = (float)(EstimParm.qDIalpha);  
    y[3] = (float)(EstimParm.qDIbeta);      

    y[4] = (float)(EstimParm.qVIndalpha );
    y[5] = (float)(EstimParm.qVIndbeta );

    y[6]= (float)ParkParm.qIalpha;
    y[7]= (float)ParkParm.qIbeta;

    y[8]= Valfa_fa;
    y[9]= Vbeta_fa;  

    y[10]= (float)ParkParm.qIq;
    y[11]= (float)ParkParm.qId;    

    y[12]= (float)ParkParm.qVq;
    y[13]= (float)ParkParm.qVd;

    y[14]=(float)PIParmQ.qInRef - PIParmQ.qInMeas;    //errores 
    y[15]=(float)PIParmD.qInRef - PIParmD.qInMeas;


    y[16]=((float)(tita_real))/10430;    // 10430 = 65536/ (2*pi)

    y[17]=(float)EstimParm.qEsa;
    y[18]=(float)EstimParm.qEsb;

    y[19] = ((float)(tita_estimado)/10430);


    y[20] = (float)EstimParm.qEsqf;

    y[21] = (float)EstimParm.qEsdf;        

    y[22] = (float)EstimParm.qOmegaMr;  

    y[23] = (float)EstimParm.qEsq;

    y[24] = (float)EstimParm.qEsd;

    y[25] = ((float)(delta_angulo)/10430);

    y[26] =  ((float)(ParkParm.qAngle)/10430);

    // y[27] = (float)Vr1_aux;

    // y[28] = (float)Vr2_aux;        

    //y[29] = (float)Vr3_aux;


    y[27] = Tpwm1;
    y[28] = Tpwm2; 
    y[29] = Tpwm3; 


    
}

  
  

#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
  /* Function: mdlDerivatives =================================================
   * Abstract:
   *    In this function, you compute the S-function block's derivatives.
   *    The derivatives are placed in the derivative vector, ssGetdX(S).
   */
  static void mdlDerivatives(SimStruct *S)
  {
  }
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
}


/*======================================================*
 * See sfuntmpl_doc.c for the optional S-function methods *
 *======================================================*/

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif


 void InitControlParameters(void)

{

    
    // ============= PI D Term ===============      
    PIParmD.qKp = D_CURRCNTR_PTERM;       
    PIParmD.qKi = D_CURRCNTR_ITERM;              
    PIParmD.qKc = D_CURRCNTR_CTERM;       
    PIParmD.qOutMax = D_CURRCNTR_OUTMAX;
    PIParmD.qOutMin = -PIParmD.qOutMax;

    InitPI(&PIParmD);

    // ============= PI Q Term ===============
    
    PIParmQ.qKp = Q_CURRCNTR_PTERM;    
    PIParmQ.qKi = Q_CURRCNTR_ITERM;
    PIParmQ.qKc = Q_CURRCNTR_CTERM;
    PIParmQ.qOutMax = Q_CURRCNTR_OUTMAX;
    PIParmQ.qOutMin = -PIParmQ.qOutMax;

    InitPI(&PIParmQ);
    
    
    // ============= PI Estim
    
    PIEst_rho.qKp = EST_PTERM;    
    PIEst_rho.qKi = EST_ITERM;
    PIEst_rho.qKc = EST_CTERM;
    PIEst_rho.qOutMax = EST_OUTMAX;
    PIEst_rho.qOutMin = -PIEst_rho.qOutMax;

    InitPI(&PIEst_rho);    
    
    //PI de velocidad
/*
    // ============= PI Qref Term ===============
    PIParmQref.qKp = SPEEDCNTR_PTERM;       
    PIParmQref.qKi = SPEEDCNTR_ITERM;       
    PIParmQref.qKc = SPEEDCNTR_CTERM;       
    PIParmQref.qOutMax = SPEEDCNTR_OUTMAX;   
    PIParmQref.qOutMin = -PIParmQref.qOutMax;

    InitPI(&PIParmQref);
 * 
 * 
*/
    
    // zero out i sums 
    PIParmD.qdSum = 0;
    PIParmQ.qdSum = 0;
  //  PIParmQref.qdSum = 0;
        
    
    PIParmQ.qInRef  = 0;
    PIParmD.qInRef  = 0;
    
 //   PIParmQ.qKp = 10000;
 //   PIParmD.qKp = 10000;
 //   PIParmQ.qKi = 50;
  //  PIParmD.qKi = 50;
    
    
	return;
}


