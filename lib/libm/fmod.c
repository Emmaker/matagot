/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fmod, fmodf, fmodl - floating-point remainder value function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall return the floating-point remainder of the division 
   of x by y.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   These functions shall return the value x - i * y, for some integer i such 
   that, if y is non-zero, the result has the same sign as x and magnitude 
   less than the magnitude of y.

   If the correct value would cause underflow, and is not representable, 
   a range error may occur, and fmod(), fmodf(), and fmodl() shall return 
   0.0, or (if the IEC 60559 Floating-Point option is not supported) an 
   implementation-defined value no greater in magnitude than DBL_MIN, FLT_MIN, 
   and LDBL_MIN, respectively.

   If x or y is NaN, a NaN shall be returned.

   If y is zero, a domain error shall occur, and a NaN shall be returned.

   If x is infinite, a domain error shall occur, and a NaN shall be returned.

   If x is +/-0 and y is not zero, +/-0 shall be returned.

   If x is not infinite and y is +/-Inf, x shall be returned.

   If the correct value would cause underflow, and is representable, a range 
   error may occur and the correct value shall be returned.

   ERRORS:

   These functions shall fail if:

   Domain Error
   The x argument is infinite or y is zero.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, then 
   errno shall be set to EDOM. If the integer expression (math_errhandling & 
   MATH_ERREXCEPT) is non-zero, then the invalid floating-point exception shall 
   be raised.

   These functions may fail if:

   Range Error
   The result underflows.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, then 
   errno shall be set to ERANGE. If the integer expression (math_errhandling & 
   MATH_ERREXCEPT) is non-zero, then the underflow floating-point exception 
   shall be raised.

   ALGORITHM:
   Repeated subtraction.
*/

#include "xmath.h"

double (fmod) (double x, double y)
{
  int errx, erry, n, neg, xchar, ychar;
  double t;

  errx = _Fpclassify (x);
  erry = _Fpclassify (y);
  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;	/* return whichever is a NaN */
  if (errx == FP_INFINITE || erry == FP_ZERO)
    {
      _Matherr (EDOM, FE_INVALID);
      return _Dbl->_Nan._D;
    }
  if (errx == FP_ZERO || erry == FP_INFINITE)
    return x;
  _Setsign ((unsigned char *) &y, _Dbl, 0);
  neg = _Getsign ((unsigned char *) &x, _Dbl);
  _Setsign ((unsigned char *) &x, _Dbl, 0);
  frexp (x, &xchar);
  frexp (y, &ychar);
  /* subtract |y| until |x|<|y| */
  for (n = xchar - ychar; 0 <= n; --n)
    {
      /* try to subtract |y|*2^n */
      t = ldexp (y, n);
      if (t < x)
	x -= t;
    }
  if (_Fpclassify (x) == FP_ZERO)
    _Matherr (ERANGE, FE_UNDERFLOW);
  _Setsign ((unsigned char *) &x, _Dbl, neg);
  return x;
}

float (fmodf) (float x, float y)
{
  int errx, erry, n, neg, xchar, ychar;
  float t;

  errx = _Fpclassifyf (x);
  erry = _Fpclassifyf (y);
  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;	/* return whichever is a NaN */
  if (errx == FP_INFINITE || erry == FP_ZERO)
    {
      _Matherr (EDOM, FE_INVALID);
      return _Flt->_Nan._F;
    }
  if (errx == FP_ZERO || erry == FP_INFINITE)
    return x;
  _Setsign ((unsigned char *) &y, _Flt, 0);
  neg = _Getsign ((unsigned char *) &x, _Flt);
  _Setsign ((unsigned char *) &x, _Flt, 0);
  frexpf (x, &xchar);
  frexpf (y, &ychar);
  /* subtract |y| until |x|<|y| */
  for (n = xchar - ychar; 0 <= n; --n)
    {
      /* try to subtract |y|*2^n */
      t = ldexpf (y, n);
      if (t < x)
	x -= t;
    }
  if (_Fpclassifyf (x) == FP_ZERO)
    _Matherr (ERANGE, FE_UNDERFLOW);
  _Setsign ((unsigned char *) &x, _Flt, neg);
  return x;
}

long double (fmodl) (long double x, long double y)
{
  int errx, erry, n, neg, xchar, ychar;
  long double t;

  errx = _Fpclassifyl (x);
  erry = _Fpclassifyl (y);
  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;	/* return whichever is a NaN */
  if (errx == FP_INFINITE || erry == FP_ZERO)
    {
      _Matherr (EDOM, FE_INVALID);
      return _Ldbl->_Nan._L;
    }
  if (errx == FP_ZERO || erry == FP_INFINITE)
    return x;
  _Setsign ((unsigned char *) &y, _Ldbl, 0);
  neg = _Getsign ((unsigned char *) &x, _Ldbl);
  _Setsign ((unsigned char *) &x, _Ldbl, 0);
  frexpl (x, &xchar);
  frexpl (y, &ychar);
  /* subtract |y| until |x|<|y| */
  for (n = xchar - ychar; 0 <= n; --n)
    {
      /* try to subtract |y|*2^n */
      t = ldexpl (y, n);
      if (t < x)
	x -= t;
    }
  if (_Fpclassifyl (x) == FP_ZERO)
    _Matherr (ERANGE, FE_UNDERFLOW);
  _Setsign ((unsigned char *) &x, _Ldbl, neg);
  return x;
}

/* END OF FILE */
