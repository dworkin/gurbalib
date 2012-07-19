inherit OBJECT;

void setup(void) {
   set_id("beer");
   set_adj("classy");
   set_long("A bottle of beer.");
   set_in_room_desc("A First Class Beer");
   set_eatable(1);
   set_gettable(1);
   set_value(12);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = random(5) + 1;
   write("That feels good.");
   this_player()->increase_hp(x);
   this_object()->destruct();
}
