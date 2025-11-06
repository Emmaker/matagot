/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* copysign, copysignf, copysignl - number manipulation function

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   These functions shall produce a value with the magnitude of x and the 
   sign of y. On implementations that represent a signed zero but do not 
   treat negative zero consistently in arithmetic operations, these functions 
   regard the sign of zero as positive.

   RETURN VALUE:

   Upon successful completion, these functions shall return a value with the 
   magnitude of x and the sign of y.

   ERRORS:

   No errors are defined.

   ALGORITHM:
   
   Seminumerical.
*/

#include "xmath.h"

double (copysign) (double x, double y)
{
  _Setsign ((unsigned char *) &x, _Dbl,
	    _Getsign ((unsigned char *) &y, _Dbl));
  return x;
}

float (copysignf) (float x, float y)
{
  _Setsign ((unsigned char *) &x, _Flt,
	    _Getsign ((unsigned char *) &y, _Flt));
  return x;
}

long double (copysignl) (long double x, long double y)
{
  _Setsign ((unsigned char *) &x, _Ldbl,
	    _Getsign ((unsigned char *) &y, _Ldbl));
  return x;
}

/* END OF FILE */
