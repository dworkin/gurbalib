static mixed get_otlvar(string name) {
  mapping vars;

  argcheck(stringp(name), 1, "string");

  vars = DRIVER->get_tlvar(TLS_OVARS);
  if(vars && vars[this_object()])
    return vars[this_object()][name];
}
