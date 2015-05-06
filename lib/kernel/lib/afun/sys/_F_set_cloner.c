void _F_set_cloner(string user, string trace) {
  if (!KERNEL()) {
    error("Illegal call to _F_set_cloner");
  }

  _cloner = user;
  _clone_trace = trace;
}
