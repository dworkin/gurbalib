inherit M_COMMAND;

string parse_error;

string *usage(void) {
   string mode, *lines;

   if (this_player()->query_mxp() == 1) {
      mode = "on";
   } else {
      mode = "off";
   }

   lines = ({ "Usage: ansi[-h] [on|off]" });
   lines += ({ "" });
   lines += ({ "Used to turn on or off mxp support and show the settings." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\ton\tTurn on MXP support." });
   lines += ({ "\toff\tTurn off MXP support." });
   lines += ({ "Examples:" });
   lines += ({ "\tmxp on" });

   lines += get_alsos();

   lines += ({ "" });
   lines += ({ "You currently have mxp mode: " + mode });

   return lines;
}

setup_alsos() {
   add_also("player", "alias");
   add_also("player", "clear");
   add_also("player", "describe");
   add_also("player", "ignore");
   add_also("player", "passwd");
   add_also("player", "ansi");

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
      this_player()->set_mxp(1);
      out("%^MXP_LSM%^<!-- Elements to support the Automapper --><!ELEMENT RName FLAG=\"RoomName\"><!ELEMENT RDesc FLAG=\'RoomDesc\'><!ELEMENT RExits  FLAG=\'RoomExit\'><!-- The next element is used to define a room exit link that sends the exit direction to the MUD if the user clicks on it --><!ELEMENT Ex \'<SEND>\'><!ELEMENT Announce \'<FONT COLOR=Cyan>\' OPEN><!ELEMENT Gossip \'<FONT COLOR=Green>\' OPEN><!-- the next elements deal with the MUD prompt --><!ELEMENT Prompt FLAG=\"Prompt\"><!ELEMENT Hp FLAG=\"Set hp\"><!ELEMENT MaxHp FLAG=\"Set maxhp\"><!ELEMENT Mana FLAG=\"Set mana\"><!ELEMENT MaxMana FLAG=\"Set maxmana\"><!ELEMENT End FLAG=\"Set end\"><!ELEMENT MaxEnd FLAG=\"Set maxend\"><!ELEMENT RoomX FLAG=\"Set room_x\"><!ELEMENT RoomY FLAG=\"Set room_y\"><!ELEMENT RoomZ FLAG=\"Set room_Z\"><!EL Itm \'<send \"look &text;|drop &text;|wear &text;|wield &text;|drink &text;|unwield &text;|remove &text;\">\'><!EL Click \'<send \"&text;\">\'><!EL ClickP \'<send \"&text;\" PROMPT>\'>%^MXP_LLM%^Turning on MXP...\n");

      return;
   } else if ((str == "off") || (str == "Off") || (str == "0")) {
      this_player()->set_mxp(0);
      out("Turning off MXP.\n");
      return;
   }
}

