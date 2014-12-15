static void argcheck(mixed arg, int num, varargs string type) {
   if (!arg) {
      mixed **trace;
      string str;

      trace = call_trace();

      if (type) {
         str = "(needs " + type + ")";
      } else {
         str = "";
      }

      error(MAGIC_ERROR_ARGCHECK + (string) num + " to " +
	 trace[sizeof(trace) - 2][2] + str);
   }
}
