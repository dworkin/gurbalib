static mixed get_tlvar(string name) {
  mapping vars;

  argcheck(stringp(name), 1, "string");

  vars = DRIVER->get_tlvar(TLS_UVARS);
  if(vars)
    return vars[name];
}
