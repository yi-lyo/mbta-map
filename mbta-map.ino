// pins 2 through 13 are used for the LEDs
// pins 2, 3, 4, 5, 6, 7 are the anodes
// pins 8, 9, 10, 11, 12, 13 are the cathodes

constexpr bool DEBUG = true;

constexpr byte LED_OFF = 0;
constexpr byte LED_ON = 1;
constexpr byte LED_BLINK = 2;

constexpr int BUTTON_PIN = 14;

const int WEEKDAY_INBOUND[] PROGMEM = {-1, -1, 252, 258, 263, 274, 284, 293, -1, -1, 298, 303, -1, -1, -1, 318, 322, 328, -1, -1, -1, -1, -1, -1, -1, -1, 315, 322, 325, 330, -1, 335, -1, 344, 348, 354, -1, -1, 310, 316, -1, 329, 339, 348, -1, -1, 353, 358, -1, 363, -1, 374, 378, 384, -1, -1, -1, -1, -1, -1, -1, -1, 378, 385, 388, 393, 397, 400, -1, 410, 414, 420, -1, -1, 360, 366, 371, 382, 392, 401, -1, -1, 406, 411, -1, -1, -1, 427, 431, 437, 362, 376, 391, 398, -1, 411, 421, 430, -1, -1, -1, -1, -1, -1, -1, 451, 455, 461, -1, -1, -1, -1, -1, -1, -1, -1, 435, 442, 445, 450, -1, 455, -1, 467, 471, 477, -1, -1, 430, 436, 441, 452, 462, 471, -1, -1, 476, 481, -1, -1, -1, 497, 501, 507, 422, 436, 451, 458, -1, 471, 481, 490, -1, -1, -1, -1, -1, -1, -1, 510, 514, 520, -1, -1, -1, -1, -1, -1, -1, -1, 492, 499, 502, 507, -1, 512, -1, 522, 526, 532, -1, -1, 488, 494, -1, 507, 517, 526, -1, -1, 531, 536, -1, -1, -1, 552, 556, 562, -1, -1, -1, -1, -1, -1, -1, -1, 555, 562, 565, 570, -1, 575, -1, 586, 590, 596, 518, 532, 547, 555, -1, 568, 581, 590, -1, -1, 595, 600, 604, -1, -1, 617, 621, 626, -1, -1, -1, -1, -1, -1, -1, -1, 615, 622, 625, 630, -1, 635, -1, 644, 648, 653, -1, -1, 615, 621, -1, 634, 644, 653, -1, -1, 658, 663, -1, -1, -1, 678, 682, 687, -1, -1, -1, -1, -1, -1, -1, -1, 680, 687, 690, 695, -1, 700, -1, 709, 713, 718, -1, -1, 672, 678, -1, 691, 703, 712, -1, -1, 717, 722, -1, 727, -1, 740, 744, 749, 717, 731, 746, 753, -1, 766, 776, 785, -1, -1, 790, 795, -1, -1, -1, 810, 814, 819, -1, -1, -1, -1, -1, -1, -1, -1, 802, 809, 812, 817, -1, 822, -1, 831, 835, 840, -1, -1, 795, 801, -1, 814, 824, 833, -1, -1, 838, 843, -1, -1, -1, 860, 864, 869, -1, -1, -1, -1, -1, -1, -1, -1, 855, 862, 865, 870, -1, 875, -1, 884, 888, 893, -1, -1, 850, 856, -1, 870, 880, 889, -1, -1, -1, 897, -1, -1, -1, 912, 916, 921, -1, -1, -1, -1, -1, -1, -1, -1, 905, 912, 915, 920, -1, 925, -1, 934, 938, 943, 865, 879, 895, 902, -1, 915, 925, 934, -1, -1, 939, 944, -1, -1, -1, 959, 963, 969, -1, -1, -1, -1, -1, -1, -1, -1, 965, 972, 975, 980, -1, 985, -1, 994, 998, 1004, -1, -1, 956, 962, -1, 978, 988, 997, -1, -1, 1002, 1007, 1011, -1, -1, 1024, 1028, 1034, -1, -1, -1, -1, -1, -1, -1, -1, 1020, 1027, 1030, 1035, -1, 1040, -1, 1049, 1053, 1059, 995, 1009, 1024, 1031, -1, 1044, 1054, 1063, -1, -1, 1068, 1073, -1, -1, -1, 1088, 1092, 1098, -1, -1, -1, -1, -1, -1, -1, -1, 1080, 1087, 1090, 1095, -1, 1100, -1, 1109, 1113, 1119, -1, -1, 1092, 1098, -1, 1111, 1121, 1130, -1, -1, 1135, 1140, -1, -1, -1, 1155, 1159, 1165, -1, -1, -1, -1, -1, -1, -1, -1, 1158, 1165, 1168, 1173, -1, 1178, -1, 1187, 1191, 1196, 1126, 1140, 1155, 1162, -1, 1175, 1185, 1194, -1, -1, -1, 1202, 1206, -1, -1, 1219, 1223, 1228, -1, -1, -1, -1, -1, -1, -1, -1, 1205, 1212, 1215, 1220, -1, 1225, -1, 1234, 1238, 1243, 1182, 1196, 1211, 1218, -1, 1231, 1241, 1250, -1, -1, 1255, 1260, -1, -1, -1, 1274, 1278, 1283, -1, -1, -1, -1, -1, -1, -1, -1, 1318, 1325, 1328, 1333, 1337, 1339, -1, 1349, 1353, 1358, -1, -1, 1335, 1341, -1, 1354, 1364, 1373, -1, -1, 1378, 1383, -1, 1388, -1, 1399, 1403, 1408, -1, -1, 1405, 1411, -1, 1424, 1437, 1446, -1, -1, 1451, 1456, 1460, 1462, -1, 1474, 1478, 1483};

