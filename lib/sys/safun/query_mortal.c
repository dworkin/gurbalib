int query_mortal(object player) {

  return !catch( player = (object "/std/player") player ) && 
    SECURE_D->query_mortal( player->query_name() ) ;
}
