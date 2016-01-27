inherit M_COMMAND;

string *usage(void) {
   string *lines;

   lines = ({ "Usage: time [-h] [-s]" });
   lines += ({ "" });
   lines += ({ "Show what time it is, in mud time." });
   lines += ({ "The calendar system is as follows." });
   lines += ({ "" });
   lines += ({ "One year has 17 months, one for each of the deities." });
   lines += ({ "One month has 5 weeks, one for each of the Elder Gods." });
   lines += ({ "One week has 4 days, one for each of the elements." });
   lines += ({ "" });
   lines += ({ "One year has 340 days. One month is 20 days." });
   lines += ({ "" });
   lines += ({ "Options:" });
   lines += ({ "\t-h\tHelp, this usage message." });
   lines += ({ "\t-s\tShow the short version of game time." });
   lines += ({ "Examples:" });
   lines += ({ "\ttime" });

   lines += get_alsos();

   return lines;
}

void setup_alsos() {
   add_also("player", "score");
   add_also("player", "time");

   add_also("wiz", "date");
   add_also("wiz", "scan");
   add_also("wiz", "status");
}

string get_hour0() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "It's midnight.";
         break;
      case 11..20:
         return "It's not possible to read the time more accurately " +
            "than 'midnight'.";
         break;
      case 21..30:
         return "About half an hour has passed since midnight.";
         break;
      case 31..40:
         return "You feel it's starting to close in on one o'clock.";
         break;
      case 41..50:
         return "Less than an hour since midnight.";
         break;
      default :
         return "It's about one o'clock.";
         break;
   }
}

string get_hour1() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "An hour has passed since midnight.";
         break;
      case 11..20:
         return "It's too dark to tell the time, but you think it's " +
            "a little past one.";
         break;
      case 21..30:
         return "It's probably half past one, but you can't be quite " +
            "sure.";
         break;
      case 31..40:
         return "The time is in between one and two, you guess.";
         break;
      case 41..50:
         return "You feel time approaching on two o'clock.";
         break;
      default:
         return "About two hours passed since midnight.";
         break;
   }
}

string get_hour2() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "Two o'clock and all's well.";
         break;
      case 11..20:
         return "Everyone should be asleep now. Everyone except you...";
         break;
      case 21..30:
         return "Given the lack of a sun, you estimate that it's " +
            "about two thirty.";
         break;
      case 31..40:
         return "It's not easy to tell time in this darkness.";
         break;
      case 41..50:
         return "It's too dark to tell time.";
         break;
      default:
         return "The time is probably around three.";
   }
}

string get_hour3() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "It's probably around three o'clock.";
         break;
      case 11..20:
         return "What are you doing up at this hour? It's past three!.";
         break;
      case 21..30:
         return "Midways between three and four, nothing exciting " +
            "is happening.";
         break;
      case 31..40:
         return "You estimate the time to be almost four o'clock.";
         break;
      case 41..50:
         return "It's closing in on four o'clock.";
         break;
      default:
         return "The night watchman should soon yell: 'Four " +
            "o'clock and all's well!'";
         break;
   }
}

string get_hour4() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "The night watchman yells his usual 'Four o'clock " +
            "and all's well!'";
         break;
      case 11..20:
         return "About fifteen minutes past since four o'clock.";
         break;
      case 21..30:
         return "About thirty minutes past four.";
         break;
      case 31..40:
         return "It's starting to close in on five o'clock.";
         break;
      case 41..50:
         return "You tremble in anticipation of five o'clock. Well almost.";
         break;
      default :
         return "The baker is awakening to bake his bread. Must be " +
            "about five.";
         break;
   }
}

string get_hour5() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "You hear the baker starting his job. It's " +
            "five o'clock.";
         break;
      case 11..20:
         return "It's about twenty minutes past five.";
         break;
      case 21..30:
         return "Half an hour has passed since five.";
         break;
      case 31..40:
         return "You can barely see a glimpse of the sun on the " +
            "horizon.";
         break;
      case 41..50:
         return "The sun is starting to come out of its sleep.";
         break;
      default:
         return "Freshly baked bread is in the air; it's six o'clock.";
         break;
   }
}

