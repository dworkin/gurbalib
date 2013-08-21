inherit M_COMMAND;
#define CHUNK_SIZE 1024

void usage() {
   string *lines;

   lines = ({ "Usage: cat [-h] [file]" });
   lines += ({ " " });
   lines += ({ "cat allows a wizard to concatenate a file " +
      "(print it to the screen)." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tcat void.c" });
   lines += ({ "\tcat " + DOMAINS_DIR + "/required/rooms/void.c" });
   lines += ({ "See also:" });
   lines += ({ "\tbrowse, cd, cp, diff, edit, ls, more, mkdir, pwd, " +
      "rm, tail" });

   this_player()->more(lines);
}

void cat_the_file(string file) {
   int cur, file_size, i, maxi;
   string *lines;
   string chunk;

   file_size = file_size(file);
   while (cur < file_size) {
      chunk = read_file(file, cur, CHUNK_SIZE);
      cur = cur + CHUNK_SIZE;
      lines = explode(chunk, "\n");
      maxi = sizeof(lines) - 1;
      for (i = 0; i < maxi; i++) {
         out(lines[i] + "\n");
      }
      out(lines[i]);
   }
}

static void main(string file) {
   string name;

   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

   if (!file || (file == "")) {
      file = this_player()->query_env("cwf");
   } else if (sscanf(file, "-%s", file)) {
      usage();
      return;
   }

   name = normalize_path(file, this_player()->query_env("cwd"));

   if (!name || (name == "")) {
      write("Access denied.\n");
      return;
   }

   if (file_exists(name) == 1) {
      cat_the_file(name);
      out("\n");
   } else {
      write("That file: " + file + "  does not exist.");
   }
}
