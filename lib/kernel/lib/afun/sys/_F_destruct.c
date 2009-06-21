atomic private void del_clone() {
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
  if(next) {
    ptr = next->get_list( "clones" );
    ptr[LIST_PREV] = prev;
  }

  /*
   * Set the 'next' object in our 'prev', if there is no
   * 'prev' we are in big trouble. (this should only
   * occur in the master, and the code that runs here
   * should never get called in the master)
   */
  if(prev) {
    ptr = prev->get_list( "clones" );
    ptr[LIST_NEXT] = next;
  } else {
    error("There must be a previous link when removing a clone");
  }
  find_object(base_name())->_F_remove_clone();
}

nomask void _F_destruct() {
  object * ptr;

  if(!KERNEL())
    return;

  ptr = get_list( "clones" );

  switch(clone_num()) {
    case -1 :
      break;
    case 0  :
      if( ptr && ( ptr[LIST_PREV] || ptr[LIST_NEXT] ) ) {
        error("Trying to destruct master that has clones.");
      }
      break;
    default :
      del_clone();
      break;
  }
  if( function_object( "destructing", this_object() ) ) {
    call_other( this_object(), "destructing" );
  }

  ::destruct_object(this_object());
}

