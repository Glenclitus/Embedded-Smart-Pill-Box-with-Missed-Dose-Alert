# 💊 Embedded Smart Pill Box with Missed-Dose Alert

## 📌 Overview
The Embedded Smart Pill Box is an Arduino-based healthcare device designed to help users take their medication on time and avoid missed doses. It provides real-time reminders and verifies whether the medicine has been taken using sensor-based detection.

## 🚀 Features
- ⏰ Time-based reminders using RTC module  
- 🔔 Buzzer alerts and LED indication  
- 📟 LCD display for real-time information  
- 👆 Touch sensor for user interaction  
- ⚙️ Servo motor for automatic box opening  
- 📡 IR sensor for medicine intake detection  
- ⚠️ Missed-dose detection system  

## 🛠️ Components Used
- Arduino Uno  
- RTC Module (DS3231)  
- IR Sensor  
- Touch Sensor  
- Servo Motor (SG90)  
- 16x2 LCD Display (I2C)  
- Buzzer  
- LED  
- Jumper Wires & Breadboard  

## ⚙️ Working Principle
1. RTC module tracks real-time medication schedule  
2. At set times, buzzer and LED alert the user  
3. LCD displays the corresponding dose (Morning/Afternoon/Night)  
4. User touches the sensor → servo opens pill compartment  
5. IR sensor detects pill removal  
6. System confirms whether medicine is taken or missed  

## 📂 Project Structure
smart-pill-box/
│
├── code/
│   └── smart_pill_box.ino
│
├── images/
│   └── setup.jpg
│
├── report/
│   └── documentation.pdf
│
└── README.md

## 📸 Output / Setup
<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/daf0ecb4-01ca-4e51-a596-cbb5dfb68c27" />


## 🔮 Future Scope
- 📱 Mobile app integration  
- 🌐 IoT-based monitoring  
- 🔔 SMS alerts for caregivers  
- 🗂️ Data logging for medical tracking  

## 👨‍💻 Authors
- Glen Clitus Manjooran  
- Bertil Anto I  

## ⭐ Note
This project demonstrates how embedded systems and sensor technologies can be used to improve healthcare and medication adherence.
