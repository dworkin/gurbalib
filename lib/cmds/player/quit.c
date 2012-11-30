void usage() {
   write("Usage: quit [-h]\n");
   write("This is how you leave the game.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("Examples:\n");
   write("\tquit\n");
   write("See also: score, who\n");
}

void main(string str) {
   if (str && str != "") {
      usage();
      return;
   }

   this_player()->do_quit();
}
