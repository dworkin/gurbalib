static void set_tlvar(string name, mixed value) {
  mapping vars;

  argcheck(stringp(name), 1, "string");

  vars = DRIVER->get_tlvar(TLS_UVARS);

  if(!vars) {
    vars = ([ ]);
  }

  vars[name] = value;
  DRIVER->set_tlvar(TLS_UVARS, vars);
}

