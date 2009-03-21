string lowercase(string str) {

  int i ;

  argcheck( str, 1, "string" );

  for (i=0;i<strlen(str);i++) {
    if (str[i]>='A' && str[i]<='Z') str[i] += 'a' - 'A' ;
  }
  return str ;
}

