int clone_num() {

  string str ;
  int clone ;

  if (sscanf(object_name(this_object()),"%s#%d",str,clone)==2) {
    return clone ;
  }
  return 0 ;
}

