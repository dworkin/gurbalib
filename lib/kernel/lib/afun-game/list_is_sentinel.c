// Is this object the sentinel for the given list?
int list_is_sentinel(string list) {
   object *ptr;

   ptr = get_list(list);
   return ptr && ptr[LIST_SENTINEL] == this_object();
}
