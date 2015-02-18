mixed *set_difference(mixed *a, mixed *b, varargs int r) {
   mixed *c;

   c = set_intersection(a, set_symmetric_difference(a, b));

   if (r) {
      return set_remove_repeats(c);
   }

   return c;
}
