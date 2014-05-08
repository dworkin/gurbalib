nomask void set_property_file(string path) {
	string *lines, *parts;
	string key, val;
	int i, dim, property_was_set;
	property_was_set = 0;
	if (file_exists(path) == 1) { /* valid read has to be assumed. */
		lines = explode(read_file(path), "\n");
		for (i = 0, dim = sizeof(lines); i < dim; i++) {
			if (lines[i][0] == '#') {
				continue;
			}
			parts = explode(lines[i], "=");
			if (sizeof(parts) == 2) {
				key = parts[0];
				val = parts[1];
			} else if (sizeof(parts) > 2) {
				key = parts[0];
				val = implode(parts[1..], "=");
			} else {
				key = nil;
			}
			if (!nilp(key)) {
				property_was_set = set_property(key, val, "*");
			}
		}
	}
}

