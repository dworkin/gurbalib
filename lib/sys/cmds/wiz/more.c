inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: more [-h] [file]" });
   lines += ({ " " });
   lines += ({ "cat allows a wizard to concatenate a file " +
      "(print it to the screen)." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tmore void.c" });
   lines += ({ "\tmore " + DOMAINS_DIR + "/required/rooms/void.c" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cat, cd, cp, diff, edit, indent, ls, mkdir, pwd, " +
      "rm, tail" });

   return lines;
}

/* A highly advanced more command
 * By Fudge, Improved by Quixadhal
 */

#include <status.h>
#include <limits.h>

int file_size(string path) {
   /* by Mikael Lind */
   int i;
   mixed **dir;
   string *comps, base;

   if (path == "/") {
      return -2;
   }
   comps = explode(path, "/");
   base = comps[sizeof(comps) - 1];
   dir = get_dir(path);
   i = sizeof(dir[0]);
   while (i--) {
      if (dir[0][i] == base) {
         return dir[1][i];
      }
   }
   return -1;
}

static void main(string arg) {
   string file, file_data;
   string *tmp;
   string *lines;
   int where, i, size, length, offset, chopped, maxlines;

   if (empty_str(arg)) {
      arg = this_environment()->file_name();
   }

   if (sscanf(arg, "-%s", arg)) {
      this_player()->more(usage());
      return;
   }

   file = normalize_path(arg, this_player()->query_env("cwd"));
   size = file_size(file);

   if (file_exists(file) < 1) {
      write(arg + ": File not found.");
      return;
   }

   chopped = 0;
   offset = 0;
   lines = ( { } );
   length = size >= status()[ST_STRSIZE] / 2 ? status()[ST_STRSIZE] / 2 : size;
   maxlines = status()[ST_ARRAYSIZE] - 1;

   while (offset < size) {
      file_data = read_file(file, offset, length);
      offset += length;
      while (catch(tmp = explode(file_data, "\n"))) {
         chopped = 1;
         file_data = file_data[0..strlen(file_data) / 2];
      }

      for (i = 0; i < sizeof(tmp); i++) {
         if (sizeof(lines) < maxlines) {
            if (strlen(tmp[i]) > 79) {
               /* Big line. Break it up. */
               where = 0;
               while (where < strlen(tmp[i])) {
                  if (sizeof(lines) < maxlines) {
                     if (where + 79 < strlen(tmp[i])) {
                        lines += ( { tmp[i][where..where + 78] } );
                        where += 79;
                     } else {
                        lines += ( { tmp[i][where..] } );
                        where = strlen(tmp[i]);
                     }
                  } else {
                     chopped = 1;
                     break;
                  }
               }
            } else {
               lines += ( { tmp[i] } );
            }
         } else {
            chopped = 1;
            break;
         }
      }
   }
   if (chopped == 1) {
      lines += ( { "*** TRUNCATED ***" } );
   }

   this_player()->more(lines);
}
