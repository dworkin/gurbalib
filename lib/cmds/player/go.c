inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: go [-h] DIRECTION" });
   lines += ({ "" });
   lines += ({ "Allows you to move in the specified direction.  To see " +
      "where you" });
   lines += ({ "can go, \"look\" around." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tgo north" });
   lines += ({ "See also:" });
   lines += ({ "\tattack, cast, eat, enter, follow, pray, query, quit, wimpy"
      });

   return lines;
}

static void main(string str) {
   string error, str2;
   int len;

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }
   if (sscanf(str, "-%s", str) || sscanf(str, "%s -%s", str, str2)) {
      this_player()->more(usage());
      return;
   }

   len = strlen(str);
   if (str[len - 1] == ' ') {
      str = str[..len - 2];
   }

   error = this_environment()->body_exit(this_player(), str);

   if (error) {
      write(error);
   }
}
