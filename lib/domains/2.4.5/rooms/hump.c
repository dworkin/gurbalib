inherit ROOM;

void setup(void) {
   object ob;
   string name;
   add_area("2.4.5");

   set_brief("Humpbacked bridge");
   set_long("An old humpbacked bridge.");

   add_exit("east","/domains/2.4.5/rooms/vill_green.c");
   add_exit("west","/domains/2.4.5/rooms/wild1.c");

   set_objects (([
      "/domains/2.4.5/obj/torch.c": 1,
   ]));

   name = "/std/money.c";
   if (!this_environment()->present(name)) {
      ob = clone_object(name);
      ob->set_amount(10);
      ob->move(object_name(this_object()));
      ob->setup();
   }
}

// XXX Need to add money and put it on the ground...
