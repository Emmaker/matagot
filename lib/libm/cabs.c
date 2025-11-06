/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* cabs, cabsf, cabsl - return a complex absolute value

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall compute the complex absolute value (also called 
   norm, modulus, or magnitude) of z.

   RETURN VALUE:

   These functions shall return the complex absolute value.

   ERRORS:

   No errors are defined.
*/

#include <complex.h>
#include "xmath.h"

double (cabs) (double _Complex z)
{
  return hypot (creal (z), cimag (z));
}

float (cabsf) (float _Complex z)
{
  return hypotf (crealf (z), cimagf (z));
}

long double (cabsl) (long double _Complex z)
{
  return hypotl (creall (z), cimagl (z));
}

/* END OF FILE */
