/*
 * File: _coder_obs_zaki_api.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 20-Mar-2019 18:28:34
 */

#ifndef _CODER_OBS_ZAKI_API_H
#define _CODER_OBS_ZAKI_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_obs_zaki_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void obs_zaki(real32_T z_est[4], real32_T vv[2], real32_T ii[2], real32_T
                     w, real32_T dz[4], real32_T *dw_est1);
extern void obs_zaki_api(const mxArray * const prhs[4], int32_T nlhs, const
  mxArray *plhs[2]);
extern void obs_zaki_atexit(void);
extern void obs_zaki_initialize(void);
extern void obs_zaki_terminate(void);
extern void obs_zaki_xil_terminate(void);

#endif

/*
 * File trailer for _coder_obs_zaki_api.h
 *
 * [EOF]
 */
