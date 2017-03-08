float get_nth_fibonacci(float n) {
   return ( (1.0 / sqrt(5.0) ) * pow(((1.0 + sqrt(5.0)) / 2.0), n) ) -
      ( (1.0 / sqrt(5.0) ) * pow(( (1.0 - sqrt(5.0)) / 2.0), n) );
}

float *get_m_through_n_fibonacci(int m, int n) {
   float *fibos;
   int    i, dim;

   dim = n - m;
   fibos = allocate(dim);
   
   for (i = 0; i < dim; i++) {
      fibos[i] = get_nth_fibonacci((float) m + (float) i);
   }

   return fibos;
}
