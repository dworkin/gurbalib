/* vim:set ft=lpc: */

inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: ls [-l] [-h] [<dir> ...]" });
   lines += ({ " " });
   lines += ({ "ls allows a wizard to list the contents of a directory." });
   lines += ({ "If no directory is given, it uses the wizard's current " +
      "working directory." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-l\tUse long listing, giving you more info" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples" });
   lines += ({ "\tls " + DOMAINS_DIR + "/required" });
   lines += ({ "\tls" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, cp, diff, edit, indent, more, mkdir, pwd, " +
      "rm, tail" });

   this_player()->more(lines);
}

static void main(string str) {
   int width;
   mixed *files;
   string *names, timestr, dirlist, path;
   int *sizes, *times, long, ancient, i, j, sz, max, len, rows, time, color_len;
   string cur_col;

   if (empty_str(str)) {
      str = ".";
   } else if (sscanf(str, "-%s", str)) {
      long = 1;
      if (str == "l") {
	 str = ".";
      } else if (!sscanf(str, "l %s", str)) {
	 usage();
	 return;
      }
   }

   str = normalize_path(str, this_player()->query_env("cwd"));
   if (!valid_read(str)) {
      write("Access denied.\n");
      return;
   }

   width = this_player()->query_width();

   files = get_dir(str);

   if (!files) {
      write("No such dir.\n");
      return;
   }

   path = str + "/";

   files = get_dir(path + "*");
   if (!files) {
      write(str + ": Access denied.\n");
      return;
   }

   names = files[0];
   sz = sizeof(names);
   if (sz == 0) {
      write(str + " is empty.\n");
      return;
   }
   sizes = files[1];
   times = files[2];

   for (i = 0; i < sz; i++) {
      j = strlen(names[i]);
      if (j > max) {
	 max = j;
      }
      j = sizes[i];
      if (j > len) {
	 len = j;
      }
   }
   if (long) {
      len = strlen((string) len) + 1;
      max += len + 14;
      ancient = time() - 6 * 30 * 24 * 60 * 60;
   }

   max += 2;
   j = (width + 1) / (max + 1);
   if (j == 0) {
      rows = sz;
   } else {
      rows = (sz + j - 1) / j;
   }

   dirlist = "";
   for (i = 0; i < rows; i++) {
      j = i;
      for (;;) {
	 if (sizes[j] < 0) {
	    cur_col = "%^MAGENTA%^";
	 } else {
	    string *parts;
	    parts = explode(names[j], ".");

	    if (sizeof(parts) > 1) {
	       if (parts[sizeof(parts) - 1] == "c") {
                  string name;
                  name = path + names[j][..strlen(names[j])-3];

                  if (COMPILER_D->test_object(name) && find_object(name)) {
                     cur_col = "%^HWHITE%^";
                     names[j] += "*";
                  } else {
                    cur_col = "%^YELLOW%^";
                  }
	       } else if (parts[sizeof(parts) - 1] == "o") {
		  cur_col = "%^BLUE%^";
	       } else if (strstr(parts[sizeof(parts) - 1], "~") != -1) {
		  cur_col = "%^ORANGE%^";
	       } else {
		  cur_col = "%^GREEN%^";
	       }
	    } else {
	       cur_col = "%^CYAN%^";
	    }
	 }

	 if (long) {
	    str = "            ";
	    if (sizes[j] >= 0) {
	       str += (string) sizes[j];
	    }

	    time = times[j];
	    timestr = ctime(time);
	    if (time >= ancient) {
	       timestr = timestr[3..15];
	    } else {
	       timestr = timestr[3..10] + timestr[19..23];
	    }
	    str =
	       str[strlen(str) - len..] + timestr + " " + cur_col + names[j] +
	       "%^RESET%^";
	 } else {
	    str = cur_col + names[j] + "%^RESET%^";
	 }

	 if (sizes[j] < 0) {
	    str += "/";
	 }
	 j += rows;
	 if (j >= sz) {
	    dirlist += str + "\n";
	    break;
	 }

	 color_len = strlen(str) - strlen(ANSI_D->strip_colors(str));

	 dirlist +=
	    (str + "                                        ")[0..(max +
	       color_len)];
      }
   }
   write(dirlist);
}
