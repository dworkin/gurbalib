string capitalize(string str) {
  if (!str) return str ;
  if (str[0] >= 'a' && str[0] <= 'z') {
    str[0] -= 'a' - 'A';
  }
  return str;
}

