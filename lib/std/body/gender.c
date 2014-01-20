string gender;

void set_gender(string gen) {
   gender = gen;
}

string query_gender(void) {
   switch (gender) {
      case "male":
	 return "male";
      case "female":
	 return "female";
      case "neuter":
         return "neuter";
      default:
	 return "unknown";
   }
}

string query_gender_pronoun(void) {
   switch (gender) {
      case "male":
	 return "he";
      case "female":
	 return "she";
      default:
	 return "it";
   }
}

string query_gender_possessive(void) {
   switch (gender) {
      case "male":
	 return "his";
      case "female":
	 return "hers";
      default:
	 return "its";
   }
}

string query_gender_reflexive(void) {
   switch (gender) {
      case "male":
	 return "himself";
      case "female":
	 return "herself";
      default:
	 return "itself";
   }
}
