inherit OBJECT;

void setup(void) {
   set_id("firebreather");
   set_long("This is an assume drink.");
   set_in_room_desc("A firebreather");
   set_eatable(1);
   set_gettable(1);
   set_value(2);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = random(2) + 1;
   write("A shockwave runs through your body.");
   this_player()->increase_hp(x);
   this_object()->destruct();
}
