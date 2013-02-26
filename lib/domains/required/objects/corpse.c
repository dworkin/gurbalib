inherit CONTAINER;

static string orig_name;

void create(void) {
   ::create();
   if (clone_num() != 0)
      call_out("decompose", 30);
   set_id("corpse");
   set_short("A foul smelling corpse");
   set_long("It looks just as awful as it smells.");
}

void set_name(string name) {
   orig_name = name;
   set_short("The corpse of " + name);
}

void decompose(void) {
   call_out("destruct", 30);
   if (!orig_name)
      orig_name = "noone";

   set_short("The somewhat decayed corpse of " + orig_name);
}