string get_hour6() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "The sun has risen. A new day has begun.";
         break;
      case 11..20:
         return "Everywhere people are getting up from their " +
            "sleep. Except you.";
         break;
      case 21..30:
         return "The town is starting to come alive ever so slowly.";
         break;
      case 31..40:
         return "Breakfast would be nice at this time.";
         break;
      case 41..50:
         return "Almost an hour after sunrise, there are still not " +
            "many people about.";
         break;
      default:
         return "The watchman is doing his seven o'clock round.";
         break;
   }
}

string get_hour7() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "'Seven o'clock; time to start the day!' the " +
            "watchman shouts.";
         break;
      case 11..20:
         return "You feel the city really starting to awaken.";
         break;
      case 21..30:
         return "The occasional farmer walks out to his fields. " +
            "It's seven thirty.";
         break;
      case 31..40:
         return "Merchants are setting up their stands and opening " +
            "their shops.";
         break;
      case 41..50:
         return "The flags are raised over the castle meaning that " +
            "the king has awoken.";
         break;
      default:
         return "Merchants have started yelling although they're " +
            "not officially open until 8.";
         break;
   }
}

string get_hour8() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "The watchman yells that it's eight o'clock.";
         break;
      case 11..20:
         return "The city is now bustling with life, a little " +
            "past eight.";
         break;
      case 21..30:
         return "It's almost half an hour past eight.";
         break;
      case 31..40:
         return "More than half an hour past eight.";
         break;
      case 41..50:
         return "It's closing in on nine o'clock.";
         break;
      default:
         return "It's almost nine o'clock.";
         break;
   }
}

string get_hour9() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "It's nine o'clock.";
         break;
      case 11..20:
         return "It's about ten minutes past nine.";
         break;
      case 21..30:
         return "Half an hour until ten.";
         break;
      case 31..40:
         return "About a quarter to ten.";
         break;
      case 41..50:
         return "Almost ten.";
         break;
      case 51..60:
         return "Just about eleven o'clock.";
         break;
   }
}

string get_hour10() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "It's still morning, ten o'clock.";
         break;
      case 11..20:
         return "The sun is rising on the sky, it's a little past ten.";
         break;
      case 21..30:
         return "From looking at the sun's position, you deem it to " +
            "be ten thirty.";
         break;
      case 31..40:
         return "Slowly the sun is climbing to its peak, still a " +
            "long way to go.";
         break;
      case 41..50:
         return "Time passes slowly, it's now almost eleven.";
         break;
      default:
         return "It's just a little before eleven.";
         break;
   }
}

string get_hour11() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "It's eleven o'clock.";
         break;
      case 11..20:
         return "Fifteen minutes past eleven, forty-five until noon.";
         break;
      case 21..30:
         return "Half an hour past eleven.";
         break;
      case 31..40:
         return "The sun is almost at its peak.";
         break;
      case 41..50:
         return "It's just about noon.";
         break;
      default:
         return "It's noon. The sun is at its peak.";
         break;
   }
}

string get_hour12() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "It's noon.";
         break;
      case 11..20:
         return "People are starting to think about their mid-day " +
            "meals.";
         break;
      case 21..30:
         return "If you have a routine that you do at half one, " +
            "you should be doing it now.";
         break;
      case 31..40:
         return "The shopkeepers are preparing to close their " +
            "shops for lunch.";
         break;
      case 41..50:
         return "The city calms itself down as people go for their " +
            "noon break.";
         break;
      default:
         return "Suddenly the town goes silent; people are taking a " +
            "break at one.";
         break;
   }
}

