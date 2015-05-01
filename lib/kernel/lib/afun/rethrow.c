#include <error_handling.h>

void rethrow(varargs string str) {
   string error;
   string *lines;

   if (error = caught_error(1)) {
      if (str) {
         lines = explode(error, "\n");
         lines[0] = str;
         error = implode(lines, "\n");
      }
      error(MAGIC_ERROR_RETHROWN + error);
   }
}
