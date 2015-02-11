string horizontal_rule(object "/sys/obj/player" player, string str) {
	int width, i;
	string retval;
	width = str2val((string) this_player()->query_env("width"));
	for (retval = "", i = 0; i < width; i++) {
		retval += str;
	}
	return retval;
}

