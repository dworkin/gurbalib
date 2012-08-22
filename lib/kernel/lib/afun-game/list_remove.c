/* removes this object from a list */
atomic int list_remove(string list) {
   object *ptr;
   object sentinel, prev, next;

   if (PRIVLIST[list]) {
      if (owner_file(previous_program()) != PRIVLIST[list]) {
	 error("Attempt to manipulate privileged list " + list);
      }
   }

   ptr = get_list(list);

   if (!ptr) {
      return 0;
   }

   prev = ptr[LIST_PREV];
   next = ptr[LIST_NEXT];

   ptr = prev->get_list(list);
   ptr[LIST_NEXT] = next;

   ptr = next->get_list(list);
   ptr[LIST_PREV] = prev;

   return 1;
}
