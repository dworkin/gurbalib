atomic private void del_clone(void) {
  object * ptr;
  object prev;
  object next;

  ptr = get_list( "clones" );
  prev = ptr[LIST_PREV];
  next = ptr[LIST_NEXT];

  /*
   * If there is a next object in the list, ensure its
   * 'prev' object gets set to our 'prev' object.
   */
  if (next) {
    ptr = next->get_list( "clones" );
    ptr[LIST_PREV] = prev;
  }

  /*
   * Set the 'next' object in our 'prev', if there is no
   * 'prev' we are in big trouble. (this should only
   * occur in the master, and the code that runs here
   * should never get called in the master)
   */
  if (prev) {
    ptr = prev->get_list( "clones" );
    ptr[LIST_NEXT] = next;
  } else {
    error("There must be a previous link when removing a clone");
  }
  find_object(base_name())->_F_remove_clone();
}

private void __F_destruct(void) {
  switch( clone_num() ) {
    case 0 :
      DRIVER->remove_program(
        base_name(),
        status( this_object() )[O_COMPILETIME],
        status( this_object() )[O_INDEX]
      );
      break;
    case -1 :
      break;
    default :
      del_clone();
      break; 
  }

  ::destruct_object(this_object());
}

nomask void _F_destruct(void) {
  object * ptr;

  if (!KERNEL()) {
     return;
  }

/*
 * Nice idea, but not yet...
 */

#if 0
  if ( sscanf( base_name(), "/kernel/%*s" ) == 1 || sscanf( base_name(), "/sys/%*s" ) == 1 ) {
    if ( !require_priv( "system" ) ) {
      error( "Permission denied" );
    }
  }
#endif

  ptr = get_list( "clones" );

  switch(clone_num()) {
    case 0  :
      if ( ptr && ( ptr[LIST_PREV] || ptr[LIST_NEXT] ) ) {
        error("Trying to destruct master that has clones.");
      }
      break;
  }
  if ( function_object( "destructing", this_object() ) ) {
    call_other( this_object(), "destructing" );
  }
  __F_destruct();
}
