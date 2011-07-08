string oldpass, curpass, newpass;

void usage() {
  write("Usage: passwd [-h]\n");
  write("Allows you to change your password.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
}

void input_newpass2( string str) {
   if (!str || str == "") {
      write("Empty password aborting.");
      return;
   }
   if (str == newpass) {
      this_player()->set_password(str);
      write("You have changed your password.\n");
   } else {
	write("Password's do not match.\n");
	return;
   }
}

void input_newpass( string str) {
   if (!str || str == "") {
      write("You need to enter a password, to change it.\n");
      return;
   }

   newpass = str;
   write("Verify new password: ");
   this_player()->input_to_object( this_object(), "input_newpass2");
}

void input_curpass( string str) {
   if (!str || str == "") {
	write("ouchie...\n");
   }
   if (str == oldpass) {
      write("New password: ");
//      send_message( 0 );
      this_player()->input_to_object( this_object(), "input_newpass");
   } else {
      write("That is not your current password.\n");
      write("passwd = " + oldpass + "\n");
      write("new passwd = " + str + "\n");
      return;
   }
}

void main( string arg ) {
  if (arg && arg != "" ) {
     usage();
     return;
  }

  oldpass = this_player()->query_passwd();
  this_player()->input_to_object(this_object(), "input_curpass");
  write( "\nPlease enter your password : " );
}
