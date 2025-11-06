/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fdim, fdimf, fdiml - compute positive difference between two floating-point 
   numbers

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall determine the positive difference between their 
   arguments. If x is greater than y, x - y is returned. If x is less than 
   or equal to y, +0 is returned.

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO 
   | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the positive 
   difference value.

   If x - y is positive and overflows, a range error shall occur and fdim(), 
   fdimf(), and fdiml() shall return the value of the macro HUGE_VAL, 
   HUGE_VALF, and HUGE_VALL, respectively.

   If the correct value would cause underflow, a range error may occur, and 
   fdim(), fdimf(), and fdiml() shall return the correct value, or (if the 
   IEC 60559 Floating-Point option is not supported) an implementation-
   defined value no greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, 
   respectively.

   If x or y is NaN, a NaN shall be returned.

   ERRORS

   The fdim() function shall fail if:
   Range Error
   The result overflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   The fdim() function may fail if:
   Range Error
   The result underflows. 
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

double (fdim) (double x, double y)
{
  int errx, erry, errz;
  double z;

  errx = _Fpclassify (x);
  erry = _Fpclassify (y);
  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;
  if (x > y)
    {
      z = x - y;
      errz = _Fpclassify (z);
      if (errz == FP_INFINITE)
	_Matherr (ERANGE, FE_OVERFLOW);
      if (errz == FP_ZERO)
	_Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    }
  else
    return +0.0;
}

float (fdimf) (float x, float y)
{
  int errx, erry, errz;
  float z;

  errx = _Fpclassifyf (x);
  erry = _Fpclassifyf (y);
  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;
  if (x > y)
    {
      z = x - y;
      errz = _Fpclassifyf (z);
      if (errz == FP_INFINITE)
	_Matherr (ERANGE, FE_OVERFLOW);
      if (errz == FP_ZERO)
	_Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    }
  else
    return +0.0F;
}

long double (fdiml) (long double x, long double y)
{
  int errx, erry, errz;
  long double z;

  errx = _Fpclassifyl (x);
  erry = _Fpclassifyl (y);
  if (errx == FP_NAN || erry == FP_NAN)
    return (errx == FP_NAN) ? x : y;
  if (x > y)
    {
      z = x - y;
      errz = _Fpclassifyl (z);
      if (errz == FP_INFINITE)
	_Matherr (ERANGE, FE_OVERFLOW);
      if (errz == FP_ZERO)
	_Matherr (ERANGE, FE_UNDERFLOW);
      return z;
    }
  else
    return +0.0L;
}

/* END OF FILE */
