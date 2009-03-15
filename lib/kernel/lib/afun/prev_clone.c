nomask object prev_clone() {
  if( clone_num() != -1 ) {
    return get_list( "clones" )[LIST_PREV];
  }
}

