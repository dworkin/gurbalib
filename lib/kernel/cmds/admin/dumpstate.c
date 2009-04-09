/*
 * Note:
 *
 * The statedump is made when the current thread ends.
 * We schedule a 0 delay call_out which will run after
 * the current thread ends to notify the user.
 *
 */

void main(string str) {
  DRIVER->save_game();
  write("Writing statedump");
  call_out("done",0);
}

void done() {
  write("Statedump done.");
}

