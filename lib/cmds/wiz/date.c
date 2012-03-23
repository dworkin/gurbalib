void usage() {
   write("Usage: date [-h]\n");
   write("Show the real world date.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("See also: time, status, wtime\n");
}

void main(string str) {
   if (str && str != "") {
      usage();
      return;
   }
   write(ctime(time()) + "\n");
}
