/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/
/* ilogb, ilogbf, ilogbl - return an unbiased exponent

   DESCRIPTION
   
   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2017 defers 
   to the ISO C standard.

   These functions shall return the exponent part of their argument x. 
   Formally, the return value is the integral part of log_r|x| as a signed 
   integral value, for non-zero x, where r is the radix of the machine's 
   floating-point arithmetic, which is the value of FLT_RADIX defined in 
   <float.h>.

   An application wishing to check for error situations should set errno 
   to zero and call feclearexcept(FE_ALL_EXCEPT) before calling these 
   functions. On return, if errno is non-zero or fetestexcept(FE_INVALID 
   | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has 
   occurred.

   RETURN VALUE
   
   Upon successful completion, these functions shall return the exponent 
   part of x as a signed integer value. They are equivalent to calling the 
   corresponding logb() function and casting the returned value to type int.

   If x is 0, the value FP_ILOGB0 shall be returned. On XSI-conformant 
   systems, a domain error shall occur; otherwise, a domain error may occur.

   If x is +/-Inf, the value INT_MAX shall be returned. On XSI-conformant 
   systems, a domain error shall occur; otherwise, a domain error may occur.

   If x is a NaN, the value FP_ILOGBNAN shall be returned. On XSI-conformant 
   systems, a domain error shall occur; otherwise, a domain error may occur.

   If the correct value is greater than INT_MAX, a domain error shall occur 
   and an unspecified value shall be returned. On XSI-conformant systems, a 
   domain error shall occur and INT_MAX shall be returned.

   If the correct value is less than INT_MIN, a domain error shall occur and 
   an unspecified value shall be returned. On XSI-conformant systems, a domain 
   error shall occur and INT_MIN shall be returned.

   ERRORS

   These functions shall fail if:

   Domain Error
   The correct value is not representable as an integer. 
   The x argument is zero, NaN, or +/-Inf. 

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised. 

   These functions may fail if:

   Domain Error
   The x argument is zero, NaN, or +/-Inf.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.
*/

#include "xmath.h"
#include <limits.h>

int
ilogb (double x)
{
  switch (_Fpclassify (x))
    {
    case FP_NAN:
      _Matherr (EDOM, FE_INVALID);
      return FP_ILOGBNAN;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return INT_MAX;
    case FP_ZERO:
      _Matherr (EDOM, FE_INVALID);
      return FP_ILOGB0;
    default:
      if (FLT_RADIX == 2)
	return (int) (log2 (x));
      else
	return (int) (log (x) / log (FLT_RADIX));
    }
}

int
ilogbf (float x)
{
  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      _Matherr (EDOM, FE_INVALID);
      return FP_ILOGBNAN;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return INT_MAX;
    case FP_ZERO:
      _Matherr (EDOM, FE_INVALID);
      return FP_ILOGB0;
    default:
      if (FLT_RADIX == 2)
	return (int) (log2f (x));
      else
	return (int) (logf (x) / logf (FLT_RADIX));
    }
}

int
ilogbl (long double x)
{
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      _Matherr (EDOM, FE_INVALID);
      return FP_ILOGBNAN;
    case FP_INFINITE:
      _Matherr (EDOM, FE_INVALID);
      return INT_MAX;
    case FP_ZERO:
      _Matherr (EDOM, FE_INVALID);
      return FP_ILOGB0;
    default:
      if (FLT_RADIX == 2)
	return (int) (log2l (x));
      else
	return (int) (logl (x) / logl (FLT_RADIX));
    }
}

/* END OF FILE */
