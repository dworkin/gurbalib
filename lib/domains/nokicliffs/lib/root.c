#include "../domain.h"

inherit obj "/std/object";
inherit flags DIR + "/lib/flags";

#define IS_SPOILED 1
#define IS_DRIED   2

static int count;
static int spoil_handle;

int is_spoiled() {
   return test_flag(IS_SPOILED);
}

string get_warn_short() {
   return "A less than fresh root";
}

string get_warn_long() {
   return "The root is less the fresh as " +
      "as it continues to spoil. There is "+
      "still time to properly dry it, " +
      "however.";
}

string get_spoiled_short() {
   return "A spoiled root";
}

string get_spoiled_long() {
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

void spoil(void) {
   emit_message("The " + query_id() + " spoils because it was not properly dried.");
   set_value(0);
   set_short(get_spoiled_short());
   set_long(get_spoiled_long());
   set_flag(IS_SPOILED);
}

void handle_warn_spoil() {
   emit_message("The " + query_id() + " needs to be properly dried soon or it will spoil.");
   set_short(get_warn_short());
   set_long(get_warn_long());
}

nomask static void warn_spoil(void) {
   remove_call_out(spoil_handle);
   spoil_handle = call_out("spoil", DEFAULT_SPOIL_INTERVAL);
   handle_warn_spoil();
}

nomask void start_spoiling(void) {
   spoil_handle = call_out("warn_spoil", DEFAULT_SPOIL_INTERVAL);
}

void handle_properly_dried() {
}

void notify_properly_dried() {
   remove_call_out(spoil_handle);
   set_flag(IS_DRIED);
   handle_properly_dried();
}

void setup(void) {
   set_id("root");
   set_short("A root");
   set_long("A root that may have some additional " +
      "properties once it has been properly dried.");
   set_gettable(1);
   set_weight(1);
   set_value(5);
}

void create(void) {
   obj::create();
   flags::create();
}
