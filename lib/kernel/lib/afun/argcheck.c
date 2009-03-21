static void argcheck(mixed arg, int num, mixed type) {
  mixed **trace;

  if( ( type == "string" && typeof( arg ) != T_STRING ) ||
      ( type == "mapping" && typeof( arg ) != T_MAPPING ) ||
      ( type == "array" && typeof( arg ) != T_ARRAY ) ||
      ( type == "int" && typeof( arg ) != T_INT ) ||
      ( type == "float" && typeof( arg ) != T_FLOAT ) ||
      ( type == "object" && typeof( arg ) != T_OBJECT ) ||
      ( type == 0 ) 
  ) {
    trace = call_trace();
    error( MAGIC_ERROR_ARGCHECK + (string) num + " to " + 
      trace[sizeof(trace)-2][2] + ( type ? " (needs " + type + ")" : "" ) 
    );
  }
}
