mixed * filter_array( mixed * arr, string fun, varargs object obj, mixed extra... ) {
  mixed * res;
  int i;
  int sz;

  argcheck( arrayp( arr ), 1, "array" );
  argcheck( stringp( fun ), 2, "string" );

  if( !objectp( obj ) ) {
    obj = this_object();
  }

  res = ({ });

  for( i = 0, sz = sizeof( arr ); i < sz; i++ ) {
    if( call_other( obj, fun, arr[i], extra... ) ) {
      res += ({ arr[i] });
    }
  }

  return res;
}

