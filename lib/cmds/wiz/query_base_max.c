void usage() {
   write("Usage: query_base_max [-h] [STAT]\n");
   write("Get the maximum base for stat STAT.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   write("base_stat_maximum = " +
      this_player()->query_race_object()->query_base_stat_maximum(str) + "\n");
   write("done!\n");
}
