string replace_string( string str, string old, string new ) {
  int i;
  int olen;
  int slen;
  string done;
  int d;

  argcheck( str, 1, "string" );
  argcheck( old, 2, "string" );
  argcheck( new, 3, "string" );

  olen = strlen( old );
  slen = strlen( str );

  d = 0;
  done = "";
  for( i=0; i < slen; i++ ) {

    if( slen > i + olen -1 ) {
      /* Still not reached the end of the string */
      if( str[i..(i+olen-1)] == old ) {
        /*Found an occurance of the old string*/
        done += new;
        d += strlen( new );
        i += olen-1;
      } else {
        done += " ";
        done[d] = str[i];
        d++;
      }
    } else {
      done += str[i..];
      return( done );
    }
  }
  return( done );
}

