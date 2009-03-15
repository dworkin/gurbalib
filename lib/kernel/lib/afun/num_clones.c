nomask int num_clones() {
  object next;
  int count;

  if( clone_num() == -1 ) {
    return -1;
  }

  next = find_object(base_name());
  count = 0;

  while(next = next->next_clone()) {
    count++;
  }
  return count;
}
