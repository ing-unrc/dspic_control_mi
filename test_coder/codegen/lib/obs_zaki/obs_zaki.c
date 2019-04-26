/*
 * File: obs_zaki.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 20-Mar-2019 18:28:34
 */

/* Include Files */
#include <math.h>
#include "rt_nonfinite.h"
#include "obs_zaki.h"

/* Function Definitions */

/*
 * Parametros necesarios
 *  - Observador
 *    k, del
 *
 *  - Maquina
 *    AA, BB
 * Arguments    : const float z_est[4]
 *                const float vv[2]
 *                const float ii[2]
 *                float w
 *                float dz[4]
 *                float *dw_est1
 * Return Type  : void
 */
void obs_zaki(const float z_est[4], const float vv[2], const float ii[2], float
              w, float dz[4], float *dw_est1)
{
  float eid;
  float k2;
  float eiq;
  float ld;
  float lq;
  float v_id;
  float v_iq;
  float f1;
  float f2;
  float f3;
  float f4;
  float c;
  float lam_d_est1;
  float lam_q_est1;
  float i_q_est1;
  float i_d_est1;
  float b_c;
  float c_c;

  /*  Entradas */
  /*  estimador zaki */
  eid = w;
  if (w < 0.0F) {
    eid = -1.0F;
  } else if (w > 0.0F) {
    eid = 1.0F;
  } else {
    if (w == 0.0F) {
      eid = 0.0F;
    }
  }

  k2 = 0.001F * eid;

  /*  Funciones discontinuas */
  /*  == Paso 1 */
  eid = z_est[0] - ii[0];
  eiq = z_est[3] - ii[1];

  /* ld = 2/(1+exp(-2*eid))-1; */
  /* lq = 2/(1+exp(-2*eiq))-1; */
  ld = eid / ((float)fabs(eid) + 50.0F);
  lq = eiq / ((float)fabs(eiq) + 50.0F);
  v_id = 7.0F * ld;
  v_iq = 7.0F * lq;
  f1 = ((ii[0] - z_est[1]) - w * z_est[2]) + (-v_id + k2 * v_iq);
  f2 = ((ii[1] - z_est[2]) + w * z_est[1]) + (-k2 * v_id + -v_iq);
  f3 = (((-z_est[3] + z_est[2]) - w * z_est[1]) + vv[1]) - v_iq;
  f4 = (((-z_est[0] + z_est[1]) + w * z_est[2]) + vv[0]) - v_id;
  c = ld * z_est[2] - lq * z_est[1];
  lam_d_est1 = z_est[1] + f1;
  lam_q_est1 = z_est[2] + f2;
  i_q_est1 = z_est[3] + f3;
  i_d_est1 = z_est[0] + f4;
  *dw_est1 = w + -c;

  /*  == Paso 2 */
  eid = i_d_est1 - ii[0];
  eiq = i_q_est1 - ii[1];

  /* ld = 2/(1+exp(-2*eid))-1; */
  /* lq = 2/(1+exp(-2*eiq))-1; */
  ld = eid / ((float)fabs(eid) + 50.0F);
  lq = eiq / ((float)fabs(eiq) + 50.0F);
  v_id = 7.0F * ld;
  v_iq = 7.0F * lq;

  /* dw_est1 = w; */
  b_c = (ii[0] - lam_d_est1) - *dw_est1 * lam_q_est1;
  c_c = (ii[1] - lam_q_est1) + *dw_est1 * lam_d_est1;
  eiq = ((-i_q_est1 + lam_q_est1) - *dw_est1 * lam_d_est1) + vv[1];
  eid = ((-i_d_est1 + lam_d_est1) + *dw_est1 * lam_q_est1) + vv[0];
  *dw_est1 = w + 20000.0F * (-c + -(ld * lam_q_est1 - lq * lam_d_est1));
  dz[0] = z_est[0] + 0.5F * (f4 + (eid - v_id));
  dz[1] = z_est[1] + 0.5F * (f1 + (b_c + (-v_id + k2 * v_iq)));
  dz[2] = z_est[2] + 0.5F * (f2 + (c_c + (-k2 * v_id + -v_iq)));
  dz[3] = z_est[3] + 0.5F * (f3 + (eiq - v_iq));
}

/*
 * File trailer for obs_zaki.c
 *
 * [EOF]
 */
