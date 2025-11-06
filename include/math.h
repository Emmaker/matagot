/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* math.h - mathematical declarations

   AUTHOR: Gregory Pietsch

   DESCRIPTION

   Some of the functionality described on this reference page extends the
   ISO C standard. Applications shall define the appropriate feature test
   macro (see XSH The Compilation Environment) to enable the visibility of
   these symbols in this header.
*/

#ifndef _MATH_H
#define _MATH_H

#include <sys/cdefs.h>

#include <yvals.h>
#include <float.h>
#include <limits.h>

/* The <math.h> header shall define at least the following types:

   float_t
       A real-floating type at least as wide as float.
   double_t
       A real-floating type at least as wide as double, and at least as wide
       as float_t.

   If FLT_EVAL_METHOD equals 0, float_t and double_t shall be float and
   double, respectively; if FLT_EVAL_METHOD equals 1, they shall both be
   double; if FLT_EVAL_METHOD equals 2, they shall both be long double;
   for other values of FLT_EVAL_METHOD, they are otherwise implementation-
   defined.
*/

#if FLT_EVAL_METHOD == 0
typedef float float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 1
typedef double float_t;
typedef double double_t;
#elif FLT_EVAL_METHOD == 2
typedef long double float_t;
typedef long double double_t;
#else
#error FLT_EVAL_METHOD is misdefined
#endif

/* The <math.h> header shall define the following macros, where real-floating
   indicates that the argument shall be an expression of real-floating type:

    int fpclassify(real-floating x);
    int isfinite(real-floating x);
    int isgreater(real-floating x, real-floating y);
    int isgreaterequal(real-floating x, real-floating y);
    int isinf(real-floating x);
    int isless(real-floating x, real-floating y);
    int islessequal(real-floating x, real-floating y);
    int islessgreater(real-floating x, real-floating y);
    int isnan(real-floating x);
    int isnormal(real-floating x);
    int isunordered(real-floating x, real-floating y);
    int signbit(real-floating x);
*/

#define fpclassify(_X) \
  (sizeof(_X)==sizeof(float)?_Fpclassifyf(_X):\
  (sizeof(_X)==sizeof(double)?_Fpclassify(_X):_Fpclassifyl(_X)))
#define isfinite(_X)		(fpclassify(_X)<=0)
#define isgreater(_X,_Y)	(isunordered(_X,_Y)?0:((_X)>(_Y)))
#define isgreaterequal(_X,_Y)	(isunordered(_X,_Y)?0:((_X)>=(_Y)))
#define isinf(_X)		(fpclassify(_X)==FP_INFINITE)
#define isless(_X,_Y)		(isunordered(_X,_Y)?0:((_X)<(_Y)))
#define islessequal(_X,_Y)	(isunordered(_X,_Y)?0:((_X)<=(_Y)))
#define islessgreater(_X,_Y)	(isunordered(_X,_Y)?0:((_X)!=(_Y)))
#define isnan(_X)		(fpclassify(_X)==FP_NAN)
#define isnormal(_X)		(fpclassify(_X)==FP_NORMAL)
#define isunordered(_X,_Y)	(isnan(_X)||isnan(_Y))
#define signbit(_X) \
  (sizeof(_X)==sizeof(float)?_Signbitf(_X):\
  (sizeof(_X)==sizeof(double)?_Signbit(_X):_Signbitl(_X)))

/* The <math.h> header shall define the following symbolic constants. The
   values shall have type double and shall be accurate within the precision
   of the double type.
*/

#if _XOPEN_UNIX != -1 && _XOPEN_VERSION == 700
#define M_E		\
(2.7182818284590452353602874713526624977572\
4709369995957496696762772407663035354759)
#define M_LOG2E		\
(1.4426950408889634073599246810018921374266\
4595415298593413544940693110921918118509)
#define M_LOG10E	\
(0.4342944819032518276511289189166050822943\
9700580366656611445378316586464920887077)
#define M_LN2           \
(0.6931471805599453094172321214581765680755\
0013436025525412068000949339362196969471)
#define M_LN10		\
(2.3025850929940456840179914546843642076011\
0148862877297603332790096757260967735248)
#define M_PI		\
(3.1415926535897932384626433832795028841971\
6939937510582097494459230781640628620896)
#define M_PI_2		\
(1.5707963267948966192313216916397514420985\
8469968755291048747229615390820314310448)
#define M_PI_4		\
(0.7853981633974483096156608458198757210492\
9234984377645524373614807695410157155224)
#define M_1_PI		\
(0.3183098861837906715377675267450287240689\
1929148091289749533468811779359526845307)
#define M_2_PI		\
(0.6366197723675813430755350534900574481378\
3858296182579499066937623558719053690614)
#define M_2_SQRTPI	\
(1.1283791670955125738961589031215451716881\
0125865799771368817144342128493688298683)
#define M_SQRT2		\
(1.4142135623730950488016887242096980785696\
7187537694807317667973799073247846210703)
#define M_SQRT1_2	\
(0.7071067811865475244008443621048490392848\
3593768847403658833986899536623923105351)

