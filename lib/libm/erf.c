/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* erf, erff, erfl - error functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2017 defers 
   to the ISO C standard.

   These functions shall compute the error function of their argument x, 
   defined as:
                   _
                  | |  t^2
   2/sqrt(M_PI)   |   e    dt
                |_|

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO | 
   FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the value of the 
   error function.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, +/-0 shall be returned.

   If x is +/-Inf, +/-1 shall be returned.

   If the correct value would cause underflow, a range error may occur, and 
   erf(), erff(), and erfl() shall return an implementation-defined value no 
   greater in magnitude than DBL_MIN, FLT_MIN, and LDBL_MIN, respectively.

   If the IEC 60559 Floating-Point option is supported, 2 * x/ sqrt(M_PI) 
   should be returned.

   ERRORS
   
   These functions may fail if:

   Range Error

   The result underflows.

   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.

*/

/* erfc, erfcf, erfcl - complementary error functions

   AUTHOR: Gregory Pietsch
   
   DESCRIPTION
   
   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2017 defers to 
   the ISO C standard.

   These functions shall compute the complementary error function 1.0 - erf(x).

   An application wishing to check for error situations should set errno to 
   zero and call feclearexcept(FE_ALL_EXCEPT) before calling these functions. 
   On return, if errno is non-zero or fetestexcept(FE_INVALID | FE_DIVBYZERO | 
   FE_OVERFLOW | FE_UNDERFLOW) is non-zero, an error has occurred.

   RETURN VALUE

   Upon successful completion, these functions shall return the value of the 
   complementary error function.

   If the correct value would cause underflow, and is not representable, 
   a range error may occur, and erfc(), erfcf(), and erfcl() shall return 
   0.0, or (if the IEC 60559 Floating-Point option is not supported) an 
   implementation-defined value no greater in magnitude than DBL_MIN, 
   FLT_MIN, and LDBL_MIN, respectively.

   If x is NaN, a NaN shall be returned.

   If x is +/-0, +1 shall be returned.

   If x is -Inf, +2 shall be returned.

   If x is +Inf, +0 shall be returned.

   If the correct value would cause underflow and is representable, a range 
   error may occur and the correct value shall be returned.

   ERRORS

   These functions may fail if:

   Range Error

   The result underflows.
   If the integer expression (math_errhandling & MATH_ERRNO) is non-zero, 
   then errno shall be set to ERANGE. If the integer expression 
   (math_errhandling & MATH_ERREXCEPT) is non-zero, then the underflow 
   floating-point exception shall be raised.
*/

#include "xmath.h"

double
(erf) (double x)
{
  double t, ans;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Dbl) ? -1.0 : +1.0;
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return M_2_SQRTPI * x;
    default:
      t = 1.0 / (1.0 + 0.5 * fabs (x));
      ans =
	t * exp (-x * x - 1.26551223 +
		 t * (1.00002368 +
		      t * (0.37409196 +
			   t * (0.09678418 +
				t * (-0.18628806 +
				     t * (0.27886807 +
					  t * (-1.13520398 +
					       t * (1.48851587 +
						    t * (-0.82215223 +
							 t *
							 0.17087277)))))))));
      return (x >= 0.0) ? ans : -ans;
    }
}

double
(erfc) (double x)
{
  switch (_Fpclassify (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      return +1;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Dbl) ? +2.0 : +0.0;
    default:
      return +1.0 - erf (x);
    }
}

float
(erff) (float x)
{
  float t, ans;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Flt) ? -1.0F : +1.0F;
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return _M_2_SQRTPIF * x;
    default:
      t = 1.0F / (1.0F + 0.5F * fabsf (x));
      ans =
	t * expf (-x * x - 1.26551223F +
		  t * (1.00002368F +
		       t * (0.37409196F +
			    t * (0.09678418F +
				 t * (-0.18628806F +
				      t * (0.27886807F +
					   t * (-1.13520398F +
						t * (1.48851587F +
						     t * (-0.82215223F +
							  t *
							  0.17087277F)))))))));
      return _Getsign ((unsigned char *) &x, _Flt) ? ans : -ans;
    }
}

float
(erfcf) (float x)
{
  float t, z, ans;

  switch (_Fpclassifyf (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      return +1.0F;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Flt) ? +2.0F : +0.0F;
    default:
      z = fabsf (x);
      t = 1.0L / (1.0L + 0.5L * z);
      ans =
	t * expf (-z * z - 1.26551223F +
		  t * (1.00002368F +
		       t * (0.37409196F +
			    t * (0.09678418F +
				 t * (-0.18628806F +
				      t * (0.27886807F +
					   t * (-1.13520398F +
						t * (1.48851587F +
						     t * (-0.82215223F +
							  t *
							  0.17087277F)))))))));
      return (x >= 0.0F) ? ans : +2.0F - ans;
    }
}

long double
(erfl) (long double x)
{
  long double t, ans;

  switch (_Fpclassify (x))
    {
    case FP_NAN:
    case FP_ZERO:
      return x;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Ldbl) ? -1.0L : +1.0L;
    case FP_SUBNORMAL:
      _Matherr (ERANGE, FE_UNDERFLOW);
      return _M_2_SQRTPIL * x;
    default:
      t = 1.0L / (1.0L + 0.5L * fabsl (x));
      ans =
	t * expl (-x * x - 1.26551223L +
		  t * (1.00002368L +
		       t * (0.37409196L +
			    t * (0.09678418L +
				 t * (-0.18628806L +
				      t * (0.27886807L +
					   t * (-1.13520398L +
						t * (1.48851587L +
						     t * (-0.82215223L +
							  t *
							  0.17087277L)))))))));
      return (x >= 0.0L) ? ans : -ans;
    }
}

long double
(erfcl) (long double x)
{
  long double t, z, ans;
  switch (_Fpclassifyl (x))
    {
    case FP_NAN:
      return x;
    case FP_ZERO:
      return +1.0L;
    case FP_INFINITE:
      return _Getsign ((unsigned char *) &x, _Ldbl) ? +2.0L : +0.0L;
    default:
      z = fabsl (x);
      t = 1.0L / (1.0L + 0.5L * z);
      ans =
	t * expl (-z * z - 1.26551223L +
		  t * (1.00002368L +
		       t * (0.37409196L +
			    t * (0.09678418L +
				 t * (-0.18628806L +
				      t * (0.27886807L +
					   t * (-1.13520398L +
						t * (1.48851587L +
						     t * (-0.82215223L +
							  t *
							  0.17087277L)))))))));
      return (x >= 0.0L) ? ans : 2.0L - ans;
    }
}

/* END OF FILE */