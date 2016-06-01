bool isPowerOfTwo(int n)
{ return n>0 && !(n&(n-1));}

bool isPowerOfTwo(int n) { // 0x00000100 ^ 0x00000011 == (0x00000100 << 1) - 1 return ((n > 0) && ((n ^ (n - 1)) == (n << 1) - 1)); }