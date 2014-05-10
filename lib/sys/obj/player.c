/* Player object. By Fudge */

#include <channel.h>
#include <type.h>
#include <limits.h>

inherit con "/std/container";
inherit bod "/std/body";
inherit "/sys/lib/runas";
inherit "/std/modules/m_messages";
inherit "/sys/lib/editor";
inherit "/std/modules/m_autoload_string";
inherit "/std/modules/m_language";
inherit "/std/body/skills";
inherit cmd M_CMDS;

static object user;		/* This players user object */
static string input_to_func;	/* The function we're redirecting input to */
static mixed input_to_arg;      /* Optional extra argument(s) to the function 
                                   we're redirecting input to */
static object input_to_obj;	/* The object we're redirecting input to */
static int linkdead;		/* Are we linkdead? */
static int quitting;		/* Are we in the process of quitting? */
static int timestamp;		/* Last time we got input */
static int more_line_num;	/* How far in the file we're more'ing are we */
static object more_caller;	/* Who called more in us 
					(so we can call it back when done */
static string *more_lines;	/* All the lines in the file we're more'ing */
string last_tell;		/* Who did we get a tell from last? */
static int color_more;		/* Flag to specify color more */

string real_name;		/* This players real name */
string email_address;		/* The email address */
string website;			/* Players webpage */
mapping environment_variables;	/* The environment variables of the player */
string title;			/* The title */
string password;		/* The password */
string *cmd_path;		/* The path which is searched for commands */
string *channels;		/* Channels we're listening to */
string *ignored;		/* the users we are ignoring */
mapping alias;			/* The players aliases */
int last_login;			/* The last login */
mapping guilds;			/* The guilds the player is a member of. 
					The values are the guild title. */
mapping custom_colors;		/* custom color symbols for this player */
static mixed menu_data;		/* temp storage for menu system */
int muzzle;			/* if 0 we are allowed to shout. */

void set_env(string name, mixed value);
mixed query_env(string name);
string query_title(void);
string query_name(void);

void create(void) {
   con::create();
   bod::create();
   cmd::create();

   living_name = "guest";
   channels = ( { "gossip", "announce" } );
   ignored = ( { } );
   title = "$N the nondescript";
   long_desc = "";
   set_short("A nondescript player");
   timestamp = time();
   set_env("cwd", "/");
   set_env("pwd", "/");
   set_env("width", "78");
   set_env("height", "23");

   custom_colors = ([]);
   level = 1;
}

/* Save the player */
void save_me(void) {
   if (living_name != "guest") {
      unguarded("save_object", "/data/players/" + living_name + ".o");
   }
}

void restore_privs() {
   string privs;

   if (user) {
      privs = "game:" + user->_Q_cpriv();
   } else {
      privs = "game:nobody";
   }

   run_as(privs);
}

/* Restore the player */
void restore_me(void) {
   if (!unguarded("restore_object", "/data/players/" + living_name + ".o")) {
      write("Error while restoring \"/data/players/" + living_name + ".o");
      write("Please notify the administration.");
      return;
   }

   set_id(living_name);
   if (!alias)
      alias = ([]);
   if (cmd_path) {
      int i, sz;
      /* convert cmd_path */
      for(i = 0, sz = sizeof( cmd_path ); i < sz; i++) {
         if(cmd_path[i] == "/kernel/cmds/admin") { 
            cmd_path[i] = "/sys/cmds/admin";
         } else if(cmd_path[i] == "/cmds/wiz") {
            cmd_path[i] = "/sys/cmds/wiz";
         }
      }
      cmd::set_cmd_path( cmd_path );
      cmd_path = nil;
      call_out( "save_me", 0 );
   }
}

