inherit M_COMMAND;

void usage() {
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

static void main(string str) {

   if (!str || (str == "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   this_player()->set_env(str, nil);
}
