/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* setsign.c - sets the sign bit of a floating-point value

   AUTHOR: Gregory Pietsch
   
   ALGORITHM:

   Seminumerical.
*/

#include "xmath.h"

int
_Setsign (unsigned char *x, const _FP_METRIC_T * const m, int sign)
{
  if (sign)
    x[_BYTE (m->_Size, 0)] |= (1 << (CHAR_BIT - 1));
  else
    x[_BYTE (m->_Size, 0)] &= ~(~0 << (CHAR_BIT - 1));
}

/* END OF FILE */
