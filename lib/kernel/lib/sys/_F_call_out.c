private void _F_call_out2(mixed * tls, string fun, object pl, varargs mixed arg) {
  DRIVER->set_tlvar(TLS_THIS_PLAYER,pl);

  rlimits(MAX_DEPTH; MAX_TICKS) {
    if(arg && sizeof(arg)) {
      call_other(this_object(),fun,arg...);
    } else {
      call_other(this_object(),fun);
    }
  }
}

nomask void _F_call_out(string fun, object pl, varargs mixed arg) {
  _F_call_out2(DRIVER->new_tls(), fun, pl, arg);
}

