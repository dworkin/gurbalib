nomask string base_name( void ) {

  string str,obname;
  int clone;

  obname = object_name(this_object());
  if( sscanf( obname, "%s#%d", str, clone ) ==2 )
    return str;
  return obname;
}

