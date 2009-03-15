private void _F_call_out2(mixed * tls, string fun, varargs mixed arg) {
  rlimits(MAX_DEPTH; MAX_TICKS) {
    if(arg && sizeof(arg)) {
      call_other(this_object(),fun,arg...);
    } else {
      call_other(this_object(),fun);
    }
  }
}

nomask void _F_call_out(string fun, varargs mixed arg) {
  _F_call_out2(DRIVER->new_tls(), fun, arg);
}

