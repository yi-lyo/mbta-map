// pins 2 through 13 are used for the LEDs
// pins 2, 3, 4, 5, 6, 7 are the anodes
// pins 8, 9, 10, 11, 12, 13 are the cathodes

constexpr bool DEBUG = true;

constexpr byte LED_OFF = 0;
constexpr byte LED_ON = 1;
constexpr byte LED_BLINK = 2;

constexpr int BUTTON_PIN = 14;

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

void setup() {
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
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
