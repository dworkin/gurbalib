string uppercase(string str) {

  int i, sz;

  argcheck( str, 1, "string" );
  
  for ( i = 0, sz = strlen(str); i < sz; i++ ) {
    if (str[i]>='a' && str[i]<='z') str[i] -= 'a' - 'A' ;
  }
  return str ;
}
