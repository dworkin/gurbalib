#include <type.h>

static object monster;
static mapping events;

static object compile_object( string path ) {
  if( strlen(path) > 2 ) {
    if( path[strlen(path)-2] == '.' && path[strlen(path)-1] == 'c' )
      path = path[..strlen(path)-3];
  }
  return ::compile_object( path );
}

static object clone_object( string path ) {
  object ob;

  if( strlen(path) > 2 ) {
    if( path[strlen(path)-2] == '.' && path[strlen(path)-1] == 'c' )
      path = path[..strlen(path)-3];
  }

  if( ob = find_object( path ) ) 
    return ::clone_object( ob );
  else
    return ::clone_object( compile_object( path ) );
}

static set_this_player( object ob ) {
  monster = ob;
}

static object this_player( void ) {
  if( !this_user() ) {
    if( !monster )
      return( previous_object() );
    else 
      return( monster );
  }
  if( this_user()->query_player()->is_possessing() )
    return( this_user()->query_player()->query_possessing() );
  return( this_user()->query_player() );
}

static object this_body( void ) {
  if( !this_user() ) {
    if( !monster )
      return( previous_object() );
    else 
      return( monster );
  }
  if( this_user()->query_player()->is_possessing() )
    return( this_user()->query_player()->query_possessing() );
  return( this_user()->query_player() );
}

static object this_race( void ) {
  if( !this_user() ) {
    if( !monster )
      return( previous_object() );
    else 
      return( monster );
  }
  if( this_user()->query_player()->is_possessing() )
    return( this_user()->query_player()->query_possessing()->query_race_object() );
  return( this_body()->query_race_object() );
}

object this_environment( void ) {
  return( this_player()->query_environment() );
}

nomask int file_exists (string str) {
  mixed *val;
  int *sizes;
  
  val = get_dir( str );
  sizes = val[1];
  if( !sizes || sizeof( sizes ) == 0 ) 
    return 0;
  if( sizes[0] == -2 ) 
    return -1;
  return 1;
}

int absolute_path( string dir ) {
  if( !dir || dir == "" )
    return( 0 );
  if( dir[0] == '/' || dir[0] == '~' )
    return( 1 );
  return( 0 );
}

void out_unmod( string str ) {
  if( !this_user()  )
    return;
  this_user()->put_original( str );
  if( this_player()->is_snooped() )
    this_player()->do_snoop( str );
}

void out( string str ) {
  if( !this_user()  )
    return;
  this_player()->message_orig( str );
/*   this_user()->put_message( str ); */
  if( this_player()->is_snooped() )
    this_player()->do_snoop( str );
}

void write( string str ) {
  if( !this_user() )
    return;
  this_player()->message( str );
  if( this_player()->is_snooped() )
    this_player()->do_snoop( str );
}

string capitalize(string str) {
  if (!str) return str ;
  if (str[0] >= 'a' && str[0] <= 'z') {
    str[0] -= 'a' - 'A';
  }
  return str;
}

string lowercase(string str) {
  
  int i ;
  
  for (i=0;i<strlen(str);i++) {
    if (str[i]>='A' && str[i]<='Z') str[i] += 'a' - 'A' ;
  }
  return str ;
}

string uppercase(string str) {
  
  int i ;
  
  for (i=0;i<strlen(str);i++) {
    if (str[i]>='a' && str[i]<='z') str[i] -= 'a' - 'A' ;
  }
  return str ;
}

string article( string name ) {
  if( lowercase( name ) == "hour" )
    return( "an" );

  switch( name[0] ) {
  case 'a':
  case 'e':
  case 'i':
  case 'o':
  case 'u':
    return( "an" );
  default:
    return( "a" );
  }
}

string format_idle_time( int time ) {
  
  int mins;
  int hrs;
  int days;
  string str;
  
  mins = time / 60;
  time = time - (mins * 60);
  
  hrs = mins / 60;
  mins = mins - (hrs * 60);
  
  days = hrs / 24;
  hrs = hrs - ( days * 24 );
  
  str = "";
  
  if( time > 0 )
    str = " " + time + "s";
  if( mins > 0 )
    str = " " + mins + "m";
  if( hrs > 0 )
    str = " " + hrs + "h";
  if( days > 0 ) 
    str = " " + days + "d";
  
  return str;
}

string format_time( int time ) {
  
  int mins;
  int hrs;
  int days;
  string str;
  
  mins = time / 60;
  time = time - (mins * 60);
  
  hrs = mins / 60;
  mins = mins - (hrs * 60);
  
  days = hrs / 24;
  hrs = hrs - ( days * 24 );
  
  str = "";
  
  if( days > 0 ) 
    str += " " + days + "d";
  if( hrs > 0 )
    str += " " + hrs + "h";
  if( mins > 0 )
    str += " " + mins + "m";
  if( time > 0 )
    str += " " + time + "s";
  
  return str;
}

int member_array( mixed item, mixed *arr ) {
  int i;

  for( i=0; i < sizeof( arr ); i++ ) {
    if( arr[i] == item )
      return( i );
  }
  return( -1 );
}

