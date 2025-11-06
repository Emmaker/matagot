/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* pow, powf, powl - power function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the value of x raised to the power y. If x 
   is negative, the application shall ensure that y is an integer value.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the value of x 
   raised to the power y.

   For finite values of x < 0, and finite non-integer values of y, a domain 
   error shall occur and either a NaN (if representable), or an 
   implementation-defined value shall be returned.

   If the correct value would cause overflow, a range error shall occur and 
   pow(), powf(), and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and 
   +/-HUGE_VALL, respectively, with the same sign as the correct value of 
   the function.

   If the correct value would cause underflow, and is not representable, 
   a range error may occur, and pow(), powf(), and powl() shall return 
   0.0, or (if IEC 60559 Floating-Point is not supported) an implementation-
   defined value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
   respectively.

   For y < 0, if x is zero, a pole error may occur and pow(), powf(), 
   and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL, 
   respectively. On systems that support the IEC 60559 Floating-Point option, 
   if x is +/-0, a pole error shall occur and pow(), powf(), and powl() shall 
   return +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL, respectively if y is 
   an odd integer, or HUGE_VAL, HUGE_VALF, and HUGE_VALL, respectively if y 
   is not an odd integer.

   If x or y is a NaN, a NaN shall be returned (unless specified elsewhere 
   in this description).

   For any value of y (including NaN), if x is +1, 1.0 shall be returned.

   For any value of x (including NaN), if y is +/-0, 1.0 shall be returned.

   For any odd integer value of y > 0, if x is +/-0, +/-0 shall be returned.

   For y > 0 and not an odd integer, if x is +/-0, +0 shall be returned.

   If x is -1, and y is +/-Inf, 1.0 shall be returned.

   For |x| < 1, if y is -Inf, +Inf shall be returned.

   For |x| > 1, if y is -Inf, +0 shall be returned.

   For |x| < 1, if y is +Inf, +0 shall be returned.

   For |x| > 1, if y is +Inf, +Inf shall be returned.

   For y an odd integer < 0, if x is -Inf, -0 shall be returned.

   For y < 0 and not an odd integer, if x is -Inf, +0 shall be returned.

   For y an odd integer > 0, if x is -Inf, -Inf shall be returned.

   For y > 0 and not an odd integer, if x is -Inf, +Inf shall be returned.

   For y < 0, if x is +Inf, +0 shall be returned.

   For y > 0, if x is +Inf, +Inf shall be returned. 

   If the correct value would cause underflow, and is representable, a 
   range error may occur and the correct value shall be returned.

   ERRORS:

   These functions shall fail if:

   Domain Error
   
   The value of x is negative and y is a finite non-integer. 
   
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   Pole Error
   
   The value of x is zero and y is negative. 
   
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
   floating-point exception shall be raised.

   Range Error
   
   The result overflows. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   These functions may fail if:

   Pole Error
   
   The value of x is zero and y is negative. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
   floating-point exception shall be raised.

   Range Error
   
   The result underflows. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.

   ALGORITHM:
   
   1. Classify x and y. Determine if y is an integer, and whether y is odd.
   2. Handle all the special cases.
   3. Split x into f and e (x = f * 2^e, e is an integer).
   4. Split y into n and g where n = trunc(y) and y = n + g.
   5. The expression is now f^n * f^g * 2^(e*g) * 2^(e*n).
      Compute f^n by multiplying in a loop.
   6. Compute f^g * 2^(e*g) by calculating exp(g*log(f)+(e*g)*log(2)).
   7. 2^(e*n) is a call to ldexp().
   
*/

#include "xmath.h"

