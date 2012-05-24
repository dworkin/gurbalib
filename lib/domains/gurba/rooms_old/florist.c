inherit ROOM;

void setup(void) {
   set_brief("Fridas Floristeria");
   set_long("This small hut is the flower shop. Flowers bulge out from " +
      "everywhere. Flowerpots of all colors house the dozens of different " +
      "flowers at sale here. Partly hidden behind a large specimen of " +
      "Tussilago Farfara, Frida is making another one of her beutiful " +
      "flower arrangements. When you enter she smiles invitingly at you. ");
   set_exits(([
      "north" : "/domains/gurba/rooms/market1",
   ]));

   add_item("flowers", "She has a lot of them, in all the colors of the " +
      "rainbow. When you study them you also smell the delightful variety " +
      "of scents they have.");
   add_item("flowerpots", "pots", "pot", "flowerpot", "All differnet size, " +
      "shape and color. Mostly made out of clay or wood.");

   set_objects(([
      "/domains/gurba/monsters/frida" : 1, 
      "/domains/gurba/objects/florist_sign" : 1,
   ]));
}

void do_listen(object player) {
   write("You're not sure but the way she makes these flowers thrive, " +
      "you could have sweared you heard them whisper, gently.");
}
