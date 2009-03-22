/*
 * secondary auto object for kernel objects.
 *
 */

nomask int is_game_object() {
  return 0;
}

nomask int is_kernel_object() {
  return 1;
}

static object this_player() {
  return this_user() ? this_user()->query_player():nil;
}


static void write(string message) {
  if(this_player()) {
    this_player()->write(message);
  }
}
