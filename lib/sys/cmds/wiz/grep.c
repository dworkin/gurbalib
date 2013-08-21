inherit M_COMMAND;
void usage() {
   write("Usage: grep [-h] STRING FILE(s)\n");
   write("Find files in the list of FILES that contain STRING.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: diff\n");
}

static void main(string str) {
   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   /* XXX do the work here... */
}
