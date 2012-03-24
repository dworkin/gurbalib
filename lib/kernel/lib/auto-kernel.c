/*
 * secondary auto object for kernel objects.
 */

nomask int is_game_object() {
   return 0;
}

nomask int is_kernel_object() {
   return 1;
}
