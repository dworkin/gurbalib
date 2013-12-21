/* Return the sentinel object for a list */
object list_sentinel(string list) {
   object *ptr;

   ptr = get_list(list);

   if (ptr) {
      return ptr[LIST_SENTINEL];
   }

   return nil;
}
