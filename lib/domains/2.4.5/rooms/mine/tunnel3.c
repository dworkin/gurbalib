#define DIR "/domains/2.4.5/rooms"
inherit ROOM;
int tied_rope;  // Flag to note if the rope is here and tied or not..

void setup(void) {
   add_area("2.4.5");

   set_brief("Hole");
   set_long("There is a giant hole in the ground here, " +
      "and a large iron ring attached to the wall.");

   add_exit("north",DIR + "/tunnel4.c");
   add_exit("south",DIR + "/tunnel2.c");

   add_room_command("tie","do_tie");
   add_room_command("untie","do_untie");
   add_room_command("climb","do_climb");
   add_item("ring","A large iron ring hooked to the wall. " +
      "You could probably tie a rope to it.");
   add_item("hole","The hole looks very deep an looks unsafe.");
}

int do_tie(string str) {
   object obj;

   if (str == "ring" || str == "rope") {
      obj = this_player()->present("rope");
      if (obj) {
         if (tied_rope) {
            write("You make sure the rope is securely tied to the ring.\n");
            this_player()->query_environment()->tell_room(this_player(),
               this_player()->query_Name() + 
               " makes sure the rope is secure.\n");
         } else {
            if (obj->move(this_player()->query_environment())) {
               obj->set_gettable(0);
               obj->set_in_room_description("An old rope tied to the ring");
               write("You tie the rope to the ring.\n");
               this_player()->query_environment()->tell_room(this_player(),
                  this_player()->query_Name() + 
                  " ties a rope to the ring.\n");
               tied_rope = 1;
            }
         }
      } else {
         write("You do not have a rope to tie to the ring.\n");
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
            obj->set_in_room_description("An old rope");
            if (obj->move(this_player())) {
               write("You untie the rope from the ring, and pick it up.\n");
               this_player()->query_environment()->tell_room(this_player(),
                  this_player()->query_Name() + 
                  " unties the rope.\n");
               tied_rope = 0;
            }
         } else {
            write("There is no rope tied to the ring.\n");
            this_player()->query_environment()->tell_room(this_player(),
               this_player()->query_Name() + 
               " looks longingly at the ring.\n");
         }
      } else {
         write("There is nothing tied to the ring.\n");
      }
      return 1;
   }
   return 0;
}

int do_climb(string str) {
   if ((str == "down") || (str == "rope")) {
      if (tied_rope) {
         this_player()->move(DIR + "/mine/tunnel8.c");
         write("You climb down the rope.\n");
         this_player()->query_environment()->tell_room(this_player(),
            this_player()->query_Name() + " climbs down the rope.\n");
         this_player()->do_look(0);
      } else {
         write("You would fall down the hole and possibly hurt yourself.\n");
         this_player()->query_environment()->tell_room(this_player(),
            this_player()->query_Name() + 
            " attempts to go down the hole and fails.\n");
      }
      return 1;
   } 
   return 0;
}

int query_tied() {
   return tied_rope;
}