void login_player(void) {
   int i, is_new_player;
   string *didlog, *tmpchannels;
   mixed autoload;
   string race;

   restore_privs();

   /* If we're a wiz, show the didlog since last login */
   if (query_user_type(living_name) > 0) {
      didlog = DID_D->get_entries(last_login);

      if (didlog) {
	 for (i = 0; i < sizeof(didlog); i++) {
	    if (didlog[i] == "")
	       write("\n");
	    else
	       write(didlog[i]);
	 }
      }
   }
	is_new_player = !last_login;
   if (is_new_player) {
      EVENT_D->event("new_player", living_name);
      last_login = time();
   } else {
      last_login = time();
      EVENT_D->event("player_login", living_name);
   }

   /* Set the current working directory */
   if (!query_env("cwd")) {
      set_env("cwd", "/");
   }

   /* Subscribe to default channels */
   if (!channels) {
      channels = ( { } );
   }

   tmpchannels = channels;
   channels = ( { } );
   /* Register with the subscribed channels */
   for (i = 0; i < sizeof(tmpchannels); i++) {
      if (CHANNEL_D->query_channel(tmpchannels[i])) {
	 if (!CHANNEL_D->chan_join(tmpchannels[i], this_player())) {
            write("Error joining channel: " + tmpchannels[i] + "\n");
         }
      } else {
         write("Error no such channel: " + tmpchannels[i] + "\n");
	 tmpchannels[i] = nil;
      }
   }
  	race = query_race();
  	set_race(race, is_new_player);
	if (is_new_player) {
  		set_hit_skill("combat/unarmed");
	}
   set_short(query_title());
   ANSI_D->set_player_translations(custom_colors);
   autoload = query_env("autoload");
   if (autoload == nil) {
      autoload = 0;
   } else if (autoload == 1) {
      this_player()->clone_autoload_objects();
   }
}

int query_last_login(void) {
   return last_login;
}

void set_last_tell(string who) {
   last_tell = who;
}

string query_last_tell(void) {
   return last_tell;
}

int is_player(void) {
   return 1;
}

void set_env(string name, mixed value) {
   if (!environment_variables) {
      environment_variables = ([]);
   }
   if(name == "PATH") {
      /* we always require the wiz cmdpath so set remains available for changing the path again */
      if(sizeof(explode(value,":") & ({ "$PATH", "/sys/cmds/wiz", "/sys/cmds/wiz/" }) ) >= 1) {
         cmd::set_searchpath(value);
      }
   } else {
      environment_variables[name] = value;
   }
   if (living_name) save_me();
}

mixed query_env(string name) {
   if (!environment_variables) {
      environment_variables = ([]);
   }
   if(name == "PATH") {
      return cmd::query_searchpath();
   }
   return environment_variables[name];
}

string *query_env_indices(void) {
   if (!environment_variables) {
      environment_variables = ([]);
   }
   return map_indices(environment_variables) + ({ "PATH" });
}

int query_ansi(void) {
   mixed x;

   x = query_env("ansi");
   if (typeof(x) == T_NIL) {
      return 1;		/* ansi is on if query_env("ansi") is undefined */
   }
   return x;
}

void set_ansi(int state) {
   set_env("ansi", state);
   save_me();
}

void set_user(object usr) {
   user = usr;
}

void set_title(string t) {
   title = t;
   set_short(query_title());
}

string query_title(void) {
   string t, t2;

   t = title;
   if (!query_name()) {
      return "";
   }

   if (!t || t == "") {
      t = "$N the title less";
   }
   t2 = replace_string(t, "$N", capitalize(living_name));
   if (t2 == t)  t2 = capitalize(living_name) + " " + t;

   return t2;
}

string query_title_string(void) {
   return title;
}

void set_linkdead(int flag) {
   if (flag == 1) {
		LINKDEAD_D->add_linkdead(query_title());
      set_short(query_title() + " [link-dead]");
      linkdead = call_out("do_quit", LINKDEAD_TIMEOUT);
   } else {
      set_short(query_title());
      if (linkdead)
	 remove_call_out(linkdead);
      linkdead = 0;
   }
}

void set_editing(int flag) {
   if (flag == 1) {
      set_short(query_title() + " [editing]");
   } else {
      set_short(query_title());
   }
}

int query_linkdead(void) {
   return (linkdead > 0);
}

int query_idle(void) {
   return (time() - timestamp);
}

object query_user(void) {
   return user;
}

void set_real_name(string str) {
   real_name = str;
}

string query_real_name(void) {
   if (!real_name) {
      return "";
   }
   return real_name;
}

void set_email_address(string str) {
   email_address = str;
}

string query_email_address(void) {
   if (!email_address) {
      return "";
   }
   return email_address;
}

void set_website(string str) {
   website = str;
}

string query_website() {
   if (!website) {
      return "";
   }
   return website;
}

void initialize_cmd_path(void) {
   cmd::set_cmd_path( ({ "/cmds/player/" }) );
}

/* Add a path to the command path */
void add_cmd_path(string path) {
   if(require_priv(owner_file(path))) {
      cmd::add_cmd_path( path );
   } else {
      error("Permission denied.");
   }
}

string *query_path(void) {
   return cmd::query_cmd_path();
}

