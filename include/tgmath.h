/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* tgmath.h - type-generic macros

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the
   ISO C standard. Any conflict between the requirements described here and
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers
   to the ISO C standard.

   The <tgmath.h> header shall include the headers <math.h> and <complex.h>
   and shall define several type-generic macros.

   Of the functions contained within the <math.h> and <complex.h> headers
   without an f (float) or l (long double) suffix, several have one or more
   parameters whose corresponding real type is double. For each such function,
   except modf(), j0(), j1(), jn(), y0(), y1(), and yn(), there shall be a
   corresponding type-generic macro. The parameters whose corresponding real
   type is double in the function synopsis are generic parameters. Use of the
   macro invokes a function whose corresponding real type and type domain are
   determined by the arguments for the generic parameters.

   For each unsuffixed function in the <math.h> header for which there is a
   function in the <complex.h> header with the same name except for a c
   prefix, the corresponding type-generic macro (for both functions) has the
   same name as the function in the <math.h> header. The corresponding
   type-generic macro for fabs() and cabs() is fabs().

   If at least one argument for a generic parameter is complex, then use of the
   macro invokes a complex function; otherwise, use of the macro invokes a real
   function.

   For each unsuffixed function in the <math.h> header without a c-prefixed
   counterpart in the <complex.h> header, except for modf(), j0(), j1(), jn(),
   y0(), y1(), and yn(), the corresponding type-generic macro has the same
   name as the function.

   If all arguments for generic parameters are real, then use of the macro
   invokes a real function; otherwise, use of the macro results in undefined
   behavior.

   For each unsuffixed function in the <complex.h> header that is not a
   c-prefixed counterpart to a function in the <math.h> header, the
   corresponding type-generic macro has the same name as the function.
*/

#ifndef __TGMATH_H__
#define __TGMATH_H__

#include <complex.h>
#include <math.h>

#define acos(_X) \
(_Generic (_X, long double _Complex: cacosl, double _Complex: cacos, \
           float _Complex: cacosf, long double: acosl, double: acos, \
           float: acosf, default: acos))(_X)
#define acosh(_X) \
(_Generic (_X, long double _Complex: cacoshl, double _Complex: cacosh, \
           float _Complex: cacoshf, long double: acoshl, double: acosh, \
           float: acoshf, default: acosh))(_X)
#define asin(_X) \
(_Generic (_X, long double _Complex: casinl, double _Complex: casin, \
           float _Complex: casinf, long double: asinl, double: asin, \
           float: asinf, default: asin))(_X)
#define asinh(_X) \
(_Generic (_X, long double _Complex: casinhl, double _Complex: casinh, \
           float _Complex: casinhf, long double: asinhl, double: asinh, \
           float: asinhf, default: asinh))(_X)
#define atan(_X) \
(_Generic (_X, long double _Complex: catanl, double _Complex: catan, \
           float _Complex: catanf, long double: atanl, double: atan, \
           float: atanf, default: atan))(_X)
#define atan2(_X, _Y) \
(_Generic (_X * _Y, long double: atan2l, double: atan2, float: atan2f, \
           default: atan2))(_X, _Y)
#define atanh(_X) \
(_Generic (_X, long double _Complex: catanhl, double _Complex: catanh, \
           float _Complex: catanhf, long double: atanhl, double: atanh, \
           float: atanhf, default: atanh))(_X)
#define carg(_X) \
(_Generic (_X, long double _Complex: cargl, double _Complex: carg, \
           float _Complex: cargf, default: carg))(_X)
#define cbrt(_X) \
(_Generic (_X, long double: cbrtl, double: cbrt, float: cbrtf, \
           default: cbrt))(_X)
#define ceil(_X) \
(_Generic (_X, long double: ceill, double: ceil, float: ceilf, \
           default: ceil))(_X)
#define cimag(_X) \
(_Generic (_X, long double _Complex: cimagl, double _Complex: cimag, \
           float _Complex: cimagf, default: cimag))(_X)
#define conj(_X) \
(_Generic (_X, long double _Complex: conjl, double _Complex: conj, \
           float _Complex: conjf, default: conj))(_X)
