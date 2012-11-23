object *followers;

int add_follower(object who) {
   if (!followers) followers = ({ });
   followers += ( { who } );
   return 1;
}

int remove_follower(object who) {
   followers -= ( { who } );
   return 1;
}

/* return 1 if who is a follower */
int query_follower(object who) {
   int i;

   if (!followers) return 0;
   for (i = 0; i < sizeof(followers); i++) {
      if (followers[i] == who) {
         return 1;
      }
   }
   return 0;
}
