mixed *set_invert(mixed *a, int dim, varargs int r) {
   mixed *c;
   int    nr;

   c = ({ });

   if (dim > sizeof(a)) {
      dim = sizeof(a);
   }

   for (nr = (dim-1); nr >= 0; nr--) {
      c += ({ a[nr] });
   }

   return r ? set_remove_repeats(c) : c;
}
