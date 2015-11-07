string convert_number(int num, varargs int flag) {
   string *nums;
   string *numt;
   string str;
 
   str = "";
   nums = ({"one", "two", "three", "four", "five", "six", "seven", "eight",
      "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen",
      "sixteen", "seventeen", "eighteen", "nineteen"});
   numt = ({"twenty", "thirty", "forty", "fifty", "sixty",
      "seventy", "eighty", "ninety"});
 
   if (num == 0) {
      return "no";
   }
 
   if (num < 0) {
      str += "negative ";
      num = num * -1;
      }

   if (num<20) {
      str += nums[num-1];
      return str;
   }
   if (num>99) {
      if (num>999) {
         if (num>999999) {
            if (str != "") {
               str = "far below zero";
            } else {
               str = "many";
            }
            return str;
         }
         str += convert_number(num / 1000, 1) + " thousand";
         if (num % 1000 != 0) {
            str += " " + convert_number(num % 1000);
         }
         return str;
      }
     str += convert_number (num / 100) + " hundred";
     if (num % 100 != 0) {
        str += " " + convert_number(num % 100);
     }
     return str;
   }
   if ( (num % 10) == 0) {
      str += numt[num / 10 - 2];
      return str;
   } else {
        if (flag) {
           str += numt[num / 10 - 2] + " " + nums[num % 10 - 1];
        } else {
           str += numt[num / 10 - 2] + "-" + nums[num % 10 - 1];
        }
   }
   return str;
}
