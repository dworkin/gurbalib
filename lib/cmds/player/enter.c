void usage() {
   write("Usage: enter [-h] OBJECT\n");
   write("Allows you to enter the specified object.  To see what you\n");
   write("can enter, \"look\" around.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string str) {
   string error;

   if (!str || str == "") {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   error = this_environment()->body_exit(this_player(), str);

   if (error)
      write(error);
}
