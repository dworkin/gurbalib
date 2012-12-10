void usage() {
   string *lines;

   lines = ({ "Usage: update [-h] FILE" });
   lines += ({ " " });
   lines += ({ "Recompile the file, FILE." });
   lines += ({ " " });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tupdate /domains/required/rooms/start.c" });
   lines += ({ "\tupdate start.c" });
   lines += ({ "See also:" });

   if (query_admin(this_player())) {
      lines += ({ "\tcheck, clean, clone, dest, eval, graph, rebuild, " +
         "warmboot" });
   } else {
      lines += ({ "\tcheck, clean, clone, dest, eval, graph, rebuild, "
          });
   }

   this_player()->more(lines);
}

object compiler_d;

void create() {
   compiler_d = find_object(COMPILER_D);
}

/*
 * This function is atomic so that the destruct_object() gets
 * undone if the following compile_object() fails.
 */
static int recompile_library(string str) {
   return compile_library(str);
}

static object recompile_object(string str) {
   object ob;

   ob = find_object(str);

   /*
    * object isn't loaded yet, compile it
    * and make sure the create() function is
    * called.
    */
   if (!ob) {
      ob = compile_object(str);

      /*
       * if this fails, we destruct the object so
       * we aren't left with half constructed objects.
       */
      if (catch(call_other(ob, "???"))) {
	 destruct_object(ob);
	 rethrow();
      }
   } else {
      /*
       * object is loaded, simply recompile it and let the
       * driver object handle the rest.
       */
      ob = compile_object(str);
   }
   return ob;
}

void main(string str) {
   string path;
   object *objs;
   object *players;
   object ob;
   int i;

   if (!str || str == "") {
      str = this_player()->query_env("cwf");
   }

   if (!str || str == "") {
      usage();
      return;
   }

   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   path = this_player()->query_env("cwd");

   if (strlen(str) > 2) {
      if (str[strlen(str) - 2] == '.' && str[strlen(str) - 1] == 'c')
	 str = str[..strlen(str) - 3];
   }

   path = normalize_path(str, path);
   if (!path || path == "") {
      write("Access denied.\n");
      return;
   }

   if (str == "here") {
      str = this_environment()->base_name();

      /* Check for errors before moving people out of the room */

      this_player()->write(str + "\n");

      objs = this_environment()->query_inventory();
      players = ( { } );
      for (i = 0; i < sizeof(objs); i++) {
	 if (objs[i]->is_player()) {
	    players += ( {
	       objs[i]}
	    );
	 } else {
	    objs[i]->destruct();
	 }
      }

      for (i = 0; i < sizeof(players); i++) {
	 players[i]->move(VOID);
      }

      ob = compile_object(str);

      /* And move into the new room */

      for (i = 0; i < sizeof(players); i++) {
	 players[i]->move(str);
      }
      this_player()->do_look(0);
   } else if (file_exists(path + ".c")) {
      this_player()->set_env("cwf", path);
      if (compiler_d->test_inheritable(path)) {
	 if (recompile_library(path)) {
	    write("Compilation successful.\n");
	 } else {
	    write("Something went wrong.\n");
	 }
      } else if (compiler_d->test_object(path)) {
	 catch { ob = recompile_object(path); } : {
	    switch (caught_error()) {
	       case "Cannot recompile inherited object":
		  write(path + " is inherited, trying to destruct/compile.");
		  if (!recompile_library(path)) {
		     write("Something went wrong. ");
		  } else {
		     write("Compilation successful.\n");
		  }
		  return;
		  break;
	       default:
		  rethrow();
		  break;
	    }
	 }
      } else {
	 write("Cannot compile " + path +
	    ", it is neither object or inheritable (see 'man objects')");
	 return;
      }

      if (ob) {
	 write("Compilation successful.\n");
      }
   } else {
      write("File not found.\n");
   }
}
