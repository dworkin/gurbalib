private void _F_call_out2(mixed * tls, string fun, varargs mixed pl, mixed arg) {

  if (objectp(pl)) {
    DRIVER->set_tlvar(TLS_THIS_PLAYER, pl);
  } else if (pl && !arg) {
    arg = pl;
    pl = nil;
  }


  rlimits(MAX_DEPTH; MAX_TICKS) {
    if (arg && sizeof(arg)) {
      call_other(this_object(), fun, arg...);
    } else {
      call_other(this_object(), fun);
    }
  }
}

nomask void _F_call_out(string fun, varargs mixed pl, mixed arg) {
  _F_call_out2(DRIVER->new_tls(), fun, pl, arg);
}

