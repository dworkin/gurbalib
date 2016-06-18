int can_heal(object patient) {
   return !nilp(patient) && patient->is_living();
}

int hp_needed(object patient) {
   return patient->query_hp() < patient->query_max_hp();
}

int mana_needed(object patient) {
   return patient->query_mana() < patient->query_max_mana();
}

int end_needed(object patient) {
   return patient->query_end() < patient->query_max_end();
}

int healing_hp_needed(object patient) {
   return can_heal(patient) && hp_needed(patient);
}

int healing_mana_needed(object patient) {
   return can_heal(patient) && mana_needed(patient);
}

int healing_end_needed(object patient) {
   return can_heal(patient) && end_needed(patient);
}

void show_message(object doc, object patient, string msg) {
   if (!nilp(doc) && !nilp(patient) && !empty_str(msg)) {
      doc->targeted_action(msg, patient);
   }
}

int recover_hp(object doc, object patient, int amt, string msg) {
   if (healing_hp_needed(patient)) {
      patient->increase_hp(amt);
      show_message(doc, patient, msg);
      return 1;
   }
   return 0;
}

int recover_mana(object doc, object patient, int amt, string msg) {
   if (healing_mana_needed(patient)) {
      patient->increase_mana(amt);
      show_message(doc, patient, msg);
      return 1;
   }
   return 0;
}

int recover_end(object doc, object patient, int amt, string msg) {
   if (healing_end_needed(patient)) {
      patient->increase_end(amt);
      show_message(doc, patient, msg);
      return 1;
   }
   return 0;
}
