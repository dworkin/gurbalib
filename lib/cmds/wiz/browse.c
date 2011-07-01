void usage() {
  write("Usage: browse [-h] [dir]\n");
  write("An interactive way to look at files.");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write("See also: cd, ls, pwd\n");
}

void main(varargs string arg) {
  if (sscanf(arg, "-%s",arg)) {
     usage();
     return;
  }

  "/sys/obj/browser"->browse( arg );
}
