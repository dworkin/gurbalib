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
   write(query_message());
   return 1;
}
