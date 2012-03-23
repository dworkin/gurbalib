void usage() {
   write("Usage: attack [-h] OBJ\n");
   write("OBJ offends you your going to destroy it.\n");
   write("Options:\n");
   write("\t-h\tHelp, this usage message.\n");
}

string *query_verb_info() {
   return (( { "", "LIV" }));
}

int can_attack() {
   return 1;
}

int can_attack_liv(object liv) {
   return 1;
}

void do_attack() {
   write("Attack who?");
   return;
}

void do_attack_liv(object liv) {
   this_player()->targetted_action("$N $vattack $t.", liv);
   this_player()->attack(liv);
}
