nomask object prev_clone(void) {
   if (clone_num() != -1) {
      return get_list("clones")[LIST_PREV];
   }
}
