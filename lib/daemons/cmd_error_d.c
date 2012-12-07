void create(varargs int clone) {
   if (clone)
      error("Can't clone daemons.");
}

string random_error() {
   int randomval;
   randomval = random(3);
   switch (randomval) {
      case 0:
	 return ("What?");
	 break;
      case 1:
	 return ("Que?");
	 break;
      case 2:
	 return ("Huh?");
	 break;
   }
}
