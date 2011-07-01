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
  write("Usage: coloradm [-h] COMMANDS\n");
  write("Allows you to modify the color table, using a grammar noted below.\n");
  write("Options:\n");
  write("\t-h\tHelp, this usage message.\n");
  write(GRAMMAR);
}
                
/*
 * If the arg[0] is a base symbol, it can't be used
 * as a custom tag.
 *
 */
mixed * valid_tag_name(mixed * arg) {
  return !ANSI_D->query_base_symbol(arg[0]) ? arg : nil ;
}

mixed * valid_value(mixed * arg) {
  return (arg[0] == "NIL" || ANSI_D->query_any_symbol(arg[0])) ? arg : nil ;
}

mixed * wrap_assign(mixed * arg) {
  return ({ ([ arg[0] : (arg[2..] - ({ "+" })) ]) });
}

mixed * collect_map(mixed * arg) {
  int i, sz;
  mapping result;

  result = ([ ]);

  for(i = 0, sz = sizeof(arg); i < sz; i++) {
    if(mappingp(arg[i])) {
      result += arg[i];
    }
  }
  return ({ result });
}

void main(string str) {
  mixed * args;
  string error;
  string * symbols;
  string * values;
  int i, sz, pos;

  if (!str || str == "") {
     usage();
     return;
  }
  if (sscanf(str, "-%s",str)) {
     usage();
     return;
  }

  if( !require_priv( "system" ) ) {
    write("You must be admin to do that.");
    return;
  }

  str = uppercase(str);

  error = catch(args = parse_string(GRAMMAR, str));

  if(error) {
    if(sscanf(error,"Bad token at offset %d",pos) == 1) {
      write("Invalid character "+str[pos..pos]+".");
      return;
    } else {
      rethrow();
    }
  }
  if(!arrayp(args) || !mappingp(args[0])) {
    write("I didn't quite understand that.\n"+
          "Try something like 'colorsymbols SYMBOL = ATTRIBUTE + COLOR'\n"+
          "                or 'colorsymbols SYMBOL = COLOR, SYMBOL = COLOR'\n"+
          "Note that using predefined color names as SYMBOL is not allowed.");
  } else {
    symbols = map_indices(args[0]);

    for(i = 0, sz = sizeof(symbols); i < sz; i++ ) {
      if(args[0][symbols[i]][0] == "NIL") {
        ANSI_D->ansi_remove_color(symbols[i]);
      } else {
        ANSI_D->ansi_set_color(symbols[i], args[0][symbols[i]]);
      }
    }
  }
}


