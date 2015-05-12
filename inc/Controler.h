
#ifndef CONTROLER_H
#define CONTROLER_H

#include <string>
#include <RF24.h>

/**
  * class Controler
  * 
  */

class Controler
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  Controler ();

  /**
   * Empty Destructor
   */
  virtual ~Controler ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   */
  void setupConnection ()
  {
    RF24 radio(RPI_BPLUS_GPIO_J8_15,RPI_BPLUS_GPIO_J8_24, BCM2835_SPI_SPEED_8MHZ);
  }


  /**
   */
  void receiveMessages ()
  {
    // if there is data ready
    if (radio.available())
    {
        // dump the payloads until we've got everything
        Message receivedData = {0};
        radio.read(&receivedData, sizeof(Message));
        if (receivedData.header.nodeId == 1) {
            TempSensorData data = receivedData.msgData.tempSensorData;
            printf("1111 retVal: %d, temperature: %d deg. Celsius, humidity %d %% \n", data.result, 
                                                                                       data.temperature, 
                                                                                       data.humidity );
        }
        if (receivedData.header.nodeId == 2) {
            TempSensorData data = receivedData.msgData.tempSensorData;
            printf("2222 with counter value: %d\n", data.result);
        }
    }
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  RF24 radio;
  SensorDB sensorDB;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of radio
   * @param new_var the new value of radio
   */
  void setRadio (RF24 new_var)   {
      radio = new_var;
  }

  /**
   * Get the value of radio
   * @return the value of radio
   */
  RF24 getRadio ()   {
    return radio;
  }

  /**
   * Set the value of sensorDB
   * @param new_var the new value of sensorDB
   */
  void setSensorDB (SensorDB new_var)   {
      sensorDB = new_var;
  }

  /**
   * Get the value of sensorDB
   * @return the value of sensorDB
   */
  SensorDB getSensorDB ()   {
    return sensorDB;
  }
private:


  void initAttributes () ;

};

#endif // CONTROLER_H