void add_channel(string chan) {
   if (!channels) {
      channels = ( { } );
   }
   channels -= ( { chan } );
   channels += ( { chan } );
}

void remove_channel(string chan) {
   if (!channels) {
      channels = ( { } );
   }
   channels -= ( { chan } );
}

string *query_channels(void) {
   return channels;
}

void add_ignore(string who) {
   if (who == "") {
      return;
   }
   ignored += ( { lowercase(who) } );
}

void remove_ignore(string who) {
   if (!ignored) {
      ignored = ( { } );
   }
   ignored -= ( { lowercase(who) } );
}

int query_ignored(string who) {
   if (!ignored) {
      ignored = ( { } );
   }
   who = lowercase(who);
   return member_array(who, ignored) >= 0;
}

string *query_ignored_all() {
   if (!ignored) {
      ignored = ( { } );
   }
   return ignored;
}

/* Redirect input to another function */
void input_to(string func, varargs mixed arg...) {
   input_to_obj = this_player();
   input_to_func = func;
   input_to_arg = arg;
}

/* Redirect input to another object */
void input_to_object(object ob, string func, varargs mixed arg...) {
   input_to_obj = ob;
   input_to_func = func;
   input_to_arg = arg;
}

/* Send a message to the player */
void message(string str, varargs int chat_flag) {
   if (!this_object()->query_user()) {
      return;
   }
   if (this_object()->is_snooped()) {
      this_object()->do_snoop(str);
   }

   if (chat_flag) {
      this_object()->query_user()->wrap_message(str, 1);
   } else {
      this_object()->query_user()->wrap_message(str);
   }
}

/* Send an almost unmodified message to the player */
void message_orig(string str) {
   if (!query_user()) {
      return;
   }

   if (this_player()->is_snooped()) {
      this_player()->do_snoop(str);
   }
   query_user()->put_message(str);
}

void write_prompt() {
   string prompt;
   string date;

   if (this_object()->is_editing()) {
      out("%^GREEN%^edit> %^RESET%^");
      return;
   }

   prompt = query_env("prompt");
   if (!prompt) {
      prompt = "> ";
   } else {
      date = ctime(time());
      prompt = replace_string(prompt, "%d", date[4..10] + date[20..23]);
      prompt = replace_string(prompt, "%t", ctime(time())[11..18]);
      prompt = replace_string(prompt, "%n", capitalize(living_name));
      prompt = replace_string(prompt, "%m", MUD_NAME);
      prompt = replace_string(prompt, "%w", query_env("cwd"));
      prompt = replace_string(prompt, "%_", "\n");

      if (this_environment()) {
	 prompt = replace_string(prompt, "%l", this_environment()->file_name());
	 if (!this_environment()->query_area()) {
	    prompt = replace_string(prompt, "%a", "(none)");
	 } else {
	    prompt =
	       replace_string(prompt, "%a", this_environment()->query_area());
	 }
      } else {
	 prompt = replace_string(prompt, "%l", "(no environment)");
	 prompt = replace_string(prompt, "%a", "(none)");
      }

      prompt = replace_string(prompt, "%h", "" + this_player()->query_hp());
      prompt = replace_string(prompt, "%H", "" + this_player()->query_max_hp());
      prompt = replace_string(prompt, "%b", "" + this_player()->query_mana());
      prompt = replace_string(prompt, "%B", "" + 
         this_player()->query_max_mana());
      prompt = replace_string(prompt, "%e", "" + this_player()->query_end());
      prompt = replace_string(prompt, "%E", "" + 
         this_player()->query_max_end());
   }

   out(prompt + "%^RESET%^ ");
}

int query_width() {
   mixed width;
   int x;

   width = this_player()->query_env("width");
   if (!intp(width) || (width < 2)) {
      width = DEFAULT_WIDTH;
   }
   x = width;
   return x;
}

