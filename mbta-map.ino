// pins 2 through 13 are used for the LEDs
// pins 2, 3, 4, 5, 6, 7 are the anodes
// pins 8, 9, 10, 11, 12, 13 are the cathodes

constexpr bool DEBUG = false;

constexpr byte LED_OFF = 0;
constexpr byte LED_ON = 1;
constexpr byte LED_BLINK = 2;

constexpr int BUTTON_PIN = 14;
constexpr int DEBUG_PIN = 15;

constexpr byte NUM_STATIONS = 18;
constexpr byte WEEKDAY_NUM_TRAINS = 37;
const int WEEKDAY_INBOUND[] PROGMEM = {-1, -1, 252, 258, 263, 274, 284, 293, -1, -1, 298, 303, -1, -1, -1, 318, 322, 328, -1, -1, -1, -1, -1, -1, -1, -1, 315, 322, 325, 330, -1, 335, -1, 344, 348, 354, -1, -1, 310, 316, -1, 329, 339, 348, -1, -1, 353, 358, -1, 363, -1, 374, 378, 384, -1, -1, -1, -1, -1, -1, -1, -1, 378, 385, 388, 393, 397, 400, -1, 410, 414, 420, -1, -1, 360, 366, 371, 382, 392, 401, -1, -1, 406, 411, -1, -1, -1, 427, 431, 437, 362, 376, 391, 398, -1, 411, 421, 430, -1, -1, -1, -1, -1, -1, -1, 451, 455, 461, -1, -1, -1, -1, -1, -1, -1, -1, 435, 442, 445, 450, -1, 455, -1, 467, 471, 477, -1, -1, 430, 436, 441, 452, 462, 471, -1, -1, 476, 481, -1, -1, -1, 497, 501, 507, 422, 436, 451, 458, -1, 471, 481, 490, -1, -1, -1, -1, -1, -1, -1, 510, 514, 520, -1, -1, -1, -1, -1, -1, -1, -1, 492, 499, 502, 507, -1, 512, -1, 522, 526, 532, -1, -1, 488, 494, -1, 507, 517, 526, -1, -1, 531, 536, -1, -1, -1, 552, 556, 562, -1, -1, -1, -1, -1, -1, -1, -1, 555, 562, 565, 570, -1, 575, -1, 586, 590, 596, 518, 532, 547, 555, -1, 568, 581, 590, -1, -1, 595, 600, 604, -1, -1, 617, 621, 626, -1, -1, -1, -1, -1, -1, -1, -1, 615, 622, 625, 630, -1, 635, -1, 644, 648, 653, -1, -1, 615, 621, -1, 634, 644, 653, -1, -1, 658, 663, -1, -1, -1, 678, 682, 687, -1, -1, -1, -1, -1, -1, -1, -1, 680, 687, 690, 695, -1, 700, -1, 709, 713, 718, -1, -1, 672, 678, -1, 691, 703, 712, -1, -1, 717, 722, -1, 727, -1, 740, 744, 749, 717, 731, 746, 753, -1, 766, 776, 785, -1, -1, 790, 795, -1, -1, -1, 810, 814, 819, -1, -1, -1, -1, -1, -1, -1, -1, 802, 809, 812, 817, -1, 822, -1, 831, 835, 840, -1, -1, 795, 801, -1, 814, 824, 833, -1, -1, 838, 843, -1, -1, -1, 860, 864, 869, -1, -1, -1, -1, -1, -1, -1, -1, 855, 862, 865, 870, -1, 875, -1, 884, 888, 893, -1, -1, 850, 856, -1, 870, 880, 889, -1, -1, -1, 897, -1, -1, -1, 912, 916, 921, -1, -1, -1, -1, -1, -1, -1, -1, 905, 912, 915, 920, -1, 925, -1, 934, 938, 943, 865, 879, 895, 902, -1, 915, 925, 934, -1, -1, 939, 944, -1, -1, -1, 959, 963, 969, -1, -1, -1, -1, -1, -1, -1, -1, 965, 972, 975, 980, -1, 985, -1, 994, 998, 1004, -1, -1, 956, 962, -1, 978, 988, 997, -1, -1, 1002, 1007, 1011, -1, -1, 1024, 1028, 1034, -1, -1, -1, -1, -1, -1, -1, -1, 1020, 1027, 1030, 1035, -1, 1040, -1, 1049, 1053, 1059, 995, 1009, 1024, 1031, -1, 1044, 1054, 1063, -1, -1, 1068, 1073, -1, -1, -1, 1088, 1092, 1098, -1, -1, -1, -1, -1, -1, -1, -1, 1080, 1087, 1090, 1095, -1, 1100, -1, 1109, 1113, 1119, -1, -1, 1092, 1098, -1, 1111, 1121, 1130, -1, -1, 1135, 1140, -1, -1, -1, 1155, 1159, 1165, -1, -1, -1, -1, -1, -1, -1, -1, 1158, 1165, 1168, 1173, -1, 1178, -1, 1187, 1191, 1196, 1126, 1140, 1155, 1162, -1, 1175, 1185, 1194, -1, -1, -1, 1202, 1206, -1, -1, 1219, 1223, 1228, -1, -1, -1, -1, -1, -1, -1, -1, 1205, 1212, 1215, 1220, -1, 1225, -1, 1234, 1238, 1243, 1182, 1196, 1211, 1218, -1, 1231, 1241, 1250, -1, -1, 1255, 1260, -1, -1, -1, 1274, 1278, 1283, -1, -1, -1, -1, -1, -1, -1, -1, 1318, 1325, 1328, 1333, 1337, 1339, -1, 1349, 1353, 1358, -1, -1, 1335, 1341, -1, 1354, 1364, 1373, -1, -1, 1378, 1383, -1, 1388, -1, 1399, 1403, 1408, -1, -1, 1405, 1411, -1, 1424, 1437, 1446, -1, -1, 1451, 1456, 1460, 1462, -1, 1474, 1478, 1483};
const int WEEKDAY_OUTBOUND[] PROGMEM = {260, 265, 268, -1, -1, -1, 279, 285, -1, -1, 291, 299, 307, -1, 316, 330, 360, 378, 325, 330, 333, -1, -1, -1, 344, 350, 353, 361, -1, -1, -1, -1, -1, -1, -1, -1, 390, 395, 398, -1, -1, -1, 409, 415, -1, -1, 421, 429, 437, -1, 446, 463, 480, 495, 420, 425, 428, -1, -1, -1, 438, 444, 448, 457, -1, -1, -1, -1, -1, -1, -1, -1, 450, 455, 458, -1, -1, -1, 469, 475, -1, -1, 481, 489, 497, -1, 506, 520, -1, -1, 480, 485, 488, -1, -1, -1, 498, 504, 507, 517, -1, -1, -1, -1, -1, -1, -1, -1, 505, 510, 513, -1, -1, -1, 524, 530, -1, -1, 536, 544, 552, -1, 561, 575, -1, -1, 537, 542, 545, -1, -1, -1, 555, 561, 568, 577, -1, -1, -1, -1, -1, -1, -1, -1, 565, 570, 573, -1, 581, -1, 587, 593, -1, -1, 599, 607, 615, -1, 624, 636, 652, 673, 602, 607, 610, -1, -1, -1, 621, 627, 630, 638, -1, -1, -1, -1, -1, -1, -1, -1, 625, 630, 633, -1, -1, -1, 644, 650, -1, -1, 656, 664, 672, -1, 681, 695, -1, -1, 678, 683, 686, -1, -1, -1, 697, 703, -1, -1, 709, 717, 725, 735, 739, 753, -1, -1, 1440, 1445, 1448, -1, 1456, 1458, 1462, 1468, 1471, 1479, -1, -1, -1, -1, -1, -1, -1, -1, 1460, 1465, 1468, -1, -1, -1, 1479, 1485, -1, -1, 1491, 1499, 1507, -1, 1516, 1528, 1545, 1565, 785, 790, 793, -1, 801, -1, 806, 812, 815, 823, -1, -1, -1, -1, -1, -1, -1, -1, 800, 805, 808, -1, -1, -1, 819, 825, -1, -1, 831, 839, 847, -1, 856, 868, -1, -1, 845, 850, 853, -1, 861, -1, 866, 872, 875, 883, -1, -1, -1, -1, -1, -1, -1, -1, 860, 865, 868, -1, -1, -1, 879, 885, -1, -1, 891, 899, 907, 914, 918, 929, 944, 964, 895, 900, 903, -1, -1, -1, 914, 920, 924, 934, -1, -1, -1, -1, -1, -1, -1, -1, 920, 925, 928, -1, -1, -1, 939, 945, -1, -1, 951, 959, 967, -1, 976, 990, -1, -1, 952, 957, 961, -1, -1, -1, -1, -1, -1, -1, 977, 985, 994, 1004, 1008, 1020, 1035, 1055, 960, 965, 968, -1, -1, -1, 979, 985, 988, 999, -1, -1, -1, -1, -1, -1, -1, -1, 980, 985, 988, -1, -1, -1, 999, 1005, -1, -1, 1011, 1019, 1027, -1, 1036, 1051, -1, -1, 1012, 1017, 1021, -1, -1, -1, -1, -1, -1, -1, 1037, 1045, 1054, -1, 1063, 1072, 1087, 1113, 1020, 1025, 1028, -1, -1, -1, 1039, 1045, 1049, 1060, -1, -1, -1, -1, -1, -1, -1, -1, 1057, 1062, 1066, -1, -1, -1, 1077, 1083, -1, -1, 1089, 1098, 1108, 1119, 1123, 1134, 1150, 1169, 1072, 1077, 1080, -1, -1, -1, 1091, 1097, 1101, 1111, -1, -1, -1, -1, -1, -1, -1, -1, 1102, 1107, 1110, -1, -1, -1, 1121, 1127, -1, -1, 1133, 1141, 1149, -1, 1161, 1176, -1, -1, 1145, 1150, 1153, -1, 1161, -1, 1166, 1172, 1175, 1184, -1, -1, -1, -1, -1, -1, -1, -1, 1158, 1163, 1166, -1, -1, 1177, 1181, 1187, -1, -1, 1193, 1201, 1209, -1, 1221, 1233, -1, -1, 1200, 1205, 1208, -1, 1216, -1, 1221, 1227, 1230, 1238, -1, -1, -1, -1, -1, -1, -1, -1, 1235, 1240, 1243, -1, -1, -1, 1254, 1260, -1, -1, 1266, 1274, 1282, -1, 1291, 1305, -1, -1, 1260, 1265, 1268, -1, 1276, 1278, 1282, 1288, 1291, 1299, -1, -1, -1, -1, -1, -1, -1, -1, 1295, 1300, 1303, -1, 1311, 1313, 1317, 1323, -1, -1, 1329, 1337, 1345, -1, 1354, 1371, -1, -1, 1365, 1370, 1373, 1378, 1383, -1, 1388, 1394, -1, -1, 1400, 1408, 1416, -1, 1425, 1441, -1, -1, 1385, -1, -1, -1, -1, -1, 1417, 1423, 1426, 1435, -1, -1, -1, -1, -1, -1, -1, -1, 1435, 1440, 1443, 1448, 1453, 1455, 1459, 1465, -1, -1, 1471, 1479, 1487, -1, 1496, 1512, -1, -1};

