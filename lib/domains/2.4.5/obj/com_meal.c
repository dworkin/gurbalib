inherit OBJECT;

void setup(void) {
   set_id("meal");
   set_adj("commonor's");
   set_long("A small bowl of something on a piece of stale bread. " +
      "it smells awful.");
   set_short("Commonor's meal");
   set_eatable(1);
   set_gettable(1);
   set_value(20);
   set_weight(2);
}

int do_eat(void) {
   int x;

   x = random(5) + 1;
   write("You eat the common meal.  It's tollerable if you plug your nose.");
   this_player()->query_environment()->tell_room(this_player(),
      this_player()->query_Name() + 
      " eats something that looks about 2 days to old to eat.\n");
   this_player()->increase_hp(x);
   this_object()->destruct();
}
