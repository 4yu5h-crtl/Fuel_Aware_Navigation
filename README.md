# 🚗 IoT Based Fuel Efficient Route Optimizer

This project combines an ESP32-based fuel monitoring system with a React web application for fuel-efficient route planning.

## 🌟 Features

- **Real-time Fuel Monitoring**: Integrates with ESP32 and ultrasonic sensor to track fuel levels in a bottle
- **Smart Route Optimization**: Calculates routes based on current fuel levels and consumption rates
- **Multiple Route Options**: Provides alternative routes based on fuel efficiency
- **Automatic Location Detection**: Uses browser geolocation for quick start
- **Refueling Alerts**: Notifies you when you need to refuel for your journey
- **Interactive Map Interface**: Clean and intuitive Google Maps integration
- **Fuel History Visualization**: Charts and tables showing historical fuel level data
- **Responsive Design**: Works seamlessly on desktop and mobile devices

## 🛠️ Tech Stack

- **Frontend**: React.js with TypeScript and Material-UI
- **Maps**: Google Maps JavaScript API
- **Charts**: Chart.js with react-chartjs-2
- **Hardware Integration**: ESP32 microcontroller with ultrasonic sensor
- **Backend**: Node.js with Express
- **Database**: MySQL for storing fuel readings
- **Real-time Updates**: HTTP polling for data refresh

## 🚀 Getting Started

### Prerequisites

- Node.js (v14 or higher)
- npm or yarn
- Google Maps API key
- ESP32 microcontroller with ultrasonic sensor
- MySQL database

### Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/fuel-aware-navigation.git
cd fuel-aware-navigation
```

2. Install frontend dependencies:
```bash
npm install
```

3. Create a `.env` file in the root directory and add your Google Maps API key:
```
REACT_APP_GOOGLE_MAPS_API_KEY=your_api_key_here
```

4. Install server dependencies:
```bash
cd server
npm install
```

5. Update the MySQL connection details in `server.js` if needed:
```javascript
const db = mysql.createConnection({
  host: 'localhost',
  user: 'root',
  password: 'YOUR_MYSQL_PASSWORD',
  database: 'fuel_monitor'
});
```

6. Start the server:
```bash
cd server
npm start
```

7. In a new terminal, start the frontend development server:
```bash
cd fuel-aware-navigation
npm start
```

8. Open [http://localhost:3000](http://localhost:3000) to view the application in your browser.

## 🔧 Hardware Setup

1. Connect the ultrasonic sensor to your ESP32:
   - TRIG_PIN: GPIO 5
   - ECHO_PIN: GPIO 18

2. Update the WiFi credentials and server URL in `fuel_efficiency.ino`:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   const char* serverUrl = "http://YOUR_SERVER_IP:3001";
   ```

3. Adjust the bottle dimensions and calibration parameters in the code:
   ```cpp
   const float BOTTLE_HEIGHT = 15.9;  // Height of the bottle in cm
   const float BOTTLE_DIAMETER = 6.0; // Diameter of the bottle in cm
   const float BOTTLE_VOLUME = 0.45;  // Total volume of the bottle in liters
   const float EMPTY_DISTANCE = 10.0; // Distance when bottle is empty (in cm)
   const float FULL_DISTANCE = 2.0;   // Distance when bottle is full (in cm)
   ```

4. Upload the code to your ESP32 using the Arduino IDE.

## 📱 How to Use

1. **Monitor Fuel Levels**:
   - The application automatically connects to the ESP32 and displays real-time fuel levels
   - Fuel level is displayed as a progress bar with color indicators
   - Connection status is shown with a chip indicator

2. **Plan Routes**:
   - Enter your destination in the search bar
   - The system will automatically detect your current location
   - View multiple route options based on fuel efficiency
   - Select the most suitable route based on your needs

3. **View Fuel History**:
   - Switch to the "Fuel History" tab to view historical data
   - See a chart of fuel levels and distances over time
   - View a table of recent readings

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


## Troubleshooting

- If the ESP32 cannot connect to the server, check the WiFi credentials and server URL.
- If the server cannot connect to the MySQL database, check the database credentials.
- If the web application cannot fetch data from the server, check that the server is running and the API endpoints are correct.
- If the fuel level readings seem inaccurate, recalibrate the ultrasonic sensor parameters in the ESP32 code.
