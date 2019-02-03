inherit "/std/object";

nomask int is_inert(void) {
   return 1;
}

void setup(void) {
   set_id("automaton");
   set_short("An inert automaton");
   set_long("This automaton is incomplete. It has many " +
      "pieces from many sources stitched together, but " +
      "it's missing something. It's not clear from mere " +
      "inspection what, however.");
   set_gettable(0);
}
