string *quests;

void create() {
}

string *query_quests_complated() {
	return quests;
}

int set_completed_quest(string quest) {
   int x,s;

   s=sizeof(quests);
   for(x=0;x<s;x++) {
      if (quest == quests[x]) {
         return 0;
      }
   }
   quests += ({ quest });
}

int is_completed_quest(string quest) {
   int x,s;

   s=sizeof(quests);
   for(x=0;x<s;x++) {
      if (quest == quests[x]) {
         return 1;
      }
   }
   return 0;
}
