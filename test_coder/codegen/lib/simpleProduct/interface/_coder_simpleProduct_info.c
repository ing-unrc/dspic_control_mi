/*
 * File: _coder_simpleProduct_info.c
 *
 * MATLAB Coder version            : 4.0
 * C/C++ source code generated on  : 20-Mar-2019 17:43:39
 */

/* Include Files */
#include "_coder_simpleProduct_info.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : const mxArray *
 */
const mxArray *emlrtMexFcnResolvedFunctionsInfo(void)
{
  const mxArray *nameCaptureInfo;
  const char * data[7] = {
    "789ced58cd6eda40105eaa344a0f693955e9312f8081a66a7b6a8040ea0868026e1335aaa8b117bc617fc03f09e49217a9aa3c402bf5d8635fa23df4297ae9bd"
    "5eb0c1b66239928923524642cbc767cfb73b9e9d590352622d050078687f362f00c86e80b1ad4f069076c67bc06f413ee58c2b01ecda7d8759f7f05cef938315",
    "464d38342700230aeb166943dd06542670ea46650451999ad2a80f810e0d864fa13a663a0843091158651ef01ad980543cd414708a7f2f6950e9352d0274cd98"
    "4d177b0170e2c3ed63c8fa5780df827cd082f1095e17a5b71aa1970a195d7b00d63c6863dbd5eb87f88b5a5f2af07bd8fa5c5e358d56db7e94faa8c5b8e6bcf4",
    "1f45e8bb7cc7a28a89186d693255319cea7f8ba95f8fd077f963f1a8fc41b00c5dc04c91b1502b48d5425168e4b3b917b2603286db6c28284c85bad0c14c36f3"
    "1d3484aa60c70da3b6e00b5fa69f68be7c3dfffcab906c7e26bd1f6e4f6f18e2efbaf9f738442f1de0e9416d4fa4084b2fb3d673bd7e46de95f746bbb379ec47",
    "e844cd0384e0a4fc2ff7f1d5f3f7e7dd9f5771fb5a54df4f3b0c323abc17c7eea3aeffd5009ee94d1803d1ae5dd6a77a9731f5b643f5fcfcb158bd4e42408205"
    "fefcc7c9d067889a028f508624f8fcbffffdfd7359c76f482fa93ade1cf5117936681ce6505bdd12df1fecd772a73b77a78e5f86dcff1fef5bdbb2899fd79141",
    "2d0275a498fccd6b7e753caa6f289acc5f02e7d6d7c5503d3f1f271f3c91ca10c75f92e7f3c327cbbabee8757df7696fd41c74112e49a55e6350ec4abdb7e53b"
    "54d797e7f3abe77f53e7f3b50006d3eb260c5fa8221be66d9dcf93abebb1f3818729e3f6dde4f2e1c797e5ff2e8b5fd78b7a5e2b944f768eb4937a1756de54b6",
    "2a67f9d2e2d7f57fb6c153b7", "" };

  nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(data, 6216U, &nameCaptureInfo);
  return nameCaptureInfo;
}

/*
 * Arguments    : void
 * Return Type  : mxArray *
 */
mxArray *emlrtMexFcnProperties(void)
{
  mxArray *xResult;
  mxArray *xEntryPoints;
  const char * fldNames[6] = { "Name", "NumberOfInputs", "NumberOfOutputs",
    "ConstantInputs", "FullPath", "TimeStamp" };

  mxArray *xInputs;
  const char * b_fldNames[4] = { "Version", "ResolvedFunctions", "EntryPoints",
    "CoverageInfo" };

  xEntryPoints = emlrtCreateStructMatrix(1, 1, 6, fldNames);
  xInputs = emlrtCreateLogicalMatrix(1, 2);
  emlrtSetField(xEntryPoints, 0, "Name", emlrtMxCreateString("simpleProduct"));
  emlrtSetField(xEntryPoints, 0, "NumberOfInputs", emlrtMxCreateDoubleScalar(2.0));
  emlrtSetField(xEntryPoints, 0, "NumberOfOutputs", emlrtMxCreateDoubleScalar
                (1.0));
  emlrtSetField(xEntryPoints, 0, "ConstantInputs", xInputs);
  emlrtSetField(xEntryPoints, 0, "FullPath", emlrtMxCreateString(
    "/home/facu/documentos/GEA/Desarrollos/control_MI/algoritmos_pic/MI_1_Trans/MI_1/test_coder/simpleProduct.m"));
  emlrtSetField(xEntryPoints, 0, "TimeStamp", emlrtMxCreateDoubleScalar
                (737504.73640046292));
  xResult = emlrtCreateStructMatrix(1, 1, 4, b_fldNames);
  emlrtSetField(xResult, 0, "Version", emlrtMxCreateString(
    "9.4.0.813654 (R2018a)"));
  emlrtSetField(xResult, 0, "ResolvedFunctions", (mxArray *)
                emlrtMexFcnResolvedFunctionsInfo());
  emlrtSetField(xResult, 0, "EntryPoints", xEntryPoints);
  return xResult;
}

/*
 * File trailer for _coder_simpleProduct_info.c
 *
 * [EOF]
 */
