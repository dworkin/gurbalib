/* An interface to the channel daemon By Fudge */

inherit M_COMMAND;

#include <channel.h>

static void chan_cmd(string chan, string cmd);

void usage() {
   string *lines;

   lines = ({ "Usage: chan [-h] [COMMAND CHANNEL | CHANNEL MSG]" });
   lines += ({ "" });
   lines += ({ "The chan command allows you to interact with channels." });
   lines += ({ "Channels are basically a way to group chat both within the " });
   lines += ({ "mud and also within the greater mud community." });
   lines += ({ "If no args are given list channels you are currently on." });
   lines += ({ "" });
   lines += ({ "Command can be: " });
   lines += ({ "\ton\tJoin a channel" });
   lines += ({ "\toff\tleave a channel" });
   lines += ({ "\thist\tDisplay history of a channel" });
   lines += ({ "\tinfo\tDisplay info on a channel" });
   lines += ({ "\tlist\tDisplay who is on a channel" });

   if (query_wizard(this_player())) {
      lines += ({ "\tnew\tCreate a channel." });
      lines += ({ "\tdelete\tDelete the channel." });
      lines += ({ "\treadonly\tToggle this channel as readonly." });
      lines += ({ "\tcolor\tChange the color of the channel." });
      lines += ({ "\timud\tToggle this channel as an intermud channel ." });
      lines += ({ "\tguild\tToggle this channel as a guild channel." });
   }

   if (query_admin(this_player())) {
      lines += ({ "\tadmin\tToggle this channel as an admin channel." });
      lines += ({ "\twiz\tToggle this channel as a wizard channel." });
      lines += ({ "\tinfo\tDisplay info about a channel." });
      lines += ({ "\tpermanent\tToggle this channel as permanent." });
   }

   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "" });

   lines += ({ "Examples:" });
   lines += ({ "\tchan join announce" });
   lines += ({ "\tchan leave announce" });
   lines += ({ "\tchan announce hi all!" });
   lines += ({ "" });
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tbug, echo, echoto, emote, rsay, shout, ssay, say, " +
         "sysmsg, tell, translate, whisper, wizcall" });
   } else {
      lines += ({ "\tbug, emote, rsay, say, shout, tell, whisper, " +
         "wizcall" });
   }

   this_player()->more(lines);
}

static void list_channels(int x) {
   string *channels, *schannels, *lines;
   mapping ichans;
   string line;
   int i, sz;

   channels = CHANNEL_D->query_channels();
   schannels = this_player()->query_channels();

   if (x) {
      lines = ( { "%^BOLD%^%^CYAN%^Channels your on: %^RESET%^" } );
   } else {
      lines = ( { "%^BOLD%^%^CYAN%^Available channels: %^RESET%^" } );
   }

   for (i = 0, sz = sizeof(channels); i < sz; i++) {
      if (member_array(channels[i], schannels) == -1) {
         if (!x) {
            line = channels[i] + "     \t";
            line += "%^RED%^OFF%^RESET%^";
            lines += ({ line });
         }
      } else {
         line = channels[i] + "     \t";
         line += "%^GREEN%^ON%^RESET%^";
         lines += ( { line } );
      }
   }

   /* XXX Need to check for x and only display if your a member */
   if (query_wizard(this_player())) {
      ichans = IMUD_D->query_chanlist();
      channels = map_indices(ichans);

      lines += ( { "" } );
      lines += ( { "IMud channels" } );
      lines += ( { "--------------" } );
      for (i = 0; i < sizeof(channels); i++) {
         if ((ichans[channels[i]][0]) && (ichans[channels[i]][0] != -1)) {
            lines += ( { channels[i] + ", " + ichans[channels[i]][0] } );
         }
      }
   }

   this_player()->more(lines,1);
}

static void chan_cmd(string cmd, string chan) {

   switch (cmd) {
      case "join":
      case "on":
	 CHANNEL_D->chan_join(chan, this_player());
	 break;
      case "leave":
      case "off":
	 CHANNEL_D->chan_leave(chan, this_player());
	 break;
      case "new":
	 CHANNEL_D->chan_new(chan, ALL);
	 break;
      case "admin":
	 CHANNEL_D->chan_set_flag(chan, ADMIN_ONLY);
	 break;
      case "wiz":
	 CHANNEL_D->chan_set_flag(chan, WIZ_ONLY);
	 break;
      case "readonly":
	 CHANNEL_D->chan_set_flag(chan, READ_ONLY);
	 break;
      case "permanent":
	 CHANNEL_D->chan_make_permanent(chan);
	 break;
      case "":
      case "who":
      case "list":
	 CHANNEL_D->chan_who(chan);
	 break;
      case "hist":
      case "history":
	 CHANNEL_D->show_history(chan);
	 break;
      case "delete":
	 break;
      case "info":
         CHANNEL_D->show_info(chan);
	 break;
      case "help":
	 usage();
	 break;
/* THESE Need FIXING XXXX */
      case "color":
         CHANNEL_D->chan_set_color(chan, cmd[7..]);
         break;
      case "imud":
	 CHANNEL_D->chan_imud(chan, cmd[6..]);
         break;
      case "guild":
	 CHANNEL_D->chan_set_guild(chan, cmd[6..]);
         break;
      default:
	 CHANNEL_D->chan_say(cmd, chan);
	 return;

/* old stuff that needs converting yet...
      default:
	 if (strlen(cmd) > 8)
	    if (cmd[..5] == "color") {
	       CHANNEL_D->chan_set_color(chan, cmd[7..]);
	       break;
	    } else if (cmd[..4] == "imud") {
	       CHANNEL_D->chan_imud(chan, cmd[6..]);
	       break;
	    } else if (cmd[..5] == "guild") {
	       CHANNEL_D->chan_set_guild(chan, cmd[7..]);
	       break;
	    }
	 if ((cmd[0] == ';') || (cmd[0] == ':') || (cmd[0] == '!')) {
	    if (cmd[1] != cmd[0]) {
	       CHANNEL_D->chan_emote(chan, cmd[1..]);
	       break;
	    } else {
	       cmd = cmd[1..];
	    }
	 }
*/
   }
}

static void main(string str) {
   string chan, cmd;

   if (empty_str(str)) {
      list_channels(1);
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }
   if (str == "list" || str == "who") {
      list_channels(0);
      return;
   }

   if (sscanf(str, "%s %s", cmd, chan) != 2) {
      usage();
      return;
   }

   chan_cmd(cmd, chan);
}
