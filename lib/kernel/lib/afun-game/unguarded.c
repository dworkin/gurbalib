static mixed unguarded( string fun, varargs mixed args... ) {
  return call_other( this_object(), fun, args... );
}
