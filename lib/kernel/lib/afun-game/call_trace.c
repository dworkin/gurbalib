/*
 * filter on call_trace kfun to hide arguments on
 * the stack from non-kernel code.
 */
static mixed *call_trace(void) {
   mixed *trace;
   int i, sz;

   trace =::call_trace();
   sz = sizeof(trace);
   trace = trace[0..(sz - 2)];
   for (i = 0; i < (sz-1); i++) {
      trace[i] = trace[i][0..(TRACE_FIRSTARG - 1)];
   }
   return trace;
}
