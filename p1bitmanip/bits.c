/* 
 * CS:APP Data Lab 
 * 
 * Victor Cheung victorcheung
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  //NOTE: impossible to represent INT_MIN as a positive int
  //Uses mask to determine whether or not to invert bits
  //Uses arithmetic shift to determine mask
  //Uses mask to determine whether to add one
  int mask = x >> 31;
  return (mask ^ x) + !!mask;
}
/* 
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  //exploits properties of overflow
  //overflow only occurs when sign bits are the same
  //if the sign bit of sum differs from both then overflow has occured
  int sum = x + y;
  return !(((sum ^ x) & (sum ^ y)) >> 31);
}
/* 
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
	//we create by oring together 0x55 mask that has 1 in all even positions
	//we and it over x; if the output is the mask then all even bits are on
	//note we ignore bits in the odd positions
	//if it's not equal to the mask then not all even bits are set. 
  int a = 0X55;
  int b = a << 24 | a << 16 | a << 8 | a;
  return !((x & b) ^ b);
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    //extract specific bytes using shifts and masks
    //put bytes in place with opposing shifts
    //use inverted mask to copy over unchanged bits.
    int nshift = n << 3;
    int mshift = m << 3;
    int mask = 0XFF;
    int n_mask = mask << nshift;
    int m_mask = mask << mshift;
    int big_mask = ~(n_mask | m_mask);
    int nth = ((x & n_mask) >> nshift) & mask;
    int mth = ((x & m_mask) >> mshift) & mask;
    return ((nth << mshift) | (mth << nshift)) | (x & big_mask);
}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  //division by 2^n is just a right shift by n;
  //complication arises when x is negative since shift
  //causes rounding down instead of rounding to 0
  //we add a bias (number one less than the divisor) to rounding towards 0
  int divisor = (1 << n);
  int neg1 = ~0;
  int bias = divisor + neg1;
  int mask = (x >> 31);
  return (x + (mask & bias)) >> n;
}
/*
 * ezThreeFourths - multiplies by 3/4 rounding toward 0,
 *   Should exactly duplicate effect of C expression (x*3/4),
 *   including overflow behavior.
 *   Examples: ezThreeFourths(11) = 8
 *             ezThreeFourths(-9) = -6
 *             ezThreeFourths(1073741824) = -268435456 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int ezThreeFourths(int x) {
  //after the initial summation
  //we use the same idea as divpwr2
  //except with a given divisor and shift
  int sum = x + x + x;
  int mask = (sum >> 31);
  return (sum + (mask & 3)) >> 2;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //if the truncated-down-to-n-bits version of the number
  //is EQUAL to the original number then it fits
  //else it doesn't. 
  int shift = 32 + (~n + 1);
  return !(((x << shift) >> shift) ^ x);
}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {
  // use | to extend highest 1 all the way through
  // use ^ to isolate highest position bit
  // mask is used to distinguish between negatives and positives.
  int mask = x >> 31;
  int result;
  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  //isolate highest bit here
  result = ((x >> 1) ^ x);
  //exploits arithmetic shift to mask or not mask result
  return (mask & (1 << 31)) |  (~mask & result);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {

  //ilog2 is conveniently the number of bits after the greatest bit
  //we use the same algorithmn from greatestBitPos 
  //we shift the result down by 1 and then
  //we use a hamming-weight algorithmn to compute the number of set bits.
  //see http://en.wikipedia.org/wiki/Hamming_weight

  int c1;
  int c2;
  int c3;
  int c4;
  int c5;

  x = x | (x >> 1);
  x = x | (x >> 2);
  x = x | (x >> 4);
  x = x | (x >> 8);
  x = x | (x >> 16);
  x = (x >> 1);

  //hamming-weight CONSTANTS

  //c1 = 0X55555555
  c1 = 0X55 | (0X55 << 8);
  c1 = c1 | (c1 << 16);

  //c2 = 0X33333333
  c2 = 0X33 | (0X33 << 8);
  c2 = c2 | (c2 << 16);

  //c3 = 0X0F0F0F0F
  c3 = 0X0F | (0X0F << 8);
  c3 = c3 | (c3 << 16);

  //c4 = 0X00FF00FF
  c4 = 0XFF;
  c4 = c4 | (c4 << 16);

  //c5 = 0X0000FFFF
  c5 = 0XFF;
  c5 = c5 | (c5 << 8);

  x = (x & c1) + ((x >> 1) & c1);
  x = (x & c2) + ((x >> 2) & c2);
  x = (x & c3) + ((x >> 4) & c3);
  x = (x & c4) + ((x >> 8) & c4);
  x = (x & c5) + ((x >> 16) & c5);

  return x;
}
/* 
 * implication - return x -> y in propositional logic - 0 for false, 1
 * for true
 *   Example: implication(1,1) = 1
 *            implication(1,0) = 0
 *   Legal ops: ! ~ ^ |
 *   Max ops: 5
 *   Rating: 2
 */
