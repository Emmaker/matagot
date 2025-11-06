/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* ctan, ctanf, ctanl - complex tangent functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex tangent of z.

   RETURN VALUE:
  
   These functions shall return the complex tangent value.

   ERRORS:

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

double _Complex (ctan) (double _Complex z)
{
  double x = creal (z);
  double y = cimag (z);
  double sin_2x = sin (2.0 * x);
  double sinh_2y = sinh (2.0 * y);
  double cos_2x = cos (2.0 * x);
  double cosh_2y = cosh (2.0 * y);
  double real = sin_2x / (cos_2x + cosh_2y);
  double imag = sinh_2y / (cos_2x + cosh_2y);
  return CMPLX (real, imag);
}

float _Complex (ctanf) (float _Complex z)
{
  float x = crealf (z);
  float y = cimagf (z);
  float sin_2x = sinf (2.0F * x);
  float sinh_2y = sinhf (2.0F * y);
  float cos_2x = cosf (2.0F * x);
  float cosh_2y = coshf (2.0F * y);
  float real = sin_2x / (cos_2x + cosh_2y);
  float imag = sinh_2y / (cos_2x + cosh_2y);
  return CMPLXF (real, imag);
}

long double _Complex (ctanl) (long double _Complex z)
{
  long double x = creall (z);
  long double y = cimagl (z);
  long double sin_2x = sinl (2.0L * x);
  long double sinh_2y = sinhl (2.0L * y);
  long double cos_2x = cosl (2.0L * x);
  long double cosh_2y = coshl (2.0L * y);
  long double real = sin_2x / (cos_2x + cosh_2y);
  long double imag = sinh_2y / (cos_2x + cosh_2y);
  return CMPLXL (real, imag);
}

/* END OF FILE */
