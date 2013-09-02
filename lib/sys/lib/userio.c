/*
 * IO functions for player/shell objects
 *
 * Aidil@Way of the Force
 *
 * XXX snooping should move to the user object
 *
 * XXX need to implement full stdin/out redirection for shell commands
 *
 * XXX out() and out_unmod() should move out of the auto-game object and 
 *     be turned into an output stream redir
 *
 */

static string input_to_func;
static object input_to_obj;
static mixed  input_to_arg;

/* Redirect input to another funtion */
void input_to(string func, varargs mixed arg) {
   input_to_obj = this_player();
   input_to_func = func;
   input_to_arg = arg;
}

/* Redirect input to another object */
void input_to_object(object ob, string func, varargs mixed arg) {
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

/* Send an almost unmodified message to the player *
 * used from the auto-game object!                 */
void message_orig(string str) {
   if (!query_user()) {
      return;
   }

   if (this_player()->is_snooped()) {
      this_player()->do_snoop(str);
   }
   query_user()->put_message(str);
}

