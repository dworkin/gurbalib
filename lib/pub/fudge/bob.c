inherit "/std/monster";

int nFollow;

void setup(void) {
   set_name("bob");
   set_gender("male");
   set_adj("slave");
   set_short("Bob, Fudge's slave.");
   set_long("Bob is wearing a simple robe, and his head is always bent in " +
      "humbleness.");
   set_race("human");
   set_level(1);
   nFollow = call_out("follow_fudge", 2);
}

void follow_fudge(void) {
   object *objs;
   object fudge;
   int i;
   int nFudgeHere;

   nFudgeHere = 0;
   objs = query_environment()->query_inventory();
   for (i = 0; i < sizeof(objs); i++) {
      if (objs[i]->query_id() == "fudge") {
         nFudgeHere = 1;
      }
   }

   if (nFudgeHere == 0) {
      fudge = USER_D->find_player("fudge");
      if (!fudge) {
         /* Fudge has left the building */
         remove_call_out(nFollow);
         respond("say It seems Fudge has left these planes.");
         die();
         destruct_object(this_object());
         return;
      }
      if (query_environment() != fudge->query_environment()) {
         switch (random(10)) {
            case 0:
               query_environment()->tell_room(0, "Bob leaves.");
               break;
            case 1:
               query_environment()->tell_room(0,
                  "Bob tries to follow his master.");
               break;
            case 2:
               query_environment()->tell_room(0, "Bob follows Fudge.");
               break;
            case 3:
               query_environment()->tell_room(0,
                  "Bob disappears in a cloud of smoke.");
               break;
            case 4:
               query_environment()->tell_room(0, "Bob suddenly vanishes.");
               break;
            case 5:
               query_environment()->tell_room(0, "Bob fades out of view.");
               break;
            case 6:
               query_environment()->tell_room(0, "Bob runs off after Fudge.");
               break;
            case 7:
               query_environment()->tell_room(0,
                  "Bob suddenly notices that Fudge has left, and runs off.");
               break;
            case 8:
               query_environment()->tell_room(0,
                  "Bob fades into the shadows, and is gone.");
               break;
            case 9:
               query_environment()->tell_room(0,
                  "Bob snaps his fingers, and is gone.");
               break;
         }

         move(fudge->query_environment()->base_name());
         switch (random(10)) {
            case 0:
               query_environment()->tell_room(0,
                  "Bob follows the light of his life.");
               break;
            case 1:
               query_environment()->tell_room(0,
                  "Bob follows in his masters footsteps.");
               break;
            case 2:
               query_environment()->tell_room(0,
                  "Bob appears next to Fudge in a cloud of smoke.");
               break;
            case 3:
               query_environment()->tell_room(0, "Bob enters.");
               break;
            case 4:
               query_environment()->tell_room(0, "Bob appears.");
               break;
            case 5:
               query_environment()->tell_room(0,
                  "Bob arrives shortly after Fudge.");
               break;
            case 6:
               query_environment()->tell_room(0,
                  "Bob comes running, tying to keep up with Fudge.");
               break;
            case 7:
               query_environment()->tell_room(0, "A humble slave enters.");
               break;
            case 8:
               query_environment()->tell_room(0,
                  "A humble person wearing a robe enters.");
               break;
            case 9:
               query_environment()->tell_room(0, "Bob catches up with Fudge.");
               break;
         }
      }
   }
   nFollow = call_out("follow_fudge", 2);
}

void parse(string str) {
   if (str == "status") {
      respond("say There are " + sizeof(USER_D->query_players()) +
         " players here.");
      respond("say Of these " + sizeof(USER_D->query_players()) +
         " players, " + sizeof(USER_D->query_wizards()) + " are wizards.");
   } else {
      respond(str);
   }
}

void outside_message(string str) {

   str = ANSI_D->strip_colors(str);
   str = str[..(strlen(str) - 3)];
   if (strlen(str) > 18) {
      if (str[..16] == "Fudge says: Bob, ") {
         parse(str[17..]);
      }
   }
}
