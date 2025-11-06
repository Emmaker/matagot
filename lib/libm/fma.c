/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fma, fmaf, fmal - floating-point multiply-add

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute (x * y) + z, rounded as one ternary 
   operation: they shall compute the value (as if) to infinite precision and 
   round once to the result format, according to the rounding mode 
   characterized by the value of FLT_ROUNDS.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return (x * y) + z, 
   rounded as one ternary operation.

   If the result overflows or underflows, a range error may occur. On systems 
   that support the IEC 60559 Floating-Point option, if the result overflows 
   a range error shall occur.

   If x or y are NaN, a NaN shall be returned.

   If x multiplied by y is an exact infinity and z is also an infinity but 
   with the opposite sign, a domain error shall occur, and either a NaN 
   (if supported), or an implementation-defined value shall be returned.

   If one of x and y is infinite, the other is zero, and z is not a NaN, a 
   domain error shall occur, and either a NaN (if supported), or an 
   implementation-defined value shall be returned.

   If one of x and y is infinite, the other is zero, and z is a NaN, a NaN 
   shall be returned and a domain error may occur.

   If x * y is not 0*Inf nor Inf*0 and z is a NaN, a NaN shall be returned.

   ERRORS

   These functions shall fail if:
   Domain Error
   The value of x*y+z is invalid, or the value x*y is invalid and z is not 
   a NaN. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   Range Error
   The result overflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   These functions may fail if:
   Domain Error
   The value x*y is invalid and z is a NaN. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   Range Error
   The result underflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.

   Range Error
   The result overflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

double (fma) (double x, double y, double z)
{
  int errx, erry, errz, errw;
  double w;

  errx = _Fpclassify (x);
  erry = _Fpclassify (y);
  errz = _Fpclassify (z);

  /* Handle the special cases */
  if (errx == FP_NAN)
    return x;
  if (erry == FP_NAN)
    return y;
  if ((errx == FP_ZERO && erry == FP_INFINITE)
      || (erry == FP_ZERO && errx == FP_INFINITE))
    {
      _Matherr (EDOM, FE_INVALID);
      return (errz == FP_NAN) ? z : _Dbl->_Nan._D;
    }
  if (errz == FP_NAN)
    return z;
  w = x * y;
  errw = _Fpclassify (w);
  if (errw == FP_INFINITE && errz == FP_INFINITE
      && (_Getsign ((unsigned char *) &w, _Dbl) !=
	  _Getsign ((unsigned char *) &z, _Dbl)))
    {
      _Matherr (EDOM, FE_INVALID);
      return _Dbl->_Nan._D;
    }
  return w + z;
}

float (fmaf) (float x, float y, float z)
{
  int errx, erry, errz, errw;
  float w;

  errx = _Fpclassifyf (x);
  erry = _Fpclassifyf (y);
  errz = _Fpclassifyf (z);

  /* Handle the special cases */
  if (errx == FP_NAN)
    return x;
  if (erry == FP_NAN)
    return y;
  if ((errx == FP_ZERO && erry == FP_INFINITE)
      || (erry == FP_ZERO && errx == FP_INFINITE))
    {
      _Matherr (EDOM, FE_INVALID);
      return (errz == FP_NAN) ? z : _Flt->_Nan._F;
    }
  if (errz == FP_NAN)
    return z;
  w = x * y;
  errw = _Fpclassifyf (w);
  if (errw == FP_INFINITE && errz == FP_INFINITE
      && (_Getsign ((unsigned char *) &w, _Flt) !=
	  _Getsign ((unsigned char *) &z, _Flt)))
    {
      _Matherr (EDOM, FE_INVALID);
      return _Flt->_Nan._F;
    }
  return w + z;
}

long double (fmal) (long double x, long double y, long double z)
{
  int errx, erry, errz, errw;
  long double w;

  errx = _Fpclassifyl (x);
  erry = _Fpclassifyl (y);
  errz = _Fpclassifyl (z);

  /* Handle the special cases */
  if (errx == FP_NAN)
    return x;
  if (erry == FP_NAN)
    return y;
  if ((errx == FP_ZERO && erry == FP_INFINITE)
      || (erry == FP_ZERO && errx == FP_INFINITE))
    {
      _Matherr (EDOM, FE_INVALID);
      return (errz == FP_NAN) ? z : _Ldbl->_Nan._L;
    }
  if (errz == FP_NAN)
    return z;
  w = x * y;
  errw = _Fpclassifyl (w);
  if (errw == FP_INFINITE && errz == FP_INFINITE
      && (_Getsign ((unsigned char *) &w, _Ldbl) !=
	  _Getsign ((unsigned char *) &z, _Ldbl)))
    {
      _Matherr (EDOM, FE_INVALID);
      return _Ldbl->_Nan._L;
    }
  return w + z;
}

/* END OF FILE */
