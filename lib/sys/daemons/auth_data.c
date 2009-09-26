#define AUTH_DATA_DIR "/sys/daemons/data/users/"

string name;
string password;

static void secure() {
  if( previous_program(1) != USER_D && !require_priv( "system" ) ) {
    error( "Access denied." );
  }
}

static void save_me() {
  unguarded( "save_object", AUTH_DATA_DIR + name[0..0] + "/" + name + ".o" );
}

int load( string str ) {
  string file;

  secure();

  file = AUTH_DATA_DIR + str[0..0] + "/" + str + ".o";

  return unguarded( "restore_object", file ); 
}

int test( string str ) {
  secure();

  return crypt( str, "gurba" ) == password;
}

void set_name( string str ) {
  secure();

  name = str;
}

void set_pass( string str ) {
  secure();

  password = crypt( str, "gurba" );
  save_me();
}

void convert_user( string str ) {
  secure();

  restore_object( "/data/players/" + str + ".o" );
  name = str;
  save_me();
}

