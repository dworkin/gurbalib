int query_mortal(mixed player) {

   if (objectp(player)) {
      if (!player <-"/sys/obj/player") {
	 return 0;
      }
      player = player->query_name();
   } else {
      argcheck(stringp(player), 1, "player object or string");
   }

   return USER_D->query_mortal(player);
}
