# Mass Flow Controller Commmunication Arduino library

Arduino Library for Serial MFC communication 

To be used with SparkFun Transceiver Breakout - MAX3232
https://www.sparkfun.com/products/11189

-Rishi Tappeta


## Functions

The following public functions are exposed.

### setFlow(float flow)

### setupFlow()

### getFlow()
 
### setUnitID()

### setMaxFlow()


  
## Example usage

Make sure you have the LCD03 library installed as above. To use LCD03 simply include Wire.h and "LCD03.h" in your sketch and instantiate a new LCD03 instance.

```c++
#include <Wire.h>
#include "LCD03.h"

// Create new LCD03 instance
LCD03 lcd;

void setup() {
  // Initialise the LCD
  lcd.begin(20, 4);

  // Turn on the backlight
  lcd.backlight();
  
  // Write to the LCD
  lcd.print("Hello world!");

  // Wait for 5 seconds
  delay(5000);

  // Clear the LCD
  lcd.clear();
}

void loop() {
  // Set the cursor to the top left
  lcd.home();

  // Print the uptime in millis
  lcd.print(millis());
}
```







