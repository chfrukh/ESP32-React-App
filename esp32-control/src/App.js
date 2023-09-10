import React, { useState, useEffect } from 'react';

function App() {
  // State to store distance from ultrasonic sensor
  const [distance, setDistance] = useState('Loading...');

  // Function to fetch the distance from the ESP32
  const fetchDistance = async () => {
    try {
      // Send a GET request to the ESP32's endpoint
      const response = await fetch('http://esp32-ip-address');
      const data = await response.text();
      
      // Update the 'distance' state with the fetched data
      setDistance(data);
    } catch (error) {
      // Handle errors, such as network issues or ESP32 unavailability
      console.error('Error fetching data from ESP32:', error);
    }
  };

  // Use useEffect to fetch the distance on component mount
  useEffect(() => {
    // Call 'fetchDistance' when the component mounts
    fetchDistance();
  }, []);

  // Function to send requests to control the LEDs
  const controlLED = async (command) => {
    try {
      // Send a request to control the LEDs on the ESP32
      await fetch(`http://esp32-ip-address/${command}`);
      
      // Update the distance after controlling the LEDs (you can remove this if not needed)
      fetchDistance();
    } catch (error) {
      // Handle errors that may occur during LED control
      console.error('Error controlling LED:', error);
    }
  };

  return (
    <div className="App">
      <h1>ESP32 Control</h1>
      <p>Distance from Ultrasonic Sensor: {distance} inches</p>
      <button onClick={() => controlLED('on1')}>Turn On LED 1</button>
      <button onClick={() => controlLED('off1')}>Turn Off LED 1</button>
      <button onClick={() => controlLED('on2')}>Turn On LED 2</button>
      <button onClick={() => controlLED('off2')}>Turn Off LED 2</button>
    </div>
  );
}

export default App;
