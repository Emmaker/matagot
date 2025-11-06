/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* fegetround - get current rounding direction

   AUTHOR: Gregory Pietsch

   DESCRIPTION:

   The functionality described on this reference page is aligned with the 
   ISO C standard. Any conflict between the requirements described here and 
   the ISO C standard is unintentional. This volume of POSIX.1-2008 defers 
   to the ISO C standard.

   The fegetround() function shall get the current rounding direction.

   RETURN VALUE:

   The fegetround() function shall return the value of the rounding direction 
   macro representing the current rounding direction or a negative value if 
   there is no such rounding direction macro or the current rounding direction 
   is not determinable.

   ERRORS:

   No errors are defined.
*/

#include <fenv.h>

int (fegetround) (void)
{
  return _FEcurrent._FErounding;
}

/* END OF FILE */
