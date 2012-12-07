/*
 * Create a new doubly linked list with the current object
 * as list sentinel
 */
atomic int list_new(string list) {
   object *ptr;

   if (PRIVLIST[list]) {
      if (owner_file(previous_program()) != PRIVLIST[list]) {
	 error("Attempt to manipulate privileged list " + list);
      }
   }

   if (get_list(list)) {
      return 0;
   }

   set_list(list, ( { this_object(), this_object(), this_object() } ) );
}
