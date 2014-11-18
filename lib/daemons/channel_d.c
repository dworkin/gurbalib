#include <channel.h>

#define NOT_EMOTE   0
#define EMOTE       (!NOT_EMOTE)
#define DATA_VERSION 2
#define DATAFILE "/daemons/data/channel_d.o"

inherit "/std/modules/m_messages";

mapping permanent, colors, imud, guilds, history;
int data_version;
static mapping channels;
static mapping listeners;

void resubscribe(void) {
#ifndef DISABLE_IMUD
   IMUD_D->subscribe_event("i3_connection");
#endif
}

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);
}

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

void create(void) {
   string *chans;
   int i, sz;

   channels = ([]);
   listeners = ([]);
   history = ([]);
   imud = ([]);
   colors = ([]);
   permanent = ([]);
   guilds = ([]);

   if (file_exists(DATAFILE)) {
      restore_me();
   } else {

      permanent = (["admin": 3, "announce": 4, "dchat": 2, "dgd": 2, "dstest": 2, "fighter": 1, "gossip": 1, "icode": 2, "igossip": 2, "wiz":2,]);
      colors = (["admin": "%^BLUE%^", "announce": "%^CYAN%^", "dchat": "%^CYAN%^", "dgd": "%^BLUE%^", "fighter": "%^BLUE%^", "gossip": "%^GREEN%^", "icode": "%^RED%^", "igossip": "%^GREEN%^", "imud_code": "%^YELLOW%^", "imud_gossip": "%^GREEN%^", "inews": "%^RED%^", "wiz":"%^RED%^"]);
      imud = (["dchat": "dchat", "dgd": "dgd", "imud_code": "icode", "imud_dgd": "idgd", "imud_gossip": "igossip", "inews":"inews"]);
      guilds = (["fighter":"fighter"]);
      save_me();
   }

   chans = map_indices(permanent);

   for (i = 0, sz = sizeof(chans); i < sz; i++) {
      channels[chans[i]] = permanent[chans[i]];
   }

   EVENT_D->subscribe_event("player_login");
   EVENT_D->subscribe_event("player_logout");
   EVENT_D->subscribe_event("player_linkdeath");
   EVENT_D->subscribe_event("player_unlinkdeath");
   EVENT_D->subscribe_event("new_player");
   resubscribe();
}

void chan_set_flag(string chan, int flag) {
   if (query_admin(this_player()->query_name()) != 1) {
      write("Access denied.\n");
      return;
   }
   channels[chan] = flag;
   if (permanent[chan]) {
      permanent[chan] = channels[chan];
   }

   save_me();
}

void chan_make_permanent(string name) {
   if (query_admin(this_player()->query_name()) != 1) {
      write("Access denied.\n");
      return;
   }

   if (permanent[name] == channels[name]) {
      permanent[name] = nil;
      write("Channel " + name + " is no longer permanent.\n");
   } else {
      permanent[name] = channels[name];
      write("Channel " + name + " is now permanent.\n");
   }
   save_me();
}

void chan_imud(string chan, string name) {
   if (query_admin(this_player()->query_name()) != 1) {
      write("Access denied.\n");
      return;
   }

   if (!channels[chan]) {
      write("Channel doesn't exist.\n");
      return;
   }

   if (imud[name] == chan) {
      imud[name] = nil;
/* XXX do more here... */
   } else {
      imud[name] = chan;
      chan_make_permanent(chan);
   }
   save_me();
}

int chan_new(string name, int flags) {

   name = lowercase(name);

   if (query_wizard(this_player()->query_name()) != 1) {
      write("Access denied.\n");
      return 0;
   }

   if (channels[name]) {
      write("Channel already exists.\n");
      return 0;
   }
   channels[name] = flags;
   write("Channel created.\n");

   return 1;
}

