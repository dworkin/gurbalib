#define VOWELS ({ "a", "e", "i", "o", "u" })

string plur(string str);

string pluralize(string str) {
   string a, b;

   if (sscanf(str, "%s of %s", a, b) == 2) {
      return (plur(a) + " of " + b);
      }
   return plur(str);
}

string plur(string str) {
   string a, b;
   if (sscanf(str, "%swife", a) ) {
      return a + "wives";
      }
   if (sscanf(str, "%sman", a) ) {
      return a + "men";
      }
   if (sscanf(str, "%schild", a) ) {
      return a + "children";
      }
   if (sscanf(str, "%sknife", a) ) {
      return a + "knives";
      }
   switch (str) {
      case "life":
         return "lives";
         break;
      case "foot":
         return "feet";
         break;
      case "goose":
         return "geese";
         break;
      case "mouse":
         return "mice";
         break;
      case "tooth":
         return "teeth";
         break;
      case "person":
         return "people";
         break;

      case "sheep":
      case "moose":
      case "series":
      case "aircraft":
      case "deer":
      case "reindeer":
      case "fish":
      case "offspring":
      case "salmon":
      case "shrimp":
      case "swine":
      case "trout":
      case "tuna":
         return str;
         break;

      case "photo":
      case "piano":
      case "disco":
            return str + "s";
            break;

      case "elf":
      case "dwarf":
      case "wharf":
      case "loaf":
      case "calf":
      case "wolf":
      case "thief":
      case "shelf":
      case "half":
      case "leaf":
         return str[0..(strlen(str) - 2)] + "ves";
         break;

      default:
         break;
    }
    a = str[(strlen(str) - 2)..(strlen(str) - 1)];
    switch (a) { 
        case "sh":
        case "ch":
            return a + "es";
            break;
        default:
           break;
    }
    if (b) {
       return str[0..(strlen(str)-3)] + b;
    }
    a = str[(strlen(str)-1)..(strlen(str)-1)];
    switch (a) {
        case "s":
        case "x":
        case "z":
           b = a + "es";
           break;
        case "y":
           if (member_array(str[(strlen(str) - 2)..(strlen(str) - 2)],
              VOWELS) == -1) {
              b = "ies";
           } else {
              b = "ys";
           }
           break;
        case "o":
           if (member_array(str[(strlen(str) - 2)..(strlen(str) - 2)],
              VOWELS) == -1) {
               b = "oes";
           } else {
              b = "os";
           }
           break;
        default:
           b = a + "s";
           break;
    }
    return str[0..(strlen(str) - 2)] + b;
}
