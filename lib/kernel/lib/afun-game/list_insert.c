// inserts an object into a list before the object 'before'.
atomic int list_insert(string list, object before) {
   object *ptr;
   object sentinel, prev, next;

   if (PRIVLIST[list]) {
      if (owner_file(previous_program()) != PRIVLIST[list]) {
	 error("Attempt to manipulate privileged list " + list);
      }
   }

   if (get_list(list)) {
      return 0;
   }

   ptr = before->get_list(list);

   prev = ptr[LIST_PREV];
   next = before;
   sentinel = ptr[LIST_SENTINEL];

   set_list(list, ( { prev, next, sentinel } ) );
   ptr = prev->get_list(list);
   ptr[LIST_NEXT] = this_object();

   ptr = next->get_list(list);
   ptr[LIST_PREV] = this_object();

   return 1;
}