int chan_join(string chan, object ob) {

   chan = lowercase(chan);

   if (!channels[chan]) {
      write("No such channel.");
      return 0;
   }

   if (channels[chan] < READ_ONLY) {
      /* XXX need to rethink this */
      if (query_user_type(ob->query_name()) < channels[chan] - 1) {
         write("No such channel.\n");
         return 0;
      }
   }

   if (guilds[chan]) {
      if (!ob->guild_member(guilds[chan])) {
         write("No such channel.\n");
         return 0;
      }
   }

   if (!listeners[chan]) {
      listeners[chan] = ({ });
   } else {
      listeners[chan] -= ({ ob });
   }
   listeners[chan] += ({ ob });
   write("Subscribed to " + chan + ".\n");

   this_player()->add_channel(chan);

   ob->save_me();
   return 1;
}

int chan_leave(string chan, object ob) {

   chan = lowercase(chan);

   if (!channels[chan]) {
      write("No such channel.");
      return 0;
   }

   if (listeners[chan]) {
      listeners[chan] -= ( {
         ob}
      );
   }
   write("No longer subscribed to " + chan + ".\n");
   this_player()->remove_channel(chan);

   return 1;
}

void chan_who(string chan) {
   object *users;
   int i, sz;

   chan = lowercase(chan);

   users = listeners[chan];
   if (users) {
      sz = sizeof(users);
   }

   if (!users || sz < 1) {
      write("No subscribers.");
      return;
   }

   write("Subscribed to " + chan + ":\n");

   for (i = 0; i < sz; i++) {
      if (users[i]) {
         write("  " + users[i]->query_Name() + "\n");
      }
   }
}

void add_history(string channel, string who, string message) {
   int i, sz;
   string *temp;

   if (empty_str(channel)) {
      return;
   }
   if (empty_str(message)) {
      return;
   }

   temp = history[channel];
   if (!temp) {
      temp = ({ });
   }
   if (sizeof(temp) >= MAX_HIST_SIZE) {
      temp = temp[sizeof(temp) - (MAX_HIST_SIZE - 1)..sizeof(temp) - 1];
   }

   temp += ({ "%^CHAN_DATE%^[" + (ctime(time()) [4..18]) + "]%^RESET%^" +
      "[%^CHAN_USER%^" + who + "]%^RESET%^ " +
      "%^CHAN_TEXT%^" + message + "%^RESET%^" });

   history[channel] = nil;
   history += ([channel:temp]);

   return;
}

string get_history(string channel) {
   int i, sz;
   string out;

   out = "";
   if (catch(sz = sizeof(history[channel]))) {
      return out;
   }

   for (i = 0; i < sz; ++i) {
      out += "%^CHAN_NAME%^" + (colors[channel] ? colors[channel] : "");
      out += "[" + channel + "]%^RESET%^" + history[channel][i] + "%^RESET%^\n";
   }

   return out;
}

void show_history(string channel) {
   this_player()->message(get_history(channel), 1);
}

int get_num_listeners(string channel) {
   object *users;
   int x;

   users = listeners[channel];

   if (users) {
      users -= ({ nil });
      x = sizeof(users);
      return x;
   }

   return 0;
}

void show_info(string channel) {
   string value;
   int x;

   this_player()->message("Channel: " + channel + "\n");
   x = get_num_listeners(channel);
   this_player()->message("Members: " + x + "\n");

   if (imud[channel] == channel) {
      value = "yes";
   } else {
      value = "no";
   }
   this_player()->message("Imud: " + value + "\n");

   if (permanent[channel] == channel) {
      value = "yes";
   } else {
      value = "no";
   }
   this_player()->message("Permanent: " + value + "\n");

   if (guilds[channel]) {
      this_player()->message("Guild restrictions: " + guilds[channel] + "\n");
   } else {
      this_player()->message("Guild restrictions: no, open\n");
   }

   if (channels[channel] == READ_ONLY) {
      this_player()->message("Access level: Read only\n");
   } else if (channels[channel] == ADMIN_ONLY) {
      this_player()->message("Access level: Admin only\n");
   } else if (channels[channel] == WIZ_ONLY) {
      this_player()->message("Access level: Wizard only\n");
   } else {
      this_player()->message("Access level: open\n");
   }
}

