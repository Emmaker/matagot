/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* ctanh, ctanhf, ctanhl - complex hyperbolic tangent functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex hyperbolic tangent of z.

   RETURN VALUE:
  
   These functions shall return the complex hyperbolic tangent value.

   ERRORS:

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

double _Complex (ctanh) (double _Complex z)
{
  double x = creal (z);
  double y = cimag (z);
  double sinh_2x = sinh (2.0 * x);
  double sin_2y = sin (2.0 * y);
  double cosh_2x = cosh (2.0 * x);
  double cos_2y = cos (2.0 * y);
  double real = sinh_2x / cosh_2x;
  double imag = sin_2y / cosh_2x;
  return CMPLX (real, imag);
}

float _Complex (ctanhf) (float _Complex z)
{
  float x = crealf (z);
  float y = cimagf (z);
  float sinh_2x = sinhf (2.0L * x);
  float sin_2y = sinf (2.0L * y);
  float cosh_2x = coshf (2.0L * x);
  float cos_2y = cosf (2.0L * y);
  float real = sinh_2x / cosh_2x;
  float imag = sin_2y / cosh_2x;
  return CMPLXF (real, imag);
}

long double _Complex (ctanhl) (long double _Complex z)
{
  long double x = creall (z);
  long double y = cimagl (z);
  long double sinh_2x = sinhl (2.0L * x);
  long double sin_2y = sinl (2.0L * y);
  long double cosh_2x = coshl (2.0L * x);
  long double cos_2y = cosl (2.0L * y);
  long double real = sinh_2x / cosh_2x;
  long double imag = sin_2y / cosh_2x;
  return CMPLXL (real, imag);
}

/* END OF FILE */
