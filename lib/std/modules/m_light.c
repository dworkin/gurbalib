int fuel, lit;

int set_fuel(int x) {
   fuel = x;
}

int query_fuel() {
   if fuel < 0)
      return 0;
   return fuel;
}

int query_lit() {
   return lit;
}

int light() {
   lit = 1;
   EVENT_D->subscribe_event("burn_fuel");
}

int extinguish() {
   EVENT_D->unsubscribe_event("burn_fuel");
   lit = 0;
}

void create() {
   fuel = 1000;
}

int event_burn_fuel() {
   object room;
   fuel = fuel -1;
   if (fuel < 1) {
      room = this_object()->query_environment();
      if (is_living(room)) {
         room = room->query_environment();
      }
      room->tell_room(this_object(),"The light goes out.\n");
      this_object()->extinguish();
   }
}