void chan_send_string(string chan, string from, string str,
   varargs int is_emote) {
   object *users;
   string line;
   int i, sz;

   line = "%^CHAN_NAME%^";
   line += colors[chan] ? colors[chan] : "";
   line += "[" + chan + "]%^RESET%^ ";
   if (!is_emote) {
      line += "%^CHAN_USER%^" + capitalize(from) + "%^RESET%^: ";
   }
   line += "%^CHAN_TEXT%^" + str + "%^RESET%^";
   users = listeners[chan];

   if (users) {
      users -= ({ nil });
      for (i = 0, sz = sizeof(users); i < sz; i++) {
         if (!users[i]->query_ignored(from)) {
            users[i]->message(
               (users[i]->query_env("imud_timestamp") ? "%^CHAN_DATE%^[" +
               (ctime(time())[11..18]) + "]%^RESET%^" : "") + line, 1);
         }
      }
   }

   add_history(chan, from, str);
}

void chan_imud_rcv_targeted(string chan, string who, string where,
   string target, string targetmud, string what) {

   if (!imud[chan]) {
      return;
   }

   what = replace_string(what, "$O", target + "@" + targetmud);
   what = replace_string(what, "$N", who + "@" + where);
   chan_send_string(imud[chan], who + "@" + where, what, NOT_EMOTE);
}

void chan_imud_rcv_emote(string chan, string who, string where, string what) {

   if (!imud[chan]) {
      return;
   }
   what = replace_string(what, "$N", who + "@" + where);
   chan_send_string(imud[chan], who + "@" + where, what, EMOTE);
}

void chan_imud_rcv_say(string chan, string who, string where, string what) {

   if (!imud[chan]) {
      return;
   }

   chan_send_string(imud[chan], who + "@" + where, what, NOT_EMOTE);
}

int query_subscribed(string chan) {
   chan = lowercase(chan);
   if (listeners[chan]) {
      if (member_array(this_player(), listeners[chan]) != -1) {
         return 1;
      }
   }
   return 0;
}

void chan_emote(string chan, string what) {
   string *ichans, *result;
   int i, sz;
   string cmd, arg;

   if (!query_subscribed(chan)) {
      write("Not subscribed to channel " + chan + ".\n");
      return;
   }

   if (channels[chan] == READ_ONLY) {
      write(chan + " is read only.");
      return;
   }

   if (!what || what == "") {
      return;
   }

   if (sscanf(what, "%s %s", cmd, arg) != 2) {
      cmd = what;
   }

   if (EMOTE_D->is_emote(cmd)) {
      string rule, *rules;
      object target;

      rules = EMOTE_D->query_rules(cmd);

      /* Targeted emote? Find the target */
      if (arg && arg != "") {
         target = this_environment()->present(arg);
         if (!target) {
            target = USER_D->find_player(arg);
         }

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
         result =
            compose_message(this_player(), EMOTE_D->query_emote(cmd, rule),
            target, nil);
         what = result[2];
      } else if (rule == "OBJ") {
         result =
            compose_message(this_player(), EMOTE_D->query_emote(cmd, rule),
            nil, ({ target }));
         what = result[2];
      } else if (rule == "STR") {
         result =
            compose_message(this_player(), EMOTE_D->query_emote(cmd, rule),
            nil, ({ arg }));
         what = result[2];
      } else {
         if (member_array("", rules) != -1) {
            result =
               compose_message(this_player(), EMOTE_D->query_emote(cmd, rule),
               nil, nil);
            what = result[2];
         } else
            write("No such emote.\n");
      }
   } else {
      if (arg && arg != "")
         what = this_player()->query_Name() + " " + cmd + " " + arg;
      else
         what = this_player()->query_Name() + " " + cmd;
   }

   ichans = map_indices(imud);
   for (i = 0, sz = sizeof(ichans); i < sz; i++) {
      if (imud[ichans[i]] == chan) {

         what = replace_string(what, this_player()->query_Name(), "$N");

         /* Found an intermud channel */
         IMUD_D->do_channel_e(ichans[i], what);
         return;
      }
   }

   chan_send_string(chan, this_player()->query_name(), what, EMOTE);
}

