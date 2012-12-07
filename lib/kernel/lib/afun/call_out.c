nomask static int call_out(string fun, mixed delay, varargs mixed arg ...) {
   argcheck(fun, 1, "string");
   argcheck((intp(delay) || floatp(delay)), 2, "int or float");

   return::call_out("_F_call_out", delay, fun,
      driver->get_tlvar(TLS_THIS_PLAYER), arg);
}
