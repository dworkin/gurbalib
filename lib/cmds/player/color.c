XXX merge with ansi command....

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

string parse_error;
                
/*
 * If the arg[0] is a base symbol, it can't be used
 * as a custom tag.
 *
 */
mixed * valid_tag_name(mixed * arg) {
  if(ANSI_D->query_custom_symbol(arg[0])) {
    return arg;
  } else {
    parse_error = "Invalid tag: "+arg[0];
    return nil;
  }
}

mixed * valid_value(mixed * arg) {
  if(arg[0] == "NIL" || ANSI_D->query_any_symbol(arg[0])) {
    return  arg;
  } else {
    parse_error = "Invalid value: "+arg[0];
    return nil;
  } 
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

  str = uppercase(str);

  parse_error = nil;
  error = catch(args = parse_string(GRAMMAR, str));

  if(parse_error) {
    write(parse_error);
  } else {
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
          "Try something like 'color symbol = ATTRIBUTE + COLOR'\n"+
          "                or 'color symbol = COLOR, symbol = COLOR'\n"+
          "Note that using predefined color names as symbol is not allowed\n"+
          "but using symbols as colors is allowed, ie\n"+
          " 'color room_desc = room_exit' will work\n\n"+
          "Valid color and symbol names:\n\n");
      "/cmds/player/ansi"->main("show");
    } else {
      symbols = map_indices(args[0]);

      for(i = 0, sz = sizeof(symbols); i < sz; i++ ) {
        /* special case, 'NIL' tag means remove this symbol.
         * also note this is a string, not the nil value */
        if(args[0][symbols[i]][0] == "NIL") {
          this_player()->set_custom_color(symbols[i], nil);
        } else {
          this_player()->set_custom_color(symbols[i], args[0][symbols[i]]);
        }
      }
    }
  }
}
