/* This file has been put into the public domain by its author.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
   OTHER DEALINGS IN THE SOFTWARE.
*/

/* This is a little program that generates the values in float.c 
   AUTHOR: Gregory Pietsch
*/

#include <stdio.h>
#include <math.h>
#include <float.h>

int
little_endian (int s, int x)
{
  return s - x - 1;
}

int
big_endian (int s, int x)
{
  return x;
}

int
pdp_endian (int s, int x)
{
  return (s - x - 1) ^ 1;
}

int
middle_endian (int s, int x)
{
  return x ^ 1;
}

void
output_f (int s, int (*e) (int, int))
{
  static char d[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int i, j;

  printf ("#define _F%d(", s);
  for (i = 0; i < s; ++i)
    {
      printf ("_%c%c", d[i], i == s - 1 ? ')' : ',');
      if (i == 15 && i != s - 1)
	printf ("\\\n\t\t");
    }
  putchar ('\\');
  putchar ('\n');
  putchar ('\t');
  for (i = 0; i < s; ++i)
    {
      j = e (s, i);
      printf ("_%c%c", d[j], i == s - 1 ? '\n' : ',');
      if (i == 15 && i != s - 1)
	printf ("\\\n\t");
    }
}

void
byteorder (void)
{
  printf ("/* define __BYTE_ORDER */\n");
  printf ("#ifndef __BYTE_ORDER\n");
  printf ("#define __LITTLE_ENDIAN\t(0)\n");
  printf ("#define __BIG_ENDIAN\t(1)\n");
  printf ("#define __PDP_ENDIAN\t(2)\n");
  printf ("#define __MIDDLE_ENDIAN\t(3)\n");
  printf
    ("#define __BYTE_ORDER\t__LITTLE_ENDIAN\t/* change if not a PC... */\n");
  printf ("#endif\n");
  printf ("#if __BYTE_ORDER == __LITTLE_ENDIAN\n");
  output_f (4, little_endian);
  output_f (8, little_endian);
  output_f (10, little_endian);
  output_f (16, little_endian);
  /* output_f (32, little_endian); */
  printf ("#elif __BYTE_ORDER == __BIG_ENDIAN\n");
  output_f (4, big_endian);
  output_f (8, big_endian);
  output_f (10, big_endian);
  output_f (16, big_endian);
  /* output_f (32, big_endian); */
  printf ("#elif __BYTE_ORDER == __PDP_ENDIAN\n");
  output_f (4, pdp_endian);
  output_f (8, pdp_endian);
  output_f (10, pdp_endian);
  output_f (16, pdp_endian);
  /* output_f (32, pdp_endian); */
  printf ("#elif __BYTE_ORDER == __MIDDLE_ENDIAN\n");
  output_f (4, middle_endian);
  output_f (8, middle_endian);
  output_f (10, middle_endian);
  output_f (16, middle_endian);
  /* output_f (32, middle_endian); */
  printf ("#endif\n\n");
}

void
genfp (char *name, int sz, int e, int i)
{
  int p, dig, bias;
  int emin, emax;
  long double ld;
  unsigned char s[32];
  int j, x;

  printf ("_FP_METRIC_T %s = {\n", name);
  printf
    ("\t%d,\t/* _Size */\n\t%d,\t/* _Ebits */\n\t%d,\t/* _Explicit1bit */\n",
     sz, e, (sz == 10));
  p = (sz << 3) - e - i;
  printf ("\t%d,\t/* _Mant_dig */\n", p);
  dig = (int) ((p - 1) * log10l (2.0L));
  printf ("\t%d,\t/* _Dig */\n", dig);
  bias = ~(~0U << (e - 1));
  printf ("\t%d,\t/* _Min_exp */\n", emin = (int) (1 - bias));
  printf ("\t%d,\t/* _Max_exp */\n", emax = (int) (~(~0 << e) - 1 - bias));
  ld = ceill ((emin - 1) * log10l (2.0L));
  printf ("\t%d,\t/* _Min_10_exp */\n", (int) (ld));
  ld = floorl (emax * log10l (2.0L));
  printf ("\t%d,\t/* _Max_10_exp */\n", (int) (ld));
  printf ("\t/* _Max */\n");
  printf ("\t{ _F%u( ", (unsigned) sz);
  for (j = 0; j < sz; ++j)
    s[j] = (unsigned char) (~0);
  s[0] >>= 1;
  if (e <= 15)
    s[1] &= ~(1 << (15 - e));
  else
    s[2] &= ~(1 << (23 - e));
  for (j = 0; j < sz; ++j)
    {
      printf ("\'\\x%02X\'%s", s[j], (j == sz - 1) ? ") },\n" : ", ");
      if ((j & 7) == 7 && j < sz - 1)
	printf ("\n\t");
    }
  printf ("\t/* _Epsilon */\n");
  printf ("\t{ _F%u( ", (unsigned) sz);
  for (j = 0; j < sz; ++j)
    s[j] = (unsigned char) (0);
  x = 1 - p + bias;
  s[0] = x >> (e - 7);
  if (e > 15)
    {
      s[2] = x << (23 - e);
      s[1] = x >> (e - 15);
    }
  else
    s[1] = x << (15 - e);
  if (i)
    {
      if (e > 15)
	s[2] |= (0x80 >> (e - 14));
      else if (e == 15)
	s[2] |= 0x80;
      else
	s[1] |= 1 << (14 - e);
    }
  for (j = 0; j < sz; ++j)
    {
      printf ("\'\\x%02X\'%s", s[j], (j == sz - 1) ? ") },\n" : ", ");
      if ((j & 7) == 7 && j < sz - 1)
	printf ("\n\t");
    }
  printf ("\t/* _Min */\n");
  printf ("\t{ _F%u( ", (unsigned) sz);
  for (j = 0; j < sz; ++j)
    s[j] = (unsigned char) (0);
  if (e > 15)
    s[2] = (1 << (23 - e));
  else
    s[1] = (1 << (15 - e));
  if (i)
    {
      if (e > 15)
	s[2] |= (0x80 >> (e - 14));
      else if (e == 15)
	s[2] |= 0x80;
      else
	s[1] |= 1 << (14 - e);
    }
  for (j = 0; j < sz; ++j)
    {
      printf ("\'\\x%02X\'%s", s[j], (j == sz - 1) ? ") },\n" : ", ");
      if ((j & 7) == 7 && j < sz - 1)
	printf ("\n\t");
    }
  printf ("\t/* _Inf */\n");
  printf ("\t{ _F%u( ", (unsigned) sz);
  for (j = 0; j < sz; ++j)
    s[j] = (unsigned char) (0);
  s[0] = (unsigned char) (~0) >> 1;
  if (e <= 15)
    s[1] = (unsigned char) (~0) << (15 - e);
  else
    {
      s[1] = (unsigned char) (~0);
      s[2] = (unsigned char) (~0) << (23 - e);
    }
  for (j = 0; j < sz; ++j)
    {
      printf ("\'\\x%02X\'%s", s[j], (j == sz - 1) ? ") },\n" : ", ");
      if ((j & 7) == 7 && j < sz - 1)
	printf ("\n\t");
    }
  printf ("\t/* _NaN */\n");
  printf ("\t{ _F%u( ", (unsigned) sz);
  if (i)
    {
      if (e > 15)
	s[2] |= (0x80 >> (e - 15));
      else if (e == 14 || e == 15)
	s[2] = (e == 14) ? 0x80 : 0x40;
      else
	s[1] |= (1 << (e - 13));
    }
  else
    {
      if (e > 15)
	s[2] |= (0x80 >> (e - 15));
      else if (e == 15)
	s[2] = 0x80;
      else
	s[1] = (unsigned char) (~0) << (14 - e);
    }
  for (j = 0; j < sz; ++j)
    {
      printf ("\'\\x%02X\'%s", s[j], (j == sz - 1) ? ") }\n" : ", ");
      if ((j & 7) == 7 && j < sz - 1)
	printf ("\n\t");
    }
  printf ("};\n\n");
}

int
main (void)
{
  static int szs[] = { 4, 8, 10, 16, 32 };
  int i;

  printf ("/* float.c - constants for float.h\n"
	  "\n"
	  "   AUTHOR: Gregory Pietsch\n"
	  "\n" "*/\n" "\n" "#include \"xmath.h\"\n" "\n");
  byteorder ();
  genfp ("_FP4", 4, 8, 0);
  genfp ("_FP8", 8, 11, 0);
  genfp ("_FP10", 10, 15, 1);
  genfp ("_FP16", 16, 15, 0);
  /* genfp ("_FP32", 32, 19, 0); */
  for (i = 0; i < 4; ++i)
    printf ("#%s _FLT_SIZE == %d\nconst _FP_METRIC_T * const _Flt = (&_FP%d);\n",
	    i ? "elif" : "if", szs[i], szs[i]);
  printf ("#endif\n\n");
  for (i = 1; i < 4; ++i)
    printf ("#%s _DBL_SIZE == %d\nconst _FP_METRIC_T * const _Dbl = (&_FP%d);\n",
	    i != 1 ? "elif" : "if", szs[i], szs[i]);
  printf ("#endif\n\n");
  for (i = 1; i < 4; ++i)
    printf ("#%s _LDBL_SIZE == %d\nconst _FP_METRIC_T * const _Ldbl = (&_FP%d);\n",
	    i != 1 ? "elif" : "if", szs[i], szs[i]);
  printf ("#endif\n\n");
  printf ("/* END OF FILE */\n");
  return 0;
}
