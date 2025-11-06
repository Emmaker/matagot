/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* exp, expf, expl - exponential function

   AUTHOR: Gregory Pietsch
   
   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the base-e exponential of x.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE:

   Upon successful completion, these functions shall return the exponential 
   value of x.

   If the correct value would cause overflow, a range error shall occur and 
   exp(), expf(), and expl() shall return the value of the macro HUGE_VAL, 
   HUGE_VALF, and HUGE_VALL, respectively.

   If the correct value would cause underflow, and is not representable, 
   a range error may occur, and exp(), expf(), and expl() shall return 
   0.0, or (if the IEC 60559 Floating-Point option is not supported) an 
   implementation-defined value no greater in magnitude than DBL_MIN, FLT_MIN, 
   and LDBL_MIN, respectively.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, 1 shall be returned.

   If x is -Inf, +0 shall be returned.

   If x is +Inf, x shall be returned.

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

double (exp) (double x)
{
  double t, y, z;
  unsigned i;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      return 1.0;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Dbl) ? +0.0 : x;
    default:
      y = 1.0 + x;
      t = x;
      i = 2;
      do
	{
	  z = y;
	  t *= x / i;
	  y += t;
	  ++i;
	  z -= y;
	}
      while (_Fpclassify (z) != FP_ZERO);
      return y;
    }
}

float (expf) (float x)
{
  float t, y, z;
  unsigned i;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      return 1.0F;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Flt) ? +0.0F : x;
    default:
      y = 1.0F + x;
      t = x;
      i = 2;
      do
	{
	  z = y;
	  t *= x / i;
	  y += t;
	  ++i;
	  z -= y;
	}
      while (_Fpclassifyf (z) != FP_ZERO);
      return y;
    }
}

long double (expl) (long double x)
{
  long double t, y, z;
  unsigned i;

  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      return 1.0L;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Dbl) ? +0.0L : x;
    default:
      y = 1.0L + x;
      t = x;
      i = 2;
      do
	{
	  z = y;
	  t *= x / i;
	  y += t;
	  ++i;
	  z -= y;
	}
      while (_Fpclassifyl (z) != FP_ZERO);
      return y;
    }
}

/* END OF FILE */
