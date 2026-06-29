#ifndef EFFECTS_H
#define EFFECTS_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

// Generates mathematical plasma using overlapping sine/cosine waves
void renderPlasma(Adafruit_NeoMatrix &m) {
  static float timeCounter = 0;
  timeCounter += 0.05;

  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      // Calculate wave interference values
      float value1 = sin(x / 2.0 + timeCounter);
      float value2 = sin(y / 2.0 + timeCounter * 1.5);
      float value3 = sin((x + y) / 3.0 + timeCounter);
      float finalVal = (value1 + value2 + value3) / 3.0;

      // Map values into smooth RGB shifts
      uint8_t r = (uint8_t)((sin(finalVal * PI) + 1.0) * 127);
      uint8_t g = (uint8_t)((cos(finalVal * PI) + 1.0) * 127);
      uint8_t b = (uint8_t)((sin((finalVal + 0.5) * PI) + 1.0) * 127);

      m.drawPixel(x, y, m.Color(r, g, b));
    }
  }
  m.show();
}

#endif