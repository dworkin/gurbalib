inherit "/std/container";

static string orig_name;

void setup(void) { }

void create(void) {
   ::create();

   if (clone_num() != 0) {
      call_out("decompose", 30);
   }

   set_id("corpse");
   set_short("A foul smelling corpse");
   set_long("It looks just as awful as it smells.");
}

void set_name(string name) {
   orig_name = name;
   set_short("The corpse of " + name);
}

void corpse_destruct(void) {
   int i, dim;
   object *inv;

   inv = query_inventory();
   for (i = 0, dim = sizeof(inv); i < dim; i++) {
      inv[i]->move(query_environment());
   }
   query_environment()->tell_room(nil, "Ash to ash, dust to dust.");
   destruct();
}

void decompose(void) {
   call_out("corpse_destruct", 30);
   if (!orig_name) {
      orig_name = "noone";
   }

   set_short("The somewhat decayed corpse of " + orig_name);
   query_environment()->tell_room(nil, "The corpse of " +
      orig_name + " decomposes a bit.");
}
