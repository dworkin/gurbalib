/*
 * secondary auto object for kernel objects.
 */

nomask int is_game_object(void) {
   return 0;
}

nomask int is_kernel_object(void) {
   return 1;
}
