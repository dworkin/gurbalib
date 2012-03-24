// Return the previous object in the list
object list_next(string list) {
   object *ptr;
   ptr = get_list(list);
   if (ptr)
      return ptr[LIST_PREV];
}
