/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* Bessel functions

   AUTHOR: Gregory Pietsch
*/

/* j0, j1, jn - Bessel functions of the first kind

   DESCRIPTION
   
   The j0(), j1(), and jn() functions shall compute Bessel functions of x 
   of the first kind of orders 0, 1, and n, respectively.

   An application wishing to check for error situations should set errno 
   to zero and call feclearexcept(FE_ALL_EXCEPT) before calling these 
   functions. On return, if errno is non-zero or fetestexcept(FE_INVALID | 
   FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has 
   occurred.

   RETURN VALUE
   
   Upon successful completion, these functions shall return the relevant 
   Bessel value of x of the first kind.

   If the x argument is too large in magnitude, or the correct result would 
   cause underflow, 0 shall be returned and a range error may occur.

   If x is NaN, a NaN shall be returned.

   ERRORS

   These functions may fail if:

   Range Error

   The value of x was too large in magnitude, or an underflow occurred.
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.

   No other errors shall occur.

   y0, y1, yn - Bessel functions of the second kind

   DESCRIPTION

   The y0(), y1(), and yn() functions shall compute Bessel functions of x 
   of the second kind of orders 0, 1, and n, respectively.

   An application wishing to check for error situations should set errno 
   to zero and call feclearexcept(FE_ALL_EXCEPT) before calling these 
   functions. On return, if errno is non-zero or fetestexcept(FE_INVALID | 
   FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has 
   occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the relevant 
   Bessel value of x of the second kind.

   If x is NaN, NaN shall be returned.

   If the x argument to these functions is negative, -HUGE_VAL or NaN shall 
   be returned, and a domain error may occur.

   If x is 0.0, -HUGE_VAL shall be returned and a pole error may occur.

   If the correct result would cause underflow, 0.0 shall be returned and a 
   range error may occur.

   If the correct result would cause overflow, -HUGE_VAL or 0.0 shall be 
   returned and a range error may occur.

   ERRORS

   These functions may fail if:

   Domain Error

   The value of x is negative.
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to EDOM. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the invalid 
   floating-point exception shall be raised.

   Pole Error

   The value of x is zero.
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the divide-by-zero 
   floating-point exception shall be raised.

   Range Error

   The correct result would cause overflow.
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the overflow 
   floating-point exception shall be raised.

   Range Error

   The value of x is too large in magnitude, or the correct result would 
   cause underflow.
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

static double
factorial (int n)
{
  double result = 1.0;
  static double facs[] = { 1.0, 1.0, 2.0, 6.0, 24.0, 120.0, 720.0,
    5040.0, 40320.0, 362880.0, 3628800.0
  };
  int i;

  if (n >= 0 && n <= 10)
    return facs[n];
  for (result = facs[10], i = 11; i <= n; i++)
    result *= i;
  return result;
}

static double
intpow (double x, int n)
{
  double result = 1.0;

  for (; n; n >>= 1, x *= x)
    {
      if (n & 1)
	result *= x;
    }
  return result;
}

static double
jk (double x, int k)
{
  double sum = 0.0;

  for (int n = 0; n <= 10; n++)
    {
      double term =
	intpow (x / 2.0, 2 * n + k) / (factorial (n) * factorial (n + k));
      if (n & 1)
	term = -term;
      sum += term;
    }
  return sum;
}

double (j0) (double x)
{
  double sum = 0.0;

  for (int k = 0; k <= 10; k++)
    {
      double term = intpow (x / 2.0, 2 * k) / (factorial (k) * factorial (k));
      if (k & 1)
	term = -term;
      sum += term;
    }
  return sum;
}

double (j1) (double x)
{
  double sum = 0.0;
  for (int k = 0; k <= 10; k++)
    {
      double term =
	intpow (x / 2.0, 2 * k + 1) / (factorial (k) * factorial (k + 1));
      if (k & 1)
	term = -term;
      sum += term;
    }
  return sum;
}

double (jn) (int n, double x)
{
  double sum = 0.0;
  int k;

  if (isnan (x))
    return x;
  for (k = 0; k <= 10; k++)
    {
      double term =
	intpow (x / 2.0, 2 * k + n) / (factorial (k) * factorial (k + n));
      if (k & 1)
	term = -term;
      sum += term;
    }
  return sum;
}

double (y0) (double x)
{
  double j, sum, term;
  int k;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VAL;
    default:
      if (_Getsign ((unsigned char *)&x, _Dbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return -HUGE_VAL;
	}
      else
	{
	  j = j0 (x);
	  sum = 0.0;

	  for (k = 0; k <= 10; k++)
	    {
	      term = jk (x, k) * cos (k * M_PI_2);
	      sum += term;
	    }
	  return M_2_PI * (j * log (x / 2.0) - sum);
	}
    }
}

double (y1) (double x)
{
  double j, sum, term;
  int k;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VAL;
    default:
      if (_Getsign ((unsigned char *)&x, _Dbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return -HUGE_VAL;
	}
      else
	{
	  j = j1 (x);
	  sum = 0.0;

	  for (k = 0; k <= 10; k++)
	    {
	      term = jk (x, k) * cos ((k + 1) * M_PI_2);
	      sum += term;
	    }
	  return M_2_PI * (j * log (x / 2.0) - sum);
	}
    }
}

double (yn) (int n, double x)
{
  double j, sum, term;
  int k;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      _Matherr (ERANGE, FE_DIVBYZERO);
      return -HUGE_VAL;
    default:
      if (_Getsign ((unsigned char *)&x, _Dbl))
	{
	  _Matherr (EDOM, FE_INVALID);
	  return -HUGE_VAL;
	}
      else
	{
	  j = jn (n, x);
	  sum = 0.0;
	  for (k = 0; k <= n - 1; k++)
	    {
	      term = jk (x, k) * cos ((n - k) * M_PI_2);
	      sum += term;
	    }
	  return M_2_PI * (j * log (x / 2.0) - sum);
	}
    }
}

/* END OF FILE */
