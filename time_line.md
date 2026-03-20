# 📅 Project Timeline: 5-DoF Robotic Arm

[cite_start]This log tracks the technical development and hardware iterations of the 5-DoF robotic arm. [cite: 4, 10]

---

### **24 Jan 2026**
* [cite_start]**Initial Procurement:** Ordered 2 DC motors and an L293D motor driver. [cite: 40, 42]
* [cite_start]**Electronics Club Sourcing:** Obtained an ESP32, breadboards, and basic wiring. 

### **6 Feb 2026**
* **Component Validation:** Verified L293D motor and direction control.
* **PWM Tuning:** Identified the PWM threshold for motor rotation.
* **Input Conditioning:** Implemented signal filtering for potentiometer readings.

### **10 Feb 2026**
* **Mapping Attempt:** Tried mapping potentiometer input to motor rotation.
* **Result:** ⚠️ Failed. Logic was hindered by unknown gear ratios and PPR data.

### **13 Feb 2026**
* **System Resolution:** Found PPR for the encoder wheel and output shaft.
* **Kinematics:** Calculated the Gear Ratio to finalize the input-to-output transfer function.

### **18 Feb 2026**
* [cite_start]**Mapping Completion:** Successfully completed the mapping of potentiometer rotation angle to the motor shaft. [cite: 13]

### **Hardware Update**
* [cite_start]**Expansion:** Procured 2 additional DC motors, 1 L293D, and 4 potentiometers to begin scaling toward the 5-DoF goal. [cite: 42, 55]

### **< Midsem Break >**

### **16 March 2026**
* **Parallel Testing:** Successfully tested the new batch of motors and drivers.
* [cite_start]**Simultaneous Sensing:** Verified to read analog values from all potentiometers simultaneously. 

### **19 March 2026**
* **Multi-Motor Integration:** Attempted to control 4 motors simultaneously.
* **Result:** ⚠️ Partial Failure. 
* **Technical Discovery:** Identified ESP32 GPIO limitations. [cite_start]Several pins showed arbitrary behavior during boot-up (strapping pins), and the total usable GPIO count restricted full 4-motor implementation. 
* **Current State:** Successfully implemented stable control for 2 motors simultaneously.

---

### **Next Steps**
* [cite_start]**Controller Evaluation:** Assessing the feasibility of switching to an **Arduino Mega** (54 GPIOs) versus using two ESP32s in parallel. [cite: 56, 57]
* [cite_start]**Mechanical Design:** Designing the 3D-printed/laser-cut structure for the Stage 1 arm. [cite: 8]
* [cite_start]**Scaling Control:** Implementing 4-motor simultaneous control and completing Stage 1. [cite: 12]