int implication(int x, int y) {
    // simple implementation by definition of implications
	//if x is 0 we always return 1
	//else we return x == y
    return !x | !(x ^ y);
}
/*
 * isPower2 - returns 1 if x is a power of 2, and 0 otherwise
 *   Examples: isPower2(5) = 0, isPower2(8) = 1, isPower2(0) = 0
 *   Note that no negative number is a power of 2.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int isPower2(int x) {
  //1, 0 and negatives are all false and thus special cases
  //uses the fact that one less than a power of 2 turns on all
  //subsequent bits
  int neg1 = ~0;
  //if x is one returns 1
  //if x is not one returns 0
  int onecheck = !(x + ~0);
  // if x is zero returns 1
  // if x is not zero returns 0
  int zerocheck = !(neg1 & x);
  // if x is neg returns 0
  // if x is pos returns 1
  int negcheck = !(x >> 31);
  return ((!zerocheck) & negcheck & (!(x & (x + neg1)))) | onecheck;
}
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  // convert x to positive value; then only 0 - 1 will be negative
  // in which case the sign bit represents the return value.
  // creates the absval using a mask (same idea as absVal above)
  // modified to not use !! but mask to add 1 or not
  int mask = x >> 31;
  int absval = (mask ^ x) + (~mask + 1);
  int res = absval + ~0;
  return (res >> 31) & 1;
}
/*
 * multFiveEighths - multiplies by 5/8 rounding toward 0.
 *   Should exactly duplicate effect of C expression (x*5/8),
 *   including overflow behavior.
 *   Examples: multFiveEighths(77) = 48
 *             multFiveEighths(-22) = -13
 *             multFiveEighths(1073741824) = 13421728 (overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 3
 */
int multFiveEighths(int x) {
  //exact same idea as multThreeFourths
  //we compute the sum as usual
  //then we create a bias to round towards 0
  //as well as a mask for when the sum is negative. 
  int sum = x + x + x + x + x;
  int mask = sum >> 31;
  return (sum + (mask & 7)) >> 3;
}
/* 
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateLeft(int x, int n) {
  //we use the fact that we can piece together the result by 
  //considering the "left" and "right" parts.
  //the right part is interesting, since these are the bits
  //that get shifted out at the left.
  //we shift the leftmost bits (the right part) to the right
  //and isolate them with a mask
  //before unioning everything at the end.
  int left       = x << n;
  int initright  = x >> (32 + (~n + 1));
  int mask       = (1 << n) + ~0;
  int finalright = initright & mask;
  return left | finalright;
}
/*
 * satAdd - adds two numbers but when positive overflow occurs, returns
 *          maximum possible value, and when negative overflow occurs,
 *          it returns minimum positive value.
 *   Examples: satAdd(0x40000000,0x40000000) = 0x7fffffff
 *             satAdd(0x80000000,0xffffffff) = 0x80000000
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 4
 */
int satAdd(int x, int y) {
  //uses the the same property of integer overflow as from addOK
  //we test for positive overflow by checking that both x and y lead with 0 and that there is overflow
  //there is negative overflow if there is overflow but it's not postitive
  //finally we mask over the sum if there's overflow with the special return values
  //or we mask over the special return values if there is no overflow.
  int neg1         = ~0;
  int T_MIN        = 1 << 31;
  int T_MAX        = ~T_MIN;
  int sum          = x + y;
  int overflow     = (((sum ^ x) & (sum ^ y)) >> 31);
  int pos_overflow = !!(((x ^ T_MIN) & (y ^ T_MIN) & overflow) >> 31);
  int neg_overflow = overflow & !pos_overflow;
  overflow         = !!overflow;
  return ((overflow + neg1) & sum) | (~(pos_overflow + neg1) & T_MAX) | (~(neg_overflow + neg1) & T_MIN);
}
/* 
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) {
  //we find the absolute value of the signed number
  //invert the bits and add 1
  //we use a mask built from x to construct a branchless ternary expression
  //that determines our return value since in the case of a positive sign-magnitude
  //number the representations are the same.  
  int mask = x >> 31;
  int absVal = ~(1 << 31) & x;
  return (~mask & x) | (mask & (~absVal + 1));
}
/* 
 * tc2sm - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: tc2sm(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int tc2sm(int x) {
  //given that x > TMIN
  //we simply find the absolute value of the TC int via the same logic of absval 
  //and then use the mask to determine whether or not to set the MSB depending
  //upon whether the TC int was negative in the first place. 
  int mask = x >> 31;
  int absVal = (mask ^ x) + !!mask;
  int maskMSB = mask & (1 << 31);
  return absVal | maskMSB;
}
/*
 * trueThreeFourths - multiplies by 3/4 rounding toward 0,
 *   avoiding errors due to overflow
 *   Examples: trueThreeFourths(11) = 8
 *             trueThreeFourths(-9) = -6
 *             trueThreeFourths(1073741824) = 805306368 (no overflow)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int trueThreeFourths(int x)
{
  //we divide first to prevent overflow
  //we also have to take into account the effect of the last two bits
  //therefore we isolate them and multiply by three before dividing by 4
  //and if x is negative we note that to achieve rounding towards 0
  //we must add 1 to y (defined as 3/4 of the last three bits) whenever
  //there's a remainder. 
  int mask = x >> 31;
  int y = x & 3;
  y = (y << 1) + y;
  y = (y >> 2) + (mask & !!(0 ^ y));
  x = x >> 2;
  return (x << 1) + x + y;
}
/*we
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x)
{
  //we divide first to prevent overflow
  //we also have to take into account the effect of the last three bits
  //therefore we isolate them and multiply by five before dividing by 8
  //and if x is negative we note that to achieve rounding towards 0
  //we must add 1 to y (defined as 5/8 of the last three bits) whenever
  //there's a remainder. 
  int mask = x >> 31;
  int y = x & 7;
  y = (y << 2) + y;
  y = (y >> 3) + (mask & !!(y ^ 0));
  x = x >> 3;
  return (x << 2) + x + y;
}
