/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* nextafter, nextafterf, nextafterl, nexttoward, nexttowardf, nexttowardl - 
   next representable floating-point number

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The nextafter(), nextafterf(), and nextafterl() functions shall compute 
   the next representable floating-point value following x in the direction 
   of y. Thus, if y is less than x, nextafter() shall return the largest 
   representable floating-point number less than x. The nextafter(), 
   nextafterf(), and nextafterl() functions shall return y if x equals y.

   The nexttoward(), nexttowardf(), and nexttowardl() functions shall be 
   equivalent to the corresponding nextafter() functions, except that the 
   second parameter shall have type long double and the functions shall 
   return y converted to the type of the function if x equals y.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the next 
   representable floating-point value following x in the direction of y.

   If x == y, y (of the type x) shall be returned.

   If x is finite and the correct function value would overflow, a range 
   error shall occur and +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL (with 
   the same sign as x) shall be returned as appropriate for the return type 
   of the function.

   If x or y is NaN, a NaN shall be returned.

   If x != y and the correct function value is subnormal, zero, or underflows, 
   a range error shall occur, and the correct function value (if 
   representable) or 0.0 shall be returned.

   ERRORS:

   These functions shall fail if:
   Range Error
   The correct value overflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   Range Error
   The correct value is subnormal or underflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow
   floating-point exception shall be raised. 
*/

#include "xmath.h"

static void
_Next (unsigned char *x, const _FP_METRIC_T * const m, int dir)
{
  int sign = 0, i, b;

  sign = _Getsign (x, m);
  if ((sign == 0 && dir == 1) || (sign && dir == -1))
    {
      /* increase magnitude */
      for (i = m->_Size - 1; i >= 0; --i)
	{
	  ++(x[_BYTE (i, m->_Size)]);
	  if (x[_BYTE (i, m->_Size)])
	    break;
	}
    }
  else
    {
      /* decrease magnitude */
      for (i = m->_Size - 1; i >= 0; --i)
	{
	  b = x[_BYTE (i, m->_Size)];
	  --(x[_BYTE (i, m->_Size)]);
	  if (b)
	    break;
	}
    }
}

double (nextafter) (double x, double y)
{
  int errx, erry, errz, c;
  double z;

  errx = _Fpclassify (x);
  erry = _Fpclassify (y);
  if (errx == FP_NAN || errx == FP_INFINITE)
    return x;
  if (erry == FP_NAN || x == y)
    return y;
  c = (x > y) - (x < y);
  z = x;
  _Next ((unsigned char *) &z, _Dbl, c);
  errz = _Fpclassify (z);
  switch (errz)
    {
    case FP_ZERO:
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    case FP_INFINITE:
    case FP_NAN:
      _Matherr (ERANGE, FE_OVERFLOW);
      return _Getsign ((unsigned char *) &x, _Dbl) ? -HUGE_VAL : HUGE_VAL;
    default:
      return z;
    }
}

float (nextafterf) (float x, float y)
{
  int errx, erry, errz, c;
  float z;

  errx = _Fpclassifyf (x);
  erry = _Fpclassifyf (y);
  if (errx == FP_NAN || errx == FP_INFINITE)
    return x;
  if (erry == FP_NAN || x == y)
    return y;
  c = (x > y) - (x < y);
  z = x;
  _Next ((unsigned char *) &z, _Flt, c);
  errz = _Fpclassifyf (z);
  switch (errz)
    {
    case FP_ZERO:
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    case FP_INFINITE:
    case FP_NAN:
      _Matherr (ERANGE, FE_OVERFLOW);
      return _Getsign ((unsigned char *) &x, _Flt) ? -HUGE_VALF : HUGE_VALF;
    default:
      return z;
    }
}

long double (nextafterl) (long double x, long double y)
{
  int errx, erry, errz, c;
  float z;

  errx = _Fpclassifyl (x);
  erry = _Fpclassifyl (y);
  if (errx == FP_NAN || errx == FP_INFINITE)
    return x;
  if (erry == FP_NAN || x == y)
    return y;
  c = (x > y) - (x < y);
  z = x;
  _Next ((unsigned char *) &z, _Ldbl, c);
  errz = _Fpclassifyl (z);
  switch (errz)
    {
    case FP_ZERO:
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    case FP_INFINITE:
    case FP_NAN:
      _Matherr (ERANGE, FE_OVERFLOW);
      return _Getsign ((unsigned char *) &x, _Ldbl) ? -HUGE_VALL : HUGE_VALL;
    default:
      return z;
    }
}

double (nexttoward) (double x, long double y)
{
  int errx, erry, errz, c;
  double z;

  errx = _Fpclassify (x);
  erry = _Fpclassifyl (y);
  if (errx == FP_NAN || errx == FP_INFINITE)
    return x;
  if (erry == FP_NAN || x == (double) y)
    return (double) y;
  c = (x > y) - (x < y);
  z = x;
  _Next ((unsigned char *) &z, _Dbl, c);
  errz = _Fpclassify (z);
  switch (errz)
    {
    case FP_ZERO:
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    case FP_INFINITE:
    case FP_NAN:
      _Matherr (ERANGE, FE_OVERFLOW);
      return _Getsign ((unsigned char *) &x, _Dbl) ? -HUGE_VAL : HUGE_VAL;
    default:
      return z;
    }
}

float (nexttowardf) (float x, long double y)
{
  int errx, erry, errz, c;
  float z;

  errx = _Fpclassifyf (x);
  erry = _Fpclassifyl (y);
  if (errx == FP_NAN || errx == FP_INFINITE)
    return x;
  if (erry == FP_NAN || x == (float) y)
    return (float) y;
  c = (x > y) - (x < y);
  z = x;
  _Next ((unsigned char *) &z, _Flt, c);
  errz = _Fpclassifyf (z);
  switch (errz)
    {
    case FP_ZERO:
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    case FP_INFINITE:
    case FP_NAN:
      _Matherr (ERANGE, FE_OVERFLOW);
      return _Getsign ((unsigned char *) &x, _Flt) ? -HUGE_VALF : HUGE_VALF;
    default:
      return z;
    }
}

long double (nexttowardl) (long double x, long double y)
{
  int errx, erry, errz, c;
  long double z;

  errx = _Fpclassifyl (x);
  erry = _Fpclassifyl (y);
  if (errx == FP_NAN || errx == FP_INFINITE)
    return x;
  if (erry == FP_NAN || x == y)
    return y;
  c = (x > y) - (x < y);
  z = x;
  _Next ((unsigned char *) &z, _Ldbl, c);
  errz = _Fpclassifyl (z);
  switch (errz)
    {
    case FP_ZERO:
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    case FP_INFINITE:
    case FP_NAN:
      _Matherr (ERANGE, FE_OVERFLOW);
      return _Getsign ((unsigned char *) &x, _Ldbl) ? -HUGE_VALL : HUGE_VALL;
    default:
      return z;
    }
}

/* END OF FILE */
