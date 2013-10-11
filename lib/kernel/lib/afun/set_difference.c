mixed *set_difference(mixed *a, mixed *b, varargs int r) {
   mixed *c;

   c = set_intersection(a, set_symmetric_difference(a, b));

   return r ? set_remove_repeats(c) : c;
}
