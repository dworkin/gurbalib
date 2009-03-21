nomask void _F_upgraded() {
  if(!KERNEL()) {
    return;
  }

  if( function_object( "upgraded", this_object( ) ) ) {
    this_object()->upgraded();
  }

  if( function_object( "setup", this_object() ) ) {
    this_object()->setup();
  }
}