constexpr byte WEEKEND_NUM_TRAINS = 10;
const int WEEKEND_INBOUND[] PROGMEM = {-1, -1, 315, 321, -1, 333, 343, 352, -1, -1, 357, 363, 367, 370, -1, 381, 385, 390, -1, -1, 495, 501, -1, 513, 523, 532, -1, -1, 537, 543, 547, 550, -1, 561, 565, 570, -1, -1, 585, 591, -1, 603, 613, 622, -1, -1, 627, 633, 637, 640, -1, 651, 655, 660, -1, -1, 705, 711, -1, 723, 733, 742, -1, -1, 747, 753, 757, 760, -1, 771, 775, 780, -1, -1, 825, 831, -1, 843, 853, 862, -1, -1, 867, 873, 877, 880, -1, 891, 895, 900, -1, -1, 945, 951, -1, 963, 973, 982, -1, -1, 987, 993, 997, 1000, -1, 1011, 1015, 1020, -1, -1, 1075, 1081, -1, 1093, 1103, 1112, -1, -1, 1117, 1123, 1127, 1130, -1, 1141, 1145, 1150, -1, -1, 1195, 1201, -1, 1213, 1223, 1232, -1, -1, 1237, 1243, 1247, 1250, -1, 1261, 1265, 1270, -1, -1, 1285, 1291, -1, 1303, 1313, 1322, -1, -1, 1327, 1333, 1337, 1340, -1, 1351, 1355, 1360, -1, -1, 1405, 1411, -1, 1423, 1433, 1442, -1, -1, 1447, 1453, 1457, 1460, -1, 1471, 1475, 1480};
const int WEEKEND_OUTBOUND[] PROGMEM = {405, 410, 413, -1, 421, 424, 428, 434, -1, -1, 439, 447, 457, -1, 466, 478, -1, -1, 475, 480, 483, -1, 491, 494, 498, 504, -1, -1, 509, 517, 527, -1, 539, 551, -1, -1, 615, 620, 623, -1, 631, 634, 638, 644, -1, -1, 649, 657, 667, -1, 676, 688, -1, -1, 1455, 1460, 1463, -1, 1471, 1474, 1478, 1484, -1, -1, 1489, 1497, 1507, -1, 1516, 1528, -1, -1, 855, 860, 863, -1, 871, 874, 878, 884, -1, -1, 889, 897, 907, -1, 916, 928, -1, -1, 945, 950, 953, -1, 961, 964, 968, 974, -1, -1, 979, 987, 997, -1, 1006, 1021, -1, -1, 1065, 1070, 1073, -1, 1081, 1084, 1088, 1094, -1, -1, 1099, 1107, 1117, -1, 1126, 1138, -1, -1, 1195, 1200, 1203, -1, 1211, 1214, 1218, 1224, -1, -1, 1229, 1237, 1247, -1, 1256, 1268, -1, -1, 1315, 1320, 1323, -1, 1331, 1334, 1338, 1344, -1, -1, 1349, 1357, 1367, -1, 1376, 1388, -1, -1, 1435, 1440, 1443, -1, 1451, 1454, 1458, 1464, -1, -1, 1469, 1477, 1487, -1, 1496, 1508, -1, -1};

