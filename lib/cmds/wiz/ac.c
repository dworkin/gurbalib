void usage() {
   write("Usage: ac [-h]\n");
   write("Display your current armor class.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
   int ac;

   if (str && (str != "")) {
      usage();
      return;
   }

   ac = this_player()->query_defense();
   this_player()->message("%^CYAN%^AC: " + ac + "%^RESET%^");
}
