object compile_object(string path, string code ...) {
   argcheck(path, 1, "string");

   if (!KERNEL() && !SYSTEM() ) {
#ifdef SECURITY_COMPILER_RW
      if (!valid_write(path)) {
         error("Permission denied.");
      }
#endif

      if (code && sizeof(code)) {
         if (!valid_write(path)) {
            error("Permission denied");
         }
      } else {
         if (!valid_read(path)) {
            error("Permission denied");
         }
      }
   }

   if (strlen(path) > 2) {
      if (path[strlen(path) - 2] == '.' && path[strlen(path) - 1] == 'c') {
         path = path[..strlen(path) - 3];
      }
   }
   if (find_object(COMPILER_D)) {
      path = COMPILER_D->allow_object(path);
   }
   if (code && sizeof(code)) {
      return driver->compile_object(path, code...);
   } else {
      return driver->compile_object(path);
   }
}
