void usage() {
   write("Usage: diff [-h] [-w] [-o FILE] FILE1 FILE2\n");
   write("Print out the differences between FILE1 and FILE2, " +
      "in std diff format.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\t-w\tIgnore whitespace differences in the line.\n");
   write("\t-o FILE\tPrint the output to FILE instead of to the player.\n");
   write("See also: grep\n");
}

// Return an array of differences between the files
// if flag==1 ignore white space in a line
string *do_work(string file1, string file2, int flag) {
   string *lines, *keys;
   int i, max, c1, c2;
   mapping lns1, lns2;
   string tmp;

   lns1 = ([]);
   lns2 = ([]);

   file1 = normalize_path(file1, this_player()->query_env("cwd"));
   lines = explode(read_file(file1), "\n");
   max = sizeof(lines);
   for(i=0; i< max; i++ ) {
      tmp = lines[i];
      lns1[tmp] = 1;
      c1 = 1;
   }

   file2 = normalize_path(file2, this_player()->query_env("cwd"));
   lines = explode(read_file(file2), "\n");
   max = sizeof(lines);
   for(i=0; i< max; i++ ) {
      tmp = lines[i];
      lns2[tmp] = 1;
      c2 = 1;
   }

   lines = ({ });

   if (!c1) {
      write("File1: " + file1 + " is emtpy.\n");
   } else if (!c2) {
      write("File2: " + file2 + " is emtpy.\n");
   } else if (lns1 == lns2) {
      write("Files match.\n");
   } else {

      keys = map_indices(lns1);
      max = sizeof(keys) - 1;

      lines = ({ "Lines in file1 that are not in file2:" });
      for(i=max; i>=0; i--) {
         tmp = keys[max-i];
         if(tmp && !lns2[tmp]) {
            lines += ({ tmp });
         }
      }

     if (sizeof(lines) == 1) {
         lines = ({ });
      }

      keys = map_indices(lns2);
      max = sizeof(keys) -1;

      lines += ({ "Lines in file2 that are not in file1:" });
      for(i=max; i>=0; i--) {
         tmp = keys[max-i];
         if(tmp && !lns1[tmp]) {
            lines += ({ tmp });
         }
      }
   }

   return lines;
}

void do_work_tofile(string outfile, string file1, string file2, int flag) {
   string *lines;
   int i, max;

   outfile = normalize_path(outfile, this_player()->query_env("cwd"));
   if (!valid_write(outfile)) {
      write("Unable to write to file: " + outfile + "\n");
   } else {
      lines = do_work(file1, file2, flag);
      max = sizeof(lines);
      for (i=0;i<max;i++) {
         write_file(outfile,lines[i]);
      }
   }
}

void do_work_toscreen(string file1, string file2, int flag) {
   string *lines;
 
   lines = do_work(file1, file2, flag);
   this_player()->more(lines);
}

void main(string str) {
   string outfile, file1, file2;
   int flag;

   if (!str || str == "" || sscanf(str, "-h", str)) {
      usage();
      return;
   }

// XXX Need to find -w and remove it if it exits...  also need to handle it
   flag = 0;

   if (sscanf(str, "-o %s %s %s", outfile, file1, file2)) {
      do_work_tofile(outfile, file1, file2, flag);
   } else {
      if (sscanf(str, "%s %s", file1, file2)) {
	 do_work_toscreen(file1, file2, flag);
      } else {
         usage();
	 return;
      }
   }
}
