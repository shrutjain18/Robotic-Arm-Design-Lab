# 📅 Project Timeline: 5-DoF Robotic Arm

This log tracks the technical development and hardware iterations of the 5-DoF robotic arm project.

---

### **24 Jan 2026**
* **Initial Procurement:** Ordered 2 DC motors and an L293D motor driver.
* **Electronics Club Sourcing:** Obtained an ESP32 microcontroller, breadboards, and basic wiring.

### **6 Feb 2026**
* **Component Validation:** Verified L293D motor and direction control.
* **PWM Tuning:** Identified the PWM threshold (minimum duty cycle) required for motor rotation.
* **Input Conditioning:** Implemented software filtering for potentiometer values to ensure stable analog readings.

### **10 Feb 2026**
* **Mapping Attempt:** Tried mapping potentiometer input to motor rotation.
* **Result:** ⚠️ Failed. The logic was hindered by unknown internal gear ratios and missing PPR (Pulses Per Revolution) data.

### **13 Feb 2026**
* **System Resolution:** Found the specific PPR for the encoder wheel and the output shaft.
* **Kinematics:** Calculated the Gear Ratio to finalize the input-to-output transfer function.

### **18 Feb 2026**
* **Mapping Completion:** Successfully completed the mapping of the potentiometer angle of rotation to that of the motor shaft.

### **Hardware Update**
* **Expansion:** Procured 2 additional DC motors, 1 L293D motor driver, and 4 potentiometers to begin scaling toward the 5-DoF objective.

---
### **< Midsem Break >**
---

### **16 March 2026**
* **Hardware Expansion Testing:** Successfully verified the new batch of motors and drivers.
* **Simultaneous Sensing:** Confirmed the ability to read analog values from all 4 potentiometers simultaneously.

### **19 March 2026**
* **Multi-Motor Integration:** Attempted to control 4 motors simultaneously.
* **Result:** ⚠️ Partial Failure. 
* **Technical Discovery:** Identified ESP32 GPIO limitations. Specific "strapping pins" showed arbitrary behavior during boot-up, and the total usable GPIO count restricted a full 4-motor implementation.
* **Current State:** Successfully implemented stable control for 2 motors simultaneously.

---

### **Next Steps & Future Goals**
* **Controller Evaluation:** Assessing the feasibility of switching to an Arduino Mega (54 GPIOs) versus using two ESP32s in parallel to handle the required pin count.
* **Mechanical Design:** Designing the 3D-printed or laser-cut structure for the Stage 1 arm.
* **Stage 1 Completion:** Implementing all motor control using potentiometer manual control.
* **Stage 2 Transition:** Development of a reference structure for real-time motion mimicry.
* **State Management:** Implementation of an FSM (Finite State Machine) model to record and playback arm positions.
* **User Interface:** Integration of a UI using push buttons and an I2C display.
