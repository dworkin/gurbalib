/* Created by Fudge */

static string readable_text;

void set_message(string message) {
   readable_text = message;
}

string query_message(void) {
   return readable_text;
}

int is_readable(void) {
   return 1;
}

int can_read(object who) {
   return 1;
}

int do_read(object who) {
   string msg;

   msg = query_message();

   if (msg[0] == '#') {
      msg = call_other(this_object(),msg[1..]);
   }
   write(msg);
   return 1;
}