double (pow) (double x, double y)
{
  double ey, eyn, eyg, f, g, m, n, r;
  int e, errr, errx, erry, ni, signx, signy, yint, yodd;

  errx = _Fpclassify (x);
  erry = _Fpclassify (y);

  /* For any value of y (including NaN), if x is +1, 1.0 shall be returned.
     For any value of x (including NaN), if y is +/-0, 1.0 shall be returned.
     If x is -1, and y is +/-Inf, 1.0 shall be returned.  */

  if ((errx == FP_NORMAL && x == 1.0) || erry == FP_ZERO
      || (errx == FP_NORMAL && x == -1.0 && erry == FP_INFINITE))
    return 1.0;

  /* If x or y is a NaN, a NaN shall be returned (unless specified elsewhere 
     in this description).  */

  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;

  signx = _Getsign ((unsigned char *) &x, _Dbl);
  signy = _Getsign ((unsigned char *) &y, _Dbl);
  n = trunc (y);
  g = y - n;
  yint = (_Fpclassify (g) == FP_ZERO);
  yodd = yint && (n != ldexp (trunc (ldexp (n, -1)), 1));
  if (errx == FP_ZERO)
    {
      /* For y < 0, if x is zero, a pole error may occur and pow(), powf(), 
         and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL, 
         respectively. On systems that support the IEC 60559 Floating-Point 
         option, if x is +/-0, a pole error shall occur and pow(), powf(), 
         and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL, 
         respectively if y is an odd integer, or HUGE_VAL, HUGE_VALF, and 
         HUGE_VALL, respectively if y is not an odd integer.

         For any odd integer value of y > 0, if x is +/-0, +/-0 shall be 
         returned.

         For y > 0 and not an odd integer, if x is +/-0, +0 shall be returned. 
       */

      if (signy)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return yodd ? (signy ? -HUGE_VAL : HUGE_VAL) : HUGE_VAL;
	}
      return yodd ? x : +0.0;
    }

  if (errx == FP_INFINITE)
    {
      /* For y an odd integer < 0, if x is -Inf, -0 shall be returned.
         For y < 0 and not an odd integer, if x is -Inf, +0 shall be returned.
         For y an odd integer > 0, if x is -Inf, -Inf shall be returned.
         For y > 0 and not an odd integer, if x is -Inf, +Inf shall be returned. */
      if (signx)
	return signy ? (yodd ? -0.0 : +0.0) : (yodd ? x : _Dbl->_Inf._D);
      /* For y < 0, if x is +Inf, +0 shall be returned.
         For y > 0, if x is +Inf, +Inf shall be returned. */
      return signy ? +0.0 : x;
    }
  /* For |x| < 1, if y is -Inf, +Inf shall be returned.
     For |x| > 1, if y is -Inf, +0 shall be returned.
     For |x| < 1, if y is +Inf, +0 shall be returned.
     For |x| > 1, if y is +Inf, +Inf shall be returned. */
  if (erry == FP_INFINITE)
    return (signy ^ (fabs (x) < 1.0)) ? +0.0 : _Dbl->_Inf._D;
  /* For finite values of x < 0, and finite non-integer values of y, a domain 
     error shall occur and either a NaN (if representable), or an 
     implementation-defined value shall be returned. */
  if (signx && !yint)
    {
      _Matherr (EDOM, FE_INVALID);
      return _Dbl->_Nan._D;
    }
  /* Handled all the special cases */
  if (signx)
    _Setsign ((unsigned char *) &x, _Dbl, 0);
  f = frexp (x, &e);
  ey = e * y;
  eyn = trunc (ey);
  eyg = ey - eyn;
  if (y <= INT_MIN || y >= INT_MAX)
    {
      /* cast precision to the winds */
      g = y;
      n = 0.0;
      yint = yodd = 0;
    }
  for (ni = (int) (fabs (n)), m = f, r = 1.0; ni; m *= m, ni >>= 1)
    {
      if (ni & 1)
	r *= m;
    }
  if (n < 0.0)
    r = 1.0 / r;
  if (!yint)
    r *= exp (g * log (f) + eyg * M_LN2);
  r = ldexp (r, (int) eyn);

  /* If the correct value would cause overflow, a range error shall occur and 
     pow(), powf(), and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and 
     +/-HUGE_VALL, respectively, with the same sign as the correct value of 
     the function.

     If the correct value would cause underflow, and is not representable, 
     a range error may occur, and pow(), powf(), and powl() shall return 
     0.0, or (if IEC 60559 Floating-Point is not supported) an implementation-
     defined value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
     respectively.

     If the correct value would cause underflow, and is representable, a 
     range error may occur and the correct value shall be returned.
   */

  errr = _Fpclassify (r);
  if (errr == FP_INFINITE)
    _Matherr (ERANGE, FE_OVERFLOW);
  else if (errr == FP_ZERO || errr == FP_SUBNORMAL)
    _Matherr (ERANGE, FE_UNDERFLOW);
  if (signx && yodd)
    _Setsign ((unsigned char *) &r, _Dbl, 1);
  return r;
}

