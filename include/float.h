/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* float.h - define floating-point constants

   AUTHOR: Gregory Pietsch

*/

#ifndef _FLOAT_H
#define _FLOAT_H

#include <yvals.h>

typedef union _FP_VALUE_T
{
  unsigned char _X[sizeof (long double)];
  float _F;
  double _D;
  long double _L;
} _FP_VALUE_T;

typedef struct _FP_METRIC_T
{
  int _Size, _Ebits, _Explicit1bit, _Mant_dig, _Dig, _Min_exp, _Max_exp,
    _Min_10_exp, _Max_10_exp;
  _FP_VALUE_T _Max, _Epsilon, _Min, _Inf, _Nan;
} _FP_METRIC_T;

extern const _FP_METRIC_T * const _Flt, * const _Dbl, * const _Ldbl;

#define FLT_RADIX	(2)
#define FLT_ROUNDS	_FLTROUNDS
#define FLT_EVAL_METHOD	_FLTEVALMETHOD
#define DECIMAL_DIG	(_Ldbl->_Dig)

#define FLT_MANT_DIG	(_Flt->_Mant_dig)
#define FLT_DIG		(_Flt->_Dig)
#define FLT_MIN_EXP	(_Flt->_Min_exp)
#define FLT_MAX_EXP	(_Flt->_Max_exp)
#define FLT_MIN_10_EXP	(_Flt->_Min_10_exp)
#define FLT_MAX_10_EXP	(_Flt->_Max_10_exp)
#define FLT_MAX		(_Flt->_Max._F)
#define FLT_EPSILON	(_Flt->_Epsilon._F)
#define FLT_MIN		(_Flt->_Min._F)

#define DBL_MANT_DIG	(_Dbl->_Mant_dig)
#define DBL_DIG		(_Dbl->_Dig)
#define DBL_MIN_EXP	(_Dbl->_Min_exp)
#define DBL_MAX_EXP	(_Dbl->_Max_exp)
#define DBL_MIN_10_EXP	(_Dbl->_Min_10_exp)
#define DBL_MAX_10_EXP	(_Dbl->_Max_10_exp)
#define DBL_MAX		(_Dbl->_Max._D)
#define DBL_EPSILON	(_Dbl->_Epsilon._D)
#define DBL_MIN		(_Dbl->_Min._D)

#define LDBL_MANT_DIG	(_Ldbl->_Mant_dig)
#define LDBL_DIG	(_Ldbl->_Dig)
#define LDBL_MIN_EXP	(_Ldbl->_Min_exp)
#define LDBL_MAX_EXP	(_Ldbl->_Max_exp)
#define LDBL_MIN_10_EXP	(_Ldbl->_Min_10_exp)
#define LDBL_MAX_10_EXP	(_Ldbl->_Max_10_exp)
#define LDBL_MAX	(_Ldbl->_Max._L)
#define LDBL_EPSILON	(_Ldbl->_Epsilon._L)
#define LDBL_MIN	(_Ldbl->_Min._L)

#endif /* _FLOAT_H */