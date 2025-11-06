/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* ldexp, ldexpf, ldexpl - load exponent of a floating-point number

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers to 
   the ISO C standard. 

   These functions shall compute the quantity x * 2^ex.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return x multiplied by 2, 
   raised to the power ex.

   If these functions would cause overflow, a range error shall occur and 
   ldexp(), ldexpf(), and ldexpl() shall return +/-HUGE_VAL, +/-HUGE_VALF, 
   and +/-HUGE_VALL (according to the sign of x), respectively.

   If the correct value would cause underflow, and is not representable, 
   a range error may occur, and ldexp(), ldexpf(), and ldexpl() shall return 
   0.0, or (if IEC 60559 Floating-Point is not supported) an implementation-
   defined value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
   respectively.

   If x is NaN, a NaN shall be returned.

   If x is +/-0 or +/-Inf, x shall be returned.

   If exp is 0, x shall be returned.

   If the correct value would cause underflow, and is representable, a range 
   error may occur and the correct value shall be returned.

   ERRORS:

   These functions shall fail if:

   Range Error
   The result overflows.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   These functions may fail if:

   Range Error
   The result underflows.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

static int
_Ldexp (unsigned char *x, int ex, const _FP_METRIC_T * const m)
{
  unsigned long e, ebits;
  int i, sh;

  for (i = 0, e = 0UL; i < 3; ++i)
    e = (e << CHAR_BIT) | x[_BYTE (m->_Size, i)];
  ebits = ~(~0UL << m->_Ebits);
  if (ex - 1 >= ebits)
    return FE_OVERFLOW;
  if (ex - 1 <= 0)
    return FE_UNDERFLOW;
  sh = CHAR_BIT * 3 - 1 - m->_Ebits;
  e &= ~(~0UL << sh);
  e |= ((ex - 1 + (ebits >> 1)) << sh);
  for (i = 2; i >= 0; --i)
    {
      x[_BYTE (m->_Size, i)] = (unsigned char) e;
      e >>= CHAR_BIT;
    }
  return 0;
}

double (ldexp) (double fl, int ex)
{
  int curr, sign;

  switch (_Fpclassify (fl))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return fl;
    default:
      if (ex == 0)
	return fl;
      sign = _Getsign ((unsigned char *) &fl, _Dbl);
      _Setsign ((unsigned char *) &fl, _Dbl, 0);
      fl = frexp (fl, &curr);
      ex += curr;
      switch (_Ldexp ((unsigned char *) &fl, ex, _Dbl))
	{
	case FE_OVERFLOW:
	  fl = HUGE_VAL;
	  _Matherr (ERANGE, FE_OVERFLOW);
	  break;
	case FE_UNDERFLOW:	/* try anyway */
	  while (ex < -30)
	    {
	      fl /= (1L << 30);
	      ex += 30;
	    }
	  fl /= (1L << -ex);
	  if (_Fpclassify (fl) == FP_ZERO)
	    _Matherr (ERANGE, FE_UNDERFLOW);
	  break;
	default:
	  break;
	}
      _Setsign ((unsigned char *) &fl, _Dbl, sign);
      return fl;
    }
}

float (ldexpf) (float fl, int ex)
{
  int curr, sign;

  switch (_Fpclassifyf (fl))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return fl;
    default:
      if (ex == 0)
	return fl;
      sign = _Getsign ((unsigned char *) &fl, _Flt);
      _Setsign ((unsigned char *) &fl, _Flt, 0);
      fl = frexpf (fl, &curr);
      ex += curr;
      switch (_Ldexp ((unsigned char *) &fl, ex, _Flt))
	{
	case FE_OVERFLOW:
	  fl = HUGE_VALF;
	  _Matherr (ERANGE, FE_OVERFLOW);
	  break;
	case FE_UNDERFLOW:	/* try anyway */
	  while (ex < -30)
	    {
	      fl /= (1L << 30);
	      ex += 30;
	    }
	  fl /= (1L << -ex);
	  if (_Fpclassifyf (fl) == FP_ZERO)
	    _Matherr (ERANGE, FE_UNDERFLOW);
	  break;
	default:
	  break;
	}
      _Setsign ((unsigned char *) &fl, _Flt, sign);
      return fl;
    }
}

long double (ldexpl) (long double fl, int ex)
{
  int curr, sign;

  switch (_Fpclassifyl (fl))
    {
    case FP_NAN:
    case FP_ZERO:
    case FP_INFINITE:
      return fl;
    default:
      if (ex == 0)
	return fl;
      sign = _Getsign ((unsigned char *) &fl, _Ldbl);
      _Setsign ((unsigned char *) &fl, _Ldbl, 0);
      fl = frexpl (fl, &curr);
      ex += curr;
      switch (_Ldexp ((unsigned char *) &fl, ex, _Ldbl))
	{
	case FE_OVERFLOW:
	  fl = HUGE_VALL;
	  _Matherr (ERANGE, FE_OVERFLOW);
	  break;
	case FE_UNDERFLOW:	/* try anyway */
	  while (ex < -30)
	    {
	      fl /= (1L << 30);
	      ex += 30;
	    }
	  fl /= (1L << -ex);
	  if (_Fpclassifyl (fl) == FP_ZERO)
	    _Matherr (ERANGE, FE_UNDERFLOW);
	  break;
	default:
	  break;
	}
      _Setsign ((unsigned char *) &fl, _Ldbl, sign);
      return fl;
    }
}

/* END OF FILE */
