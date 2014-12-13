/* This file is used by the email_d to pass email to an object */
string to, from, subject, date;
string *lines;

static void restore_me(string myfile) {
   console_msg("Calling restore_object on : " + myfile + "\n");
   unguarded("restore_object", myfile);
}

static void save_me(string myfile) {
   console_msg("Calling save_me on : " + myfile + "\n");
   unguarded("save_object", myfile);
}

int is_email(string name) {
   if (!date) {
      return 0;
   } else {
      return 1;
   }
}

int set_to(string who) {
   if (USER_D->user_exists(who)) {
      to = who;
      return 1;
   }
   return 0;
}

string query_to(void) {
   return to;
}

int set_from(string who) {
   if (USER_D->user_exists(who)) {
      from = who;
      return 1;
   }
   return 0;
}

string query_from(void) {
   return from;
}

int set_subject(string what) {
   subject = what;
   return 1;
}

string query_subject(void) {
   return subject;
}

string query_date(void) {
   return date;
}

int set_date(void) {
   date = ctime(time());
   return 1;
}

int set_lines(string *data) {
   lines = data;
}

string *query_lines(void) {
   return lines;
}