int member_map( mixed item, mapping map ) {
  mixed *arr;

  arr = map_indices( map );
  if( member_array( item, arr ) > -1 )
    return( 1 );
  arr = map_values( map );
  if( member_array( item, arr ) > -1 )
    return( 1 );
 
  return( 0 );
  
}

int cat_file( string filename ) {
  int i;
  string *lines;
  
  i = file_exists( filename );
  if( !i ) {
    write( "No such file.\n" );
    return( 0 );
  }
  if( i == -1 ) {
    write ( "Unable to cat directories.\n" );
    return( 0 );
  }
  lines = explode( read_file( filename ), "\n" );
  for( i = 0; i < sizeof( lines ); i++ ) {
    send_message( lines[i] + "\n" );
  }
  return( 1 );
}

/*
 * NAME:	dump_value()
 * DESCRIPTION:	return a string describing a value
 */

static string dump_value(mixed value, mapping seen)
{
  string str;
  int i, sz;
  mixed *indices, *values;
  
  switch (typeof(value)) {
  case T_INT:
  case T_FLOAT:
    return (string) value;
    
  case T_STRING:
    str = value;
    if (sscanf(str, "%*s\\") != 0) {
      str = implode(explode("\\" + str + "\\", "\\"), "\\\\");
    }
    if (sscanf(str, "%*s\"") != 0) {
      str = implode(explode("\"" + str + "\"", "\""), "\\\"");
    }
    if (sscanf(str, "%*s\n") != 0) {
      str = implode(explode("\n" + str + "\n", "\n"), "\\n");
    }
    if (sscanf(str, "%*s\t") != 0) {
      str = implode(explode("\t" + str + "\t", "\t"), "\\t");
    }
    return "\"" + str + "\"";
    
  case T_OBJECT:
    return "<" + object_name(value) + ">";
    
  case T_ARRAY:
    if (seen[value]) {
      return "#" + (seen[value] - 1);
    }
    
    seen[value] = map_sizeof(seen) + 1;
    sz = sizeof(value);
    if (sz == 0) {
      return "({ })";
    }
    
    str = "({ ";
    for (i = 0, --sz; i < sz; i++) {
      str += dump_value(value[i], seen) + ", ";
    }
    return str + dump_value(value[i], seen) + " })";
    
  case T_MAPPING:
    if (seen[value]) {
      return "@" + (seen[value] - 1);
    }
    
    seen[value] = map_sizeof(seen) + 1;
    sz = map_sizeof(value);
    if (sz == 0) {
      return "([ ])";
    }
    
    str = "([ ";
    indices = map_indices(value);
    values = map_values(value);
    for (i = 0, --sz; i < sz; i++) {
      str += dump_value(indices[i], seen) + ":" +
	dump_value(values[i], seen) + ", ";
    }
    return str + dump_value(indices[i], seen) + ":" +
      dump_value(values[i], seen) + " ])";
  }
}

string wiz_dir( object ob ) {
  return( "/wiz/" + ob->query_name() + "/" );
}

/*
 * NAME:	normalize_path()
 * DESCRIPTION:	reduce a path to its minimal absolute form
 */
string normalize_path(string file, string dir)
{
  string *path;
  int i, j, sz;

  if (strlen(file) == 0) {
    file = dir;
  }
  switch (file[0]) {
  case '~':
    /* ~path */
    if(strlen(file) == 1 || file[1] == '/') {
      file = "/wiz/" + this_user()->query_name() + file[1 ..];
    } else {
      file = "/wiz/" + file[1 ..];
    }
    /* fall through */
  case '/':
    /* absolute path */

    path = explode(file, "/");

    if( (path[0] == "data" || path[0] == "kernel") && !SECURE_D->query_admin( this_user()->query_name() ) ) 
      return("");

    if (sscanf(file, "%*s//") == 0 && sscanf(file, "%*s/.") == 0) {
      return file;	/* no changes */
    }
    break;
    
  default:
    /* relative path */
    if (sscanf(file, "%*s//") == 0 && sscanf(file, "%*s/.") == 0 &&
	sscanf(dir, "%*s/..") == 0) {
      /*
       * simple relative path
       */

      if( dir[strlen(dir)-1] == '/' )
	path = explode( dir + file, "/" );
      else
	path = explode( dir + "/" + file, "/" );

      if( (path[0] == "data" || path[0] == "kernel") && !SECURE_D->query_admin( this_user()->query_name() ) ) 
	return("");
      

      if( dir[strlen(dir)-1] == '/' )
	return dir + file;
      else
	return dir + "/" + file;
    }
    /* fall through */
  case '.':
    /*
     * complex relative path
     */
    path = explode(dir + "/" + file, "/");
    break;
  }
  
  for (i = 0, j = -1, sz = sizeof(path); i < sz; i++) {
    switch (path[i]) {
    case "..":
      if (j >= 0) {
	--j;
      }
      /* fall through */
    case "":
    case ".":
      continue;
    }
    path[++j] = path[i];
  }

  if( (path[0] == "data" || path[0] == "kernel") && !SECURE_D->query_admin( this_user()->query_name() ) ) {
    return "";
  }
  
  return "/" + implode(path[.. j], "/");
}

