inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: where [-h] [player]" });
   lines += ({ " " });
   lines += ({ "Locates the given [player] and prints out their location." });
   lines += ({ "If [player] is omitted it prints out everyones location." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\twhere" });
   lines += ({ "\twhere sirdude" });
   lines += ({ "See also:" });
   lines += ({ "\tlast, locate, look, mudlist, possess, rwho, snoop, who" });

   return lines;
}

static void main(string str) {
   int i, sz;
   object usr, *usrs;

   if (empty_str(str)) {
      usrs = USER_D->query_players();

      sz = sizeof(usrs);
      for (i = 0; i < sz; i++) {
	 write(usrs[i]->query_Name() + " Loc: (" + 
            usrs[i]->query_environment()->query_short() + ") " +
	    usrs[i]->query_environment()->base_name() + "\n");
      }
   } else {
      if (sscanf(str, "-%s", str)) {
         this_player()->more(usage());
      } else if (usr = USER_D->find_player(str)) {
	 write(usr->query_Name() + " Loc: (" +
	    usr->query_environment()->query_short() + ") " +
	    usr->query_environment()->base_name() + "\n");
      } else {
	 write("Who are you looking for?  I can't find: " + str + "!\n");
      }
   }
}
