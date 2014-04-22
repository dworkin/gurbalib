inherit "/std/object";

static object owner;

void setup(void) {
   set_id("beads");
   set_short("A string of dimensional beads");
   set_long("Some dimensional beads. Concentrate on them.");
   set_gettable(1);
   set_weight(1);
   set_value(0);
	add_action("activate_cmd", "activate");
}

void set_owner(object obj) {
	owner = obj;
}

int activate_cmd(string str) {
	write("These beads can open pocket dimensions.");
	if (owner != this_player()) {
		write("Unfortunately this is not your string of beads.");
		return 1;
	}
	write("This would take you to a pocket dimension.");
	return 1;
}
