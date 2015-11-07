void _F_add_clone(void) {
  object sentinel;

  if (!KERNEL()) {
    error("Illegal call to _F_add_clone()");
  }

  if (clone_num() != 0) {
    sentinel = find_object(base_name());

    if (sentinel) {
       sentinel->_F_add_clone();
    } else {
       error("Sentinel not found");
    }
  } else {
    _clone_count++;
  }
}

