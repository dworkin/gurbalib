void usage() {
   string *lines;

   lines = ({ "Usage: attack [-h] [OBJECT]" });
   lines += ({ "" });
   lines += ({ "OBJ offends you, you are going to destroy it." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tattack rat" });
   lines += ({ "See also:" });
   lines += ({ "\tcast, eat, enter, follow, go, pray, quit" });

   this_player()->more(lines);
}

void main(string str) {
   object obj;

   if (!str && (str != "")) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   obj = this_player()->query_environment()->present(lowercase(str));
   if (!obj) {
      write("Attack what?\n");
      return;
   }

   if (!obj->is_living()) {
      write(" You can not attack that.\n");
      return;
   }

   this_player()->targetted_action("$N $vattack $t.", obj);
   this_player()->attack(obj);
}
