/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* atan2, atan2f, atan2l - arc tangent functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the principal value of the arc tangent of 
   y/x, using the signs of both arguments to determine the quadrant of the 
   return value.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the arc tangent 
   of y/x in the range [-pi,pi] radians.

   If y is +/-0 and x is < 0, +/-pi shall be returned.

   If y is +/-0 and x is > 0, +/-0 shall be returned.

   If y is < 0 and x is +/-0, -pi/2 shall be returned.

   If y is > 0 and x is +/-0, pi/2 shall be returned.

   If x is 0, a pole error shall not occur.

   If either x or y is NaN, a NaN shall be returned.

   If the correct value would cause underflow, a range error may occur, and 
   atan(), atan2f(), and atan2l() shall return an implementation-defined 
   value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
   respectively.

   If the IEC 60559 Floating-Point option is supported, y/x should be 
   returned.

   If y is +/-0 and x is -0, +/-pi shall be returned.

   If y is +/-0 and x is +0, +/-0 shall be returned.

   For finite values of +/-y > 0, if x is -Inf, +/-pi shall be returned.

   For finite values of +/-y > 0, if x is +Inf, +/-0 shall be returned.

   For finite values of x, if y is +/-Inf, +/-pi/2 shall be returned.

   If y is +/-Inf and x is -Inf, +/-3pi/4 shall be returned.

   If y is +/-Inf and x is +Inf, +/-pi/4 shall be returned.

   If both arguments are 0, a domain error shall not occur. 

   ERRORS:

   These functions may fail if:

   Range Error
   
   The result underflows. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

double (atan2) (double y, double x)
{
  double z;
  int errx, erry, errz, sx, sy;

  erry = _Fpclassify (y);
  errx = _Fpclassify (x);
  /* If either x or y is NaN, a NaN shall be returned. */
  if (errx == FP_NAN)
    return x;
  if (erry == FP_NAN)
    return y;
  sy = _Getsign ((unsigned char *) &y, _Dbl);
  sx = _Getsign ((unsigned char *) &x, _Dbl);
  /* handle Infs */
  if (errx == FP_INFINITE || erry == FP_INFINITE)
    {
      /* If y is +/-Inf and x is -Inf, +/-3pi/4 shall be returned.
         If y is +/-Inf and x is +Inf, +/-pi/4 shall be returned. */
      if (errx == FP_INFINITE && erry == FP_INFINITE)
	return (sx ? (sy ? -M_PI_2 - M_PI_4 : M_PI_2 + M_PI_4)
		: (sy ? -M_PI_4 : M_PI_4));
      /* For finite values of +/-y > 0, if x is -Inf, +/-pi shall be returned.
         For finite values of +/-y > 0, if x is +Inf, +/-0 shall be returned.  */
      if (errx == FP_INFINITE)
	return sx ? (sy ? -M_PI : M_PI) : (sy ? -0.0 : +0.0);
      /* For finite values of x, if y is +/-Inf, +/-pi/2 shall be returned.  */
      return sy ? -M_PI_2 : M_PI_2;
    }
  /* handle zeroes */
  if (errx == FP_ZERO || erry == FP_ZERO)
    {
      /* If y is +/-0 and x is -0, +/-pi shall be returned.
         If y is +/-0 and x is +0, +/-0 shall be returned.  
         If y is +/-0 and x is < 0, +/-pi shall be returned.
         If y is +/-0 and x is > 0, +/-0 shall be returned.  */
      if (erry == FP_ZERO)
	return sx ? (sy ? -M_PI : M_PI) : (sy ? -0.0 : +0.0);
      /* If y is < 0 and x is +/-0, -pi/2 shall be returned.
         If y is > 0 and x is +/-0, pi/2 shall be returned.  */
      return sy ? -M_PI_2 : M_PI_2;
    }
  /* both finite, deal with possible underflow */
  z = y / x;
  errz = _Fpclassify (z);
  if (errz == FP_ZERO || errz == FP_SUBNORMAL)
    {
      /* If the correct value would cause underflow, a range error may occur, and 
         atan(), atan2f(), and atan2l() shall return an implementation-defined 
         value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
         respectively.

         If the IEC 60559 Floating-Point option is supported, y/x should be 
         returned.  */
      _Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    }
  z = atan (z);
  if (sx)
    z += (sy ? -M_PI : M_PI);
  return z;
}

