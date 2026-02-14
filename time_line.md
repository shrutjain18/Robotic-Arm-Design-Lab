# 📅 Project Timeline: 5-DoF Robotic Arm

This log tracks the development of a 5-Degree of Freedom robotic arm, transitioning from serial laptop control to a real-time motion mimicry system.
---

### **24 Jan 2026**
* **Procurement:** Ordered 2 DC motors and the L293D motor driver IC.
* **Hardware Sourcing:** Obtained an ESP32, breadboards, potentiometers, and wiring mesh from the Electronics Club.

### **6 Feb 2026**
* **Driver Testing:** Verified L293D functionality for bidirectional motor control and direction.
* **PWM Calibration:** Conducted speed testing to identify the PWM threshold required to overcome motor inertia.
* **Sensor Integration:** Configured encoder inputs and implemented software filtering for potentiometer values to stabilize analog readings.

### **10 Feb 2026**
* **Mapping Attempt:** Tried mapping analog input from a potentiometer directly to motor rotation.
* **Status:** ⚠️ Failed. The results were ambiguous due to missing technical data regarding internal gear ratios and the specific PPR of the shafts.

### **13 Feb 2026**
* **Kinematic Configuration:** Identified the PPR (Pulses Per Revolution) for both the encoder wheel and the output shaft.
* **System Calibration:** Calculated the exact Gear Ratio, enabling an accurate transfer function for input-to-output mapping.
* **Encoder Logic:** Finalized the configuration for reading encoder feedback to support a closed-loop control system.

---

### **Upcoming Objectives**
* Mapping potentiometer angle of rotation to that of motor shaft.
* Procurement of additional components and connecting all together.
* Implementing all motor control using potentiometer manual control. (End of Stage 1)
* Development of a reference structure for real-time motion mimicry. (Stage 2 begins)
* Implementation of an FSM (Finite State Machine) model to record and playback arm positions.
* Integration of a user interface using push buttons and an I2C display.
