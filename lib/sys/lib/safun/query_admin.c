nomask int query_admin(mixed player) {
   int p;

   if (objectp(player)) {
      if (!player <-PLAYER_OB && !player <-USER_OB) {
         return 0;
      }
      player = player->query_name();
   } else {
      argcheck(stringp(player), 1, "player object or string");
   }

   p = query_user_type(player);
   return (p == ADMIN_L);
}
