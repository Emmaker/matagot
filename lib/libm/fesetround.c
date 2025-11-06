/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fesetround - set current rounding direction

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The fesetround() function shall establish the rounding direction represented 
   by its argument round. If the argument is not equal to the value of a 
   rounding direction macro, the rounding direction is not changed.

   RETURN VALUE:

   The fesetround() function shall return a zero value if and only if the 
   requested rounding direction was established.

   ERRORS:

   No errors are defined.
*/

#include <fenv.h>

int (fesetround) (int round)
{
  switch (round)
    {
    case FE_DOWNWARD:
    case FE_TONEAREST:
    case FE_TOWARDZERO:
    case FE_UPWARD:
      _FEcurrent._FErounding = round;
      return 0;
    default:
      return 1;
    }
}

/* END OF FILE */
