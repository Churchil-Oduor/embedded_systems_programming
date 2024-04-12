
/**
 * Buzzer - turns buzzer on to produce Siren sound.
 * @pin: pin connecting Piezzo.
 * @command: either on or off.
 */

void Buzzer(const int *pin, char *command) {
  int i;

  if (strcmp(command, "turn-on") == 0) {
    for (i = 100; i < 1000; i += 100) {
      tone(*pin, i);
      delay(50);
    }

    for (i = 1000; i > 100; i -= 100) {
      tone(*pin, i);
      delay(50);
    }

  } else {
    noTone(*pin);
  }
}
