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
   lines += ({ "See also:" });
   if (query_wizard(this_player())) {
      lines += ({ "\tdate, scan, score, status, time" });
   } else {
      lines += ({ "\tscore, time" });
   }

   return lines;
}

static void main(string str) {
   int day;
   string txt, datetxt, *days, *hours, *years;

   if (!empty_str(str)) {
      if ((str == "-s") || (str == "-S")) {
         write(TIME_D->query_time());
      } else {
         this_player()->more(usage());
      }
      return;
   }

   switch (TIME_D->query_hour()) {
      case 0:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "It's midnight.";
                  break;
               case 11..20:
                  txt = "It's not possible to read the time more accurately " +
                     "than 'midnight'.";
                  break;
               case 21..30:
                  txt = "About half an hour has passed since midnight.";
                  break;
               case 31..40:
                  txt = "You feel it's starting to close in on one o'clock.";
                  break;
               case 41..50:
                  txt = "Less than an hour since midnight.";
                  break;
               case 51..60:
                  txt = "It's about one o'clock.";
            }
         }
         break;
      case 1:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "An hour has passed since midnight.";
                  break;
               case 11..20:
                  txt = "It's too dark to tell the time, but you think it's " +
                     "a little past one.";
                  break;
               case 21..30:
                  txt = "It's probably half past one, but you can't be quite " +
                     "sure.";
                  break;
               case 31..40:
                  txt = "The time is in between one and two, you guess.";
                  break;
               case 41..50:
                  txt = "You feel time approaching on two o'clock.";
                  break;
               case 51..60:
                  txt = "About two hours passed since midnight.";
            }
         }
         break;
      case 2:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "Two o'clock and all's well.";
                  break;
               case 11..20:
                  txt = "Everyone should be asleep now. Everyone except you...";
                  break;
               case 21..30:
                  txt = "Given the lack of a sun, you estimate that it's " +
                     "about two thirty.";
                  break;
               case 31..40:
                  txt = "It's not easy to tell time in this darkness.";
                  break;
               case 41..50:
                  txt = "It's too dark to tell time.";
                  break;
               case 51..60:
                  txt = "The time is probably around three.";
            }
         }
         break;
      case 3:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "It's probably around three o'clock.";
                  break;
               case 11..20:
                  txt = "What are you doing up at this hour? It's past three!.";
                  break;
               case 21..30:
                  txt = "Midways between three and four, nothing exciting " +
                     "is happening.";
                  break;
               case 31..40:
                  txt = "You estimate the time to be almost four o'clock.";
                  break;
               case 41..50:
                  txt = "It's closing in on four o'clock.";
                  break;
               case 51..60:
                  txt = "The night watchman should soon yell: 'Four " +
                     "o'clock and all's well!'";
            }
         }
         break;
      case 4:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "The night watchman yells his usual 'Four o'clock " +
                     "and all's well!'";
                  break;
               case 11..20:
                  txt = "About fifteen minutes past since four o'clock.";
                  break;
               case 21..30:
                  txt = "About thirty minutes past four.";
                  break;
               case 31..40:
                  txt = "It's starting to close in on five o'clock.";
                  break;
               case 41..50:
                  txt = "You tremble in anticipation of five o'clock. Well " +
                     "almost.";
                  break;
               case 51..60:
                  txt = "The baker is awakening to bake his bread. Must be " +
                     "about five.";
            }
         }
         break;
      case 5:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "You hear the baker starting his job. It's " +
                     "five o'clock.";
                  break;
               case 11..20:
                  txt = "It's about twenty minutes past five.";
                  break;
               case 21..30:
                  txt = "Half an hour has passed since five.";
                  break;
               case 31..40:
                  txt = "You can barely see a glimpse of the sun on the " +
                     "horizon.";
                  break;
               case 41..50:
                  txt = "The sun is starting to come out of its sleep.";
                  break;
               case 51..60:
                  txt = "Freshly baked bread is in the air; it's six o'clock.";
            }
         }
         break;
      case 6:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "The sun has risen. A new day has begun.";
                  break;
               case 11..20:
                  txt = "Everywhere people are getting up from their " +
                     "sleep. Except you.";
                  break;
               case 21..30:
                  txt = "The town is starting to come alive ever so slowly.";
                  break;
               case 31..40:
                  txt = "Breakfast would be nice at this time.";
                  break;
               case 41..50:
                  txt = "Almost an hour after sunrise, there are still not " +
                     "many people about.";
                  break;
               case 51..60:
                  txt = "The watchman is doing his seven o'clock round.";
            }
         }
         break;
      case 7:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "'Seven o'clock; time to start the day!' the " +
                     "watchman shouts.";
                  break;
               case 11..20:
                  txt = "You feel the city really starting to awaken.";
                  break;
               case 21..30:
                  txt = "The occasional farmer walks out to his fields. " +
                     "It's seven thirty.";
                  break;
               case 31..40:
                  txt = "Merchants are setting up their stands and opening " +
                     "their shops.";
                  break;
               case 41..50:
                  txt = "The flags are raised over the castle meaning that " +
                     "the king has awoken.";
                  break;
               case 51..60:
                  txt = "Merchants have started yelling although they're " +
                     "not officially open until 8.";
            }
         }
         break;
      case 8:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "The watchman yells that it's eight o'clock.";
                  break;
               case 11..20:
                  txt = "The city is now bustling with life, a little " +
                     "past eight.";
                  break;
               case 21..30:
                  txt = "It's almost half an hour past eight.";
                  break;
               case 31..40:
                  txt = "More than half an hour past eight.";
                  break;
               case 41..50:
                  txt = "It's closing in on nine o'clock.";
                  break;
               case 51..60:
                  txt = "It's almost nine o'clock.";
            }
         }
         break;
      case 9:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "It's nine o'clock.";
                  break;
               case 11..20:
                  txt = "It's about ten minutes past nine.";
                  break;
               case 21..30:
                  txt = "Half an hour until ten.";
                  break;
               case 31..40:
                  txt = "About a quarter to ten.";
                  break;
               case 41..50:
                  txt = "Almost ten.";
                  break;
               case 51..60:
                  txt = "Just about eleven o'clock.";
            }
         }
         break;
      case 10:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "It's still morning, ten o'clock.";
                  break;
               case 11..20:
                  txt = "The sun is rising on the sky, it's a little past ten.";
                  break;
               case 21..30:
                  txt = "From looking at the sun's position, you deem it to " +
                     "be ten thirty.";
                  break;
               case 31..40:
                  txt = "Slowly the sun is climbing to its peak, still a " +
                     "long way to go.";
                  break;
               case 41..50:
                  txt = "Time passes slowly, it's now almost eleven.";
                  break;
               case 51..60:
                  txt = "It's just a little before eleven.";
            }
         }
         break;
      case 11:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "It's eleven o'clock.";
                  break;
               case 11..20:
                  txt = "Fifteen minutes past eleven, forty-five until noon.";
                  break;
               case 21..30:
                  txt = "Half an hour past eleven.";
                  break;
               case 31..40:
                  txt = "The sun is almost at its peak.";
                  break;
               case 41..50:
                  txt = "It's just about noon.";
                  break;
               case 51..60:
                  txt = "It's noon. The sun is at its peak.";
            }
         }
         break;
      case 12:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "It's noon.";
                  break;
               case 11..20:
                  txt = "People are starting to think about their mid-day " +
                     "meals.";
                  break;
               case 21..30:
                  txt = "If you have a routine that you do at half one, " +
                     "you should be doing it now.";
                  break;
               case 31..40:
                  txt = "The shopkeepers are preparing to close their " +
                     "shops for lunch.";
                  break;
               case 41..50:
                  txt = "The city calms itself down as people go for their " +
                     "noon break.";
                  break;
               case 51..60:
                  txt = "Suddenly the town goes silent; people are taking a " +
                     "break at one.";
            }
         }
         break;
      case 13:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "The city is calm as the noon break goes undisturbed.";
                  break;
               case 11..20:
                  txt = "People are slowly returning to their posts from " +
                     "their break.";
                  break;
               case 21..30:
                  txt = "You can not see that there has been a one o'clock " +
                     "break, twenty minutes after.";
                  break;
               case 31..40:
                  txt = "At half past one, everything is as it should be.";
                  break;
               case 41..50:
                  txt = "It's a quarter to two.";
                  break;
               case 51..60:
                  txt = "It's almost two.";
            }
         }
         break;
      case 14:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "It's two o'clock.";
                  break;
               case 11..20:
                  txt = "A few minutes past two.";
                  break;
               case 21..30:
                  txt = "It's almost two thirty.";
                  break;
               case 31..40:
                  txt = "It's starting to close in on three o'clock.";
                  break;
               case 41..50:
                  txt = "Soon it'll be three.";
                  break;
               case 51..60:
                  txt = "You await the watchman's yell at three.";
            }
         }
         break;
      case 15:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "'Three o'clock!', the watchman yells.";
                  break;
               case 11..20:
                  txt = "The city's bustling life goes on no matter if " +
                     "the time is a quarter past three or not.";
                  break;
               case 21..30:
                  txt = "It's half past three.";
                  break;
               case 31..40:
                  txt = "It's a little over three thirty.";
                  break;
               case 41..50:
                  txt = "It's way past three thirty.";
                  break;
               case 51..60:
                  txt = "It's almost four.";
            }
         }
         break;
      case 16:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "The city is at its peak of activity; it's four " +
                     "o'clock.";
                  break;
               case 11..20:
                  txt = "The sun is setting ever so slowly in the west, at " +
                     "four and a few minutes.";
                  break;
               case 21..30:
                  txt = "The city life is gradually decreasing, it's four " +
                     "thirty.";
                  break;
               case 31..40:
                  txt = "You see many housewives starting to prepare for " +
                     "dinner, which is often at five.";
                  break;
               case 41..50:
                  txt = "Many shops are closing up in order to go home for " +
                     "dinner at five.";
                  break;
               case 51..60:
                  txt = "Dinner would really be good about now. It's five " +
                     "o'clock.";
            }
         }
         break;
      case 17:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "Dinnertime.";
                  break;
               case 11..20:
                  txt = "People are having dinner; it's a little past five.";
                  break;
               case 21..30:
                  txt = "Slowly people are returning to their workplaces " +
                     "from dinner for a last haul.";
                  break;
               case 31..40:
                  txt = "Peasants are starting to return from the fields " +
                     "with their crop.";
                  break;
               case 41..50:
                  txt = "It's almost six o'clock, the sun will be " +
                     "setting soon.";
                  break;
               case 51..60:
                  txt = "The sun is almost gone over the horizon.";
            }
         }
         break;
      case 18:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "Sunset, dusk, call it what you want. The sun is " +
                     "almost gone now.";
                  break;
               case 11..20:
                  txt = "A little past six, it is slowly getting dark.";
                  break;
               case 21..30:
                  txt = "It is darkening at six thirty.";
                  break;
               case 31..40:
                  txt = "The shopkeepers are starting to pack their stuff " +
                     "for the day.";
                  break;
               case 41..50:
                  txt = "The shopkeepers close at seven, that is not " +
                     "long away.";
                  break;
               case 51..60:
                  txt = "The shops close their doors. It is seven o'clock.";
            }
         }
         break;
      case 19:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "Shopkeepers gone home, the shops lie deserted.  " +
                     "It's a little past seven.";
                  break;
               case 11..20:
                  txt = "Although the sun is down, there is still quite a " +
                     "bit of activity.";
                  break;
               case 21..30:
                  txt = "Most of the activity moves to the local taverns.  " +
                     "It's seven thirty.";
                  break;
               case 31..40:
                  txt = "It's about an hour and a half after sunset.";
                  break;
               case 41..50:
                  txt = "You're pushing eight o'clock.";
                  break;
               case 51..60:
                  txt = "It's just a few minutes before eight.";
            }
         }
         break;
      case 20:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "The night watchman begins his route by yelling " +
                     "that it's eight o'clock.";
                  break;
               case 11..20:
                  txt = "It's a quarter or so past eight.";
                  break;
               case 21..30:
                  txt = "It's a quarter or so past eight.";
                  break;
               case 31..40:
                  txt = "It's half past eight.";
                  break;
               case 41..50:
                  txt = "It's closing in on nine.";
                  break;
               case 51..60:
                  txt = "It's almost nine.";
            }
         }
         break;
      case 21:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "'Nine o'clock and all's well!'";
                  break;
               case 11..20:
                  txt = "It's getting too dark to see the time, but you " +
                     "think it's a little over nine.";
                  break;
               case 21..30:
                  txt = "Most people are indoors by nine thirty. You aren't.";
                  break;
               case 31..40:
                  txt = "The activity at local taverns always rises before " +
                     "ten.";
                  break;
               case 41..50:
                  txt = "Most children have gone to bed. It's almost ten.";
                  break;
               case 51..60:
                  txt = "Most sound people are in bed now, resting for the " +
                     "upcoming day.";
            }
         }
         break;
      case 22:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "The night watchman yells that it's ten o'clock.";
                  break;
               case 11..20:
                  txt = "It's about fifteen minutes since the ten o'clock " +
                     "bell.";
                  break;
               case 21..30:
                  txt = "There is always a roar in the taverns at ten thirty.";
                  break;
               case 31..40:
                  txt = "Given how dark it is, you're quite proud for " +
                     "managing to tell the time to be ten thirty.";
                  break;
               case 41..50:
                  txt = "It'll be eleven sometime soon.";
                  break;
               case 51..60:
                  txt = "Just a few more minutes before eleven...";
            }
         }
         break;
      case 23:{
            switch (TIME_D->query_minute()) {
               case 0..10:
                  txt = "The night watchman yells that it's eleven o'clock.";
                  break;
               case 11..20:
                  txt = "It's not possible to know the time more " +
                     "accurately than 'a little past eleven'";
                  break;
               case 21..30:
                  txt = "It's around eleven thirty, but you can't be sure.";
                  break;
               case 31..40:
                  txt = "It's too dark to tell the time, but you think " +
                     "it's half past eleven.";
                  break;
               case 41..50:
                  txt = "From the looks of things, midnight is approaching.";
                  break;
               case 51..60:
                  txt = "Midnight is right around the corner.";
            }
         }
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
