void usage() {
  write("Usage: passwd [-h]\n");
  write("Allows you to change your password.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void main( string arg ) {
  string oldpass,curpass, newpass;

  if (arg && arg != "" ) {
     usage();
     return;
  }

  oldpass = this_player()->query_passwd();
  send_message( "\nPlease enter your password : " );
  send_message( 0 );

   /// XXX get curpass

   if (oldpass == curpass) {
	// get newpass;
	// this_player()->set_passwd(newpass);
   } else {
	write("That is not your old password.\n");
   }
}
