nomask void set_list(string list, object * ptr) {
  if(KERNEL()) {
    if(!ltable) ltable = ([ ]);
    ltable[list] = ptr;
  }
}

