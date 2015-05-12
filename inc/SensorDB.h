
#ifndef SENSORDB_H
#define SENSORDB_H

#include <string>
#include vector



/**
  * class SensorDB
  * 
  */

class SensorDB
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  SensorDB ();

  /**
   * Empty Destructor
   */
  virtual ~SensorDB ();

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

  set<SensorNode> sensorNodeContainer;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of sensorNodeContainer
   * @param new_var the new value of sensorNodeContainer
   */
  void setSensorNodeContainer (set<SensorNode> new_var)   {
      sensorNodeContainer = new_var;
  }

  /**
   * Get the value of sensorNodeContainer
   * @return the value of sensorNodeContainer
   */
  set<SensorNode> getSensorNodeContainer ()   {
    return sensorNodeContainer;
  }
private:


  void initAttributes () ;

};

#endif // SENSORDB_H
