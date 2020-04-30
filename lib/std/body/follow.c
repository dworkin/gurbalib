string *followers;
string following;

int add_follower(string who) {
   if (!followers) {
      followers = ({ });
   }

   followers += ( { who } );
   return 1;
}

int remove_follower(string who) {
   followers -= ( { who } );
   return 1;
}

void clear_followers() {
   followers = ({ });
}


string *query_followers() {
   return followers;
}

/* return 1 if who is a follower */
int is_follower(string who) {
   int i;

   if (!followers) {
      return 0;
   }

   for (i = 0; i < sizeof(followers); i++) {
      if (followers[i] == who) {
         return 1;
      }
   }
   return 0;
}

string query_follower(void) {
   if (following && following != "") {
      return following;
   }
   return "";
}

int set_follower(string who) {
   following = who;
}
