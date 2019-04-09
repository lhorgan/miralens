/**************************************************************************
 * Name: Photo.hpp
 * Author(s): Quan Do, Luck Horgan, Matin Raayai Ardakani
 * Header for controling the phototransistor(s) in MiraLens. 
 ***************************************************************************/
#pragma once
#define DEFAULT_PHOTO_PIN A3
#define DEFAULT_FRAME_ON_VAL 100
#define DEFAULT_FRAME_OFF_VAL 0

class PhotoTransistor {
  private:
    const int pin;
    const int frame_cutoff_val;

  public:
    PhotoTransistor(int pin_num=DEFAULT_PHOTO_PIN, int frame_off_val=DEFAULT_FRAME_ON_VAL,
     int frame_on_val=DEFAULT_FRAME_OFF_VAL);
    virtual ~PhotoTransistor() {};,
    bool frameState();
};