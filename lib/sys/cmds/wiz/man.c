inherit M_COMMAND;

/* A highly advanced man command 
 * By Aphex,  Improved by Aidil :)
 */

#define BASEDIR "/doc/"

static string *topics;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: man [-h] [TOPIC]" });
   lines += ({ " " });
   lines += ({ "Get more information on topic TOPIC, if it exists." });
   lines += ({ "Try \"man man\" for more info." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tman man" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "cmds");
   add_also("player", "help");
}

static string *build_dir(string str) {
   string *dir;
   string *result;
   int pos, sz;

   result = ( { } );

   dir = get_dir(str + "*")[0];
   dir -= ( { ".svn" } );
   sz = sizeof(dir);
   for (pos = 0; pos < sz; pos++) {
      if (file_exists(str + dir[pos]) == -1) {
         result += ( { str + dir[pos] } );
         result += build_dir(str + dir[pos]);
      }
   }
   return result;
}

void rebuild_topics(void) {
   topics = build_dir(BASEDIR);
}

void create(void) {
   rebuild_topics();
}

static string *dir_index(string what, int width) {
   string *res, *dir, line;
   int ncollumns, i, j, sz;

   dir = get_dir(what + "/*")[0];
   if (!dir) {
      return ({ });
   }

   ncollumns = width / 19;

   dir -= ({ ".svn" });
   res = ({ });

   sz = sizeof(dir);
   for (i = 0; i < sz; i += ncollumns) {
      line = "";
      for (j = 0; j < ncollumns; j++) {
         if (i + j < sz) {
            if (file_exists(what + dir[i + j]) == -1) {
               line += (dir[i + j] + "/                     ")[0..18];
            } else {
               line += (dir[i + j] + "                              ")[0..18];
            }
         }
      }
      res += ({ line });
   }
   return res;
}

static void main(string arg) {
   string file, header, *tmp, *lines;
   int i, j, found, where, width, sz;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(arg)) {
      arg = "";
   }

   if (sscanf(arg, "-%s", arg) || arg == "man") {
      this_player()->more(usage());
      return;
   }

   if (arg == "--reindex") {
      rebuild_topics();
      write(dump_value(topics, ([])) + "\n");
      return;
   }

   arg = lowercase(arg);

   file = normalize_path(arg, BASEDIR);

   if (file_exists(file) == 0) {
      sz = sizeof(topics);
      for (j = 0; j < sz; j++) {
         file = normalize_path(arg, topics[j]);
         if (file_exists(file) != 0) {
            found++;
            break;
         }
      }
   } else {
      found = 1;
   }

   if (!found) {
      write(capitalize(arg) + ": Unknown man page.");
      write("If \"" + arg + "\" is a command, for more info try:\n\t" +
         arg + " -h\n");
      LOG_D->write_log("man", this_player()->query_Name() + " on " +
         ctime(time()) + ": " + arg + "\n");
      return;
   }

   width = this_player()->query_width();
   width--;

   if (file_exists(file) > 0) {
      header = "Manpage for " + arg + ".";
      tmp = explode(read_file(file), "\n");
   } else {
      header = "Index for " + arg + ".";
      tmp = dir_index(file, width);
   }

   lines = ( { } );
   write(header + "\n");
   sz = strlen(header);
   for (i = 0; i < sz; i++) {
      out("-");
   }
   write("\n");
   sz = sizeof(tmp);
   for (i = 0; i < sz; i++) {
      if (strlen(tmp[i]) > width) {
         /* Big line. Break it up. */
         where = 0;
         while (where < strlen(tmp[i])) {
            if (where + width < strlen(tmp[i])) {
               lines += ( { tmp[i][where..where + (width - 1)] } );
               where += width;
            } else {
               lines += ( { tmp[i][where..] } );
               where = strlen(tmp[i]);
            }
         }
      } else {
         lines += ( { tmp[i] } );
      }
   }

   this_player()->more(lines);
}
