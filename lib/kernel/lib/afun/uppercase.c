string uppercase(string str) {

  int i ;

  for (i=0;i<strlen(str);i++) {
    if (str[i]>='a' && str[i]<='z') str[i] -= 'a' - 'A' ;
  }
  return str ;
}

