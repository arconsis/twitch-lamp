# Twitch On Air Lamp
Repository for the Twitch series on building our On Air Lamp

## Project explanation
We are building a lamp that will turn on as soon, as the [arconsis Twitch stream](https://www.twitch.tv/arconsis) goes live.

The lamp is a cheap lamp from amazon that runs on battery and USB power. It has three states - off, fading in to on, pulsing.

To control the lamp we are using a NodeMCU with an ESP8266 on it. 

We hack the lamp to have it only turn on (with fading) and off - the pulsing will be ditched. The wiring will be changed to power the led strip inside but also the NodeMCU. Since the ESP chip supports WiFi we will directly poll the Twitch API and get the information whether arconsis is streaming or not.

We are streaming every second Tuesday at 15:30 CEST.
