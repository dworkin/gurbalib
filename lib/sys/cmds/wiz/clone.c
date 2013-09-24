inherit M_COMMAND;

void usage() {
   string *lines;

   lines = ({ "Usage: clone [-h] FILENAME [WHO]" });
   lines += ({ " " });
   lines += ({ "Bring a copy of the object FILENAME into existence." });
   lines += ({ "If who is specified give it to WHO or move it to their " +
      "location." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "See also:" });

   if (query_admin(this_player())) {
      lines += ({ "\tcheck, checkmud, clean, dest, eval, graph, rebuild, " +
         "update, warmboot" });
   } else {
      lines += ({ "\tcheck, clean, dest, eval, graph, rebuild, " +
         "update" });
   }

   this_player()->more(lines);
}

string get_what(string str) {
   string path;

   path = this_player()->query_env("cwd");

   if (strlen(str) > 2) {
      if ((str[strlen(str) - 2] == '.') && (str[strlen(str) - 1] == 'c')) {
	 /* were good do nothing... */
      } else {
	 str = str + ".c";
      }
   }

   path = normalize_path(str, path);

   return path;
}

static void main(string str) {
   string who, what, id;
   object ob, player;

   if (!str || (str == "")) {
      str = this_player()->query_env("cwf");
      if (!str) {
	 usage();
	 return;
      }
   } else if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (sscanf(str, "%s %s", what, who)) {
      player = USER_D->find_player(who);
      what = get_what(what);
   } else {
      what = get_what(str);
   }

   if (!what || (what == "")) {
      write("Access denied or file does not exist.\n");
      return;
   }

   if (file_exists(what)) {
      ob = clone_object(what);
      this_player()->set_env("cwf", what);
      if (ob) {

	 ob->setup();
	 this_player()->simple_action("$N $vclap $p hands.\n");
         id = ob->query_id();

	 if (player) {
            if (id) {
	       write("You clone: " + article(id) + " " +
	          id + " and send it to " + player->query_Name() + "\n");
               if (player->query_environment() != this_environment()) {
	          player->query_environment()->tell_room(player,
                     article(id) + " " + id + " appears out of thin air.\n");
	       } else {
                  this_player()->query_environment()->tell_room(player,
                     article(id) + " " + id + " appears out of thin air.\n");
	       }
            } else {
               write("Error that object is missing an id: " + 
                  ob->file_name() + "\n");
            }

	    if (ob->is_gettable()) {
	       ob->move(player);
	    } else {
	       ob->move(player->query_environment());
	    }
	 } else {
            if (id) {
	    write("You clone: " + article(id) + " " + id + "\n");
	    this_player()->query_environment()->tell_room(this_player(),
	       capitalize(article(id)) + " " + id +
	       " appears out of thin air.\n");
            } else {
               write("Error that object is missing an id: " + 
                  ob->file_name() + "\n");
            }
	    if (ob->is_gettable()) {
	       ob->move(this_player());
	    } else {
	       ob->move(this_environment());
	    }
	 }

      } else {
	 write("Unable to clone object : " + what + "\n");
      }
   } else {
      write("File not found.\n");
   }
}
