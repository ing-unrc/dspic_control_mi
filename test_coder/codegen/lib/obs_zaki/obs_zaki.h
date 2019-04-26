/*
 * File: obs_zaki.h
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 20-Mar-2019 18:28:34
 */

#ifndef OBS_ZAKI_H
#define OBS_ZAKI_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "obs_zaki_types.h"

/* Function Declarations */
extern void obs_zaki(const float z_est[4], const float vv[2], const float ii[2],
                     float w, float dz[4], float *dw_est1);

#endif

/*
 * File trailer for obs_zaki.h
 *
 * [EOF]
 */
