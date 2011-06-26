void usage() {
  write("Usage: wear [-h] ITEM\n");
  write("Puts on an item.  If you have armor its generally a good idea to " +
    "put it on.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string str ) {
  object obj;
  object worn;

  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  obj = this_player()->present( lowercase( str ) );
  if( !obj ) {
    write( "Maybe you should get one first?" );
    return;
  }
  if( !obj->is_wearable() ) {
    write( "You can't wear that." );
    return;
  }

  worn = this_player()->query_slot( obj->query_slot() );
  if( worn ) {
    write("You're already wearing a " + worn->query_id() + "." );
    return;
  }
  
  this_player()->do_wear( obj );
  this_player()->targetted_action( obj->query_wear_message(), nil, obj );
}
