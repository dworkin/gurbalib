inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: unlock [-h] OBJECT" });
   lines += ({ "" });
   lines += ({ "Unlock the specified object. You need the appropriate key." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tunlock door" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "close");
   add_also("player", "lock");
   add_also("player", "open");
}

static void main(string str) {
   object obj;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str) || sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   obj = this_player()->present(str);
   if (!obj) {
      obj = this_player()->query_environment()->present(str);
      if (!obj) {
         write("Unlock what?");
         return;
      }
   }

   if (!obj->do_unlock(this_player())) {
      write("Unlock what?");
   }
}
