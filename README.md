# 🚗 Smart Line-Following and Obstacle-Avoiding Car

This project was developed as part of a university group assignment. We built an autonomous vehicle using an Arduino that can:

- Follow a white line path  
- Detect and avoid obstacles  
- Climb a hill using tilt detection  
- Stop automatically at the end of the course  

## 📹 Demo

https://github.com/user-attachments/assets/04ac54a8-2143-45ec-a4be-e9dd33efa9cd
https://github.com/user-attachments/assets/a25a2c38-8477-4c7f-b343-45692cd8cab3

[](https://github.com/user-attachments/assets/c5e62b38-bff8-4e1d-b33e-384c1fbf224e)

---

## 🛠 Features

### ✅ White Line Following
- Uses IR sensors to detect white lines.
- Makes real-time steering adjustments based on sensor input.

### ✅ Obstacle Avoidance
- Front and side ultrasonic sensors detect obstacles.
- Implements avoidance maneuvers based on proximity data.

### ✅ Hill Climbing
- Utilizes a tilt switch to detect inclines.
- Boosts motor speed to climb the hill and stabilizes afterward.

### ✅ Automatic Stopping
- Stops when both left and right IR sensors detect no line (i.e., course end).

---

## 🔧 Hardware Used

- Arduino UNO  
- IR Line Sensors (x4)  
- Ultrasonic Sensors (x3)  
- Tilt Sensor  
- Servo Motor for Steering  
- Dual Motor Driver  
- 2 DC Motors  

---

## 📄 Code Overview

The main logic is written in Arduino C++.

Key files:  
- `self-driving-car.ino`: Main control loop with sensor reading, steering, and movement logic.

### Highlights:

```cpp
if (leftSensorValue == 0 && rightSensorValue == 0) {
    analogWrite(RPWM, 00); // Stop the car
    steeringServo.write(90);
    stop_the_car = true;
}
```

> This snippet handles the stopping mechanism when the end of the line is reached.

---

## 📁 Repository Structure

```
Arduino/
└── self-driving-car.ino       # Main Arduino code
README.md                   # Project documentation
```

---

## 📬 Contact

For any questions or feedback, feel free to reach out at [516625@student.saxion.nl](mailto:516625@student.saxion.nl)

---

## 📜 License

This project is for educational purposes. Please contact the team for reuse or collaboration.
