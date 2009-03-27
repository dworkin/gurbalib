#define ANSI_DATA "/daemons/data/ansi_d.o"

#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define ORANGE "\x1b[33m"
#define YELLOW BOLD + ORANGE
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

#define B_BLACK "\x1b[40m"
#define B_RED "\x1b[41m"
#define B_GREEN "\x1b[42m"
#define B_ORANGE "\x1b[43m"
#define B_YELLOW BOLD + B_ORANGE
#define B_BLUE "\x1b[44m"
#define B_MAGENTA "\x1b[45m"
#define B_CYAN "\x1b[46m"
#define B_WHITE "\x1b[47m"

#define RESET "\x1b[0m"
#define BOLD "\x1b[1m"
#define ITALIC "\x1b[3m"
#define UNDERLINE "\x1b[4m"
#define FLASH "\x1b[5m"
#define REVERSE "\x1b[7m"

#define CURS_UP "\x1b[A"
#define CURS_DOWN "\x1b[B"
#define CURS_RIGHT "\x1b[C"
#define CURS_LEFT "\x1b[D"

#define CLEARLINE "\x1b[L\x1b[G"
#define INITTERM "\x1b[H\x1b[2J"
#define HOME "\x1b[H"
#define ENDTERM ""
#define SAVE "\x1b[s"
#define RESTORE "\x1b[u"
/* #define SAVE "\x1b7" */
/* #define RESTORE "\x1b8" */

static mapping color_trans, attr_trans, terminal_trans;
mapping symbolic_trans;
static mapping translations; 

void restore_me( void ) {
  restore_object( ANSI_DATA );
}

void save_me( void ) {
  save_object( ANSI_DATA );
}

void create( void ) {
  color_trans = ([
		   "BLACK" : BLACK,
		   "RED" : RED,
		   "GREEN" : GREEN,
		   "ORANGE" : ORANGE,
		   "YELLOW" : YELLOW,
		   "BLUE" : BLUE,
		   "MAGENTA" : MAGENTA,
		   "CYAN" : CYAN,
		   "WHITE" : WHITE,
		   "B_BLACK" : B_BLACK,
		   "B_RED" : B_RED,
		   "B_GREEN" : B_GREEN,
		   "B_ORANGE" : B_ORANGE,
		   "B_YELLOW" : B_YELLOW,
		   "B_BLUE" : B_BLUE,
		   "B_MAGENTA" : B_MAGENTA,
		   "B_CYAN" : B_CYAN,
		   "B_WHITE" : B_WHITE,
		  ]);
  
  attr_trans = ([
		   "RESET" : RESET,
		   "BOLD" : BOLD,
		   "ITALIC" : ITALIC,
		   "UNDERLINE" : UNDERLINE,
		   "FLASH" : FLASH,
		   "REVERSE" : REVERSE,
		  ]);

  terminal_trans = ([
		   "CURS_UP" : CURS_UP,
		   "CURS_DOWN" : CURS_DOWN,
		   "CURS_RIGHT" : CURS_RIGHT,
		   "CURS_LEFT" : CURS_LEFT,

		   "CLEARLINE" : CLEARLINE,
		   "INITTERM" : INITTERM,
		   "ENDTERM" : ENDTERM,
		   "SAVE" : SAVE,
		   "RESTORE" : RESTORE,
		   "HOME" : HOME,
		  ]);

  symbolic_trans = ([
		   "CHAN_NAME" : BLUE,
		   "CHAN_DATE" : CYAN,
		   "CHAN_TEXT" : RESET,

		   "ROOM_NAME" : GREEN,
		   "ROOM_DESC" : RESET,
		   "ROOM_EXIT" : CYAN,

		   "OBJ_ID" : WHITE,
		   "OBJ_ADJ" : WHITE,
		   "OBJ_BRIEF" : WHITE,

		   "NPC_FRIENDLY" : GREEN,
		   "PLAYER" : YELLOW,
		   "NPC_HOSTILE" : RED,
		  ]);

  restore_me();

  translations = color_trans + attr_trans + terminal_trans + symbolic_trans;
}

