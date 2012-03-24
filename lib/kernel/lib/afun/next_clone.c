nomask object next_clone() {
   if (clone_num() != -1) {
      return get_list("clones")[1];
   }
}
