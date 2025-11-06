/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* sin, sinf, sinl, cos, cosf, cosl - sine and cosine functions

   AUTHOR: Gregory Pietsch
   
   sin, sinf, sinl:
   
   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the sine of their argument x, measured in 
   radians.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the sine of x.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, x shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, sin(), sinf(), and sinl() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, FLT_MIN, 
   and LDBL_MIN, respectively.

   If x is +/-Inf, a domain error shall occur, and a NaN shall be returned. 

   ERRORS

   These functions shall fail if:
   
   Domain Error
   The x argument is +/-Inf. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   These functions may fail if:

   Range Error
   The value of x is subnormal. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised. 

   cos, cosf, cosl:

   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the cosine of their argument x, measured in 
   radians.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the cosine of x.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, the value 1.0 shall be returned.

   If x is +/-Inf, a domain error shall occur, and a NaN shall be returned.

   ERRORS

   These functions shall fail if:
 
   Domain Error
   The x argument is +/-Inf. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.
*/

#include "xmath.h"

/* static functions */

static long double
_Sin (long double x)
{
  long double a, xx, y, z;
  unsigned long d;

  xx = x * x;
  a = y = x;
  d = 1;
  do
    {
      z = y;
      d += 2;
      a = (-a * xx) / (d - 1) / d;
      y += a;
    }
  while (z != y);
  return y;
}

static long double
_Cos (long double x)
{
  long double a, xx, y, z;
  unsigned long d;

  xx = x * x;
  a = y = 1.0L;
  d = 0;
  do
    {
      z = y;
      d += 2;
      a = (-a * xx) / (d - 1) / d;
      y += a;
    }
  while (z != y);
  return y;
}

static long double
_Sincos (long double x, int qoff, const _FP_METRIC_T * const m)
{
  long double dp1, dp2, dp3, lossth, y, z;
  int j, sign = 0;

  /* dp1 + dp2 + dp3 = pi/4 to ridiculous precision */
  if (m->_Size <= 10)
    {
      dp1 = 7.853981554508209228515625E-1L;
      dp2 = 7.94662735614792836713604629039764404296875E-9L;
      dp3 = 3.0616169978683829430651648306875026455243736148E-17L;
      lossth = 5.49755813888e11L;	/* 2^39 */
    }
  else
    {
      dp1 = 7.853981633974483067550664827649598009884357452392578125E-1L;
      dp2 = 2.8605943630549158983813312792950660807511260829685741796657E-18L;
      dp3 = 2.1679525325309452561992610065108379921905808E-35L;
      lossth = 3.6028797018963968E16L;	/* 2^55 */
    }
  /* Once the wheel goes around lossth times, the result just doesn't matter
     anymore, so stop trying so hard.  */
  if (x > lossth)
    {
      /* total loss of precision */
      return 0.0L;
    }
  y = floorl (x / _M_PI_4L);
  /* strip high bits of quotient to prevent integer overflow */
  z = ldexpl (y, -4);
  z = floorl (z);		/* int part of y/8 */
  z = y - ldexpl (z, 4);	/* y - 16 * (y/16) */
  j = z;			/* convert to integer for tests on the phase 
				   angle */
  if (j & 1)
    {
      ++j;
      y += 1.0L;
    }
  j &= 7;
  /* reflect in x-axis */
  if (j > 3)
    {
      sign ^= 1;
      j -= 4;
    }
  if (qoff && j > 1)
    sign ^= 1;
  /* extended-precision modular arithmetic */
  z = ((x - y * dp1) - y * dp2) - y * dp3;
  y = ((j == 1 || j == 2) ^ qoff) ? _Sin (z) : _Cos (z);
  _Setsign ((unsigned char *) &y, m, sign);
  return y;
}

/* exported functions */

double
(sin) (double x)
{
  double y;
  int sign;

  switch (_Fpclassify (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Dbl->_Nan._D;
    default:
      /* because sin(-x) = -sin(x), save and strip sign */
      sign = _Getsign ((unsigned char *) &x, _Dbl);
      _Setsign ((unsigned char *) &x, _Dbl, 0);
      y = (double) _Sincos (x, 0, _Dbl);
      return sign ? -y : y;
    }
}

float
(sinf) (float x)
{
  float y;
  int sign;

  switch (_Fpclassifyf (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Flt->_Nan._F;
    default:
      /* because sin(-x) = -sin(x), save and strip sign */
      sign = _Getsign ((unsigned char *) &x, _Flt);
      _Setsign ((unsigned char *) &x, _Flt, 0);
      y = (float) _Sincos (x, 0, _Flt);
      return sign ? -y : y;
    }
}

long double
(sinl) (long double x)
{
  long double y;
  int sign;

  switch (_Fpclassifyl (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);	/* FALL THROUGH */
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Ldbl->_Nan._L;
    default:
      /* because sin(-x) = -sin(x), save and strip sign */
      sign = _Getsign ((unsigned char *) &x, _Ldbl);
      _Setsign ((unsigned char *) &x, _Ldbl, 0);
      y = _Sincos (x, 0, _Ldbl);
      return sign ? -y : y;
    }
}

double
(cos) (double x)
{
  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      return +1.0;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Dbl->_Nan._D;
    default:
      /* Because cos(x) = cos(-x), ignore sign */
      _Setsign ((unsigned char *) &x, _Dbl, 0);
      return (double) _Sincos (x, 1, _Dbl);
    }
}

float
(cosf) (float x)
{
  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      return +1.0F;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Flt->_Nan._F;
    default:
      /* Because cosf(x) = cosf(-x), ignore sign */
      _Setsign ((unsigned char *) &x, _Flt, 0);
      return (float) _Sincos (x, 1, _Flt);
    }
}

long double
(cosl) (long double x)
{
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      return +1.0L;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return _Ldbl->_Nan._L;
    default:
      /* Because cosl(x) = cosl(-x), ignore sign */
      _Setsign ((unsigned char *) &x, _Ldbl, 0);
      return _Sincos (x, 1, _Ldbl);
    }
}

/* END OF FILE */