string strip_colors( string str ) {
  string* tmp;
  string msg;
  int i;

  tmp = explode( str, "%^" );

  for( i=0; i < sizeof( tmp ); i++ ) {
    if( member_array( tmp[i], map_indices(translations) ) != -1 ) {
      tmp[i] = "";
    }
  }
  msg = implode( tmp, "" );
  return( msg );
}

string parse_colors( string str ) {
  string *tmp;
  string msg;
  mixed *ind, *sym;
  int i;

#ifndef SYS_COLOR
  return strip_colors( str );
#endif

  tmp = explode( str, "%^" );
  ind = map_indices( translations );
  sym = map_indices( symbolic_trans );

  for( i=0; i < sizeof( tmp ); i++ ) {
    if( member_array( tmp[i], ind ) != -1 ) {
      tmp[i] = translations[ tmp[i] ];
    } else if( member_array( tmp[i], sym ) != -1 ) {
      tmp[i] = parse_colors( symbolic_trans[ tmp[i] ] );
    }
  }
  msg = implode( tmp, "" );
  return( msg );
}

string color_table_chunk( mapping m, int codes  )
{
  int i, j, sz, pad;
  mixed *ind, *val;
  string msg, tokenized, reset;

  sz = map_sizeof(m);
  ind = map_indices(m);
  /* val = map_values(m); */
  msg = "";
  reset = ( codes ) ? "%^RESET%^" : "";
  for (i = 0; i < sz; i++) {
    tokenized = ( codes ) ? "%^" + ind[i] + "%^": "";
    pad = 16 - strlen(ind[i]) - 1;
    /* Bizzare... if I remove the space in the line below, I get nothing! */
    msg += tokenized + " " + ind[i] ;
    for ( j = 0; j < pad; j++ )
      msg += " ";
    msg += reset;
    msg += ( i % 4 == 3 ) ? "\n" : " ";
  }
  if ( sz % 4 != 0 ) msg += "\n";
  return msg;
}

string color_table( void )
{
  string msg;

  msg = "Colors:\n";
  msg += color_table_chunk( color_trans, 1 );
  msg += "\nAttributes:\n";
  msg += color_table_chunk( attr_trans, 1 );
  msg += "\nTerminal:\n";
  msg += color_table_chunk( terminal_trans, 0 );
  msg += "\nSymbolic:\n";
  msg += color_table_chunk( symbolic_trans, 1 );
  return msg;
}

/*
 * My thoughts here were to not only allow simple named colours
 * by passing an array of normal colour tokens (IE: BOLD ITALIC BLUE),
 * but to eventually allow arbitrary text as well.
 * However, things like setting FOO = %^BOLD%^Hello%^FOO%^There would
 * be Bad(TM).
 */
void ansi_set_color( string name, string *symbols )
{
  string tmp;
  mixed *ind, *sym;
  int i;

  if( SECURE_D->query_admin( this_player()->query_name() ) != 1 ) {
    write( "Access denied.\n" );
    return;
  }

  name = uppercase( name );
  ind = map_indices( translations );
  sym = map_indices( symbolic_trans );
  tmp = "";

  for( i=0; i < sizeof( symbols ); i++ ) {
    if( strstr( "%^", symbols[i] ) == -1 ) {
      symbols[i] = uppercase( symbols[i] );
      if( member_array( symbols[i], ind ) == -1 ) {
        /* Each symbol must resolve to a pre-defined token */
        write( "Symbolic color tokens must be composed of only valid base color tokens\n" );
        return;
      }
      tmp += "%^" + symbols[i] + "%^";
    } else {
      write( "Symbolic color tokens cannot (YET) contain custom tokens\n" );
      return;
    }
  }

  symbolic_trans[name] = parse_colors(tmp);
  translations = color_trans + attr_trans + terminal_trans + symbolic_trans;
  out_unmod( name + " is now " + tmp + "\n" );
  save_me();
}

void ansi_remove_color( string name )
{
  mixed *ind;

  if( SECURE_D->query_admin( this_player()->query_name() ) != 1 ) {
    write( "Access denied.\n" );
    return;
  }

  name = uppercase( name );
  ind = map_indices( symbolic_trans );

  if( member_array( name, ind ) == -1 ) {
    write( name + " is not currently a symbolic color!\n" );
    return;
  }

  symbolic_trans[name] = nil;
  write( name + " is no longer a valid color.\n" );
  save_me();
}

