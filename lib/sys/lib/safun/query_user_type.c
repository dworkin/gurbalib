nomask static int query_user_type(mixed player) {

   if (objectp(player)) {
      if (!player <-PLAYER_OB && !player <-USER_OB) {
         return 0;
      }
      player = player->query_name();
   } else {
      argcheck(stringp(player), 1, "player object or string");
   }

   return USER_D->query_type(player);
}
