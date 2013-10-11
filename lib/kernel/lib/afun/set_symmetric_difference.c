mixed *set_symmetric_difference(mixed *a, mixed *b, varargs int r) {
   mixed *c;

   c = a ^ b;

   return r ? set_remove_repeats(c) : c;
}