string get_hour13() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "The city is calm as the noon break goes undisturbed.";
         break;
      case 11..20:
         return "People are slowly returning to their posts from " +
            "their break.";
         break;
      case 21..30:
         return "You can not see that there has been a one o'clock " +
            "break, twenty minutes after.";
         break;
      case 31..40:
         return "At half past one, everything is as it should be.";
         break;
      case 41..50:
         return "It's a quarter to two.";
         break;
      default:
         return "It's almost two.";
         break;
   }
}

string get_hour14() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "It's two o'clock.";
         break;
      case 11..20:
         return "A few minutes past two.";
         break;
      case 21..30:
         return "It's almost two thirty.";
         break;
      case 31..40:
         return "It's starting to close in on three o'clock.";
         break;
      case 41..50:
         return "Soon it'll be three.";
         break;
      default:
         return "You await the watchman's yell at three.";
         break;
   }
}

string get_hour15() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "'Three o'clock!', the watchman yells.";
         break;
      case 11..20:
         return "The city's bustling life goes on no matter if " +
            "the time is a quarter past three or not.";
         break;
      case 21..30:
         return "It's half past three.";
         break;
      case 31..40:
         return "It's a little over three thirty.";
         break;
      case 41..50:
         return "It's way past three thirty.";
         break;
      default:
         return "It's almost four.";
         break;
   }
}

string get_hour16() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "The city is at its peak of activity; it's four o'clock.";
         break;
      case 11..20:
         return "The sun is setting ever so slowly in the west, at " +
            "four and a few minutes.";
         break;
      case 21..30:
         return "The city life is gradually decreasing, it's four thirty.";
         break;
      case 31..40:
         return "You see many housewives starting to prepare for " +
            "dinner, which is often at five.";
         break;
      case 41..50:
         return "Many shops are closing up in order to go home for " +
            "dinner at five.";
         break;
      default:
         return "Dinner would really be good about now. It's five o'clock.";
         break;
   }
}

string get_hour17() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "Dinnertime.";
         break;
      case 11..20:
         return "People are having dinner; it's a little past five.";
         break;
      case 21..30:
         return "Slowly people are returning to their workplaces " +
            "from dinner for a last haul.";
         break;
      case 31..40:
         return "Peasants are starting to return from the fields " +
            "with their crop.";
         break;
      case 41..50:
         return "It's almost six o'clock, the sun will be setting soon.";
         break;
      default:
         return "The sun is almost gone over the horizon.";
         break;
   }
}

string get_hour18() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "Sunset, dusk, call it what you want. The sun is " +
            "almost gone now.";
         break;
      case 11..20:
         return "A little past six, it is slowly getting dark.";
         break;
      case 21..30:
         return "It is darkening at six thirty.";
         break;
      case 31..40:
         return "The shopkeepers are starting to pack their stuff " +
            "for the day.";
         break;
      case 41..50:
         return "The shopkeepers close at seven, that is not long away.";
         break;
      default:
         return "The shops close their doors. It is seven o'clock.";
         break;
   } 
}

string get_hour19() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "Shopkeepers gone home, the shops lie deserted.  " +
            "It's a little past seven.";
         break;
      case 11..20:
         return "Although the sun is down, there is still quite a " +
            "bit of activity.";
         break;
      case 21..30:
         return "Most of the activity moves to the local taverns.  " +
            "It's seven thirty.";
         break;
      case 31..40:
         return "It's about an hour and a half after sunset.";
         break;
      case 41..50:
         return "You're pushing eight o'clock.";
         break;
      default:
         return "It's just a few minutes before eight.";
         break;
   }
}

string get_hour20() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "The night watchman begins his route by yelling " +
            "that it's eight o'clock.";
         break;
      case 11..20:
         return "It's a quarter or so past eight.";
         break;
      case 21..30:
         return "It's a quarter or so past eight.";
         break;
      case 31..40:
         return "It's half past eight.";
         break;
      case 41..50:
         return "It's closing in on nine.";
         break;
      default:
         return "It's almost nine.";
         break;
   }
}

