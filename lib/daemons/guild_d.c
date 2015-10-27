void restore_me(void);
void save_me(void);
#define DATAFILE "/daemons/data/guild_d.o"

mapping guilds;

void create(void) {

   guilds = ([ ]);

   if (file_exists(DATAFILE)) {
      restore_me();
   } else {
      /* Create a default list if we do not already have one. */
      guilds["fighter"] = "The Fighters Guild";

      save_me();
   }
}

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);

}

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

void add_guild(string guild, string title) {

   guilds[guild] = title;
   save_me();
}

int is_guild(string guild) {
   if (guilds[guild]) {
      return 1;
   }

   return 0;
}

void remove_guild(string guild) {
   guilds[guild] = nil;
   save_me();
}

void set_guild_title(string guild, string title) {
   guilds[guild] = title;
   save_me();
}

string query_guild_title(string guild) {
   return (guilds[guild]);
}

void remove_all_guilds(void) {
   guilds = ([]);
   save_me();
}

string *query_guilds(void) {
   return map_indices(guilds);
}
