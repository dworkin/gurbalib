float atan2(float y, float x) {

#ifdef LPC_EXT_MATHS
   return ::atan2(y, x);
#else
   return nil;
#endif

}

float remainder(float x, float y) {

#ifdef LPC_EXT_MATHS
   return ::remainder(x, y);
#else
   return nil;
#endif

}

int *div(int numerator, int denominator) {

#ifdef LPC_EXT_MATHS
   return ::div(numerator, denominator);
#else
   return nil;
#endif

}

