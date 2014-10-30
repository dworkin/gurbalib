inherit M_COMMAND;

void usage(void) {
   string *lines;

   lines = ({ "Usage: unset [-h] VAR" });
   lines += ({ " " });
   lines += ({ "Remove an environment variable VAR." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tunset save_on_quit" });
   lines += ({ "See also:" });
   lines += ({ "\tset" });

   this_player()->more(lines);
}

void list_vars(void) {
   string name, *names;
   int i;

   names = this_player()->query_env_indices();
   for (i = 0; i < sizeof(names); i++) {
      out_unmod(names[i] + "=" + this_player()->query_env(names[i]) + "\n");
   }
}

static void main(string str) {

   if (empty_str(str)) {
      list_vars();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   this_player()->set_env(str, nil);
}
