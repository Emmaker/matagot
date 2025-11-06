/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* exp2, exp2f, exp2l - exponential base 2 functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the base-2 exponential of x.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return 2^x.

   If the correct value would cause overflow, a range error shall occur and 
   exp2(), exp2f(), and exp2l() shall return the value of the macro HUGE_VAL, 
   HUGE_VALF, and HUGE_VALL, respectively.

   If the correct value would cause underflow, and is not representable, 
   a range error may occur, and exp2(), exp2f(), and exp2l() shall return 
   (if the IEC 60559 Floating-Point option is not supported) an implementation-
   defined value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
   respectively.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, 1 shall be returned.

   If x is -Inf, +0 shall be returned.

   If x is +Inf, x shall be returned.

   If the correct value would cause underflow, and is representable, a range 
   error may occur and the correct value shall be returned.

   ERRORS

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

double (exp2) (double x)
{
  double y, e;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Dbl) ? +0.0 : x;
    case FP_ZERO:
      return 1.0;
    default:
      y = modf (x, &e);
      if (e > INT_MIN && e < INT_MAX)
	return ldexp (exp (y * M_LN2), (int) e);
      else			/* cast precision to the winds */
	return exp (x * M_LN2);
    }
}

float (exp2f) (float x)
{
  float y, e;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Flt) ? +0.0F : x;
    case FP_ZERO:
      return 1.0F;
    default:
      y = modff (x, &e);
      if (e > INT_MIN && e < INT_MAX)
	return ldexpf (expf (y * _M_LN2F), (int) e);
      else			/* cast precision to the winds */
	return expf (x * _M_LN2F);
    }
}

long double (exp2l) (long double x)
{
  long double y, e;

  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Ldbl) ? +0.0L : x;
    case FP_ZERO:
      return 1.0L;
    default:
      y = modfl (x, &e);
      if (e > INT_MIN && e < INT_MAX)
	return ldexpl (expl (y * M_LN2), (int) e);
      else			/* cast precision to the winds */
	return expl (x * M_LN2);
    }
}

/* END OF FILE */
