string file_name(varargs object obj) {
   if (!obj) {
      return base_name() + ".c";
   } else {
      return base_name(obj) + ".c";
   }
}
