string *skills;
#define DATAFILE "/daemons/data/skill_d.o"

static void save_me(void) {
   unguarded("save_object", DATAFILE);
}

static void restore_me(void) {
   unguarded("restore_object", DATAFILE);
}

void create(void) {
   skills = ({ });

   if (file_exists(DATAFILE)) {
      restore_me();
   } else {
      /* Setup a list of default skills encase we do not have a list */
      skills = ( { 
         "combat/unarmed",
         "combat/defense",
         "combat/edge/small",
         "combat/edge/medium",
         "combat/edge/large",
         "combat/blunt/large",
         "combat/blunt/medium",
         "combat/blunt/small",
         "combat/sharp/small",
         "combat/sharp/medium",
         "combat/sharp/large",
         "language/catfolk",
         "language/dwarven",
         "language/elvish",
         "language/gnomish",
         "language/grunt",
         "spell/cure",
         "spell/missile",
         "value",
      } );

      save_me();
   }
}

void add_skill(string skill) {
   skills -= ({ skill });
   skills += ({ skill });

   save_me();
}

void remove_skill(string skill) {
   skills -= ({ skill });
   save_me();
}

string *query_skills(void) {
   return skills;
}

int is_skill(string skill) {
   if (member_array(skill, skills) != -1) {
      return 1;
   }
   return 0;
}
