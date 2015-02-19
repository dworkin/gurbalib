mixed *set_remove_repeats(mixed *a) {
   mixed *c;
   int nr, dim;

   c = ({ });

   for (nr = 0, dim = sizeof(a); nr < dim; nr++) {
      c |= ({ a[nr] });
   }

   return c;
}