/* The <math.h> header shall define the following symbolic constant:

   MAXFLOAT - Same value as FLT_MAX in <float.h>.
*/

#define MAXFLOAT	FLT_MAX
#endif

/* The <math.h> header shall define the following macros:

   HUGE_VAL - A positive double constant expression, not necessarily
   representable as a float. Used as an error value returned by the
   mathematics library. HUGE_VAL evaluates to +infinity on systems
   supporting IEEE Std 754-1985.
*/

#define HUGE_VAL	(_Dbl->_Inf._D)

/* HUGE_VALF - A positive float constant expression. Used as an
   error value returned by the mathematics library. HUGE_VALF
   evaluates to +infinity on systems supporting IEEE Std 754-1985.
*/

#define HUGE_VALF	(_Flt->_Inf._F)

/* HUGE_VALL - A positive long double constant expression. Used as
   an error value returned by the mathematics library. HUGE_VALL
   evaluates to +infinity on systems supporting IEEE Std 754-1985.
*/

#define HUGE_VALL	(_Ldbl->_Inf._L)

/* INFINITY - A constant expression of type float representing
   positive or unsigned infinity, if available; else a positive
   constant of type float that overflows at translation time.
*/

#define INFINITY	(_Flt->_Inf._F)

/* NAN - A constant expression of type float representing a quiet
   NaN. This macro is only defined if the implementation supports
   quiet NaNs for the float type.
*/

#define NAN		(_Flt->_Nan._F)

/* The following macros shall be defined for number classification.
   They represent the mutually-exclusive kinds of floating-point values.
   They expand to integer constant expressions with distinct values.
   Additional implementation-defined floating-point classifications,
   with macro definitions beginning with FP_ and an uppercase letter,
   may also be specified by the implementation.
*/

#define FP_INFINITE	(1)
#define FP_NAN		(2)
#define FP_NORMAL	(-1)
#define FP_SUBNORMAL	(-2)
#define FP_ZERO		(0)

/* The following optional macros indicate whether the fma() family of
   functions are fast compared with direct code:
*/

#define FP_FAST_FMA	1
#define FP_FAST_FMAF	1
#define FP_FAST_FMAL	1

/* If defined, the FP_FAST_FMA macro shall expand to the integer constant 1
   and shall indicate that the fma() function generally executes about as
   fast as, or faster than, a multiply and an add of double operands. If
   undefined, the speed of execution is unspecified. The other macros have
   the equivalent meaning for the float and long double versions.
*/

/* The following macros shall expand to integer constant expressions whose
   values are returned by ilogb(x) if x is zero or NaN, respectively. The
   value of FP_ILOGB0 shall be either INT_MIN or -INT_MAX. The value
   of FP_ILOGBNAN shall be either INT_MAX or INT_MIN.
*/

#define FP_ILOGB0	INT_MIN
#define FP_ILOGBNAN	INT_MIN

/* The following macros shall expand to the integer constants 1 and 2,
   respectively;
*/

#define MATH_ERRNO	(1)
#define MATH_ERREXCEPT	(2)

/* The following macro shall expand to an expression that has type int and
   the value MATH_ERRNO, MATH_ERREXCEPT, or the bitwise-inclusive OR of both:
*/
#define math_errhandling	(MATH_ERRNO|MATH_ERREXCEPT)

/* The value of math_errhandling is constant for the duration of the program.
   It is unspecified whether math_errhandling is a macro or an identifier
   with external linkage. If a macro definition is suppressed or a program
   defines an identifier with the name math_errhandling, the behavior is
   undefined. If the expression (math_errhandling & MATH_ERREXCEPT) can be
   non-zero, the implementation shall define the macros FE_DIVBYZERO,
   FE_INVALID, and FE_OVERFLOW in <fenv.h>.
*/

/* The following shall be declared as functions and may also be defined as
   macros. Function prototypes shall be provided.
*/

