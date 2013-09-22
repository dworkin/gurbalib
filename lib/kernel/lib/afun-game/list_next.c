/* Return the next object in a list */
object list_next(string list) {
   object *ptr;

   ptr = get_list(list);

   if (ptr) {
      return ptr[LIST_NEXT];
   }

   return nil;
}