/* More a set of lines */
void more(string * lines, varargs int docolor) {
   string msg;
   mixed height;

   if (docolor && (docolor == 1)) {
      color_more = 1;
   } else {
      color_more = 0;
   }

   if (previous_object() != this_object()) {
      more_caller = previous_object();
   }

   height = query_env("height");
   if (height == nil) {
      height = 23;
   } else if (stringp(height)) {
      height = str2val(height);
   }

   if (height == -1) {
      height = 23;
   } else if (height == 0) {
      height = INT_MAX;
   }

   if (height > 1) {
      height = height - 1;
   }

   more_line_num = 0;
   more_lines = lines;

   if (sizeof(lines) > height + more_line_num) {

      msg = implode(lines[more_line_num..more_line_num + height], "\n");

      if (docolor) {
         this_object()->query_user()->wrap_message(msg);
      } else {
         out_unmod(msg + "\n");
      }

      out("%^BOLD%^--More--(" + ((more_line_num +
         height) * 100) / sizeof(lines) + "%)%^RESET%^");
      more_line_num += height + 1;
      input_to("more_prompt");
   } else {
      msg = implode(lines[more_line_num..], "\n");

      if (docolor) {
         this_object()->query_user()->wrap_message(msg);
      } else {
         out_unmod(msg + "\n");
      }

      if (more_caller) {
	 more_caller->more_done();
	 more_caller = nil;
      }
   }
}

/* Write out the more prompt after each page */
void more_prompt(string arg) {
   string msg;
   mixed height;

   if (!arg || arg == "") {
      arg = " ";
   }
   switch (arg[0]) {
      case 'q':
      case 'Q':
	 write_prompt();
	 if (more_caller) {
	    more_caller->more_done();
	    more_caller = nil;
	 }
	 return;
	 break;
   }

   height = query_env("height");

   if (height == nil) {
      height = 23;
   } else if (stringp(height)) {
      height = str2val(height);
   }

   if (height == -1) {
      height = 23;
   } else if (height == 0) {
      height = INT_MAX;
   }

   if (height > 1) {
      height = height - 1;
   }

   if (sizeof(more_lines) > height + more_line_num) {
      msg = implode(more_lines[more_line_num..more_line_num + height], "\n");
      if (color_more) {
         this_object()->query_user()->wrap_message(msg);
      } else {
         out_unmod(msg + "\n");
      }

      out("%^BOLD%^--More--(" + ((more_line_num +
	       height) * 100) / sizeof(more_lines) + "%)%^RESET%^");
      more_line_num += height + 1;
      input_to("more_prompt");
   } else {
      msg = implode(more_lines[more_line_num..], "\n");

      if (color_more) {
         this_object()->query_user()->wrap_message(msg);
      } else {
         out_unmod(msg + "\n");
      }
      if (more_caller) {
	 more_caller->more_done();
	 more_caller = nil;
      }
      write_prompt();
   }
}

/* Look around */
void do_look(int brief) {
   object save_player;

   save_player = this_player();
   set_this_player(this_object());

   this_environment()->event("body_look", this_player());
   write(" ");
   if (query_env("show_location")) {
      write("%^BOLD%^" + query_environment()->file_name() + "%^RESET%^");
   }
   write(this_environment()->query_desc(0));

   set_this_player(save_player);
}

/* Move */
void do_go(string dir) {
   string error;

   error = this_environment()->body_exit(this_player(), dir);

   if (error) {
      write(error);
   }
}

void do_quit(void) {
   object sp;
   object *objs;
   string quitcmd;
   int i, autoload;
   string *channelstmp;

   sp = this_player();

   set_this_player(this_object());

   if (query_env("autoload")) {
      this_object()->compose_autoload_string();
      autoload = 1;
   }

   objs = query_inventory() + ( { } );

   if (is_possessing()) {
      command( "possess", nil );
   }

   for (i = 0; i < sizeof(objs); i++) {
      if (objs[i]->is_undroppable() || autoload == 1) {
         objs[i]->destruct();
      } else {
         if (objs[i]->is_worn()) {
            this_player()->do_remove(objs[i]);
            this_player()->targeted_action(objs[i]->query_remove_message(),
               nil, objs[i]);
         }
         if (objs[i]->is_wielded()) {
            this_player()->do_unwield(objs[i]);
            this_player()->targeted_action(objs[i]->query_unwield_message(),
               nil, objs[i]);
         }

         if (objs[i]->move(this_object()->query_environment())) {
            this_object()->targeted_action("$N $vdrop $o.", nil, objs[i]);
         } else {
            objs[i]->destruct();
         }
      }
   }

   if (query_env("save_on_quit")) {
      object room;

      room = this_player()->query_environment();
      if (room) { 
         set_env("start", room->file_name());
      }
   }

   quitcmd = this_player()->query_env("quit_message");
   if (!quitcmd || quitcmd == "") {
      quitcmd = "$N $vquit.";
   }
   this_object()->simple_action(quitcmd);

   channelstmp = channels;
   for (i = 0; i < sizeof(channels); i++) {
      if (CHANNEL_D->query_channel(channels[i])) {
	 CHANNEL_D->chan_leave(channels[i], this_object());
      } else {
	 channels[i] = nil;
      }
   }
   channels = channelstmp;
   EVENT_D->event("player_logout", living_name);
	LINKDEAD_D->remove_linkdead(query_title());
   quitting = 1;
   set_this_player(sp);
   query_user()->quit();
}

