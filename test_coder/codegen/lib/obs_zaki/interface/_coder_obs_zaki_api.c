/*
 * File: _coder_obs_zaki_api.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 20-Mar-2019 18:28:34
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_obs_zaki_api.h"
#include "_coder_obs_zaki_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131466U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "obs_zaki",                          /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4]);
static const mxArray *b_emlrt_marshallOut(const real32_T u);
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *vv, const
  char_T *identifier, real32_T y[2]);
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[2]);
static real32_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *w, const
  char_T *identifier);
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *z_est, const
  char_T *identifier, real32_T y[4]);
static const mxArray *emlrt_marshallOut(const real32_T u[4]);
static real32_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4]);
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[2]);
static real32_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[4]
 * Return Type  : void
 */
static void b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[4])
{
  g_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const real32_T u
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real32_T u)
{
  const mxArray *y;
  const mxArray *m1;
  y = NULL;
  m1 = emlrtCreateNumericMatrix(1, 1, mxSINGLE_CLASS, mxREAL);
  *(real32_T *)emlrtMxGetData(m1) = u;
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *vv
 *                const char_T *identifier
 *                real32_T y[2]
 * Return Type  : void
 */
static void c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *vv, const
  char_T *identifier, real32_T y[2])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  d_emlrt_marshallIn(sp, emlrtAlias(vv), &thisId, y);
  emlrtDestroyArray(&vv);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 *                real32_T y[2]
 * Return Type  : void
 */
static void d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId, real32_T y[2])
{
  h_emlrt_marshallIn(sp, emlrtAlias(u), parentId, y);
  emlrtDestroyArray(&u);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *w
 *                const char_T *identifier
 * Return Type  : real32_T
 */
static real32_T e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *w, const
  char_T *identifier)
{
  real32_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(w), &thisId);
  emlrtDestroyArray(&w);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *z_est
 *                const char_T *identifier
 *                real32_T y[4]
 * Return Type  : void
 */
static void emlrt_marshallIn(const emlrtStack *sp, const mxArray *z_est, const
  char_T *identifier, real32_T y[4])
{
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  b_emlrt_marshallIn(sp, emlrtAlias(z_est), &thisId, y);
  emlrtDestroyArray(&z_est);
}

/*
 * Arguments    : const real32_T u[4]
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real32_T u[4])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[1] = { 4 };

  real32_T *pData;
  int32_T i0;
  int32_T i;
  y = NULL;
  m0 = emlrtCreateNumericArray(1, iv0, mxSINGLE_CLASS, mxREAL);
  pData = (real32_T *)emlrtMxGetData(m0);
  i0 = 0;
  for (i = 0; i < 4; i++) {
    pData[i0] = u[i];
    i0++;
  }

  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real32_T
 */
static real32_T f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real32_T y;
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[4]
 * Return Type  : void
 */
static void g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[4])
{
  static const int32_T dims[2] = { 1, 4 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 2U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 *                real32_T ret[2]
 * Return Type  : void
 */
static void h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId, real32_T ret[2])
{
  static const int32_T dims[2] = { 1, 2 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 2U, dims);
  emlrtImportArrayR2015b(sp, src, ret, 4, false);
  emlrtDestroyArray(&src);
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real32_T
 */
static real32_T i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
{
  real32_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "single|double", false, 0U, &dims);
  emlrtImportArrayR2015b(sp, src, &ret, 4, false);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray * const prhs[4]
 *                int32_T nlhs
 *                const mxArray *plhs[2]
 * Return Type  : void
 */
void obs_zaki_api(const mxArray * const prhs[4], int32_T nlhs, const mxArray
                  *plhs[2])
{
  real32_T z_est[4];
  real32_T vv[2];
  real32_T ii[2];
  real32_T w;
  real32_T dz[4];
  real32_T dw_est1;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "z_est", z_est);
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "vv", vv);
  c_emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "ii", ii);
  w = e_emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "w");

  /* Invoke the target function */
  obs_zaki(z_est, vv, ii, w, dz, &dw_est1);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(dz);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(dw_est1);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void obs_zaki_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  obs_zaki_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void obs_zaki_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void obs_zaki_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_obs_zaki_api.c
 *
 * [EOF]
 */
