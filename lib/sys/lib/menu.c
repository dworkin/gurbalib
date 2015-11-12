/*
 * Gurbalib's menu generator             Aidil, March 2010
 */
/* #define DEBUG_MENU 1 */

#ifdef DEBUG_MENU
#define DBT(X) write( X )
#else
#define DBT(X)
#endif

#define FCALL call_other

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

#define PAD            "                                                                                                                                                                                                            "
#define LINE           "------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------"

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
   if (args && sizeof(args)) {
      return ({ ob, fun }) + args;
   }
   return ({ ob, fun });
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
         disp += "[" + implode(keys[0..3], ", ") + "..." + 
            implode(keys[l - 2..l], ", ") + "] ";
      }
   }
   this_player()->query_user()->out(disp);
}

private void input_to(string fun) {
   this_player()->input_to_object(this_object(), fun);
}

private string fixlen(string str, int len, varargs int flag) {
   if (flag) {
      str = PAD + str;
      if (len > strlen(str)) {
         len = strlen(str);
      }
      return str[(strlen(str)-len)..];
   } else {
      str += PAD;
      return str[..len - 1];
   }
}

private mixed get_val(mixed item) {
   if (arrayp(item)) {
      return FCALL(item...);
   } else {
      return item;
   }
}

private string *display_conv(string str) {
   string *r, *words, line;
   int width, len, i, sz, total, pos;

   r = ({ });
   width = this_player()->query_width();
   len = strlen(ANSI_D->strip_colors(str));
   /* stupid line splitter, will split on word breaks, but 
      will fail on long words deal with lines that are too long still, 
      should only happen when width < 40  */
   if (len > width) {
      words = rexplode(str, " ");
      line = "";
      total = 0;
      sz = sizeof(words);
      for (i = 0; i < sz; i++) {
         if (strlen(words[i]) > 0) {
            total += strlen(ANSI_D->strip_colors(words[i]));
            if (total > width) {
               r += ({ line });
               total = strlen(words[i]);
               line = "";
            }
            line += words[i];
         }
         total++;
         line += " ";
      }
      if (strlen(line)) {
         r += ({ line });
      }
   } else {
      r = ({ str });
   }
   
   return map_array(r, "parse_colors", ANSI_D);
}

private string make_display_line(mixed * m) {
   string result, tmp;
   int width;

   width = this_player()->query_width();
   if (width > 132) {
      width = 132;
   }
   /* we'll deal with smaller displays later */
   if (width < 40) {
      width = 40;
   }

   result = C_KEY + fixlen(get_val(m[KEY]), 3) + C_OFF;
   result += " : ";
   if (m[OPT_DESC]) {
      int dlen, olen;
      string desc, opt;

      desc = get_val(m[DESC]);
      opt = get_val(m[OPT_DESC]);

      olen = strlen(opt);
      if (olen > ((width - 8) / 2) + 4) {
         olen = (width - 8) / 2;
         opt = opt[..olen-1];
         opt += "...";
         olen = 8 + strlen(opt);
      } else {
         olen += 8;
      }
      dlen = width - olen;
      result += C_DESC + fixlen(desc, dlen) + C_OFF;
      result += "(" + C_OPT_DESC + opt + C_OFF + ")";
   } else {
      result += C_DESC + fixlen(get_val(m[DESC]), width-7) + C_OFF;
   }

   return result;
}

private void display_menu(mixed header, mixed * menu, mixed footer,
   string * keys) {
   int i, sz, width;
   string *output;

   output = ( { } ); 
   width = this_player()->query_width();
   if (width > 132) {
      width = 132;
   }

   width--;

   if (arrayp(header)) {
      header = FCALL(header...);
   }

   if (arrayp(footer)) {
      footer = FCALL(footer...);
   }

   if (header) {
      output += display_conv(header);
   }
   output += display_conv(C_DECOR + LINE[..width] + C_OFF);
   for (i = 0, sz = sizeof(menu); i < sz; i++) {
      output += display_conv(make_display_line(menu[i]));
   }
   output += display_conv(C_DECOR + LINE[..width] + C_OFF);
   if (footer) {
      output += display_conv(footer);
   }
   this_player()->more(output);
}

private void exec_menu(void) {
   mixed header, footer, *menu;
   mapping actions;

   ({ header, menu, footer, actions }) = this_player()->retrieve_menu();
   display_menu(header, menu, footer, map_indices(actions));
}

void menu_response(string str) {
   mixed header, footer, *menu, resp;
   mapping actions;

   ({ header, menu, footer, actions }) = this_player()->retrieve_menu();

   if (actions[str]) {
      resp = FCALL(actions[str]...);
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

void more_done(void) {
   mixed header, *menu, footer;
   mapping actions;

   ({ header, menu, footer, actions }) = this_player()->retrieve_menu();
   if (actions) {
      input_to("menu_response");
      prompt(map_indices(actions));
   }
}
