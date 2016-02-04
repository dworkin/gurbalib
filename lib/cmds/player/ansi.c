inherit M_COMMAND;

string parse_error;

string *usage(void) {
   string mode, *lines;

   if (this_player()->query_ansi() == 1) {
      mode = "on";
   } else {
      mode = "off";
   }

   lines = ({ "Usage: ansi[-h] [on|off|show]" });
   lines += ({ "" });
   lines += ({ "Used to turn on or off color support and show the settings." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\ton\tTurn on ANSI support." });
   lines += ({ "\toff\tTurn off ANSI support." });
   lines += ({ "\tshow\tDisplay your current ANSI support settings." });
   lines += ({ "Examples:" });
   lines += ({ "\tansi on" });
   lines += ({ "\tansi show" });

   lines += get_alsos();

   lines += ({ "" });
   lines += ({ "You currently have ansi mode: " + mode });

   return lines;
}

setup_alsos() {
   add_also("player", "alias");
   add_also("player", "clear");
   add_also("player", "describe");
   add_also("player", "ignore");
   add_also("player", "passwd");

   add_also("admin", "coloradm");
}

#define GRAMMAR "whitespace=/[ ]+/\n" + \
                "TAG=/[A-Z_][A-Z0-9_]*/ \n" + \
                "TAG=/NIL/\n" + \
                "args: tags ? collect_map\n" + \
                "assign: tag '=' values ? wrap_assign\n" + \
                "tags: assign\n" + \
                "tags: tags assign\n" + \
                "tags: tags ',' assign\n" + \
                "tags: tags 'and' assign\n" + \
                "tag: TAG ? valid_tag_name\n" + \
                "values: value_list\n" + \
                "value_list: value\n" + \
                "value_list: value_list '+' value\n" + \
                "value: TAG ? valid_value\n"

/*
 * If the arg[0] is a base symbol, it can't be used
 * as a custom tag.
 */
mixed *valid_tag_name(mixed * arg) {
   if (ANSI_D->query_custom_symbol(arg[0])) {
      return arg;
   } else {
      parse_error = "Invalid tag: " + arg[0];
      return nil;
   }
}

mixed *valid_value(mixed * arg) {
   if ((arg[0] == "NIL") || ANSI_D->query_any_symbol(arg[0])) {
      return arg;
   } else {
      parse_error = "Invalid value: " + arg[0];
      return nil;
   }
}

mixed *wrap_assign(mixed * arg) {
   return ( { ([arg[0]:(arg[2..] - ( { "+" } ))]) } );
}

mixed *collect_map(mixed * arg) {
   int i, sz;
   mapping result;

   result = ([]);

   for (i = 0, sz = sizeof(arg); i < sz; i++) {
      if (mappingp(arg[i])) {
         result += arg[i];
      }
   }
   return ( { result } );
}

void set_colors(mixed *args) {
   int i, sz;
   string *symbols;

   if (!arrayp(args) || !mappingp(args[0])) {
      write("I didn't quite understand that.\n" +
         "Try something like 'color symbol = ATTRIBUTE + COLOR'\n" +
         "                or 'color symbol = COLOR, symbol = COLOR'\n" +
         "Note that using predefined color names as symbol is not " +
         "allowed\nbut using symbols as colors is allowed, ie\n" +
         " 'color room_desc = room_exit' will work\n\n" +
         "Valid color and symbol names:\n\n");
         "/cmds/player/ansi"->main("show");
   } else {
      symbols = map_indices(args[0]);
      sz = sizeof(symbols);
      for (i = 0; i < sz; i++) {
         /* special case, 'NIL' tag means remove this symbol.
            also note this is a string, not the nil value */
         if (args[0][symbols[i]][0] == "NIL") {
            this_player()->set_custom_color(symbols[i], nil);
         } else {
            this_player()->set_custom_color(symbols[i],
               args[0][symbols[i]]);
         }
      }
   }
}

static void main(string str) {
   mixed *args;
   string error;
   int i, pos;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if ((str == "on") || (str == "On") || (str == "1")) {
      this_player()->set_ansi(1);
      out("Turning on ANSI.\n");
   } else if ((str == "off") || (str == "Off") || (str == "0")) {
      this_player()->set_ansi(0);
      out("Turning off ANSI.\n");
   } else if ((str == "show") || (str == "display")) {
      out(ANSI_D->color_table());
   } else {
      str = uppercase(str);

      parse_error = nil;
      error = catch(args = parse_string(GRAMMAR, str));

      if (parse_error) {
         write(parse_error);
      } else {
         if (error) {
            if (sscanf(error, "Bad token at offset %d", pos) == 1) {
               write("Invalid character " + str[pos..pos] + ".");
               return;
            } else {
               rethrow();
            }
         }

         set_colors(args);
      }
   }
}

