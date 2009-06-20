int query_wizard(mixed player) {

  if(objectp(player)) {
    if( !player<-"/sys/lib/player" ) {
      return 0;
    }
    player = player->query_name();
  } else {
    argcheck( stringp(player), 1, "player object or string" );
  }

  return SECURE_D->query_wiz( player ) ;
}
