nomask object next_clone(void) {
   if (clone_num() != -1) {
      return get_list("clones")[1];
   }
   return nil;
}
