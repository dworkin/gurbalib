void usage() {
   write("Usage: follow [-h] [WHO]\n");
   write("Allows you to follow/unfollow another player.\n");
   write("If you give no aguments, it will print who you are following.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

/* XXX need to still put backend of this in..... */

void main(string str) {
   string name;
   object obj;

   name = this_player()->query_follow();
   if (!str || str == "") {
      if (name && name != "") {
         write("You are currently following: " + name + "\n");
      } else {
         write("You are currently not following anyone.\n");
      }
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   /* Stop following whoever we are following */
   if (str == name) {
      this_player()->set_follow("");
      write("You stop following " + str + ".\n");
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " stops following " + 
         capitalize(str) + ".\n");
      obj = find_object(name);
      obj->remove_follower(this_player());
      return;
   }

   /* Actually follow someone */
   obj = this_environment()->present(str);
   if (obj) {
      this_player()->set_follow(str);

      write("You start following " + str + ".\n");
      this_environment()->tell_room(this_player(), 
         this_player()->query_Name() + " starts following " + 
         capitalize(str) + ".\n");
       obj->add_follower(this_player());
   } else {
      write("You can not find: " + str + ".\n");
   }
}
