inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: follow [-h] [WHO]" });
   lines += ({ "" });
   lines += ({ "Allows you to follow/unfollow another player." });
   lines += ({ "If you give no arguments, it will print who you are following." 
      });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tfollow sirdude" });
   lines += ({ "\tfollow" });
   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "attack");
   add_also("player", "cast");
   add_also("player", "eat");
   add_also("player", "enter");
   add_also("player", "go");
   add_also("player", "pray");
   add_also("player", "query");
   add_also("player", "quit");
   add_also("player", "wimpy");
}

/* XXX need to still put backend of this in..... */

static void main(string str) {
   string name;
   object obj;

   if (!alsos) {
      setup_alsos();
   }

   name = this_player()->query_follower();
   if (empty_str(str)) {
      if (name && (name != "")) {
         write("You are currently following: " + name + "\n");
      } else {
         write("You are currently not following anyone.\n");
      }
      return;
   }

   if (str == this_player()->query_name()) {
      write("You can not follow yourself.\n");
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   /* Stop following whoever we are following */
   if (str == name) {
      this_player()->set_follower("");
      write("You stop following " + str + ".\n");
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " stops following " + 
         capitalize(str) + ".\n");
      obj = USER_D->find_player(name);

      obj->remove_follower(this_player());
      return;
   }

   /* Actually follow someone */
   obj = this_environment()->present(str);
   if (obj) {
      this_player()->set_follower(str);

      write("You start following " + str + ".\n");
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " starts following " + 
         capitalize(str) + ".\n");
       obj->add_follower(this_player());
   } else {
      write("You can not find: " + str + ".\n");
   }
}
