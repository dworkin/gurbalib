mapping state;

void create(void) {
   state = ([
      "hp100" : "$N $vare in perfect condition.", 
      "hp90" : "$N $vare fatigued.", 
      "hp80" : "$N $vare slightly hurt.", 
      "hp70" : "$N $vare hurt.", 
      "hp60" : "$N $vare bleeding.", 
      "hp50" : "$N $vare slightly wounded.", 
      "hp40" : "$N $vare wounded.", 
      "hp30" : "$N $vare heavily wounded.", 
      "hp20" : "$N $vare critically wounded.", 
      "hp10" : "$N $vare dying.",
   ]);
}

string query_state(string which) {
   if (!state[which]) {
      return "Message '" + which + "' not in MESSAGES_D.";
   }
   return state[which];
}
