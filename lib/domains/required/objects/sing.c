inherit "/std/object";

void setup(void) {
   set_id("singularity");
   set_adj("small");
   set_short("A singularity");
   set_long("This is a signularity.  It is created when another object " +
      "fails to load.  If you see this, let a wizard know where it is so " +
      "they can fix it.");
   set_gettable(1);
   set_weight(1);
   set_value(50);
}

