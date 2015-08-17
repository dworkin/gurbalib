void say(string str, varargs object obj) {
   int i;
   object room, player;
   object *listeners;

   argcheck(str, 1, "string");

   if (!this_player() ) {
      return;
   }

   if (obj) {
      player = obj;
      }
   else {
      player = this_player();
   }

   listeners = this_environment()->query_inventory();
   for (i = 0; i < sizeof(listeners); i++) {
      if (listeners[i]->is_living() && listeners[i] != player) {
         listeners[i]->message(str);
      }
   }
}
