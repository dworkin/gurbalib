/*
 * Gurbalib's menu generator 		Aidil, March 2010
 */
#undef DEBUG

#ifdef DEBUG
#define DBT(X) write( X )
#else
#define DBT(X)
#endif

#define KEY            0
#define DESC           1
#define OPT_DESC       2
#define ACTION         3

#define INSANE         11

#define C_KEY          "%^MENU_KEY%^"
#define C_DESC         "%^MENU_TEXT%^"
#define C_OPT_DESC     "%^MENU_HILITE%^"
#define C_DECOR        "%^MENU_DECORATE%^"
#define C_OFF          "%^RESET%^"

#define PAD            "                                                                                                                 "
#define LINE           "------------------------------------------------------------------------------"

/* prototypes */
private void exec_menu();

/* Interface for object using this library */

/* Displays a menu to this_player() and redirects the input to the
 * menu handler.
 */
static void do_menu(mixed header, mixed * menu, varargs mixed footer) {
   int i, sz;
   mapping actmap;

   actmap = ([]);

   DBT(dump_value(menu));
   for (i = 0, sz = sizeof(menu); i < sz; i++) {
      DBT("" + i + ":" + dump_value(menu[i]));
      actmap[menu[i][KEY]] = menu[i][ACTION];
   }

   this_player()->store_menu(header, menu, footer, actmap);
   exec_menu();
}

/* Create a call array for use with the menu system, a call array
 * allows making function calls from descriptive items in a menu,
 * and is used for constructing the 'action' part of a menu item.
 */
static mixed *make_fcall(object ob, string fun, mixed args ...) {
   return ( {
      ob, fun}
   ) + ((args && sizeof(args)) ? args : ( {
	 }
      ));
}

/* Private functions */
private void prompt(string * keys) {
   string disp;

   disp = "\n";
   if (sizeof(keys)) {
      if (sizeof(keys) < INSANE) {
	 disp += "[" + implode(keys, ", ") + "] ";
      } else {
	 int l;
	 l = sizeof(keys) - 1;
	 disp +=
	    "[" + implode(keys[0..3], ", ") + "..." + implode(keys[l - 2..l],
	    ", ") + "] ";
      }
   }
   this_player()->query_user()->out(disp);
}

private void input_to(string fun) {
   this_player()->input_to_object(this_object(), fun);
}

private mixed FCALL(mixed * fpa) {
   object ob;
   string fun;
   mixed *args;

   if (objectp(fpa[0])) {
      ob = fpa[0];
   } else if (stringp(fpa[0])) {
      ob = find_object(fpa[0]);
   }

   if (!ob) {
      error("No object for FCALL");
   }

   fun = fpa[1];

   if (sizeof(fpa) > 2) {
      args = fpa[2..];
      return call_other(ob, fun, args...);
   } else {
      return call_other(ob, fun);
   }
}

private string fixlen(string str, int len) {
   str += PAD;
   return str[..len - 1];
}

private mixed get_val(mixed item) {
   if (arrayp(item)) {
      return FCALL(item);
   } else {
      return item;
   }
}

private string *display_conv(string str) {
   return ( {
      ANSI_D->parse_colors(str)}
   );
}

private string make_display_line(mixed * m) {
   string result, tmp;

   result = C_KEY + fixlen(get_val(m[KEY]), 3) + C_OFF;
   result += " : ";
   result += C_DESC + fixlen(get_val(m[DESC]), 40) + C_OFF;
   if (m[OPT_DESC]) {
      result += "(" + C_OPT_DESC + get_val(m[OPT_DESC]) + "%^RESET%^)";
   }

   return result;
}

private void display_menu(mixed header, mixed * menu, mixed footer,
   string * keys) {
   int i, sz;

   string *output;

   output = ( { } ); 

   if (arrayp(header)) {
      header = FCALL(header);
   }

   if (arrayp(footer)) {
      footer = FCALL(footer);
   }

   if (header) {
      output += display_conv(header);
   }
   output += display_conv(C_DECOR + LINE + C_OFF);
   for (i = 0, sz = sizeof(menu); i < sz; i++) {
      output += display_conv(make_display_line(menu[i]));
   }
   output += display_conv(C_DECOR + LINE + C_OFF);
   if (footer) {
      output += display_conv(footer);
   }
   this_player()->more(output);
}

private void exec_menu() {
   mixed header, footer, *menu;
   mapping actions;

   ( { header, menu, footer, actions } ) = this_player()->retrieve_menu();
   display_menu(header, menu, footer, map_indices(actions));
}

void menu_response(string str) {
   mixed header, footer, *menu, resp;
   mapping actions;

   ( { header, menu, footer, actions } ) = this_player()->retrieve_menu();

   if (actions[str]) {
      resp = FCALL(actions[str]);
      if (intp(resp)) {
	 switch (resp) {
	    case 0:
	       display_menu(header, menu, footer, map_indices(actions));
	       break;
	    case 2:
	       break;
	    default:
	       this_player()->store_menu(nil, nil, nil, nil);
	       break;
	 }
      } else {
	 write(dump_value(resp));
	 this_player()->store_menu(nil, nil, nil, nil);
      }
   } else {
      display_menu(header, menu, footer, map_indices(actions));
   }
}

void more_done() {
   mixed header, *menu, footer;
   mapping actions;

   ( { header, menu, footer, actions } ) = this_player()->retrieve_menu();
   if (actions) {
      input_to("menu_response");
      prompt(map_indices(actions));
   }
}
