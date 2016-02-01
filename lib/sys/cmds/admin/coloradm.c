inherit M_COMMAND;

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

string *usage(void) {
   string *lines;

   lines = ({ "Usage: coloradm [-h] [SHOW|COMMAND]" });
   lines += ({ " " });
   lines += ({ "Allows you to modify the color table, or look at the current " +
      "color table." });
   lines += ({ "COMMAND has the following SYNTAX:" });
   lines += ({ "\tSYMBOL=COLOR" });
   lines += ({ "\tSYMBOL=COLOR+ATTRIBUTES" });
   lines += ({ "Use coloradm show to see your options." });
   lines += ({ " " });

   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\tshow\tShows you the current symbols." });

   lines += ({ "Examples:" });
   lines += ({ "\tcoloradm ROOM_NAME=GREEN" });
   lines += ({ "\tcoloradm ROOM_NAME=RED+REVERSE" });
   lines += ({ "\tcoloradm ROOM_NAME=RED+REVERSE+UNDERLINE" });
   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "ansi");
   add_also("player", "alias");
   add_also("player", "cmds");
   add_also("player", "emote");
   add_also("player", "ignore");
   add_also("player", "passwd");

   add_also("wiz", "aliasadm");
   add_also("wiz", "cmdadm");
   add_also("wiz", "describe");
   add_also("wiz", "domain");
   add_also("wiz", "emoteadm");
   add_also("wiz", "skilladm");
   add_also("wiz", "rehash");
   add_also("wiz", "questadm");
}

/* If the arg[0] is a base symbol, it can't be used as a custom tag. */
mixed *valid_tag_name(mixed * arg) {
   if (!ANSI_D->query_base_symbol(arg[0])) {
      return arg;
   }
   return nil;
}

mixed *valid_value(mixed * arg) {
   if (arg[0] == "NIL" || ANSI_D->query_any_symbol(arg[0])) {
      return arg;
   }
   return  nil;
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

static void main(string str) {
   mixed *args;
   string error, *symbols, *values;
   int i, sz, pos;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      this_player()->more(usage());
      return;
   }
   if ((str == "show") || (str == "display")) {
      write(ANSI_D->color_table());
      return;
   }
   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   str = uppercase(str);

   error = catch(args = parse_string(GRAMMAR, str));

   if (error) {
      if (sscanf(error, "Bad token at offset %d", pos) == 1) {
         write("Invalid character " + str[pos..pos] + ".");
         return;
      } else {
         rethrow();
      }
   }
   if (!arrayp(args) || !mappingp(args[0])) {
      write("I didn't quite understand that.\n" +
         "Try something like 'coloradm SYMBOL = ATTRIBUTE + COLOR'\n" +
         "                or 'coloradm SYMBOL = COLOR, SYMBOL = COLOR'\n" +
         "Note that using predefined color names as SYMBOL is not allowed.");
   } else {
      symbols = map_indices(args[0]);

      for (i = 0, sz = sizeof(symbols); i < sz; i++) {
         if (args[0][symbols[i]][0] == "NIL") {
            ANSI_D->ansi_remove_color(symbols[i]);
         } else {
            ANSI_D->ansi_set_color(symbols[i], args[0][symbols[i]]);
         }
      }
   }
}
