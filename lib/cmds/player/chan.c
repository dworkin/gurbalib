/* An interface to the channel daemon By Fudge */

inherit M_COMMAND;

#include <channel.h>

string *usage(void) {
   string *lines;

   lines = ({ "Usage: chan [-h] [cmd COMMAND CHANNEL | CHANNEL MSG]" });
   lines += ({ "" });
   lines += ({ "The chan command allows you to interact with channels." });
   lines += ({ "Channels are basically a way to group chat both within the " });
   lines += ({ "mud and also within the greater mud community." });
   lines += ({ "If no args are given list channels you are currently on." });
   lines += ({ "" });
   lines += ({ "Command can be: " });
   lines += ({ "\ton\tJoin a channel." });
   lines += ({ "\toff\tleave a channel." });
   lines += ({ "\thist\tDisplay history of a channel." });
   lines += ({ "\tinfo\tDisplay info on a channel." });
   lines += ({ "\tlist\tDisplay who is on a channel." });

   if (query_wizard(this_player())) {
      lines += ({ "\tnew\tCreate a channel." });
      lines += ({ "\tdelete\tDelete the channel." });
      lines += ({ "\tcolor COL\tChange the color of the channel to COL." });
   }

   if (query_admin(this_player())) {
      lines += ({ "\timud CHAN\tLink this channel to intermud channel CHAN." });
      lines += ({ "\tguild GUILD\tSet channel to be a guild channel GUILD." });
      lines += ({ "\tadmin\tSet this channel as an admin only channel." });
      lines += ({ "\twiz\tSet this channel as a wizard only channel." });
      lines += ({ "\topen\tSet this channel as an open channel." });
      lines += ({ "\treadonly\tToggle this channel as readonly." });
      lines += ({ "\tpermanent\tToggle this channel as permanent." });
   }

   lines += ({ "If MSG starts with one of the following symbols it is " });
   lines += ({ "considered an emote: ':', '!', ';' " });
   lines += ({ "If you want your message to start with : use :: instead." });

   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "Examples:" });
   lines += ({ "\tchan cmd off announce" });
   lines += ({ "\tchan cmd on announce" });
   lines += ({ "\tchan announce hi all!" });
   lines += ({ "\tchan gossip :woo" });
   lines += ({ "\tchan gossip ::woo" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "bug");
   add_also("player", "emote");
   add_also("player", "rsay");
   add_also("player", "say");
   add_also("player", "shout");
   add_also("player", "tell");
   add_also("player", "whisper");
   add_also("player", "wizcall");

   add_also("wiz", "echoto");
   add_also("wiz", "ssay");
   add_also("wiz", "sysmsg");
   add_also("wiz", "translate");
   add_also("wiz", "wizlog");

   add_also("admin", "wall");
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

   this_player()->more(lines, 1);
}

static void chan_cmd(string cmd, string chan) {
   string rest, *args;

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
         write("Channel " + chan + " set to admin only access.\n");
         break;
      case "wiz":
         CHANNEL_D->chan_set_flag(chan, WIZ_ONLY);
         write("Channel " + chan + " set to wizard only access.\n");
         break;
      case "open":
         CHANNEL_D->chan_set_flag(chan, ALL);
         write("Channel " + chan + " set to open access.\n");
         break;
      case "readonly":
         CHANNEL_D->chan_set_flag(chan, READ_ONLY);
         write("Channel " + chan + " set to read only access.\n");
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
         CHANNEL_D->chan_delete(chan);
         break;
      case "info":
         CHANNEL_D->show_info(chan);
         break;
      case "help":
         this_player()->more(usage());
         break;
      case "color":
         args = explode(chan, " ");
         if (sizeof(args) < 2) {
            this_player()->more(usage());
            return;
         }
         write("Old color for channel " + args[1] + ": " + 
            CHANNEL_D->chan_query_color(args[1]) + "\n");
            CHANNEL_D->chan_set_color(args[1], args[0]);
         write("New color for channel " + args[1] + ": " + 
            CHANNEL_D->chan_query_color(args[1]) + "\n");
         break;
      case "imud":
         args = explode(chan, " ");
         CHANNEL_D->chan_imud(args[1], args[0]);
         write("Associating channel: " + args[0] + " with imud channel: " +
            args[1] + "\n");
         break;
      case "guild":
         args = explode(chan, " ");
         if (sizeof(args) < 2) {
            this_player()->more(usage());
            return;
         }
         write("Old guild for channel " + args[1] + ": " + 
            CHANNEL_D->chan_query_guild(args[1]) + "\n");
            CHANNEL_D->chan_set_guild(args[1], args[0]);
         break;
      default:
         write("Invalid command " + cmd + "\n");
         this_player()->more(usage());
         break;
   }
}

static void main(string str) {
   string chan, cmd, rest;

   if (!alsos) {
      setup_alsos();
   }

   if (empty_str(str)) {
      list_channels(1);
      return;
   }

   if (sscanf(str, "-%s", str)) {
      this_player()->more(usage());
      return;
   }

   if (sscanf(str, "%s %s", cmd, chan) != 2) {
      this_player()->more(usage());
      return;
   }

   if (cmd == "cmd") {
      if ((chan == "list") || (chan == "who")) {
         list_channels(0);
         return;
      } else if (sscanf(chan, "%s %s", cmd, rest) < 2) {
         this_player()->more(usage());
         return;
      }
  
      chan_cmd(cmd, rest);
   } else {
      if (sscanf(str, "%s %s", chan, rest) == 2) {
         if ((rest[0] == ';') || (rest[0] == ':') || (rest[0] == '!')) {
            if (rest[1] != rest[0]) {
               CHANNEL_D->chan_emote(chan, rest[1..]);
               return;
            } else {
               rest = rest[1..];
            }
         }
         CHANNEL_D->chan_say(chan, rest);
      } else {
         this_player()->more(usage());
      }
   }
}
