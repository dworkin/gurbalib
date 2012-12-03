void usage() {
   string *lines;

   lines = ({ "Usage: eat [-h] [OBJECT]" });
   lines += ({ "Consume the specified object." });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\teat apple" });
   lines += ({ "See also: attack, cast, enter, follow, go, pray" });


   this_player()->more(lines);
}

void main(string str) {
   object obj;

   if (!str && str != "") {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   obj = this_player()->present(lowercase(str));
   if (!obj) {
      write("Consume what?\n");
      return;
   }

   if (!obj->is_eatable()) {
      write(" You can not consume that.\n");
      return;
   }

   call_other(obj, "do_eat");
}
