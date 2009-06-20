int query_wizard(mixed player) {

  if(objectp(player)) {
    argcheck( player<-"/sys/lib/player", 1, "player object or string" );
    player = player->query_name();
  } else {
    argcheck( stringp(player), 1, "player object or string" );
  }

  return SECURE_D->query_wiz( player ) ;
}
