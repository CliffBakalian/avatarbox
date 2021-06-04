#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav           playSdWav1;
AudioOutputAnalog        i2s1;
AudioConnection          patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection          patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;

#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11 
#define SDCARD_SCK_PIN   13 

//init how many audio tracks per person
int aang = 6;
int katara = 5;
int zuko = 6;
int toph = 6;
int sokka = 5;
int suki = 4;
int iroh = 5;
int opening = 1;
int appa = 3;
int mai = 3;
int azula = 4;
int tylee = 4;

//assign each person an index
int num_tracks[12] = {aang, katara, zuko, toph, sokka, suki, iroh, opening, appa, mai, azula, tylee};

char filename[7];

void setup() {
  Serial.begin(9600);
  Serial4.begin(9600); // because I used RX4 and TX4
  pinMode(5, OUTPUT); 
  pinMode(13, OUTPUT);
  digitalWrite(5, 1); // this tells the audio amplifier something that's important no idea really
  AudioMemory(8);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  delay(1000);
}

void play_track(int id){
  if (playSdWav1.isPlaying()) { // lazy interrupt
    playSdWav1.stop();
    delay(10);
  }
  int track = random(0,num_tracks[id]);
  sprintf(filename,"%d%d.wav",id,track); // lazy naming convention
  playSdWav1.play(filename);
  delay(10); // wait for library to parse WAV info
}
void loop() {
  if (Serial4.available()){
    byte a = Serial4.read(); // each person got a different code and index
    // Nextion code will send a single byte of data telling which person was tapped
    if (a == 0x01) play_track(0);
    else if (a == 0x02) play_track(1);
    else if (a == 0x03) play_track(2);
    else if (a == 0x04) play_track(3);
    else if (a == 0x05) play_track(4);
    else if (a == 0x06) play_track(5);
    else if (a == 0x07) play_track(6);
    else if (a == 0x08) play_track(7);
    else if (a == 0x09) play_track(8);
    else if (a == 0x0A) play_track(9);
    else if (a == 0x0B) play_track(10);
    else if (a == 0x0C) play_track(11);
  }
}
