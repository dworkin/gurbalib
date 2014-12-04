string *quests;

void create(void) {
   if (!quests) {
      quests = ({ });
   }
}

string *query_quests_completed(void) {
   return quests;
}

int add_completed_quest(string quest) {
   int x, s;

   if (quests) {
      s = sizeof(quests);
      for (x = 0; x < s; x++) {
         if (quest == quests[x]) {
            return 0;
         }
      }
      quests += ({quest});
   } else {
      quests = ({quest});
   }
   return 1;
}

int is_completed_quest(string quest) {
   int x, s;

   if (quests) {
      s = sizeof(quests);
      for (x = 0; x < s; x++) {
         if (quest == quests[x]) {
            return 1;
         }
      }
   }
   return 0;
}
