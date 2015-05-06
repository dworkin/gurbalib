nomask void _F_upgraded(void) {
  if (!KERNEL()) {
    return;
  }

  if ( function_object( "upgraded", this_object( ) ) ) {
    this_object()->upgraded();
  }
}
