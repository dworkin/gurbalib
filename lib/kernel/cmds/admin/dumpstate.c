void usage() {
  write("Usage: dumpstate [-h]\n");
  write("Create a backup of the current state of the mud.\n");
  write("* Note:\n");
  write("* The statedump is made when the current thread ends.\n");
  write("* We schedule a 0 delay call_out which will run after\n");
  write("* the current thread ends to notify the user.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
    if (str && str != "") {
     usage();
     return;
  }

  if( !require_priv( "system" ) ) {
    write("You must be admin to do that.");
    return;
  }

  DRIVER->save_game();
  write("Writing statedump");
  call_out("done",0);
}

void done() {
  write("Statedump done.");
}

