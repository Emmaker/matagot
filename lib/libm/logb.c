/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/
/* logb, logbf, logbl - radix-independent exponent

   AUTHOR: Gregory Pietsch

   DESCRIPTION
   
   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2017 defers to 
   the ISO C standard.

   These functions shall compute the exponent of x, which is the integral 
   part of log_r |x|, as a signed floating-point value, for non-zero x, 
   where r is the radix of the machine's floating-point arithmetic, which is 
   the value of FLT_RADIX defined in the <float.h> header.

   If x is subnormal it is treated as though it were normalized; thus for 
   finite positive x:

   1 <= x * FLT_RADIX^-logb(x) < FLT_RADIX

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the exponent of x.

   If x is +/-0, logb(), logbf(), and logbl() shall return -HUGE_VAL, 
   -HUGE_VALF, and -HUGE_VALL, respectively.

   On systems that support the IEC 60559 Floating-Point option, a pole error 
   shall occur; otherwise, a pole error may occur.

   If x is NaN, a NaN shall be returned.

   If x is +/-Inf, +Inf shall be returned.

   ERRORS

   These functions shall fail if:

   Pole Error
   The value of x is +/-0.
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
   floating-point exception shall be raised.

   These functions may fail if:

   Pole Error
   The value of x is 0.
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
   floating-point exception shall be raised.
*/

#include "xmath.h"

double
(logb) (double x)
{
  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      return _Dbl->_Inf._D;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VAL;
    default:
#if FLT_RADIX == 2
      return log2 (x);
#else
      return log (x) / log (FLT_RADIX);
#endif
    }
}

float
(logbf) (float x)
{
  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      return _Flt->_Inf._F;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VALF;
    default:
#if FLT_RADIX == 2
      return log2f (x);
#else
      return logf (x) / logf (FLT_RADIX);
#endif
    }
}

long double
(logbl) (long double x)
{
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      return x;
    case FP_INFINITE:
      return _Ldbl->_Inf._L;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VALL;
    default:
#if FLT_RADIX == 2
      return log2l (x);
#else
      return logl (x) / logl (FLT_RADIX);
#endif
    }
}

/* END OF FILE */