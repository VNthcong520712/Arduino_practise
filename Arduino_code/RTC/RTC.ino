/*
  DS1302 Real Time Clock (RTC) Example
  ------------------------------------
  Description:
  This sketch demonstrates how to use the DS1302 RTC module with Arduino.
  It initializes the clock, sets the current time and date, and displays
  them continuously via the Serial Monitor.

  Wiring (DS1302 to Arduino):
  ---------------------------
  - CE (RST)   -> Digital Pin 2
  - I/O (DAT)  -> Digital Pin 3
  - SCLK (CLK) -> Digital Pin 4
  - VCC        -> 5V
  - GND        -> GND

  Libraries Required:
  -------------------
  - DS1302 (by Henning Karlsen or compatible)

  Setup Info:
  -----------
  - This code sets the time to 19:25:20 on Tuesday, June 8, 2021.
  - It then prints the date and time every second to the Serial Monitor.

  Notes:
  ------
  - You can comment out the `rtc.setTime()` and `rtc.setDate()` lines
    after initial setup to preserve time on battery backup.
*/

#include <DS1302.h>

// Initialize DS1302 with pin connections: CE, I/O, SCLK
DS1302 rtc(2, 3, 4);

void setup()
{
  Serial.begin(9600);

  // Allow clock to run and disable write protection
  rtc.halt(false);
  rtc.writeProtect(false);

  // Set the initial time and date (modify as needed)
  rtc.setDOW(TUESDAY);        // Set day of the week
  rtc.setTime(19, 25, 20);    // Set time: HH, MM, SS (24-hour format)
  rtc.setDate(8, 6, 2021);    // Set date: DD, MM, YYYY
}

void loop()
{
  // Display day of the week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");

  // Display date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Display time
  Serial.println(rtc.getTimeStr());

  // Wait 1 second before updating again
  delay(1000);
}
