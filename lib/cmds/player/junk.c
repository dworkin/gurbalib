inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: junk [-h] [all|OBJECT]" });
   lines += ({ "" });
   lines += ({ "The junk command allows you to clean up the mud.  "});
   lines += ({ "If you have any objects you no longer want you can instantly" +
      " vaporize them with the handy junk command." });
   lines += ({ "" });
   lines += ({ "If you want to junk your entire inventory use: junk all" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "" });
   lines += ({ "Examples:" });
   lines += ({ "\tjunk corpse" });
   lines += ({ "\tjunk sword" });
   lines += ({ "\tjunk all" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "hp");
   add_also("player", "inventory");
   add_also("player", "levels");
   add_also("player", "score");
   add_also("player", "skills");
   add_also("player", "top");

   add_also("wiz", "status");
}

void do_junk(object obj) {
   string objname;

   objname = obj->query_Name();
   if (!objname || objname == "") {
      objname = obj->query_id();
   }

   if (obj->is_living()) {
      write("You cannot junk " + objname + ".\n");
      return;
   }

   write("You junk " + objname + ".\n");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + " vaporizes " + objname + ".\n");
   destruct_object(obj);
}

static void main(string str) {
   object obj, *inv;
   int x, xmax;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (str == "all") {
      inv = this_player()->query_inventory();
      xmax = sizeof(inv);
      for (x = 0; x < xmax; x++) {
         do_junk(inv[x]);
      }
      return;
   }

   obj = this_environment()->present(str);

   if (!obj) {
      obj = this_player()->present(str);
   }

   if (!obj) {
      write("What are you trying to junk?");
      return;
   }

   do_junk(obj);
}
