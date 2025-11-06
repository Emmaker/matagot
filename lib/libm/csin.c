/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* csin, csinf, csinl - complex sine functions

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex sine of z.

   RETURN VALUE:

   These functions shall return the complex sine value.

   ERRORS:

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

/* csin(z) = i*csinh(i*z) */

double _Complex (csin) (double _Complex z)
{
  z = csinh (CMPLX (-cimag (z), creal (z)));
  return CMPLX (-cimag (z), creal (z));
}

float _Complex (csinf) (float _Complex z)
{
  z = csinhf (CMPLXF (-cimagf (z), crealf (z)));
  return CMPLXF (-cimagf (z), crealf (z));
}

long double _Complex (csinl) (long double _Complex z)
{
  z = csinhl (CMPLXL (-cimagl (z), creall (z)));
  return CMPLXL (-cimagl (z), creall (z));
}

/* END OF FILE */
