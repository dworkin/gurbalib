void main( string racialword ) {
	if(racialword != "") {
		string englishword;
		sscanf(racialword, " ", racialword, englishword);
		learn_racial_word(racialword, englishword);
	} else {
		write("Usage:\n  learn <foreignword> <englishword>\n");
	}
}
