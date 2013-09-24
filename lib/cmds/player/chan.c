/* An interface to the channel daemon By Fudge */

inherit M_COMMAND;

#include <channel.h>

static void chan_cmd(string chan, string cmd);

void usage() {
   string *lines;

   lines = ({ "Usage: chan [-h] [CHANNEL </command>]" });
   lines += ({ "" });
   lines += ({ "List and or interact with channels.  Channels are basically " +
      "a way to group " });
   lines += ({ "chat both within the mud and also within the " +
      "greater mud community." });
   lines += ({ "If no CHANNEL is given list available channels." });
   lines += ({ "" });
   lines += ({ "Command can be: " });
   lines += ({ "\ton, off, list, hist, info" });

   if (query_wizard(this_player())) {
      lines += ({ "\tnew, delete, readonly, color, guild" });
   }

   if (query_admin(this_player())) {
      lines += ({ "\tadmin, wiz, imud, permanent" });
   }

   lines += ({ "You can also just use <channel> /command" });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t/on\tJoin a channel." });
   lines += ({ "\t/off\tLeave a channel." });
   lines += ({ "\t/history\tShow what has happened in a channel." });
   lines += ({ "\t/list\tShow who is in a channel." });

   if (query_wizard(this_player())) {
      lines += ({ "\t/new\tCreate a channel." });
      lines += ({ "\t/delete\tDelete the channel." });
      lines += ({ "\t/readonly\tToggle this channel as readonly." });
      lines += ({ "\t/color\tChange the color of the channel." });
      lines += ({ "\t/imud\tToggle this channel as an intermud channel ." });
      lines += ({ "\t/guild\tToggle this channel as a guild channel." });
   }

   if (query_admin(this_player())) {
      lines += ({ "\t/admin\tToggle this channel as an admin channel." });
      lines += ({ "\t/wiz\tToggle this channel as a wizard channel." });
      lines += ({ "\t/info\tDisplay info about a channel." });
      lines += ({ "\t/permanent\tToggle this channel as permanent." });
   }

   lines += ({ "Examples:" });
   lines += ({ "\tchan announce /join" });
   lines += ({ "\tchan announce /leave" });
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

static void list_channels(void) {
   string *channels, *schannels, *lines;
   mapping ichans;
   string line;
   int i, sz;

   channels = CHANNEL_D->query_channels();
   schannels = this_player()->query_channels();

   lines = ( { "%^BOLD%^%^CYAN%^Available channels: %^RESET%^" } );
   for (i = 0, sz = sizeof(channels); i < sz; i++) {
      line = channels[i] + "     \t";   /* very suss formatting */
      line += (member_array(channels[i], schannels) == -1) ?
         "%^RED%^OFF" : "%^GREEN%^ON";
      line += "%^RESET%^";
      lines += ( { line } );
   }

   if (query_wizard(this_player())) {
      ichans = IMUD_D->query_chanlist();
      channels = map_indices(ichans);

      lines += ( { } );
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

static void main(string str) {
   string chan, cmd;

   if (!str || (str == "")) {
      usage(); /* Change this to list channels you are a member of XXX */
      return;
   }
   if (sscanf(str, "-%s", str)) {
      usage();
      return;
   }

   if (sscanf(str, "%s %s", chan, cmd) != 2) {
      if ((str == "/list") || (str == "/who")) {
         list_channels();
         return;
      } else {
         chan = str;
         cmd = "/info";
      }
   }

   chan_cmd(chan, cmd);
}

static void chan_cmd(string chan, string cmd) {

   switch (cmd) {
      case "/join":
      case "/on":
	 CHANNEL_D->chan_join(chan, this_player());
	 break;
      case "/leave":
      case "/off":
	 CHANNEL_D->chan_leave(chan, this_player());
	 break;
      case "/new":
	 CHANNEL_D->chan_new(chan, ALL);
	 break;
      case "/admin":
	 CHANNEL_D->chan_set_flag(chan, ADMIN_ONLY);
	 break;
      case "/wiz":
	 CHANNEL_D->chan_set_flag(chan, WIZ_ONLY);
	 break;
      case "/readonly":
	 CHANNEL_D->chan_set_flag(chan, READ_ONLY);
	 break;
      case "/permanent":
	 CHANNEL_D->chan_make_permanent(chan);
	 break;
      case "":
      case "/who":
      case "/list":
	 CHANNEL_D->chan_who(chan);
	 break;
      case "/hist":
	 CHANNEL_D->show_history(chan);
	 break;
      case "/delete":
	 break;
      case "/info":
	 /*this_player()->message(CHANNEL_D->query_debug()); */
	 break;
      case "/help":
	 usage();
	 break;
      default:
	 if (strlen(cmd) > 8)
	    if (cmd[..5] == "/color") {
	       /* Let's change the color of the channel */
	       CHANNEL_D->chan_set_color(chan, cmd[7..]);
	       break;
	    } else if (cmd[..4] == "/imud") {
	       CHANNEL_D->chan_imud(chan, cmd[6..]);
	       break;
	    } else if (cmd[..5] == "/guild") {
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

	 CHANNEL_D->chan_say(chan, cmd);
	 return;
   }
}
