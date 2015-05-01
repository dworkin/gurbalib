nomask mixed *get_list(varargs string list) {
   if (KERNEL()) {
      if (ltable) {
         if (list) {
            return ltable[list];
         } else {
            return map_indices(ltable);
         }
      }
   }

   return nil;
}