float (atan2f) (float y, float x)
{
  float z;
  int errx, erry, errz, sx, sy;

  erry = _Fpclassifyf (y);
  errx = _Fpclassifyf (x);
  /* If either x or y is NaN, a NaN shall be returned. */
  if (errx == FP_NAN)
    return x;
  if (erry == FP_NAN)
    return y;
  sy = _Getsign ((unsigned char *) &y, _Flt);
  sx = _Getsign ((unsigned char *) &x, _Flt);
  /* handle Infs */
  if (errx == FP_INFINITE || erry == FP_INFINITE)
    {
      /* If y is +/-Inf and x is -Inf, +/-3pi/4 shall be returned.
         If y is +/-Inf and x is +Inf, +/-pi/4 shall be returned. */
      if (errx == FP_INFINITE && erry == FP_INFINITE)
	return (sx ? (sy ? -_M_PI_2F - _M_PI_4F : _M_PI_2F + _M_PI_4F)
		: (sy ? -_M_PI_4F : _M_PI_4F));
      /* For finite values of +/-y > 0, if x is -Inf, +/-pi shall be returned.
         For finite values of +/-y > 0, if x is +Inf, +/-0 shall be returned.  */
      if (errx == FP_INFINITE)
	return sx ? (sy ? -_M_PIF : _M_PIF) : (sy ? -0.0F : +0.0F);
      /* For finite values of x, if y is +/-Inf, +/-pi/2 shall be returned.  */
      return sy ? -_M_PI_2F : _M_PI_2F;
    }
  /* handle zeroes */
  if (errx == FP_ZERO || erry == FP_ZERO)
    {
      /* If y is +/-0 and x is -0, +/-pi shall be returned.
         If y is +/-0 and x is +0, +/-0 shall be returned.  
         If y is +/-0 and x is < 0, +/-pi shall be returned.
         If y is +/-0 and x is > 0, +/-0 shall be returned.  */
      if (erry == FP_ZERO)
	return sx ? (sy ? -_M_PIF : _M_PIF) : (sy ? -0.0F : +0.0F);
      /* If y is < 0 and x is +/-0, -pi/2 shall be returned.
         If y is > 0 and x is +/-0, pi/2 shall be returned.  */
      return sy ? -_M_PI_2F : _M_PI_2F;
    }
  /* both finite, deal with possible underflow */
  z = y / x;
  errz = _Fpclassifyf (z);
  if (errz == FP_ZERO || errz == FP_SUBNORMAL)
    {
      /* If the correct value would cause underflow, a range error may occur, and 
         atan(), atan2f(), and atan2l() shall return an implementation-defined 
         value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
         respectively.

         If the IEC 60559 Floating-Point option is supported, y/x should be 
         returned.  */
      _Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    }
  z = atanf (z);
  if (sx)
    z += (sy ? -_M_PIF : _M_PIF);
  return z;
}

long double (atan2l) (long double y, long double x)
{
  long double z;
  int errx, erry, errz, sx, sy;

  erry = _Fpclassifyl (y);
  errx = _Fpclassifyl (x);
  /* If either x or y is NaN, a NaN shall be returned. */
  if (errx == FP_NAN)
    return x;
  if (erry == FP_NAN)
    return y;
  sy = _Getsign ((unsigned char *) &y, _Ldbl);
  sx = _Getsign ((unsigned char *) &x, _Ldbl);
  /* handle Infs */
  if (errx == FP_INFINITE || erry == FP_INFINITE)
    {
      /* If y is +/-Inf and x is -Inf, +/-3pi/4 shall be returned.
         If y is +/-Inf and x is +Inf, +/-pi/4 shall be returned. */
      if (errx == FP_INFINITE && erry == FP_INFINITE)
	return (sx ? (sy ? -_M_PI_2L - _M_PI_4L : _M_PI_2L + _M_PI_4L)
		: (sy ? -_M_PI_4L : _M_PI_4L));
      /* For finite values of +/-y > 0, if x is -Inf, +/-pi shall be returned.
         For finite values of +/-y > 0, if x is +Inf, +/-0 shall be returned.  */
      if (errx == FP_INFINITE)
	return sx ? (sy ? -_M_PIL : _M_PIL) : (sy ? -0.0L : +0.0L);
      /* For finite values of x, if y is +/-Inf, +/-pi/2 shall be returned.  */
      return sy ? -_M_PI_2L : _M_PI_2L;
    }
  /* handle zeroes */
  if (errx == FP_ZERO || erry == FP_ZERO)
    {
      /* If y is +/-0 and x is -0, +/-pi shall be returned.
         If y is +/-0 and x is +0, +/-0 shall be returned.  
         If y is +/-0 and x is < 0, +/-pi shall be returned.
         If y is +/-0 and x is > 0, +/-0 shall be returned.  */
      if (erry == FP_ZERO)
	return sx ? (sy ? -_M_PIL : _M_PIL) : (sy ? -0.0L : +0.0L);
      /* If y is < 0 and x is +/-0, -pi/2 shall be returned.
         If y is > 0 and x is +/-0, pi/2 shall be returned.  */
      return sy ? -_M_PI_2L : _M_PI_2L;
    }
  /* both finite, deal with possible underflow */
  z = y / x;
  errz = _Fpclassifyl (z);
  if (errz == FP_ZERO || errz == FP_SUBNORMAL)
    {
      /* If the correct value would cause underflow, a range error may occur, and 
         atan(), atan2f(), and atan2l() shall return an implementation-defined 
         value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
         respectively.

         If the IEC 60559 Floating-Point option is supported, y/x should be 
         returned.  */
      _Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    }
  z = atan (z);
  if (sx)
    z += (sy ? -_M_PIL : _M_PIL);
  return z;
}

/* END OF FILE */
