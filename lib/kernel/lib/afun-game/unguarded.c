static mixed unguarded( string fun, varargs mixed args... ) {
  if( !function_object( fun, this_object() ) ) {
    error("Undefined function: "+fun);
  }

  return call_other( this_object(), fun, args... );
}