char day_of_week = 1; // 7 represents Sunday
int minute_of_day = 180; // resets at 3am (180 <= minute_of_day < 1620)
unsigned int ms_of_minute = 0; // no more than 60000
unsigned long time_last_updated = 0;

constexpr byte NUM_GROUPS = 6;
constexpr byte LEDS_PER_GROUP = 6;
constexpr byte NUM_LEDS = NUM_GROUPS * LEDS_PER_GROUP;
volatile byte led_state[NUM_LEDS];
volatile byte led_blink_phase = 0;
volatile int led_blink_counter = 0;
volatile byte current_group = 0;

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

inline void input_time() {
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
}

void setup() {
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  if constexpr (DEBUG) {
    pinMode(DEBUG_PIN, OUTPUT);
  }

  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 64911; // 65536 - 625
  TCCR1B |= (1 << CS10) | (1 << CS11); // prescaler = 1/64
  TIMSK1 |= (1 << TOIE1);

  byte led_to_light = (millis() / 5000) % NUM_LEDS;
  for (byte led_to_light = 0; led_to_light <= NUM_LEDS; led_to_light++) {
    for (byte i = 0; i < NUM_LEDS; i++) {
      if (i == led_to_light) {
        led_state[i] = LED_ON;
      } else {
        led_state[i] = LED_OFF;
      }
    }
    delay(100);
  }

  input_time();

  if constexpr (DEBUG) {
    Serial.begin(9600);
    Serial.print(F("Day of week: "));
    Serial.println((int)day_of_week);
    Serial.print(F("Minute of day: "));
    Serial.println(minute_of_day);
    Serial.print(F("Time last updated: "));
    Serial.println(time_last_updated);
  }
}

