inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: show [-h] [all|OBJ] [to] PLAYER" });
   lines += ({ "" });
   lines += ({ "Allows you to show OBJ to PLAYER." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tshow sword to sirdude" });
   lines += ({ "\tshow sword sirdude" });
   lines += ({ "See also:" });
   lines += ({ "\tget, give, drop" });

   this_player()->more(lines);
}

static void display_object(object who, object what) {
   object *objs;
   int x, maxx;

   if (this_environment()->query_dark()) {
      write("It is too dark to see.\n");
      return;
   }

   this_environment()->event("body_look_at", who, what);
   
   who->message(what->query_long());
   if (what->is_closed()) {
      who->message("It is closed.");
   } else if (what->is_container()) {
      objs = what->query_inventory();
      who->message(" \nIt contains:\n");

      maxx = sizeof(objs);
      for (x = 0; x < maxx; x++) {
         who->message("  " + objs[x]->query_short() + "\n");
      }
   }
}

/* XXX This should be redone higher up... */
string get_name(object obj) {
   string name;

   name = obj->query_Name();

   if (!name || name == "") {
      name = obj->query_id();
   }

   return name;
}

static void do_show(object obj1, object obj2, int loud) {
   string name, name2;

   if (!obj1) {
      if (loud) {
         write("What are you trying to put where?");
      }
      return;
   }

   if (!obj2) {
      if (loud) {
         write("Where are you trying to put that?\n");
      }
      return;
   }

   if (!obj2->is_living()) {
      if (loud) {
         write("You can only give things to the living.\n");
      }
      return;
   }

   if (obj2 == this_player()) {
      if (loud) {
         write("You may not give things to yourself.\n");
      }
      return;
   }

   name = get_name(obj1);
   name2 = get_name(obj2);

   write("You show " + name + " to " + name2 + "\n");
   this_player()->query_environement()->tell_room(this_player(), 
      this_player()->query_Name() + " shows " + name + " to " + 
      name2 + "\n");

   display_object(obj2, obj1);
}

static void main(string str) {
   object obj, obj2;
   object *inv;
   int i, max, amount;
   string what, where, coin;

   if (empty_str(str)) {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (this_player()->is_dead()) {
      write("You can not do that when your are not among the living.\n");
      return;
   }

   if (sscanf(str, "%s to %s",what,where) == 2) {
   } else if (sscanf(str, "%s %s",what,where) == 2) {
   } else {
      write("You want to give what to who?");
      return;
   }

   obj = this_environment()->present(where);
   if (!obj) {
      write("Who are you trying to show that to?");
      return;
   }

   obj2 = this_player()->present(lowercase(what));
   if (!obj2) {
      obj2 = this_player()->query_environment()->present(lowercase(what));
   }
   do_show(obj2, obj, 1);
}
