/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* sinh, sinhf, sinhl - hyperbolic sine functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the hyperbolic sine of their argument x.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the hyperbolic 
   sine of x.

   If the result would cause an overflow, a range error shall occur and 
   +/-HUGE_VAL, +/-HUGE_VALF, and +/-HUGE_VALL (with the same sign as x) 
   shall be returned as appropriate for the type of the function.

   If x is NaN, a NaN shall be returned.

   If x is +/-0 or +/-Inf, x shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, sinh(), sinhf(), and sinhl() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, 
   FLT_MIN, and LDBL_MIN, respectively.

   ERRORS

   These functions shall fail if:

   Range Error
   The result would cause an overflow. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   These functions may fail if:
   Range Error
   The value x is subnormal. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

double (sinh) (double x)
{
  double y;

  switch (_Fpclassify (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      /* FALL THROUGH */
    case FP_ZERO:
    case FP_INFINITE:
    case FP_NAN:
      return x;
    default:
      y = exp (x);
      y -= 1.0 / y;
      y = ldexp (y, -1);
      return y;
    }
}

float (sinhf) (float x)
{
  float y;

  switch (_Fpclassifyf (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      /* FALL THROUGH */
    case FP_ZERO:
    case FP_INFINITE:
    case FP_NAN:
      return x;
    default:
      y = expf (x);
      y -= 1.0F / y;
      y = ldexpf (y, -1);
      return y;
    }
}

long double (sinhl) (long double x)
{
  long double y;

  switch (_Fpclassifyl (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      /* FALL THROUGH */
    case FP_ZERO:
    case FP_INFINITE:
    case FP_NAN:
      return x;
    default:
      y = expl (x);
      y -= 1.0L / y;
      y = ldexpl (y, -1);
      return y;
    }
}

/* END OF FILE */
