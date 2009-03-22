/*
 * Creators, destructors, also does clone tracking
 *
 * A note to the reader
 * Using linked lists for clone tracking may seem overly complicated
 * but it makes it scale beyond the maximum array size.
 *
 * Aidil@Way of the Force
 */

atomic private void add_clone() {
  object * ptr;
  object master;
  object next;

  master = find_object(base_name());
  if(!master) {
    error("Trying to add a clone but the master object for it is gone.");
  }

  /*
   * Master has the head of the list
   */
  ptr = master->get_list("clones");

  next = ptr[LIST_NEXT];

  /*
   * Change the 'next' field in the master to point to us
   */
  ptr[LIST_NEXT] = this_object();

  /*
   * Set our own entry for the list
   */
  set_list( "clones", ({ master, next }) );

  /*
   * Change 'prev' in the next object in the clonelist
   * so it points to us.
   */
  if(next) {
    ptr = next->get_list( "clones" );
    ptr[LIST_PREV] = this_object();
  }
}

nomask void _F_create() {
  object * ptr;
  object master, next;

  switch(clone_num()) {

    /* LWO, unhandled for now */
    case -1 : 
      break;

    /* Blueprint, setup clonelist */
    case 0  :
      set_list( "clones", ({ nil, nil }) );
      break;

    /* Clone, add to clone list */
    default :
      add_clone();
      break;
  }

  driver = find_object(DRIVER);
  if(object_name(this_object()) == SECURE_D) {
    secure_d = this_object();
  } else {
    secure_d = find_object(SECURE_D);
  }

  if( function_object( "create", this_object() ) ) {
    call_other(this_object(),"create");
  }
}
