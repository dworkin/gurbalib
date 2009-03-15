nomask static int call_out(string fun, mixed delay, varargs mixed arg...) {
  return ::call_out("_F_call_out", delay, fun, arg);
}