float (powf) (float x, float y)
{
  float ey, eyn, eyg, f, g, m, n, r;
  int e, errr, errx, erry, ni, signx, signy, yint, yodd;

  errx = _Fpclassifyf (x);
  erry = _Fpclassifyf (y);

  /* For any value of y (including NaN), if x is +1, 1.0 shall be returned.
     For any value of x (including NaN), if y is +/-0, 1.0 shall be returned.
     If x is -1, and y is +/-Inf, 1.0 shall be returned.  */

  if ((errx == FP_NORMAL && x == 1.0F) || erry == FP_ZERO
      || (errx == FP_NORMAL && x == -1.0F && erry == FP_INFINITE))
    return 1.0F;

  /* If x or y is a NaN, a NaN shall be returned (unless specified elsewhere 
     in this description).  */

  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;

  signx = _Getsign ((unsigned char *) &x, _Flt);
  signy = _Getsign ((unsigned char *) &y, _Flt);
  n = truncf (y);
  g = y - n;
  yint = (_Fpclassifyf (g) == FP_ZERO);
  yodd = yint && (n != ldexpf (truncf (ldexpf (n, -1)), 1));
  if (errx == FP_ZERO)
    {
      /* For y < 0, if x is zero, a pole error may occur and pow(), powf(), 
         and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL, 
         respectively. On systems that support the IEC 60559 Floating-Point 
         option, if x is +/-0, a pole error shall occur and pow(), powf(), 
         and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL, 
         respectively if y is an odd integer, or HUGE_VAL, HUGE_VALF, and 
         HUGE_VALL, respectively if y is not an odd integer.

         For any odd integer value of y > 0, if x is +/-0, +/-0 shall be 
         returned.

         For y > 0 and not an odd integer, if x is +/-0, +0 shall be returned. 
       */

      if (signy)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return yodd ? (signy ? -HUGE_VALF : HUGE_VALF) : HUGE_VALF;
	}
      return yodd ? x : +0.0F;
    }

  if (errx == FP_INFINITE)
    {
      /* For y an odd integer < 0, if x is -Inf, -0 shall be returned.
         For y < 0 and not an odd integer, if x is -Inf, +0 shall be returned.
         For y an odd integer > 0, if x is -Inf, -Inf shall be returned.
         For y > 0 and not an odd integer, if x is -Inf, +Inf shall be returned. */
      if (signx)
	return signy ? (yodd ? -0.0F : +0.0F) : (yodd ? x : _Flt->_Inf._F);
      /* For y < 0, if x is +Inf, +0 shall be returned.
         For y > 0, if x is +Inf, +Inf shall be returned. */
      return signy ? +0.0F : x;
    }
  /* For |x| < 1, if y is -Inf, +Inf shall be returned.
     For |x| > 1, if y is -Inf, +0 shall be returned.
     For |x| < 1, if y is +Inf, +0 shall be returned.
     For |x| > 1, if y is +Inf, +Inf shall be returned. */
  if (erry == FP_INFINITE)
    return (signy ^ (fabsf (x) < 1.0F)) ? +0.0F : _Flt->_Inf._F;
  /* For finite values of x < 0, and finite non-integer values of y, a domain 
     error shall occur and either a NaN (if representable), or an 
     implementation-defined value shall be returned. */
  if (signx && !yint)
    {
      _Matherr (EDOM, FE_INVALID);
      return _Flt->_Nan._F;
    }
  /* Handled all the special cases */
  if (signx)
    _Setsign ((unsigned char *) &x, _Flt, 0);
  f = frexpf (x, &e);
  ey = e * y;
  eyn = truncf (ey);
  eyg = ey - eyn;
  if (y <= INT_MIN || y >= INT_MAX)
    {
      /* cast precision to the winds */
      g = y;
      n = 0.0F;
      yint = yodd = 0;
    }
  for (ni = (int) (fabsf (n)), m = f, r = 1.0F; ni; m *= m, ni >>= 1)
    {
      if (ni & 1)
	r *= m;
    }
  if (n < 0.0F)
    r = 1.0F / r;
  if (!yint)
    r *= expf (g * logf (f) + eyg * _M_LN2F);
  r = ldexpf (r, (int) eyn);

  /* If the correct value would cause overflow, a range error shall occur and 
     pow(), powf(), and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and 
     +/-HUGE_VALL, respectively, with the same sign as the correct value of 
     the function.

     If the correct value would cause underflow, and is not representable, 
     a range error may occur, and pow(), powf(), and powl() shall return 
     0.0, or (if IEC 60559 Floating-Point is not supported) an implementation-
     defined value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
     respectively.

     If the correct value would cause underflow, and is representable, a 
     range error may occur and the correct value shall be returned.
   */

  errr = _Fpclassifyf (r);
  if (errr == FP_INFINITE)
    _Matherr (ERANGE, FE_OVERFLOW);
  else if (errr == FP_ZERO || errr == FP_SUBNORMAL)
    _Matherr (ERANGE, FE_UNDERFLOW);
  if (signx && yodd)
    _Setsign ((unsigned char *) &r, _Flt, 1);
  return r;
}