char day_of_week = 4; // 7 represents Sunday
int minute_of_day = 180; // resets at 3am (180 <= minute_of_day < 1620)
unsigned int ms_of_minute = 0; // no more than 60000
unsigned long time_last_updated = 0;

inline void update_time() {
  unsigned long time_now = millis();
  unsigned long time_elapsed = time_now - time_last_updated;
  ms_of_minute += time_elapsed;
  if (ms_of_minute >= 60000u) {
    ms_of_minute -= 60000u;
    minute_of_day += 1;
  }
  if (minute_of_day >= 1620) {
    minute_of_day -= 1440;
    day_of_week += 1;
  }
  if (day_of_week > 7) {
    day_of_week -= 7;
  }
  time_last_updated = time_now;
}

inline unsigned int input_time() {
  while (digitalRead(BUTTON_PIN) != LOW) {}
  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(900);
  unsigned int bit_buffer = 0;
  for (int i = 0; i < 14; i++) { // read 14 bits
    bit_buffer <<= 1;
    if (digitalRead(BUTTON_PIN) == LOW) { // Button is pressed
      bit_buffer |= 1;
    }
    // flash LED to indicate byte read
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(900);
  }
  // upper 3 bits correspond to day of week
  day_of_week = bit_buffer >> 11;
  // lower 11 bits correspond to minute of day
  minute_of_day = bit_buffer & 0x7FF;
  time_last_updated = millis();
  return bit_buffer;
}

void setup() {
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  unsigned int bit_buffer = input_time();

  if constexpr(DEBUG) {
    Serial.begin(9600);
    Serial.print(F("Bit buffer: "));
    Serial.println(bit_buffer, BIN);
    Serial.print(F("Day of week: "));
    Serial.println((int)day_of_week);
    Serial.print(F("Minute of day: "));
    Serial.println(minute_of_day);
    Serial.print(F("Time last updated: "));
    Serial.println(time_last_updated);
  }

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 64911; // 65536 - 625
  TCCR1B |= (1 << CS10) | (1 << CS11); // prescaler = 1/64
  TIMSK1 |= (1 << TOIE1);
}

inline byte group_to_cathode(byte group) {
  return group + 8;
}

constexpr byte NUM_GROUPS = 6;
constexpr byte LEDS_PER_GROUP = 6;
constexpr byte NUM_LEDS = NUM_GROUPS * LEDS_PER_GROUP;
volatile byte led_state[NUM_LEDS];
volatile byte led_blink_phase = 0;
volatile int led_blink_counter = 0;
volatile byte current_group = 0;
ISR(TIMER1_OVF_vect) {
  TCNT1 = 64911; // 65536 - 625

  led_blink_counter++;
  if (led_blink_counter >= 400) {
    led_blink_phase = 1 - led_blink_phase;
    led_blink_counter = 0;
  }

  byte previous_cathode = group_to_cathode(current_group);
  // Move to next LED group
  current_group++;
  if (current_group >= NUM_GROUPS) {
    current_group -= NUM_GROUPS;
  }
  byte now_cathode = group_to_cathode(current_group);

  byte anode_assignments = 0;
  for (byte i = 0; i < LEDS_PER_GROUP; i++) {
    switch (led_state[current_group * LEDS_PER_GROUP + i]) {
      case LED_OFF:
        break;
      case LED_ON:
        anode_assignments |= (1 << (i + 2));
        break;
      case LED_BLINK:
        anode_assignments |= (led_blink_phase << (i + 2));
        break;
    }
  }
  PORTD &= 3; // Set all anode pins to LOW
  pinMode(previous_cathode, INPUT);
  digitalWrite(previous_cathode, HIGH);
  digitalWrite(now_cathode, LOW);
  pinMode(now_cathode, OUTPUT);
  PORTD |= anode_assignments;
}

void loop() {
  update_time();
}
