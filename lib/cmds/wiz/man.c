/* A highly advanced man command 
 * Aphex
 *
 * Improved by Aidil
 * :)
 */

#define BASEDIR "/doc/"

static string * topics;

static string * build_dir(string str) {
  string *dir;
  string *result;
  int pos;

  result = ({ });

  dir = get_dir(str + "*")[0];
  dir -= ({ ".svn" });
  for(pos = 0; pos < sizeof(dir); pos++) {
    if(file_exists(str + dir[pos]) == -1) {
      result += ({ str + dir[pos] });
      result += build_dir(str + dir[pos]);
    }
  }
  return result;
}
  
void rebuild_topics() {
  topics = build_dir(BASEDIR);
}

void create() {
  rebuild_topics();
}

static string *dir_index(string what) {
  string *res;
  string *dir;
  string line;
  mixed width;
  int ncollumns;
  int i;
  int j;
  int sz;

  dir = get_dir(what+"/*")[0];
  if(!dir) return ({ });

  width = this_player()->query_env("width");
  if(!intp(width) || width < 2) width = 78;
  else width--;
  ncollumns = width/19;

  dir -= ({ ".svn" });
  res = ({ });

  for(i=0,sz=sizeof(dir);i<sz;i+=ncollumns) {
    line = "";
    for(j=0;j<ncollumns;j++) {
      if(i+j < sz) {
        if(file_exists(what+dir[i+j]) == -1) {
          line += (dir[i+j]+"/                     ")[0..18];
        } else {
          line += (dir[i+j]+"                              ")[0..18];
        }
      }
    }
    res += ({ line });
  }
  return res;
}

void main( string arg ) {
  string file;
  string *tmp;
  string *lines;
  string header;
  int i,j,found;
  int where;
  mixed width;

  if ( !arg ) {
    arg = "";
  }

  if(arg == "--reindex") {
    rebuild_topics();
    write ( dump_value(topics, ([])) +"\n");
    return;
  }

  if( query_wizard( this_player() ) != 1) {
    return;
  }

  arg = lowercase(arg);
  
  file = normalize_path( arg, BASEDIR );
  
  if( file_exists( file ) == 0 ) {
    for(j=0;j<sizeof(topics);j++) {
      file = normalize_path( arg, topics[j]);
      if( file_exists(file) != 0 ) {
        found++;
        break;
      }
    }
  } else {
    found = 1;
  }

  if(!found) {
    write( capitalize(arg) + ": Unknown man page." );
    write_file("/logs/man", capitalize(this_player()->query_name()) + " on " + ctime(time()) + ": " + arg + "\n");
    return;
  }

  width = this_player()->query_env("width");
  if(!intp(width) || width < 2) width = 78;
  else width--;

  if(file_exists(file) > 0) {
    header = "Manpage for "+arg+".";
    tmp = explode( read_file( file ), "\n" );
  } else {
    header = "Index for "+arg+".";
    tmp = dir_index(file);
  }

  lines = ({ });
  write(header + "\n");
  for( i = 0; i < strlen(header); i++){
    out("-");
  }
  write("\n");
  for( i = 0; i < sizeof( tmp ); i++ ) {
    if( strlen( tmp[i] ) > width ) {
      /* Big line. Break it up. */
      where = 0;
      while( where < strlen( tmp[i] ) ) {
	if( where + width < strlen( tmp[i] ) ) {
	  lines += ({ tmp[i][where..where+(width-1)] });
	  where += width;
	} else {
	  lines += ({ tmp[i][where..] });
	  where = strlen(tmp[i]);
	}
      }
    } else {
      lines += ({ tmp[i] }) ;
    }
  }
  
  
  this_player()->more( lines );
}
