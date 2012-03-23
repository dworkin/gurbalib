void usage() {
   write("Usage: passwd [-h]\n");
   write("Allows you to change your password.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

void main(string arg) {
   if (arg && arg != "") {
      usage();
      return;
   }

   call_other(this_user(), "change_passwd", "");
}