/* Destruct this player */
void destruct(void) {
   move_or_destruct_inventory();
   ::destruct();
}

/* Alias handling */

int is_alias(string cmd) {
   if (!alias) {
      alias = ([]);
   }
   if (alias[cmd]) {
      return 1;
   }
   return 0;
}

string query_alias(string cmd) {
   if (!alias) {
      alias = ([]);
   }
   return alias[cmd];
}

void add_alias(string cmd, string new_alias) {
   if (!alias) {
      alias = ([]);
   }
   alias[cmd] = new_alias;
}

void remove_alias(string cmd) {
   if (!alias) {
      alias = ([]);
   }

   alias[cmd] = nil;
}

mapping query_aliases(void) {
   if (!alias) {
      alias = ([]);
   }

   return alias;
}

/* Guild routines */

void join_guild(string guild) {
   if (!guilds) {
      guilds = ([]);
   }

   guilds[guild] = GUILD_D->query_guild_title(guild);
   add_cmd_path( "/cmds/guild/" + guild );
   save_me();
}

void leave_guild(string guild) {
   if (!guilds) {
      guilds = ([]);
   }

   guilds[guild] = nil;
   remove_cmd_path( "/cmds/guild/" + guild );
   set_title("$N the guildless");
   save_me();
}

int guild_member(string guild) {
   if (!guilds) {
      guilds = ([]);
   }

   if (guilds[guild]) {
      return 1;
   }
   return 0;
}

string *query_guilds(void) {
   string *blah;

   if (guilds) {
      blah = map_indices(guilds);
   }

   return blah;
}

string random_error() {
   int randomval;

   randomval = random(3);
   switch (randomval) {
      case 0:
         return "What?";
         break;
      case 1:
         return "Que?";
         break;
      case 2:
         return "Huh?";
         break;
   }
}

