void usage() {
   write("Usage: locate [-h] PLAYER\n");
   write("Locate player PLAYER.\n");
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

   IMUD_D->do_locate(str);
}
