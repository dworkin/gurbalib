inherit "/std/object";

string owner_name;

void setup(void) {
   set_id("beads");
   set_short("A string of dimensional beads");
   set_long("Some dimensional beads. You can 'activate' them.");
   set_gettable(1);
   set_weight(1);
   set_value(0);
	add_action("activate_cmd", "activate");
}

void set_owner_name(object player) {
	player->message(file_name(previous_object()) + "\n");
	player->message(previous_program() + "\n");
	owner_name = player->query_name();
}

int activate_cmd(string str) {
	write("These beads can open pocket dimensions.");
	if (this_player()->is_player() &&
	 owner_name != this_player()->query_name()) {
		write("Unfortunately this is not your string of beads.");
		return 1;
	}
	write("This would take you to a pocket dimension.");
	return 1;
}

int post_drop() {
	this_object()->query_environment()->tell_room(nil,
		"The beads shatter as they hit the ground.");
	this_object()->destruct();
	return 1;
}
