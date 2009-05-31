static void set_tlvar(string name, mixed value) {
  mapping vars;

  argcheck(stringp(name), 1, "string");

  vars = DRIVER->get_tlvar(TLS_UVARS);

  if(!vars) {
    vars = ([ ]);
  }

  vars[name] = value;
  /*
   * Needed because we might have initialized the mapping.
   * Would it make sense to use a flag indicating this so
   * we can prevent this call_other() ?
   */
  DRIVER->set_tlvar(TLS_UVARS, vars);
}

