nomask void set_list(string list, object * ptr) {
   if (KERNEL()) {
      argcheck(list, 1, "string");
      argcheck(ptr, 2, "array");

      if (!ltable) {
         ltable = ([]);
      }
      ltable[list] = ptr;
   }
}