/*
 * NAME:	dir_size()
 * DESCRIPTION:	get the size of all files in a directory
 */
private int dir_size(string file)
{
  mixed **info;
  int *sizes, size, i, sz;
  
  info = get_dir(file + "/*");
  sizes = info[1];
  size = 1;		/* 1K for directory itself */
  i = sizeof(sizes);
  while (--i >= 0) {
    sz = sizes[i];
    size += (sz > 0) ?
      (sz + 1023) >> 10 :
      (sz == 0) ? 1 : dir_size(file + "/" + info[0][i]);
  }
  
  return size;
}

/*
 * NAME:	file_size()
 * DESCRIPTION:	get the size of a file in K, or 0 if the file doesn't exist
 */
int file_size(string file, varargs int dir)
{
  mixed **info;
  string *files, name;
  int i, sz;
  
  if (file == "/") {
    file = ".";
  }
  info = get_dir(file);
  files = explode(file, "/");
  name = files[sizeof(files) - 1];
  files = info[0];
  i = 0;
  sz = sizeof(files);
  
  if (sz <= 1) {
    if (sz == 0 || files[0] != name) {
      return 0;	/* file does not exist */
    }
  } else {
    /* name is a pattern: find in file list */
    while (name != files[i]) {
      if (++i == sz) {
	return 0;	/* file does not exist */
      }
    }
  }
  
  i = info[1][i];
  return (i > 0) ?
    i :
    (i == 0) ? 1 : (i == -2 && dir) ? dir_size(file) : 0;
}

/* Returns random element from the given array.
   Returns nil if array is empty. */
mixed random_element( mixed *arr ) {
  if (sizeof(arr) < 1)
    return nil;
  
  return arr[random(sizeof(arr))];
}

string base_name( void ) {

  string str,obname;
  int clone;
  
  obname = object_name(this_object());
  if( sscanf( obname, "%s#%d", str, clone ) ==2 ) 
    return str;
  return obname;
}

string file_name() {
  return( base_name() + ".c" );
}

int clone_num() {

  string str ;
  int clone ;
  
  if (sscanf(object_name(this_object()),"%s#%d",str,clone)==2) {
    return clone ;
  }
  return 0 ;
}
 
void add_event( string name ) {
  if( !events )
    events = ([ ]);
  events[name] = ({ });
}

void remove_event( string name ) {
  events[name] = nil;
}

void subscribe_event( string name ) {
  events[name] += ({ previous_object() });
}

void unsubscribe_event( string name ) {
  events[name] -= ({ previous_object() });
}

void event( string name, varargs mixed args... ) {
  object *obs;
  int i;

  obs = events[name];
  for( i = 0; i < sizeof( obs ); i++ ) {
    if( obs[i] )
      call_other( obs[i], "event_" + name, args );
  }
}

int str2val( string str ) {
  int ten;
  int val;
  int i;

  val = 0;
  ten = 1;
  for( i = strlen( str )-1; i >= 0; i-- ) {
    if( str[i] >= '0' && str[i] <= '9' ) {
      val += ( str[i] - '0' ) * ten;
      ten = ten * 10;
    } else {
      return( -1 );
    }
  }
  return( val );
}

int intp( mixed val ) {
  if( typeof( val ) == T_INT )
    return( 1 );
  return( 0 );
}

int floatp( mixed val ) {
  if( typeof( val ) == T_FLOAT )
    return( 1 );
  return( 0 );
}

int arrayp( mixed val ) {
  if( typeof( val ) == T_ARRAY )
    return( 1 );
  return( 0 );
}

int mappingp( mixed val ) {
  if( typeof( val ) == T_MAPPING )
    return( 1 );
  return( 0 );
}

int stringp( mixed val ) {
  if( typeof( val ) == T_STRING )
    return( 1 );
  return( 0 );
}

int strstr( string search, string what ) {
  int i;

  for( i = 0; i < (strlen( search ) - ( strlen( what ) - 1 )); i++ ) {
    if( search[i..(i+strlen(what)-1)] == what )
      return i;
  }
  return( -1 );
}


string replace_string( string str, string old, string new ) {
  int i;
  int olen;
  int slen;
  string done;
  int d;


  olen = strlen( old );
  slen = strlen( str );

  d = 0;
  done = "";
  for( i=0; i < slen; i++ ) {

    if( slen > i + olen -1 ) {
      /* Still not reached the end of the string */
      if( str[i..(i+olen-1)] == old ) {
	/*Found an occurance of the old string*/
	done += new;
	d += strlen( new );
	i += olen-1;
      } else {
	done += " ";
	done[d] = str[i];
	d++;
      }
    } else {
      done += str[i..];
      return( done );
    }
  }
  return( done );
}

 
string invert_exit( string exit ) {
  switch( exit ) {
  case "north":
    return( "south" );
  case "south":
    return( "north" );
  case "east":
    return( "west" );
  case "west":
    return( "east" );
  case "northeast":
    return( "southwest" );
  case "southeast":
    return( "northwest" );
  case "northwest":
    return( "southeast" );
  case "southwest":
    return( "northeast" );
  }
  return( "unknown" );
}
