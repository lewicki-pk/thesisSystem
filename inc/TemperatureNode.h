
#ifndef TEMPERATURENODE_H
#define TEMPERATURENODE_H
#include "SensorNode.h"

#include <string>
#include vector



/**
  * class TemperatureNode
  * 
  */

class TemperatureNode : virtual public SensorNode
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  TemperatureNode ();

  /**
   * Empty Destructor
   */
  virtual ~TemperatureNode ();

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  


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

  uint8_t temperatureValue;
  uint8_t humidityValue;
  uint8_t lastReadingStatus;
  undef nodeStatus;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of temperatureValue
   * @param new_var the new value of temperatureValue
   */
  void setTemperatureValue (uint8_t new_var)   {
      temperatureValue = new_var;
  }

  /**
   * Get the value of temperatureValue
   * @return the value of temperatureValue
   */
  uint8_t getTemperatureValue ()   {
    return temperatureValue;
  }

  /**
   * Set the value of humidityValue
   * @param new_var the new value of humidityValue
   */
  void setHumidityValue (uint8_t new_var)   {
      humidityValue = new_var;
  }

  /**
   * Get the value of humidityValue
   * @return the value of humidityValue
   */
  uint8_t getHumidityValue ()   {
    return humidityValue;
  }

  /**
   * Set the value of lastReadingStatus
   * @param new_var the new value of lastReadingStatus
   */
  void setLastReadingStatus (uint8_t new_var)   {
      lastReadingStatus = new_var;
  }

  /**
   * Get the value of lastReadingStatus
   * @return the value of lastReadingStatus
   */
  uint8_t getLastReadingStatus ()   {
    return lastReadingStatus;
  }

  /**
   * Set the value of nodeStatus
   * @param new_var the new value of nodeStatus
   */
  void setNodeStatus (undef new_var)   {
      nodeStatus = new_var;
  }

  /**
   * Get the value of nodeStatus
   * @return the value of nodeStatus
   */
  undef getNodeStatus ()   {
    return nodeStatus;
  }
private:


  void initAttributes () ;

};

#endif // TEMPERATURENODE_H
