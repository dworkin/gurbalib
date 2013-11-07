inherit "/std/object";

int fuel, lit;

int set_fuel(int x) {
   fuel = x;
}

int query_fuel() {
   if (fuel < 0) {
      return 0;
   }
   return fuel;
}

int query_lit() {
   return lit;
}

int light() {
   lit = 1;
   EVENT_D->subscribe_event("burn_fuel");
   write("You light the " + this_object()->query_name() + "\n");
   this_player()->query_environment()->tell_room(this_player(), 
      this_player()->query_Name() + " lights the " + 
      this_object()->query_name() + "\n");
   return 1;
}

int extinguish() {
   EVENT_D->unsubscribe_event("burn_fuel");
   lit = 0;
   write("You extinguish the " + this_object()->query_name() + "\n");
   this_player()->query_environment()->tell_room(this_player(), 
      this_player()->query_Name() + " extinguishes the " + 
      this_object()->query_name() + "\n");
   return 1;
}

void create() {
   ::create();
   fuel = 1000;

   add_object_command("light", "do_light");
   add_object_command("extinguish", "do_extinguish");
}

int event_burn_fuel() {
   object room;
   fuel = fuel -1;
   if (fuel < 1) {
      room = this_object()->query_environment();
      if (room->is_living()) {
         room = room->query_environment();
      }
      room->tell_room(this_object(),"The light goes out.\n");
      this_object()->extinguish();
   }
}

