void usage() {
   write("Usage: diff [-h] [-o FILE] FILE1 FILE2\n");
   write("This is the poor man's diff. it uses a mapping to store lines.\n");
   write("So it only tells you if an exact line is in both files or not.\n");
   write("It will only let you know about the first occurance of a " +
      "line as well.\n");
   write("It works nicely enough for small cases though.  If you need more\n");
   write("power use a real diff.\n");
   write("Print out the differences between FILE1 and FILE2, " +
      "in std diff format.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
   write("\t-o FILE\tPrint the output to FILE instead of to the player.\n");
   write("See also: grep\n");
}

// Return an array of differences between the files
string *do_work(string file1, string file2) {
   string *lines1, *lines2, *lines, *keys;
   int i, max, c1, c2;
   mapping lns1, lns2;
   string tmp;

   lns1 = ([]);
   lns2 = ([]);

   file1 = normalize_path(file1, this_player()->query_env("cwd"));
   if (!file1 || file1 == "") {
      lines = ({ "No such file: $file1\n" });
      return lines;
   }
   file2 = normalize_path(file2, this_player()->query_env("cwd"));
   if (!file1 || file1 == "") {
      lines = ({ "No such file: $file1\n" });
      return lines;
   }

   lines1 = explode(read_file(file1), "\n");
   max = sizeof(lines1);
   for(i=0; i< max; i++ ) {
      tmp = lines1[i];
      if (!lns1[tmp]) 
         lns1[tmp] = i + 1;
      c1 = 1;
   }

   lines2 = explode(read_file(file2), "\n");
   max = sizeof(lines2);
   for(i=0; i< max; i++ ) {
      tmp = lines2[i];
      if (!lns2[tmp]) 
         lns2[tmp] = i + 1;
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
      for(i=0; i<max; i++) {
         tmp = keys[max-i];
         if(tmp && !lns2[tmp]) {
            lines += ({ lns1[tmp] + " : " + tmp });
         }
      }

     if (sizeof(lines) == 1) {
         lines = ({ });
      }

      keys = map_indices(lns2);
      max = sizeof(keys) -1;

      lines += ({ "Lines in file2 that are not in file1:" });
      for(i=0; i<max; i++) {
         tmp = keys[max-i];
         if(tmp && !lns1[tmp]) {
            lines += ({ lns2[tmp] + " : " + tmp });
         }
      }
   }

   return lines;
}

void do_work_tofile(string outfile, string file1, string file2) {
   string *lines;
   int i, max;

   outfile = normalize_path(outfile, this_player()->query_env("cwd"));
   if (!valid_write(outfile)) {
      write("Unable to write to file: " + outfile + "\n");
   } else {
      lines = do_work(file1, file2);
      max = sizeof(lines);
      for (i=0;i<max;i++) {
         write_file(outfile,lines[i]);
      }
   }
}

void do_work_toscreen(string file1, string file2) {
   string *lines;
 
   lines = do_work(file1, file2);
   this_player()->more(lines);
}

void main(string str) {
   string outfile, file1, file2;

   if (!str || str == "" || sscanf(str, "-h", str)) {
      usage();
      return;
   }

   if (sscanf(str, "-o %s %s %s", outfile, file1, file2)) {
      do_work_tofile(outfile, file1, file2);
   } else {
      if (sscanf(str, "%s %s", file1, file2)) {
	 do_work_toscreen(file1, file2);
      } else {
         usage();
	 return;
      }
   }
}
