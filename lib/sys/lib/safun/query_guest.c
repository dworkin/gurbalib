nomask int query_guest(mixed player) {
   int p;

   if (objectp(player)) {
      if (!player <-PLAYER_OB && !player <-USER_OB) {
         return 0;
      }
      player = player->query_name();
   } else {
      argcheck(stringp(player), 1, "player object or string");
   }

   /* If player name starts with guest return 1 */
   if (strstr(player, "guest") == 0) { 
     return 1;
   }

   return 0;
}
