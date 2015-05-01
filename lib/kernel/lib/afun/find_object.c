nomask static object find_object(string path, varargs int flag) {
   if (!flag || (!KERNEL() && !SYSTEM())) {
      if (::find_object(COMPILER_D)) {
         path = COMPILER_D->allow_object(path);
      }
   }
   return::find_object(path);
}
