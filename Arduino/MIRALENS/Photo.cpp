/**************************************************************************
 * Name: Photo.cpp
 * Author(s): Quan Do, Luck Horgan, Matin Raayai Ardakani
 * Source code for controling the phototransistor(s) in MiraLens. 
 ***************************************************************************/

PhotoTransistor::PhotoTransistor(int pin_num=DEFAULT_PHOTO_PIN, 
    int frame_off_val=DEFAULT_FRAME_ON_VAL,
    int frame_on_val=DEFAULT_FRAME_OFF_VAL) {
    pin = pin_num;
    frame_cutoff_val = (frame_on_val - frame_off_val) / 2;    
}

bool PhotoTransistor::frameState() {
    return analogRead(SENSOR_PIN) > FRAME_CUTTOFF_VAL;
}
