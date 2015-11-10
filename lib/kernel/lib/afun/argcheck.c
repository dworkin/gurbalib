#include <error_handling.h>

static void argcheck(mixed arg, int num, varargs string type) {
   mixed **trace;

   if (!arg) {
      trace = call_trace();
      if (type) {
         error(MAGIC_ERROR_ARGCHECK + (string) num + " to " +
            trace[sizeof(trace) - 2][2] +  " (needs " + type + ")");
      } else {
         error(MAGIC_ERROR_ARGCHECK + (string) num + " to " +
            trace[sizeof(trace) - 2][2]);
      }
   }
}
