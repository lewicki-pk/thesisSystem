
#ifndef SENSORNODE_H
#define SENSORNODE_H

#include <string>
#include <vector>
#include <map>
#include <cstdint>



/**
  * class SensorNode
  * 
  */

/******************************* Abstract Class ****************************
SensorNode does not have any pure virtual methods, but its author
  defined it as an abstract class, so you should not use it directly.
  Inherit from it instead and create only objects from the derived classes
*****************************************************************************/

class SensorNode
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  SensorNode ();

  /**
   * Empty Destructor
   */
  virtual ~SensorNode ();

  std::map<std::string, uint8_t> getNodeParametersMap();

  void getSensorValues ()
  {
  }

protected:

private:



};

#endif // SENSORNODE_H
