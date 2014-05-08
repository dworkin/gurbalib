/*
    Coded by: Satch
    File    : /std/body/race.c
    Date    : 02.22.98
*/

string race;
object race_object;
string *vulnerabilities;
string  hit_string;

void initialize_stats(void);

void set_race(string name) {
   if (!name || name == "") {
      race = "human";
   } else {
      race = name;
      race_object = RACE_D->query_race_object(name);
   }
   if (!race_object) 
      race_object = RACE_D->query_race_object("human");

   initialize_stats();		/* set up stat/race bonus here */
   /* temp removal of min and max damage satch */
}

string query_race(void) {
   if (!race) {
      return "monster";
   }
   return race;
}

object query_race_object(void) {
   return (race_object);

}

void set_vulnerabilities(string *new_vulnerabilities) {
	vulnerabilities = new_vulnerabilities;
}

void add_vulnerability(string vulnerability) {
	if (!vulnerabilities) {
		vulnerabilities = ({ });
	}
	vulnerabilities += ({ vulnerability });
	vulnerabilities = uniq_array(vulnerabilities);
}

string *query_vulnerabilities() {
	if (!vulnerabilities) {
		vulnerabilities = ({ });
	}
	return vulnerabilities;
}

int is_vulnerable(string *test_vulnerabilities) {
	if (!vulnerabilities) {
		vulnerabilities = ({ });
	}
	return sizeof(set_intersection(vulnerabilities, test_vulnerabilities));
}

void set_hit_string(string str) {
	hit_string = str;
}

string query_hit_string() {
	if (empty_str(hit_string)) {
		set_hit_string("hit");
	}
	return hit_string;
}

