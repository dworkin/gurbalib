inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: enter [-h] OBJECT" });
   lines += ({ "" });
   lines += ({ "Allows you to enter the specified object.  To see what you" });
   lines += ({ "can enter, \"look\" around." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tenter hole" });
   lines += ({ "See also:" });
   lines += ({ "\tattack, cast, eat, follow, go, pray, quit" });

   this_player()->more(lines);
}

static void main(string str) {
   string error;

   if (empty_str(str)) {
      usage();
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   error = this_environment()->body_exit(this_player(), str);

   if (error)
      write(error);
}
