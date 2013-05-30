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

void main(string str) {
   if (!query_wizard(this_player())) {
      write("You must be a wizard to do that.\n");
      return;
   }

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
