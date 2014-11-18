inherit "/std/monster";

int nFollow;
string master_name;
object master;
string my_name;

void set_master(object m) {
   if (m) {
      master = m;
      master_name = m->query_Name();
   }
}

void setup(void) {
   if (!master_name || master_name == "") { /* If no master set a default... */
      master_name = "sirdude";
   }
   set_name(master_name + "s page");
   my_name = master_name + "'s page";
   set_gender("male");
   set_level(1);
   set_adj("slave");
   set_short(capitalize(master_name) + "'s page");
   set_long("The page is wearing a simple robe, and his head is always " +
      "bent in humbleness.");
   set_race("human");
   nFollow = call_out("follow_master", 2);
   respond("bow " + master_name);
}

void follow_master(void) {
   object *objs;
   int i;
   int nMasterHere;

   nMasterHere = 0;
   objs = query_environment()->query_inventory();
   for (i = 0; i < sizeof(objs); i++) {
      if (objs[i] == master) {
         nMasterHere = 1;
      }
   }

   if (nMasterHere == 0) {
      if (!master) {
         remove_call_out(nFollow);
         respond("say It seems " + master_name +
            " no longer has a need for me.");
         die();
         destruct_object(this_object());
         return;
      }
      if (query_environment() != master->query_environment()) {
         switch (random(10)) {
            case 0:
               query_environment()->tell_room(nil, my_name + " leaves.");
               break;
            case 1:
               query_environment()->tell_room(nil, my_name +
                  " tries to follow his master.");
               break;
            case 2:
               query_environment()->tell_room(nil,
                  my_name + " follows his master.");
               break;
            case 3:
               query_environment()->tell_room(nil, my_name +
                  " disappears in a cloud of smoke.");
               break;
            case 4:
               query_environment()->tell_room(nil,
                  my_name + " suddenly vanishes.");
               break;
            case 5:
               query_environment()->tell_room(nil,
                  my_name + " fades out of view.");
               break;
            case 6:
               query_environment()->tell_room(nil, my_name +
                  " runs off after his master.");
               break;
            case 7:
               query_environment()->tell_room(nil, my_name +
                  " suddenly notices that his master has left, and runs off.");
               break;
            case 8:
               query_environment()->tell_room(nil, my_name +
                  " fades into the shadows, and is gone.");
               break;
            case 9:
               query_environment()->tell_room(nil, my_name +
                  " snaps his fingers, and is gone.");
               break;
         }

         move(master->query_environment()->base_name());
         switch (random(10)) {
            case 0:
               query_environment()->tell_room(nil, my_name +
                  " follows the light of his life.");
               break;
            case 1:
               query_environment()->tell_room(nil, my_name +
                  " follows in his masters footsteps.");
               break;
            case 2:
               query_environment()->tell_room(nil, my_name +
                  " appears next to his master in a cloud of smoke.");
               break;
            case 3:
               query_environment()->tell_room(nil, my_name + " enters.");
               break;
            case 4:
               query_environment()->tell_room(nil, my_name + " appears.");
               break;
            case 5:
               query_environment()->tell_room(nil, my_name +
                  " arrives shortly after his master.");
               break;
            case 6:
               query_environment()->tell_room(nil, my_name +
                  " comes running, tying to keep up with his master.");
               break;
            case 7:
               query_environment()->tell_room(nil, "A humble page enters.");
               break;
            case 8:
               query_environment()->tell_room(nil,
                  "A humble person wearing a robe enters.");
               break;
            case 9:
               query_environment()->tell_room(nil, my_name +
                  " catches up with his master.");
               break;
         }
      }
   }
   nFollow = call_out("follow_master", 2);
}

void parse(string str) {
   if (str == "go away" || str == "die" || str == "dismissed") {
      remove_call_out(nFollow);
      respond("say It seems " + master_name + " no longer has a need for me.");
      this_environment()->remove_object(this_object());
      destruct_object(this_object());
   } else {
      respond(str);
   }
}

void outside_message(string str) {
   string pre;

   str = ANSI_D->strip_colors(str);
   str = str[..(strlen(str) - 3)];

   pre = capitalize(master_name) + " says: Page, ";

   if (strstr(str, pre) != -1) {
      parse(str[(strlen(pre))..]);
   }
}
