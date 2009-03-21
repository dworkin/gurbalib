nomask static int call_out(string fun, mixed delay, varargs mixed arg...) {
  argcheck( fun, 1, "string" );
  argcheck( delay, 2 , ( floatp( delay ) || intp( delay ) ) );
  return ::call_out("_F_call_out", delay, fun, arg);
}

