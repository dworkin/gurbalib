mixed *set_symmetric_difference(mixed *a, mixed *b, varargs int r) {
   mixed *c;

   c = a ^ b;

   if (r) {
      return set_remove_repeats(c);
   }

   return c;
}
