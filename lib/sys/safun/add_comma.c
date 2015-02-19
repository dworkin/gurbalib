private string reverse_str(string original_str) {
	int tmp;
	int i, dim;
	for (i = 0, dim = strlen(original_str); i < dim >> 1; i++) {
		tmp = original_str[i];
		original_str[i] = original_str[dim - i - 1];
		original_str[dim - i - 1] = tmp;
	}
	return original_str;
}

string add_comma(string str) {
	string *parsed;
	int     i, dim, threes;

	argcheck(str, 1, "string");

	if (sscanf(str, "%d", i) != 1) {
		return str;
	}

	if (strlen(str) < 4) {
		return str;
	}

	parsed = parse_string("nr=/[0-9]/S: S: S nr", str);
	str = "";
	for (threes = 1, str = "", i = sizeof(parsed)-1; i > -1; i--, threes++) {
		str += parsed[i];
		if (threes % 3 == 0 && i > 0) {
			str += query_thousands_separator("en_US.utf8");
		}
	}
		
	return reverse_str(str);
}

