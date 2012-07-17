inherit OBJECT;

void setup(void) {
   set_id("singularity");
   set_adj("small");
   set_in_room_description("A singularity");
   set_long("This is a signularity.  It is created when another object fails to load.  If you see this, let a wizard know where it is so they can fix it.");
   set_gettable(1);
   set_value(1);
}

// XXX Fix mudlib so it uses this when it can't load an object to help track down bugs...
