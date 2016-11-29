string *history;

#define MAX_HISTORY_DIM 20
#define NO_SUCH_CMD "No such command in history."

int query_command_not_found_in_history(string str) {
   if (empty_str(str)) {
      return 0;
   }

   return NO_SUCH_CMD == str;
}

string get_history_character(void) {
   return "!";
}

private void setup_history(void) {
   if (nilp(history)) {
      history = ({ });
   }
}

static void create(void) {
   setup_history();
}

string list_history(void) {
   string str;
   int i, dim;

   setup_history();
   str = "Command history:\n";
   dim = sizeof(history);
   for (i = 0; i < dim; i++) {
      str += "" + (i + 1) + ": " + history[i] + "\n";
   }

   return str;
}

private string get_history_by_index(int idx) {
   setup_history();
   if (idx < 0 || idx >= sizeof(history)) {
      return "Index out of range.";
   }
   return history[idx];
}

private string get_history_by_string(string str) {
   int i, dim;
   setup_history();
   dim = sizeof(history);
   for (i = dim - 1; i > 0; i--) {
      if (history[i] == str) {
         return history[i];
      }
      if (strlen(history[i]) > strlen(str) &&
         history[i][..strlen(str) - 1] == str) {

         return history[i];
      }
   }
   return NO_SUCH_CMD;
}

string get_history(mixed arg) {
   int i;
   string str;

   setup_history();
   if (intp(arg)) {
      i = (int)arg;
      return get_history_by_index(i - 1);
   }
   if (stringp(arg)) {
      str = (string) arg;
      if (str == get_history_character()) {
         return get_history_by_index(sizeof(history) - 1);
      }
      return get_history_by_string(str);
   }
   return NO_SUCH_CMD;
}

void push_history(string str) {
   if (empty_str(str)) {
      return;
   }
   setup_history();
   if (sizeof(history) > 0 && str == history[sizeof(history) - 1]) {
      return;
   }
   if (sizeof(history) >= MAX_HISTORY_DIM) {
      history = history[1..];
   }
   history += ({str});
}

void remove_history(int nr) {
   setup_history();
   nr--;
   if (nr > -1 && nr < sizeof(history)) {
      history[nr] = nil;
   }
}

void compress_history(void) {
   setup_history();
   history -= ({ nil });
}
