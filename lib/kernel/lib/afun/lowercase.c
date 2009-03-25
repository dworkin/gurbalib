string lowercase(string str) {

  int i, sz;

  argcheck( str, 1, "string" );

  for ( i = 0, sz = strlen(str); i < sz; i++ ) {
    if (str[i]>='A' && str[i]<='Z') str[i] += 'a' - 'A' ;
  }
  return str ;
}
