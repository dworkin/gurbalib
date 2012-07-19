inherit OBJECT;

void setup(void) {
   set_id("special");
   set_long("The house special, its a fine drink.");
   set_in_room_desc("Special of the house");
   set_eatable(1);
   set_gettable(1);
   set_value(20);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = 10;
   write("A tingling feeling goes through your body.");
   this_player()->increase_hp(x);
   this_object()->destruct();
}
