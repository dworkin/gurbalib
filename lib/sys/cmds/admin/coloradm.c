inherit M_COMMAND;
#define GRAMMAR "whitespace=/[ ]+/\n"+\
                "TAG=/[A-Z_][A-Z0-9_]*/ \n"+\
                "TAG=/NIL/\n"+\
                "args: tags ? collect_map\n"+\
                "assign: tag '=' values ? wrap_assign\n"+\
                "tags: assign\n"+\
                "tags: tags assign\n"+\
                "tags: tags ',' assign\n"+\
                "tags: tags 'and' assign\n"+\
                "tag: TAG ? valid_tag_name\n"+\
                "values: value_list\n"+\
                "value_list: value\n"+\
                "value_list: value_list '+' value\n"+\
                "value: TAG ? valid_value\n"

void usage() {
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
   lines += ({ "See also:" });
   lines += ({ "\tansi, alias, aliasadm, chfn, cmds, cmdadm, " +
      "describe, emote, emoteadm, ignore, passwd, skilladm, questadm" });

   this_player()->more(lines);
}

/* If the arg[0] is a base symbol, it can't be used as a custom tag. */
mixed *valid_tag_name(mixed * arg) {
   return !ANSI_D->query_base_symbol(arg[0]) ? arg : nil;
}

mixed *valid_value(mixed * arg) {
   return (arg[0] == "NIL" || ANSI_D->query_any_symbol(arg[0])) ? arg : nil;
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
   string error;
   mixed * args;
   string *symbols, *values;
   int i, sz, pos;

   if (!require_priv("system")) {
      write("You must be an admin to do that.");
      return;
   }

   if (!str || (str == "")) {
      usage();
      return;
   }
   if ((str == "show") || (str == "display")) {
      write(ANSI_D->color_table());
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   str = uppercase(str);
write( "Looking at str: " + str + "\n");

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
