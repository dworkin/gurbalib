inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: mkdir [-h] DIR" });
   lines += ({ " " });
   lines += ({ "mkdir allows you to make a directory named DIR." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tmkdir test" });
   lines += ({ "\tmkdir /tmp/test" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "browse");
   add_also("wiz", "cat");
   add_also("wiz", "cd");
   add_also("wiz", "cp");
   add_also("wiz", "diff");
   add_also("wiz", "edit");
   add_also("wiz", "indent");
   add_also("wiz", "ls");
   add_also("wiz", "more");
   add_also("wiz", "pwd");
   add_also("wiz", "rm");
   add_also("wiz", "tail");
}

static void main(string arg) {
   string file;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(arg)) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(arg, "-%s", arg)) {
      this_player()->more(usage());
      return;
   }

   file = normalize_path(arg, this_player()->query_env("cwd"));
   if (!file || (file == "")) {
      write("Permission denied.\n");
      return;
   }

   if (!file_exists(file)) {
      if (!make_dir(file)) {
         write("Unable to create directory.\n");
         return;
      } else {
         write("Directory created.\n");
         return;
      }
   } else {
      write("File or dir already exists.\n");
   }
}
