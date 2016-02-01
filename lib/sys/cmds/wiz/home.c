inherit M_COMMAND;

string *usage(void) {
   string workroom, *lines;

   workroom = WIZ_DIR + "/" + this_player()->query_name() + 
      "/rooms/workroom.c";

   lines = ({ "Usage: home [-h]" });
   lines += ({ " " });
   lines += ({ "Transport you to your \"workroom\": " + workroom });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\thome" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("wiz", "goto");
   add_also("wiz", "summon");
   add_also("wiz", "where");
}

string get_workroom(void) {
   string badname, filename;

   filename = WIZ_DIR + "/" + this_player()->query_name() + "/rooms/workroom";

   if (!file_exists(filename + ".c")) {
      badname = WIZ_DIR + "/" + this_player()->query_name() + "/workroom";
      if (file_exists(badname + ".c")) {
         write("Please move your workroom to " + filename + ".c");
         return badname;
      } else {
         write("You need to create your workroom: " + filename + ".c");
      }
   }
   return filename;
}

static void main(string str) {
   object env, ob;
   string filename;

   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   filename = get_workroom();

   if (!file_exists(filename + ".c")) {
      return;
   }

   env = this_player()->query_environment();

   if (!(ob = find_object(filename))) {
      catch {
         ob = compile_object(filename);
         ob->setup();
         ob->setup_mudlib();
      } : {
         write("Could not load " + filename);
      }
   }

   if (ob == env) {
      write("You are already there.\n");
      return;
   } else {
      this_player()->simple_action("$N $vgo home.");
   }

   env->tell_room(this_player(),
      this_player()->query_Name() + " disappears.\n");
   if (!ob || !this_player()->move(ob)) {
      write("\nConstruction blocks your path.\n");
      env->tell_room(this_player(),
         this_player()->query_Name() + " looks confused.\n");
   } else {
      this_player()->do_look(this_environment());
   }
}