/* Process input from the player */
void receive_message(string message) {
   mixed result;
   string func, cmd, arg;
   string *exits;
   int i, flag;
   object room;

   flag = 0;

   /* Update the timestamp so we're not idle */
   timestamp = time();

   arg = "";

   if (this_player()->is_snooped()) {
      this_player()->do_snoop(message);
   }

   /* Redirect the input somewhere else */
   if (input_to_func != "") {
      func = input_to_func;
      input_to_func = "";
      call_other(input_to_obj, func, message, input_to_arg...);
   /* Are we editing? */
   } else if (is_editing()) {
      this_player()->edit(message);
   } else {
      string temp;

      /* Expand the command */
      temp = ALIAS_D->expand_alias(message);
      if (temp) {
	 message = temp;
      }

      /* Split the input into command and argument */
      if (sscanf(message, "%s %s", cmd, arg) != 2) {
	 cmd = message;
      }

      if (is_alias(cmd)) {
	 message = ALIAS_D->do_expand(query_alias(cmd), arg);
	 if (sscanf(message, "%s %s", cmd, arg) != 2) {
	    cmd = message;
         }
      }

      if (cmd != "") {
	 if (cmd[0] == '\'') {
	    if (arg == "") {
	       arg = cmd[1..];
	    } else {
	       arg = cmd[1..] + " " + arg;
	    }
	    cmd = "say";
	 } else if (cmd[0] == ';') {
	    if (arg == "") {
	       arg = cmd[1..];
	    } else {
	       arg = cmd[1..] + " " + arg;
	    }
	    cmd = "emote";
	 }
      }

      /* Substitute 'me' with my name */
      if (arg == "me") {
	 arg = this_player()->query_id();
      }

      /* Check for an object command in objects in my inv */
      if (!flag) {
	 object player;
	 string roomcmd_h;

         player = this_player();
         if (player) {
            object *objs;
            int y, maxy;

            objs = player->query_inventory();
            if (objs) {
               maxy = sizeof(objs);
               for(y=0;y<maxy; y++) {
	          roomcmd_h = objs[y]->query_action(cmd);

	          if (roomcmd_h) {
	             flag = call_other(objs[y], roomcmd_h, arg);
	          }
               }
            }
         }
      }

      /* Check for an object command in the room */
      if (!flag) {
         object room;
         string objectcmd_h;

	 room = this_player()->query_environment();
         if (room) {
            objectcmd_h = room->query_action(cmd);

            if (objectcmd_h) {
               flag = call_other(room, objectcmd_h, arg);
            }
         }
      }

      /* Check for an object command in objects in the room */
      if (!flag) {
	 object room;
	 string roomcmd_h;

         room = this_player()->query_environment();
         if (room) {
            object *objs;
            int y, maxy;

            objs = room->query_inventory();
            if (objs) {
               maxy = sizeof(objs);
               for(y=0;y<maxy; y++) {
	          roomcmd_h = objs[y]->query_action(cmd);

	          if (roomcmd_h) {
	             flag = call_other(objs[y], roomcmd_h, arg);
	          }
               }
            }
         }
      }

      /* Check for a room command */
      if (!flag) {
	 object room;
	 string roomcmd_h;

         room = this_environment();
         if (room) {
	    roomcmd_h = room->query_action(cmd);
	    if (roomcmd_h) {
	       flag = call_other(room, roomcmd_h, arg);
	    }
         }
      }

      /* Call command_d to check if it handles this command, returns -1 
         when it doesn't */
      if (!flag) {
         i = command( cmd, arg );
         if( i >= 0 ) {
            flag = 1;
         }
      }

      if (!flag) {
	 /* XXX shouldn't add cmd and arg but have to right now */
         flag = do_game_command(cmd + " " + arg);
      }

      if (!flag) {
	 /* Is it a channel? */
	 if (CHANNEL_D->query_channel(cmd) == 1) {
	    /* Okay, it's a channel. Are we privileged enough to use it? */
	    if (CHANNEL_D->query_priv(cmd) + 1 == READ_ONLY ||
	       CHANNEL_D->query_priv(cmd) <= query_user_type(living_name)) {

	       flag = 1;
	       command("chan", cmd + " " + arg);
	    }
	 }
      }

      if (!flag) {
	 /* Is it an exit? */
	 exits = this_environment()->query_exit_indices();
	 for (i = 0; i < sizeof(exits); i++) {
	    if (exits[i] == lowercase(cmd)) {
	       command("go", cmd);
	       flag = 1;
	    }
	 }
      }

      if (!flag && cmd != "") {
	 write(random_error());
      }
      if (!quitting && input_to_func == "" && !is_editing())
	 write_prompt();
   }
}

void set_custom_color(string name, string * symbols) {
   int i, sz;
   string tmp;

   tmp = "";
   if (!custom_colors) {
      custom_colors = ([]);
   }

   if (!symbols) {
      custom_colors[name] = nil;
      write("Removed color symbol " + name + "\n");
   } else {
      for (i = 0, sz = sizeof(symbols); i < sz; i++) {
	 if (strstr("%^", symbols[i]) == -1) {
	    symbols[i] = uppercase(symbols[i]);
	    if (!ANSI_D->query_any_symbol(symbols[i])) {
	       /* Each symbol must resolve to a pre-defined token */
	       write("Symbolic color tokens must be composed of only " +
                  "valid base color tokens or pre-existing custom tokens.\n" +
		  "see 'ansi show' for valid tokens");
	       return;
	    } else {
	       switch (ANSI_D->check_recursion(name, symbols[i])) {
		  case 2:
		     write("Loop in symbolic tag " + name + " : " + symbols[i]);
		     return;
		  case 1:
		     write("Too many levels of symbolic tags for " + name);
		     return;
	       }
	    }
	    tmp += "%^" + symbols[i] + "%^";
	 } else {
	    write("Symbolic color tokens cannot (YET) contain custom tokens\n");
	    return;
	 }
      }

      custom_colors[name] = tmp;
      out_unmod(name + " is now " + tmp + "\n");
   }

   ANSI_D->set_player_translations(custom_colors);
   save_me();
}

void store_menu(mixed header, mixed * menu, mixed footer, mapping actions) {
   menu_data = ( { header, menu, footer, actions } );
}

mixed *retrieve_menu() {
   if (menu_data) {
      return menu_data;
   } else {
      return ( { nil, nil, nil, nil } );
   }
}

int query_muzzle() {
   return muzzle;
}

int toggle_muzzle() {
   if (muzzle) {
      muzzle = 0;
   } else {
      muzzle = 1;
   }

   return muzzle;
}

void setup() {
}


