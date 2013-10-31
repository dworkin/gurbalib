inherit "/std/modules/m_messages";
inherit "/sys/lib/modules/m_cmds";

#include <type.h>

static string *que;
static int time;
static int actionssize;
static string *actions;
static mapping item_commands;	/* Commands that are local to worn/wielded items. */

/* Add to the item command mapping */
void add_item_command(string command, object ob) {
   if (!item_commands)
      item_commands = ([]);
   item_commands[command] = ob;
}

void remove_item_command(string command) {
   if (!item_commands)
      item_commands = ([]);
   item_commands[command] = nil;
}

void do_game_command(string message) {
   mixed result;
   string cmd, arg, *path;
   int flag;
   object save_player;

   arg = "";

   save_player = this_player();
   set_this_player(this_object());

   catch {
      if (sscanf(message, "%s %s", cmd, arg) != 2) {
	 cmd = message;
      }

      if (arg == "me") {
	 arg = this_player()->query_id();
      }

      flag = 0;

      if(!this_player()->is_player()) {
         path = ({ "/cmds/monster/", "/cmds/player/" });
      } else {
         path = this_player()->query_path();
      }

      if (command(cmd, arg, path) != -1) {
         flag = 1;
      }

      if (!flag) {
	 /* Check for an item command */
	 int i;
	 string *item_cmds;

	 if (!item_commands)
	    item_commands = ([]);
	 item_cmds = map_indices(item_commands);
	 for (i = 0; i < sizeof(item_cmds); i++) {
	    if (item_cmds[i] == cmd) {
	       call_other(item_commands[item_cmds[i]], "do_" + cmd, arg);
	       flag = 1;
	    }
	 }
      }

      /* check for emotes */
      if (!flag) {
	 if (EMOTE_D->is_emote(cmd)) {
	    string *rules;
	    string rule;
	    object target;

	    rules = EMOTE_D->query_rules(cmd);

	    if (arg != "") {
	       target = this_environment()->present(arg);
	    } else {
	       target = nil;
	    }
	    if (target) {
	       /* We've found our target, check for the correct rule */
	       if (target->is_living()) {
		  /* We're looking for a LIV rule */
		  if (member_array("LIV", rules) != -1) {
		     rule = "LIV";
		  } else {
		     rule = "";
		  }
	       } else {
		  /* We're looking for a OBJ rule */
		  if (member_array("OBJ", rules) != -1) {
		     rule = "OBJ";
		  } else {
		     rule = "";
		  }
	       }
	    } else {
	       /* Or are we just looking for a string? */
	       if (member_array("STR", rules) != -1 && arg != "") {
		  rule = "STR";
	       } else {
		  rule = "";
	       }
	    }

	    if (rule == "LIV") {
	       targeted_action(EMOTE_D->query_emote(cmd, rule), target);
	    } else if (rule == "OBJ") {
	       simple_action(EMOTE_D->query_emote(cmd, rule), target);
	    } else if (rule == "STR") {
	       simple_action(EMOTE_D->query_emote(cmd, rule), arg);
	    } else {
	       if (member_array("", rules) != -1)
		  simple_action(EMOTE_D->query_emote(cmd, rule));
	       else
		  write("No such emote.\n");
	    }
	    flag = 1;
	 }
      }
   } : {
      set_this_player(save_player);
      rethrow();
   }

   set_this_player(save_player);
}

void do_respond() {
   do_game_command(que[0]);
   que = que[1..];
}

void respond(string message) {
   if (!que)
      que = ( { } );
   que += ( { message } );

   call_out("do_respond", random(3));
}

void do_action(void) {
   respond(actions[random(actionssize)]);
   call_out("do_action", time);
}

void set_actions(int t, string * act) {
   time = t;
   actions = act;
   actionssize = sizeof(actions);

   call_out("do_action", time);
}
