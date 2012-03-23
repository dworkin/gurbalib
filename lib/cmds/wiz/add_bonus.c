void usage() {
   write("Usage: add_bonus [-h] STATNAME\n");
   write("Increase your bonus to stat STATNAME by 1.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: stats, add_base\n");
}

void main(string statname) {
   if (!statname || statname == "") {
      usage();
      return;
   }
   if (sscanf(statname, "-%s", statname)) {
      usage();
      return;
   }

   this_player()->add_bonus_stat(statname, 1);
   write("done!\n");
}
