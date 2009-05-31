/*
 * filter on call_trace kfun to hide arguments on
 * the stack from non-kernel code.
 */
static mixed *call_trace() {
  mixed *trace;
  int i, sz;

  trace = ::call_trace();
  trace = trace[0 .. sizeof(trace) - 2];
  for (i = 0, sz = sizeof(trace); i < sz; i++) {
    trace[i] = trace[i][0..(TRACE_FIRSTARG - 1)];
  }
  return trace;
}

