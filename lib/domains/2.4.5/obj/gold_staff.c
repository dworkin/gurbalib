inherit OBJECT;

void setup(void) {
   set_id("staff");
   set_adj("large");
   set_long("A Large golden staff.  You better not use it, it looks valuable.");
   set_in_room_desc("A golden staff");
   set_gettable(1);

   set_value(300);
   // XXX set_weight(10);
}

// XXX Make it so you can break it if you try to wield it?
