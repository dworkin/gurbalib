#include "../domain.h"

inherit obj "/std/object";
inherit flags DIR + "/lib/flags";

#define IS_SPOILED 1
#define IS_DRIED   2

static int count, spoil_interval, spoil_handle;

int is_spoiled(void) {
   return test_flag(IS_SPOILED);
}

string get_warn_short(void) {
   return "A less than fresh root";
}

string get_warn_long(void) {
   return "The root is less the fresh as " +
      "as it continues to spoil. There is " +
      "still time to properly dry it, " +
      "however.";
}

string get_spoiled_short(void) {
   return "A spoiled root";
}

string get_spoiled_long(void) {
   return "The root has been spoiled after " +
      "improperly drying.";
}

void emit_message(string str) {
   object env;
   env = this_object()->query_environment();
   if (env) {
      env->message(str);
   }
}

string get_spoil_message(void) {
   return "The " + query_id() + " spoils because it was not " +
      "properly dried.";
}

void spoil_hook(void) {
}

nomask void spoil(void) {
   remove_call_out(spoil_handle);
   emit_message(get_spoil_message());
   set_value(0);
   set_short(get_spoiled_short());
   set_long(get_spoiled_long());
   set_flag(IS_SPOILED);
   spoil_hook();
}

string get_warn_message(void) {
   return "The " + query_id() + " needs to be properly dried soon " +
      "or it will spoil.";
}

nomask void handle_warn_spoil(void) {
   emit_message(get_warn_message());
   set_short(get_warn_short());
   set_long(get_warn_long());
}

private void check_spoil_interval(void) {
   if (spoil_interval < 5) {
      spoil_interval = DEFAULT_SPOIL_INTERVAL;
   }
}

nomask static void warn_spoil(void) {
   check_spoil_interval();
   remove_call_out(spoil_handle);
   spoil_handle = call_out("spoil", spoil_interval);
   handle_warn_spoil();
}

nomask void start_spoiling(void) {
   check_spoil_interval();
   spoil_handle = call_out("warn_spoil", spoil_interval);
}

void handle_properly_dried(void) {
}

nomask void notify_properly_dried(void) {
   remove_call_out(spoil_handle);
   set_flag(IS_DRIED);
   handle_properly_dried();
}

void set_spoil_interval(int interval) {
   spoil_interval = interval;
}

void setup(void) {
   set_id("root");
   set_short("A root");
   set_long("A root that may have some additional " +
      "properties once it has been properly dried.");
   set_gettable(1);
   set_weight(1);
   set_value(5);
   set_spoil_interval(DEFAULT_SPOIL_INTERVAL);
}

void create(void) {
   obj::create();
   flags::create();
}
