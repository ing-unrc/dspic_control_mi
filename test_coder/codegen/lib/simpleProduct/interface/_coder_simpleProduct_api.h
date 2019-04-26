/*
 * File: _coder_simpleProduct_api.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 20-Mar-2019 17:43:39
 */

#ifndef _CODER_SIMPLEPRODUCT_API_H
#define _CODER_SIMPLEPRODUCT_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_simpleProduct_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real32_T simpleProduct(real32_T a, real32_T b);
extern void simpleProduct_api(const mxArray * const prhs[2], int32_T nlhs, const
  mxArray *plhs[1]);
extern void simpleProduct_atexit(void);
extern void simpleProduct_initialize(void);
extern void simpleProduct_terminate(void);
extern void simpleProduct_xil_terminate(void);

#endif

/*
 * File trailer for _coder_simpleProduct_api.h
 *
 * [EOF]
 */
