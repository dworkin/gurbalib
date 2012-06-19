/*
    Coded by: Satch
    File    : /std/body/race.c
    Date    : 02.22.98
*/

string race;
object race_object;

void initialize_stats(void);

void set_race(string name) {
   race = name;
   race_object = RACE_D->query_race_object(name);
   initialize_stats();		/* set up stat/race bonus here */
   /* temp removal of min and max damage satch */
}

string query_race(void) {
   if (!race) {
      return "monster";
   }
   return race;
}

void initialize_race(void) {
   if (!race || race == "") {
      race = "Human";
   }
   race_object = RACE_D->query_race_object(race);
}

object query_race_object(void) {
   return (race_object);

}
