nomask int num_clones(void) {
   if (clone_num() == 0) {
      return _clone_count;
   } else {
      return find_object(base_name())->num_clones();
   }
}