inline byte group_to_cathode(byte group) {
  return group + 8;
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = 64911; // 65536 - 625
  if constexpr (DEBUG) {
    digitalWrite(DEBUG_PIN, HIGH);
  }

  led_blink_counter++;
  if (led_blink_counter >= 200) {
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

  if constexpr (DEBUG) {
    digitalWrite(DEBUG_PIN, LOW);
  }
}

inline byte station_to_led(byte station_i, bool is_outbound) {
  if (is_outbound) {
    return station_i * 2;
  }
  return (NUM_STATIONS - station_i) * 2 - 1;
}

void write_trains_to_buffer(byte *led_buffer, const int *table_to_use, byte num_trains, bool is_outbound) {
  for (byte train_i = 0; train_i < num_trains; train_i++) {
    bool train_is_active = false;
    for (byte station_i = 0; station_i < NUM_STATIONS; station_i++) {
      int station_time = pgm_read_word_near(table_to_use + (train_i * NUM_STATIONS + station_i));
      if (station_time == -1) {
        continue;
      }
      if (minute_of_day == station_time) {
        // Train is at station
        led_buffer[station_to_led(station_i, is_outbound)] = LED_ON;
        break;
      }
      if (minute_of_day < station_time) {
        // Train has not yet arrived at station
        if (!train_is_active) {
          break; // Train hasn't yet arrived at its first stop
        }
        led_buffer[station_to_led(station_i, is_outbound)] = LED_BLINK;
        break;
      }
      // Train has already passed this station
      train_is_active = true;
    }
  }
}

void loop() {
  update_time();
  byte led_buffer[NUM_LEDS] = {};
  if (day_of_week <= 5) {
    write_trains_to_buffer(led_buffer, WEEKDAY_OUTBOUND, WEEKDAY_NUM_TRAINS, true);
    write_trains_to_buffer(led_buffer, WEEKDAY_INBOUND, WEEKDAY_NUM_TRAINS, false);
  } else {
    write_trains_to_buffer(led_buffer, WEEKEND_OUTBOUND, WEEKEND_NUM_TRAINS, true);
    write_trains_to_buffer(led_buffer, WEEKEND_INBOUND, WEEKEND_NUM_TRAINS, false);
  }
  for (byte i = 0; i < NUM_LEDS; i++) {
    led_state[i] = led_buffer[i];
  }
  if constexpr (DEBUG) {
    Serial.print(F("Day of week: "));
    Serial.println((int)day_of_week);
    Serial.print(F("Minute of day: "));
    Serial.println(minute_of_day);
    Serial.print(F("Time last updated: "));
    Serial.println(time_last_updated);
  }
}
