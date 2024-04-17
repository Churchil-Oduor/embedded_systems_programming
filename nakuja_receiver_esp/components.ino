/**
 * getLoadCellData - enables calibration of the load Cell and reading of the 
 * Load Cell Data.
 * @scale: reference to the loadCell object that has been initialized in the 
 * setup() function should be passed here so as to use it to make readings
 * Returns: Returns the loadCellData that has been read through the HX711 bridge.
 */
float getLoadCellData(HX711 &scale)
{
      long reading;
      float force;
   
      
      if (scale.is_ready())
        {
                reading = scale.read();
                force = (map(reading, 0, 4096, 0, 800) - 9225) / 100;
                return (force);
        }
        else
        {
              return (0);
        }        
}