__BEGIN_DECLS

  double acos (double);
  float acosf (float);
  double acosh (double);
  float acoshf (float);
  long double acoshl (long double);
  long double acosl (long double);
  double asin (double);
  float asinf (float);
  double asinh (double);
  float asinhf (float);
  long double asinhl (long double);
  long double asinl (long double);
  double atan (double);
  double atan2 (double, double);
  float atan2f (float, float);
  long double atan2l (long double, long double);
  float atanf (float);
  double atanh (double);
  float atanhf (float);
  long double atanhl (long double);
  long double atanl (long double);
  double cbrt (double);
  float cbrtf (float);
  long double cbrtl (long double);
  double ceil (double);
  float ceilf (float);
  long double ceill (long double);
  double copysign (double, double);
  float copysignf (float, float);
  long double copysignl (long double, long double);
  double cos (double);
  float cosf (float);
  double cosh (double);
  float coshf (float);
  long double coshl (long double);
  long double cosl (long double);
  double erf (double);
  double erfc (double);
  float erfcf (float);
  long double erfcl (long double);
  float erff (float);
  long double erfl (long double);
  double exp (double);
  double exp2 (double);
  float exp2f (float);
  long double exp2l (long double);
  float expf (float);
  long double expl (long double);
  double expm1 (double);
  float expm1f (float);
  long double expm1l (long double);
  double fabs (double);
  float fabsf (float);
  long double fabsl (long double);
  double fdim (double, double);
  float fdimf (float, float);
  long double fdiml (long double, long double);
  double floor (double);
  float floorf (float);
  long double floorl (long double);
  double fma (double, double, double);
  float fmaf (float, float, float);
  long double fmal (long double, long double, long double);
  double fmax (double, double);
  float fmaxf (float, float);
  long double fmaxl (long double, long double);
  double fmin (double, double);
  float fminf (float, float);
  long double fminl (long double, long double);
  double fmod (double, double);
  float fmodf (float, float);
  long double fmodl (long double, long double);
  double frexp (double, int *);
  float frexpf (float, int *);
  long double frexpl (long double, int *);
  double hypot (double, double);
  float hypotf (float, float);
  long double hypotl (long double, long double);
  int ilogb (double);
  int ilogbf (float);
  int ilogbl (long double);
#if _XOPEN_UNIX != -1 && _XOPEN_VERSION == 700
  double j0 (double);
  double j1 (double);
  double jn (int, double);
#endif
  double ldexp (double, int);
  float ldexpf (float, int);
  long double ldexpl (long double, int);
  double lgamma (double);
  float lgammaf (float);
  long double lgammal (long double);
  long long llrint (double);
  long long llrintf (float);
  long long llrintl (long double);
  long long llround (double);
  long long llroundf (float);
  long long llroundl (long double);
  double log (double);
  double log10 (double);
  float log10f (float);
  long double log10l (long double);
  double log1p (double);
  float log1pf (float);
  long double log1pl (long double);
  double log2 (double);
  float log2f (float);
  long double log2l (long double);
  double logb (double);
  float logbf (float);
  long double logbl (long double);
  float logf (float);
  long double logl (long double);
  long lrint (double);
  long lrintf (float);
  long lrintl (long double);
  long lround (double);
  long lroundf (float);
  long lroundl (long double);
  double modf (double, double *);
  float modff (float, float *);
  long double modfl (long double, long double *);
  double nan (const char *);
  float nanf (const char *);
  long double nanl (const char *);
  double nearbyint (double);
  float nearbyintf (float);
  long double nearbyintl (long double);
  double nextafter (double, double);
  float nextafterf (float, float);
  long double nextafterl (long double, long double);
  double nexttoward (double, long double);
  float nexttowardf (float, long double);
  long double nexttowardl (long double, long double);
  double pow (double, double);
  float powf (float, float);
  long double powl (long double, long double);
  double remainder (double, double);
  float remainderf (float, float);
  long double remainderl (long double, long double);
  double remquo (double, double, int *);
  float remquof (float, float, int *);
  long double remquol (long double, long double, int *);
  double rint (double);
  float rintf (float);
  long double rintl (long double);
  double round (double);
  float roundf (float);
  long double roundl (long double);
  double scalbln (double, long);
  float scalblnf (float, long);
  long double scalblnl (long double, long);
  double scalbn (double, int);
  float scalbnf (float, int);
  long double scalbnl (long double, int);
  double sin (double);
  float sinf (float);
  double sinh (double);
  float sinhf (float);
  long double sinhl (long double);
  long double sinl (long double);
  double sqrt (double);
  float sqrtf (float);
  long double sqrtl (long double);
  double tan (double);
  float tanf (float);
  double tanh (double);
  float tanhf (float);
  long double tanhl (long double);
  long double tanl (long double);
  double tgamma (double);
  float tgammaf (float);
  long double tgammal (long double);
  double trunc (double);
  float truncf (float);
  long double truncl (long double);
#if _XOPEN_UNIX != -1 && _XOPEN_VERSION == 700
  double y0 (double);
  double y1 (double);
  double yn (int, double);

/* The following external variable shall be defined: */

  extern int signgam;
#endif

__END_DECLS

/* The behavior of each of the functions defined in <math.h> is specified in
   the System Interfaces volume of POSIX.1-2008 for all representable values
   of its input arguments, except where stated otherwise. Each function shall
   execute as if it were a single operation without generating any externally
   visible exceptional conditions.
*/

#endif /* _MATH_H */

/* END OF FILE */
