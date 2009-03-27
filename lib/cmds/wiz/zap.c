/* kill something ensuring a corpse is left behind
     -- Arron Cusimano (mordain) 20090326 */
void main( string str ) {
  object target;
  object *obs;
  int i, sz;

  if ( !str || str == "" ) {
    write("zap someone?");
    return;
  }

  obs = this_environment()->query_inventory();
  for ( i = 0, sz = sizeof(obs); i < sz && !target; ++i ) {
    if (obs[i]->query_name() == str)
      target = obs[i];
  }

  if (!target) {
    write("Cant find " + str + "\n");
    return;
  }

  /* receive_damage()  from combat.c, this looks ugly on this_player()'s side, but looks good on the targets side */
  target->receive_damage( this_player(), target->query_max_hp(), 0 );
}