#define copysign(_X, _Y) \
(_Generic (_X * _Y, long double: copysignl, double: copysign, \
           float: copysignf, default: copysign))(_X, _Y)
#define cos(_X) \
(_Generic (_X, long double _Complex: ccosl, double _Complex: ccos, \
           float _Complex: ccosf, long double: cosl, double: cos, \
           float: cosf, default: cos))(_X)
#define cosh(_X) \
(_Generic (_X, long double _Complex: ccoshl, double _Complex: ccosh, \
           float _Complex: ccoshf, long double: coshl, double: cosh, \
           float: coshf, default: cosh))(_X)
#define cproj(_X) \
(_Generic (_X, long double _Complex: cprojl, double _Complex: cproj, \
           float _Complex: cprojf, default: cproj))(_X)
#define creal(_X) \
(_Generic (_X, long double _Complex: creall, double _Complex: creal, \
           float _Complex: crealf, default: creal))(_X)
#define erf(_X) \
(_Generic (_X, long double: erfl, double: erf, float: erff, default: erf))(_X)
#define erfc(_X) \
(_Generic (_X, long double: erfcl, double: erfc, float: erfcf, \
           default: erfc))(_X)
#define exp(_X) \
(_Generic (_X, long double _Complex: cexpl, double _Complex: cexp, \
           float _Complex: cexpf, long double: expl, double: exp, float: expf, \
           default: exp))(_X)
#define exp2(_X) \
(_Generic (_X, long double: exp2l, double: exp2, float: exp2f, \
           default: exp2))(_X)
#define expm1(_X) \
(_Generic (_X, long double: expm1l, double: expm1, float: expm1f, \
           default: expm1))(_X)
#define fabs(_X) \
(_Generic (_X, long double _Complex: cabsl, double _Complex: cabs, \
           float _Complex: cabsf, long double: fabsl, double: fabs, \
           float: fabsf, default: fabs))(_X)
#define fdim(_X, _Y) \
(_Generic (_X * _Y, long double: fdiml, double: fdim, float: fdimf, \
           default: fdim))(_X, _Y)
#define floor(_X) \
(_Generic (_X, long double: floorl, double: floor, float: floorf, \
           default: floor))(_X)
#define fma(_X, _Y, _Z) \
(_Generic (_X * _Y * _Z, long double: fmal, double: fma, float: fmaf, \
           default: fma))(_X, _Y, _Z)
#define fmax(_X, _Y) \
(_Generic (_X * _Y, long double: fmaxl, double: fmax, float: fmaxf, \
           default: fmax))(_X, _Y)
#define fmin(_X, _Y) \
(_Generic (_X * _Y, long double: fminl, double: fmin, float: fminf, \
           default: fmin))(_X, _Y)
#define fmod(_X, _Y) \
(_Generic (_X * _Y, long double: fmodl, double: fmod, float: fmodf, \
           default: fmod))(_X, _Y)
#define frexp(_X, _Y) \
(_Generic (_X, long double: frexpl, double: frexp, float: frexpf, \
           default: frexp))(_X, _Y)
#define hypot(_X, _Y) \
(_Generic (_X * _Y, long double: hypotl, double: hypot, float: hypotf, \
           default: hypot))(_X, _Y)
#define ilog(_X) \
(_Generic (_X, long double: ilogl, double: ilog, float: ilogf, \
           default: ilog))(_X)
#define ldexp(_X, _Y) \
(_Generic (_X, long double: ldexpl, double: ldexp, float: ldexpf, \
           default: ldexp))(_X, _Y)
#define lgamma(_X) \
(_Generic (_X, long double: lgammal, double: lgamma, float: lgammaf, \
           default: lgamma))(_X)
#define llrint(_X) \
(_Generic (_X, long double: llrintl, double: llrint, float: llrintf, \
           default: llrint))(_X)
#define llround(_X) \
(_Generic (_X, long double: llroundl, double: llround, float: llroundf, \
           default: llround))(_X)
