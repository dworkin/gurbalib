/* Wealth.c, created by Fudge - Mon Feb 23 14:15:30 1998 */

void main( string str ) {

  int i;

  int ducats;
  int royals;
  int crowns;

  mixed *money;
  money = this_player()->query_all_coins();

  if( sizeof( money ) == 0 ) {
    this_player()->write( "You are broke." );
    return;
  }

  for( i = 0; i < sizeof( money ); i++ ) {
    switch( money[i][0] ) {
    case "ducat" : ducats = money[i][1];
      break;
    case "royal" : royals = money[i][1];
      break;
    case "crown" : crowns = money[i][1];
      break;
    default:
      break;
    }
  }

  write( "Ducats: " + ducats ); 
  write( "Royals: " + royals ); 
  write( "Crowns: " + crowns ); 
}

