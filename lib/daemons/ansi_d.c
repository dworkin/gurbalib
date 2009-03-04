#define RESET "[0m"
#define BOLD "[1m"
#define FLASH "[5m"
#define BLACK "[30m"
#define RED "[31m"
#define GREEN "[32m"
#define ORANGE "[33m"
#define YELLOW BOLD + ORANGE
#define BLUE "[34m"
#define CYAN "[36m"
#define MAGENTA "[35m"
#define WHITE "[37m"
#define B_RED "[41m"
#define B_GREEN "[42m"
#define B_ORANGE "[43m"
#define B_YELLOW BOLD + B_ORANGE
#define B_BLUE "[44m"
#define B_CYAN "[46m"
#define B_BLACK "[40m"
#define B_WHITE "[47m"
#define CLEARLINE "[L[G"
#define B_MAGENTA "[45m"
#define INITTERM "[H[2J"
#define ENDTERM ""
#define SAVE "7"
#define RESTORE "8"
#define HOME "[H"

mapping translations; 

void create( void ) {
  translations = ([
		   "RESET" : RESET,
		   "BOLD" : BOLD,
		   "FLASH" : FLASH,
		   "RED" : RED,
		   "GREEN" : GREEN,
		   "ORANGE" : ORANGE,
		   "YELLOW" : YELLOW,
		   "BLUE" : BLUE,
		   "CYAN" : CYAN,
		   "MAGENTA" : MAGENTA,
		   "WHITE" : WHITE,
		   "B_RED" : B_RED,
		   "B_GREEN" : B_GREEN,
		   "B_ORANGE" : B_ORANGE,
		   "B_YELLOW" : B_YELLOW,
		   "B_BLUE" : B_BLUE,
		   "B_CYAN" : B_CYAN,
		   "B_BLACK" : B_BLACK,
		   "B_WHITE" : B_WHITE,
		   "B_MAGENTA" : B_MAGENTA,
		   "CLEARLINE" : CLEARLINE,
		   "INITTERM" : INITTERM,
		   "ENDTERM" : ENDTERM,
		   "SAVE" : SAVE,
		   "RESTORE" : RESTORE,
		   "HOME" : HOME,
		   ]);
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

  string* tmp;
  string msg;
  int i;

  tmp = explode( str, "%^" );

  for( i=0; i < sizeof( tmp ); i++ ) {
    if( member_array( tmp[i], map_indices(translations) ) != -1 ) {
      tmp[i] = translations[ tmp[i] ];
    }
  }
  msg = implode( tmp, "" );
  return( msg );

}
