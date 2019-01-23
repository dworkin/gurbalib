int tied_rope;  /* Flag to note if the rope is here and tied or not. */
string *rooms_to_notify;

void set_rooms_to_notify(string * str) {
   rooms_to_notify = str;
}

string *query_rooms_to_notify() {
   return rooms_to_notify;
}

int is_rope(string str) {
   return call_other(str, "query_tied");
}

string query_extra_long(int can_go_up, int can_go_down) {
   string dir_up, dir_down, or_str, str;
   if (can_go_up) {
      dir_up = "up";
   } else {
      dir_up = "";
   }
   if (can_go_down) {
      dir_down = "down";
   } else {
      dir_down = "";
   }
   if (can_go_up && can_go_down) {
      or_str = " or ";
   } else {
      or_str = "";
   }

   str = dir_up + or_str + dir_down;
   return "There is a rope allowing you to climb " + str + " from here.";
}

void move_player(object player, object old_room, string direction, string room) {
   player->move(room);
   player->write("You climb " + direction + " the rope.");
   old_room->tell_room(player, player->query_Name() + " climbs " +
      direction + " the rope.\n");
   player->query_environment()->tell_room(player, player->query_Name() +
      " climbs " + direction + " the rope.\n");
   player->do_look(player->query_environment());
}

void notify_rooms(string str) {
   string *rooms;
   int i, dim;
   rooms = query_rooms_to_notify();
   for (i = 0, dim = sizeof(rooms); i < dim; i++) {
      call_other(rooms[i], "message_room", this_player(), str);
   }
}

int do_tie(string str) {
   object obj;

   if (str == "ring" || str == "rope") {
      if (tied_rope) {
         write("You make sure the rope is securely tied to the ring.\n");
         this_player()->query_environment()->tell_room(this_player(),
            this_player()->query_Name() +
            " makes sure the rope is secure.\n");
      } else {
         obj = this_player()->present("rope");
         if (obj) {
            if (obj->move(this_player()->query_environment())) {
               obj->set_gettable(0);
               obj->set_tied("ring");
               write("You tie the rope to the ring.\n");
               this_player()->query_environment()->tell_room(this_player(),
                  this_player()->query_Name() + " ties a rope to the ring.\n");
               notify_rooms("A rope drops out from the hole in " +
                  "the ceiling!\n");
               tied_rope = 1;
            }
         } else {
            write("You do not have a rope to tie to the ring.\n");
         }
      }
      return 1;
   }
   return 0;
}

int do_untie(string str) {
   object obj;

   if (str == "ring" || str == "rope") {
      obj = this_player()->query_environment()->present("rope");
      if (obj) {
         if (tied_rope) {
            obj->set_gettable(1);
            obj->set_tied("");
            if (obj->move(this_player())) {
               write("You untie the rope from the ring, and pick it up.\n");
               this_player()->query_environment()->tell_room(this_player(),
                  this_player()->query_Name() + " unties the rope.\n");
               notify_rooms("The rope disappears from the hole in " +
                  "the ceiling!\n");
               tied_rope = 0;
            }
         } else {
            write("The rope is not tied to anything.\n");
            this_player()->query_environment()->tell_room(this_player(),
               this_player()->query_Name() + " looks longingly at the ring.\n");
         }
      } else {
         write("There is nothing tied to the ring.\n");
      }
      return 1;
   }
   return 0;
}

int query_tied() {
   return tied_rope;
}
