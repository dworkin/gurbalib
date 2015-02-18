/*
 * Thingol,10/27/2009
 * Function returns the function name that called a function.
 */
nomask static string previous_function(void) {
   mixed t;
   int i;

   t = call_trace();
   i = sizeof(t) - 3;

   if (i < 0) {
      i = 0;
   }

   t = t[i][TRACE_FUNCTION];

   return t;
}