long double (powl) (long double x, long double y)
{
  long double ey, eyn, eyg, f, g, m, n, r;
  int e, errr, errx, erry, ni, signx, signy, yint, yodd;

  errx = _Fpclassifyl (x);
  erry = _Fpclassifyl (y);

  /* For any value of y (including NaN), if x is +1, 1.0 shall be returned.
     For any value of x (including NaN), if y is +/-0, 1.0 shall be returned.
     If x is -1, and y is +/-Inf, 1.0 shall be returned.  */

  if ((errx == FP_NORMAL && x == 1.0L) || erry == FP_ZERO
      || (errx == FP_NORMAL && x == -1.0L && erry == FP_INFINITE))
    return 1.0L;

  /* If x or y is a NaN, a NaN shall be returned (unless specified elsewhere 
     in this description).  */

  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;

  signx = _Getsign ((unsigned char *) &x, _Ldbl);
  signy = _Getsign ((unsigned char *) &y, _Ldbl);
  n = truncl (y);
  g = y - n;
  yint = (_Fpclassifyl (g) == FP_ZERO);
  yodd = yint && (n != ldexpl (truncl (ldexpl (n, -1)), 1));
  if (errx == FP_ZERO)
    {
      /* For y < 0, if x is zero, a pole error may occur and pow(), powf(), 
         and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL, 
         respectively. On systems that support the IEC 60559 Floating-Point 
         option, if x is +/-0, a pole error shall occur and pow(), powf(), 
         and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL, 
         respectively if y is an odd integer, or HUGE_VAL, HUGE_VALF, and 
         HUGE_VALL, respectively if y is not an odd integer.

         For any odd integer value of y > 0, if x is +/-0, +/-0 shall be 
         returned.

         For y > 0 and not an odd integer, if x is +/-0, +0 shall be returned. 
       */

      if (signy)
	{
	  _Matherr (ERANGE, FE_DIVBYZERO);
	  return yodd ? (signy ? -HUGE_VALL : HUGE_VALL) : HUGE_VALL;
	}
      return yodd ? x : +0.0L;
    }

  if (errx == FP_INFINITE)
    {
      /* For y an odd integer < 0, if x is -Inf, -0 shall be returned.
         For y < 0 and not an odd integer, if x is -Inf, +0 shall be returned.
         For y an odd integer > 0, if x is -Inf, -Inf shall be returned.
         For y > 0 and not an odd integer, if x is -Inf, +Inf shall be returned. */
      if (signx)
	return signy ? (yodd ? -0.0L : +0.0L) : (yodd ? x : _Ldbl->_Inf._L);
      /* For y < 0, if x is +Inf, +0 shall be returned.
         For y > 0, if x is +Inf, +Inf shall be returned. */
      return signy ? +0.0L : x;
    }
  /* For |x| < 1, if y is -Inf, +Inf shall be returned.
     For |x| > 1, if y is -Inf, +0 shall be returned.
     For |x| < 1, if y is +Inf, +0 shall be returned.
     For |x| > 1, if y is +Inf, +Inf shall be returned. */
  if (erry == FP_INFINITE)
    return (signy ^ (fabsl (x) < 1.0L)) ? +0.0L : _Ldbl->_Inf._L;
  /* For finite values of x < 0, and finite non-integer values of y, a domain 
     error shall occur and either a NaN (if representable), or an 
     implementation-defined value shall be returned. */
  if (signx && !yint)
    {
      _Matherr (EDOM, FE_INVALID);
      return _Ldbl->_Nan._L;
    }
  /* Handled all the special cases */
  if (signx)
    _Setsign ((unsigned char *) &x, _Ldbl, 0);
  f = frexp (x, &e);
  ey = e * y;
  eyn = trunc (ey);
  eyg = ey - eyn;
  if (y <= INT_MIN || y >= INT_MAX)
    {
      /* cast precision to the winds */
      g = y;
      n = 0.0L;
      yint = yodd = 0;
    }
  for (ni = (int) (fabs (n)), m = f, r = 1.0L; ni; m *= m, ni >>= 1)
    {
      if (ni & 1)
	r *= m;
    }
  if (n < 0.0L)
    r = 1.0L / r;
  if (!yint)
    r *= expl (g * logl (f) + eyg * _M_LN2L);
  r = ldexpl (r, (int) eyn);

  /* If the correct value would cause overflow, a range error shall occur and 
     pow(), powf(), and powl() shall return +/-HUGE_VAL, +/-HUGE_VALF, and 
     +/-HUGE_VALL, respectively, with the same sign as the correct value of 
     the function.

     If the correct value would cause underflow, and is not representable, 
     a range error may occur, and pow(), powf(), and powl() shall return 
     0.0, or (if IEC 60559 Floating-Point is not supported) an implementation-
     defined value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
     respectively.

     If the correct value would cause underflow, and is representable, a 
     range error may occur and the correct value shall be returned.
   */

  errr = _Fpclassifyl (r);
  if (errr == FP_INFINITE)
    _Matherr (ERANGE, FE_OVERFLOW);
  else if (errr == FP_ZERO || errr == FP_SUBNORMAL)
    _Matherr (ERANGE, FE_UNDERFLOW);
  if (signx && yodd)
    _Setsign ((unsigned char *) &r, _Ldbl, 1);
  return r;
}

/* END OF FILE */
