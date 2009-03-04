inherit M_GUILD_MASTER;

void setup( void ) {
  set_guild( "fighter" );
  set_name( "bob" );
  set_proper_name( "Bob" );
  set_gender( 1 );
  add_id( "master", "guildmaster" );
  set_in_room_desc( "Bob, the Guildmaster" );
  set_long( "A sturdy fighter, if you ever saw one." );
  set_race( "human" );
  add_block( "north" );
  set_actions( 60, ({
    "say Want to be a fighter?",
      "say All you have to do is say 'join'.",
      "say Say 'join' to become a fighter.",
      "smile",
      })
	       );
  add_pattern( "%s says: Join", "call join_guild $1" );
  add_pattern( "%s says: Leave", "call leave_guild $1" );
  add_pattern( "%s smiles.", "smile $1" );
}

int can_join( object player ) {
  return( 1 );
}

void do_join( object player ) {
  this_player()->respond( "say Welcome to the Fighter Guild, " + player->query_name() );
  this_player()->respond( "smile" );
  this_player()->respond( "bow " + player->query_name() );
}

void do_reject( object player ) {
  this_player()->respond( "say Sorry, you're too puny to join." );
}

int can_leave( object player ) {
  return( 1 );
}

void do_leave( object player ) {
  this_player()->respond( "say Sorry to see you go." );
  this_player()->respond( "sigh" );
  this_player()->respond( "say A great loss for this guild." );
}

void do_keep( object player ) {
  this_player()->respond( "say You're too valuable an asset to this guild, so I can't let you go." );
}
