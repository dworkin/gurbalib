int query_admin(object player) {

  return !catch( player = (object "/std/player") player ) && 
    SECURE_D->query_admin( player->query_name() ) ;
}
