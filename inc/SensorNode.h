
#ifndef SENSORNODE_H
#define SENSORNODE_H

#include <string>
#include vector



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
  void getSensorValues ()
  {
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

public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  

private:



};

#endif // SENSORNODE_H
