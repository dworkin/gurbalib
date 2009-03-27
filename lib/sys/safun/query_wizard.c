int is_wizard(object player) {

  return !catch( player = (object "/std/player") player ) && 
    SECURE_D->query_wiz( player->query_name() ) ;
}
