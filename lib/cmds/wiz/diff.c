void usage() {
   write("Usage: diff [-h] [-o FILE] FILE1 FILE2\n");
   write("Print out the differences between FILE1 and FILE2, " +
      "in std diff format.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\t-o FILE\tPrint the output to FILE instead of to the player.\n");
   write("See also: grep\n");
}

// XXX Still need to do more here...
void do_work_tofile(string outfile, string file1, string file2) {
}

void do_work_toscreen(string file1, string file2) {
}

void main(string str) {
   string outfile, file1, file2;
   if (!str || str == "" || sscanf(str, "-h", str)) {
      return usage();
   }

   if (sscanf(str, "-o %s %s %s", outfile, file1, file2)) {
      do_work_tofile(outfile, file1, file2);
   } else {
      if sscanf
	 (str, "%s %s", file1, file2) {
	 do_work_toscreen(file1, file2);
      } else {
	 return usage();
      }
   }
}
