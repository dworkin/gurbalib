static int compile_library(string path, string code ...) {
#ifdef SECURITY_COMPILER_RW
   if (!valid_write(path)) {
      error("Permission denied");
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

   return::compile_library(path, code...);
}