string get_hour21() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "'Nine o'clock and all's well!'";
         break;
      case 11..20:
         return "It's getting too dark to see the time, but you " +
            "think it's a little over nine.";
         break;
      case 21..30:
         return "Most people are indoors by nine thirty. You aren't.";
         break;
      case 31..40:
         return "The activity at local taverns always rises before ten.";
         break;
      case 41..50:
         return "Most children have gone to bed. It's almost ten.";
         break;
      default:
         return "Most sound people are in bed now, resting for the " +
            "upcoming day.";
         break;
   }
}

string get_hour22() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "The night watchman yells that it's ten o'clock.";
         break;
      case 11..20:
         return "It's about fifteen minutes since the ten o'clock bell.";
         break;
      case 21..30:
         return "There is always a roar in the taverns at ten thirty.";
         break;
      case 31..40:
         return "Given how dark it is, you're quite proud for " +
            "managing to tell the time to be ten thirty.";
         break;
      case 41..50:
         return "It'll be eleven sometime soon.";
         break;
      default:
         return "Just a few more minutes before eleven...";
         break;
   }
}

string get_hour23() {
   switch (TIME_D->query_minute()) {
      case 0..10:
         return "The night watchman yells that it's eleven o'clock.";
         break;
      case 11..20:
         return "It's not possible to know the time more " +
            "accurately than 'a little past eleven'";
         break;
      case 21..30:
         return "It's around eleven thirty, but you can't be sure.";
         break;
      case 31..40:
         return "It's too dark to tell the time, but you think " +
            "it's half past eleven.";
         break;
      case 41..50:
         return "From the looks of things, midnight is approaching.";
         break;
      default:
         return "Midnight is right around the corner.";
         break;
   }
}

static void main(string str) {
   int day;
   string txt, datetxt, *days, *hours, *years;

   if (!alsos) {
      setup_alsos();
   }

   if (!empty_str(str)) {
      if ((str == "-s") || (str == "-S")) {
         write(TIME_D->query_time());
      } else {
         this_player()->more(usage());
      }
      return;
   }

   switch (TIME_D->query_hour()) {
      case 0:
         txt = get_hour0();
         break;
      case 1:
         txt = get_hour1();
         break;
      case 2:
         txt = get_hour2();
         break;
      case 3:
         txt = get_hour3();
         break;
      case 4:
         txt = get_hour4();
         break;
      case 5:
         txt = get_hour5();
         break;
      case 6:
         txt = get_hour6();
         break;
      case 7:
         txt = get_hour7();
         break;
      case 8:
         txt = get_hour8();
         break;
      case 9:
         txt = get_hour9();
         break;
      case 10:
         txt = get_hour10();
         break;
      case 11:
         txt = get_hour11();
         break;
      case 12:
         txt = get_hour12();
         break;
      case 13:
         txt = get_hour13();
         break;
      case 14:
         txt = get_hour14();
         break;
      case 15:
         txt = get_hour15();
         break;
      case 16:
         txt = get_hour16();
         break;
      case 17:
         txt = get_hour17();
         break;
      case 18:
         txt = get_hour18();
         break;
      case 19:
         txt = get_hour19();
         break;
      case 20:
         txt = get_hour20();
         break;
      case 21:
         txt = get_hour21();
         break;
      case 22:
         txt = get_hour22();
         break;
      default:
         txt = get_hour23();
         break;
   }

   days = ({
      "first", "second", "third", "fourth", "fifth", "sixth", "seventh",
      "eighth", "ninth", "tenth", "eleventh", "twelfth", "thirteenth",
      "fourteenth", "fifteenth", "sixteenth", "seventeenth", "eighteenth",
      "nineteenth", "last" });

   datetxt = days[TIME_D->query_day()];

   years = ({
      "wolf", "lion", "sparrow", "horse", "lizard", "cougar", "bear", "fish",
      "crocodile", "fairy", "deer" });

   write("It is " + TIME_D->query_weekday_name() + "day the " + datetxt +
      " day in the month of " + TIME_D->query_month_name() + ", year of the " +
      years[TIME_D->query_year() % 11] + ".\n");
   write(txt + "\n");
}
