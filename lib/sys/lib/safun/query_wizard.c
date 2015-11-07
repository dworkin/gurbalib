nomask int query_wizard(mixed player) {
   int p;

   if (objectp(player)) {
      if (!player <-"/sys/obj/player") {
         return 0;
      }
      player = player->query_name();
   } else {
      argcheck(stringp(player), 1, "player object or string");
   }

   p = query_user_type(player);
   return (p == ADMIN_L || p == WIZ_L);
}
