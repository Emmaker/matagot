/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* asinh, asinhf, asinhl - inverse hyperbolic sine functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the inverse hyperbolic sine of their 
   argument x.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the inverse 
   hyperbolic sine of their argument.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, or +/-Inf, x shall be returned.

   If x is subnormal, a range error may occur and x should be returned.

   If x is not returned, asinh(), asinhf(), and asinhl() shall return an 
   implementation-defined value no greater in magnitude than DBL_MIN, FLT_MIN, 
   and LDBL_MIN, respectively.

   ERRORS:

   These functions may fail if:
   Range Error
   The value of x is subnormal. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, then 
   errno shall be set to ERANGE. If the integer expression (math_errhandling 
   & MATH_ERREXCEPT) is non-zero, then the underflow floating-point exception 
   shall be raised.
*/

#include "xmath.h"

double (asinh) (double x)
{
  switch (_Fpclassify (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      /* FALL THROUGH */
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      return log (x + sqrt (x + x + 1.0));
    }
}

float (asinhf) (float x)
{
  switch (_Fpclassifyf (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      /* FALL THROUGH */
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      return logf (x + sqrtf (x + x + 1.0F));
    }
}

long double (asinhl) (long double x)
{
  switch (_Fpclassifyl (x))
    {
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      /* FALL THROUGH */
    case FP_NAN:
    case FP_INFINITE:
    case FP_ZERO:
      return x;
    default:
      return logl (x + sqrtl (x + x + 1.0L));
    }
}

/* END OF FILE */
