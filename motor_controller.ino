void motorOn(byte chosen) {
  switch (chosen) {
    case 0: digitalWrite(11, HIGH); break;
    case 1: digitalWrite(8, HIGH); break;
    case 2: digitalWrite(9, HIGH); break;
    case 3: digitalWrite(10, HIGH); break;
  }
}

void motorOff(byte chosen) {
  switch (chosen) {
    case 0: digitalWrite(11, LOW); break;
    case 1: digitalWrite(8, LOW); break;
    case 2: digitalWrite(9, LOW); break;
    case 3: digitalWrite(10, LOW); break;
  }
}
