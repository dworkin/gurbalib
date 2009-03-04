void main ( void ) {
  
  int day;
  int hour;
  string min;
  string datetxt;
  string hourtxt;
  string *days;
  string *hours;
  string *years;

  hour = TIME_D->query_hour();
  
  switch(TIME_D->query_minute()) {
  case 0..5 : min = "It's ";
    break;
  case 6..10 : min = "It's a little past ";
    break;
  case 11..15 : min = "Your sense of time tells you it's about a quarter past ";
    break;
  case 16..20 : min = "It's a while past ";
    break;
  case 21..30 : min = "It is nearly half an hour past ";
    break;
  case 31..40 : min = "More than half an hour has passed since ";
    break;
  case 41..50 : {
    min = "It is closing in on ";
    hour++;
  } 
  break;
  case 51..60 : {
    min = "It's almost ";
    hour++;
  }
  };
  
  
  days = ({ "first", "second", "third", "fourth", "fifth", "sixth", "seventh", "eighth", "ninth", "tenth", "eleventh", "twelfth", "thirteenth", "fourteenth", "fifteenth", "sixteenth", "seventeenth", "eighteenth", "nineteenth", "last" });
  
  datetxt = days[TIME_D->query_day()];
  
  hours = ({ "midnight", "one o'clock", "two", "three o'clock", "four at night", "five in the morning", "sunrise", "seven o'clock", "normal daybreak", "nine", "ten o'clock", "eleven", "noon", "one in the afternoon", "the afternoon break", "the early afternoon", "three o'clock, afternoon", "dinnertime", "eveningfall", "the early evening", "nightfall", "dusk", "the time for the first night bell", "the time for the second night bell", "midnight"});
  
  hourtxt = hours[hour];
  
  years = ({ "wolf", "lion", "sparrow", "horse", "lizard", "cougar", "bear", "fish", "crocodile", "fairy", "deer"});

    write( "It is " + TIME_D->query_weekday_name() + "day the " + datetxt + " day in the month of " + TIME_D->query_month_name() + ", year of the " + years[TIME_D->query_year() % 11] + ".\n");
    write(  min + hourtxt + ".\n");
}