#define log(_X) \
(_Generic (_X, long double _Complex: clogl, double _Complex: clog, \
           float _Complex: clogf, long double: logl, double: log, \
           float: logf, default: log))(_X)
#define log10(_X) \
(_Generic (_X, long double: log10l, double: log10, float: log10f, \
           default: log10))(_X)
#define log1p(_X) \
(_Generic (_X, long double: log1pl, double: log1p, float: log1pf, \
           default: log1p))(_X)
#define log2(_X) \
(_Generic (_X, long double: log2l, double: log2, float: log2f, \
           default: log2))(_X)
#define logb(_X) \
(_Generic (_X, long double: logbl, double: logb, float: logbf, \
           default: logb))(_X)
#define lrint(_X) \
(_Generic (_X, long double: lrintl, double: lrint, float: lrintf, \
           default: lrint))(_X)
#define lround(_X) \
(_Generic (_X, long double: lroundl, double: lround, float: lroundf, \
           default: lround))(_X)
#define nearbyint(_X) \
(_Generic (_X, long double: nearbyintl, double: nearbyint, float: nearbyintf, \
           default: nearbyint))(_X)
#define nextafter(_X, _Y) \
(_Generic (_X * _Y, long double: nextafterl, double: nextafter, \
           float: nextafterf, default: nextafter))(_X, _Y)
#define nexttoward(_X, _Y) \
(_Generic (_X, long double: nexttowardl, double: nexttoward, \
           float: nexttowardf, default: nexttoward))(_X, _Y)
#define pow(_X, _Y) \
(_Generic (_X * _Y, long double _Complex: cpowl, double _Complex: cpow, \
           float _Complex: cpowf, long double: powl, double: pow, \
           float: powf, default: pow))(_X, _Y)
#define remainder(_X, _Y) \
(_Generic (_X * _Y, long double: remainderl, double: remainder, \
           float: remainderf, default: remainder))(_X, _Y)
#define remquo(_X, _Y, _Z) \
(_Generic (_X * _Y, long double: remquol, double: remquo, float: remquof, \
           default: remquo))(_X, _Y, _Z)
#define rint(_X) \
(_Generic (_X, long double: rintl, double: rint, float: rintf, \
           default: rint))(_X)
#define round(_X) \
(_Generic (_X, long double: roundl, double: round, float: roundf, \
           default: round))(_X)
#define scalbln(_X, _Y) \
(_Generic (_X, long double: scalblnl, double: scalbln, float: scalblnf, \
           default: scalbln))(_X, _Y)
#define scalbn(_X, _Y) \
(_Generic (_X, long double: scalbnl, double: scalbn, float: scalbnf, \
           default: scalbn))(_X, _Y)
#define sin(_X) \
(_Generic (_X, long double _Complex: csinl, double _Complex: csin, \
           float _Complex: csinf, long double: sinl, double: sin, \
           float: sinf, default: sin))(_X)
#define sinh(_X) \
(_Generic (_X, long double _Complex: csinhl, double _Complex: csinh, \
           float _Complex: csinhf, long double: sinhl, double: sinh, \
           float: sinhf, default: sinh))(_X)
#define sqrt(_X) \
(_Generic (_X, long double _Complex: csqrtl, double _Complex: csqrt, \
           float _Complex: csqrtf, long double: sqrtl, double: sqrt, \
           float: sqrtf, default: sqrt))(_X)
#define tan(_X) \
(_Generic (_X, long double _Complex: ctanl, double _Complex: ctan, \
           float _Complex: ctanf, long double: tanl, double: tan, float: tanf, \
           default: tan))(_X)
#define tanh(_X) \
(_Generic (_X, long double _Complex: ctanhl, double _Complex: ctanh, \
           float _Complex: ctanhf, long double: tanhl, double: tanh, \
           float: tanhf, default: tanh))(_X)
#define tgamma(_X) \
(_Generic (_X, long double: tgammal, double: tgamma, float: tgammaf, \
           default: tgamma))(_X)
#define trunc(_X) \
(_Generic (_X, long double: truncl, double: trunc, float: truncf, \
           default: trunc))(_X)

#endif /* __TGMATH_H__ */