void chan_say(string chan, string what) {
   string *ichans;
   int i, sz;

   if (!query_subscribed(chan)) {
      write("Not subscribed to channel " + chan + ".\n");
      return;
   }

   if (channels[chan] == READ_ONLY) {
      write(chan + " is read only.");
      return;
   }

   if (!what || what == "") {
      return;
   }

   ichans = map_indices(imud);
   for (i = 0, sz = sizeof(ichans); i < sz; i++) {
      if (imud[ichans[i]] == chan) {
         /* Found an intermud channel */
         IMUD_D->do_channel_m(ichans[i], what);
         return;
      }
   }

   chan_send_string(chan, this_player()->query_name(), what, NOT_EMOTE);
}

void chan_set_color(string chan, string col) {
   if (query_admin(this_player()->query_name()) != 1) {
      write("Access denied.\n");
      return;
   }

   colors[chan] = "%^" + uppercase(col) + "%^";
   write(chan + " is now " + col + "\n");
   save_me();
}

void chan_set_guild(string chan, string guild) {
   if (query_admin(this_player()->query_name()) != 1) {
      write("Access denied.\n");
      return;
   }

   if (guilds[chan] == guild) {
      guilds[chan] == nil;
      write(chan + " is no longer a " + guild + " guild only channel.\n");
   } else {
      guilds[chan] = guild;
      write(chan + " is now a " + guild + " guild only channel.\n");
   }
   save_me();
}

int query_priv(string chan) {
   return (channels[chan] - 1);
}

int query_channel(string chan) {

   if (channels[chan]) {
      if (channels[chan] == READ_ONLY)
         return 1;
      if (guilds[chan]) {
         /* Guild channel */
         if (query_user_type(this_player()->query_name()) > 0) {
            /* A wiz can subscribe to all channels */
            return 1;
         } else {
            return (this_player()->guild_member(guilds[chan]));
         }
      }
      if (query_user_type(this_player()->query_name()) >= channels[chan] - 1) {
         return 1;
      } else {
         return 0;
      }
   } else {
      return 0;
   }
}

string *query_channels(void) {
   return map_indices(channels);
}

void event_new_player(string * args) {
   if (channels["announce"]) {
      chan_send_string("announce", "channel_d",
         "Trumpets sound as " + capitalize(args[0]) + " joins the realm.",
         NOT_EMOTE);
   }
}

void event_player_login(string * args) {
   if (channels["announce"]) {
      chan_send_string("announce", "channel_d",
         capitalize(args[0]) + " logs in.", NOT_EMOTE);
   }
}

void event_player_logout(string * args) {
   if (channels["announce"]) {
      chan_send_string("announce", "channel_d",
         capitalize(args[0]) + " logs out.", NOT_EMOTE);
   }
}

void event_player_linkdeath(string * args) {
   if (channels["announce"]) {
      chan_send_string("announce", "", capitalize(args[0]) +
         " goes link-dead.", EMOTE);
   }
}

void event_player_unlinkdeath(string * args) {
   if (channels["announce"]) {
      chan_send_string("announce", "", capitalize(args[0]) +
         " returns from link-death.", EMOTE);
   }
}

void event_player_join(string * args) {
   if (channels["announce"]) {
      chan_send_string("announce", "channel_d",
         "Trumpets blast a fanfare as " + capitalize(args[0]) + " joins " +
         args[1] + "!", NOT_EMOTE);
   }
}

void event_i3_connection(string * args) {
   if (!channels["announce"]) {
      return;
   }

   chan_send_string("announce", "imud_d", args[0], NOT_EMOTE);
}

void upgraded(void) {
   if (data_version == DATA_VERSION) {
      return;
   }

   resubscribe();
   data_version = DATA_VERSION;
}
