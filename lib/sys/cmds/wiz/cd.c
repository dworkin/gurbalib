inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: cd [-h] [-here] [dir]" });
   lines += ({ " " });
   lines += ({ "Change the current working directory(cwd) to [dir]." });
   lines += ({ "If [dir] is not given, the working directory is set to the " +
      "wizards home directory." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-here\t Here, changes to the directory of the room " +
      "you are in." });

   lines += ({ "Examples:" });
   lines += ({ "\tcd /cmds         Change cwd to the /cmds directory." });
   lines += ({ "\tcd ..            Move up one directory." });
   lines += ({ "\tcd               Change cwd to /wiz/(username)." });
   lines += ({ "\tcd -here          Change to the directory of your current " +
      "location." });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "browse");
   add_also("wiz", "cat");
   add_also("wiz", "cp");
   add_also("wiz", "diff");
   add_also("wiz", "edit");
   add_also("wiz", "indent");
   add_also("wiz", "ls");
   add_also("wiz", "more");
   add_also("wiz", "mkdir");
   add_also("wiz", "pwd");
   add_also("wiz", "rm");
   add_also("wiz", "tail");
}

#define MODE_READ 0

static void main(string arg) {
   int tmp;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(arg)) {
      arg = "/wiz/" + this_player()->query_name();
   } else if(arg=="-here") {
      arg=path_file(this_player()->query_environment()->base_name())[0];
   } else if (sscanf(arg, "-%s", arg)) {
      this_player()->more(usage());
      return;
   }

   arg = normalize_path(arg, this_player()->query_env("cwd"));

   if (!arg || (arg == "")) {
      write("Access denied.\n");
      return;
   }

   if ((strlen(arg) > 1) && (arg[strlen(arg) - 1] == '/')) {
      arg = arg[..strlen(arg) - 2];
   }

   tmp = file_exists(arg);

   if (tmp == 1) {
      write("Can not cd to a file: " + arg + "\n");
      return;
   } else if (tmp != -1) {
      write("Error " + tmp + ": Dir not found: " + arg + "\n");
      return;
   }

   if (!valid(arg, MODE_READ)) {
      write("Access denied.\n");
      return;
   }

   this_player()->set_env("cwd", arg);
   write("" + this_player()->query_env("cwd") + "\n");
}
