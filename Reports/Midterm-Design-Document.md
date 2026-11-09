# Midterm Design Document
The following document is Fall 2026 Capstone Team 1's Midterm Design Document, comprised of the team's Project Proposal & Conceptual Design.

# Project Proposal

## Introduction & Background

The IEEE (Institute of Electrical and Electronics Engineers) hosts an annual conference for the southeastern region known as SoutheastCon (SECON). As part of the conference, the annual Hardware Competition challenges university students to apply their engineering knowledge through the design, construction, and programming of an autonomous robotic system. For the 2027 competition, “Stock Car Race,” teams are tasked with developing a fully autonomous ground robot capable of navigating a racecourse and completing three laps within a three-minute time limit. During the race, the robot must avoid randomly placed obstacles, identify an assigned pit area using an AprilTag, perform a pit stop and tire exchange, and return to the course. Points are earned based on how well the robot can complete these tasks. Additional points can be earned by avoiding contact with obstacles and course walls and raising our university flag during the final lap. To meet these objectives, two Capstone teams will be responsible for the development of this autonomous robot: a mechanical team and an electrical team. The mechanical team is responsible for the chassis, drivetrain, and actuators. Because both teams build one robot under shared size, mass, and safety limits, the two teams must jointly define interface requirements.

### Proposal Overview

This proposal presents the planned development of the autonomous robot’s electrical systems and the approach the team will take to meet the requirements of the 2027 IEEE SoutheastCon Hardware Competition. The remaining sections of this proposal define the electrical requirements, design approach, and verification plan within the shared constraints.

## Formulating the Problem

The customers for this project are the TTU ECE department and Dr. Storm, the Fall 2026 Capstone instructor. The TTU ECE department, Tennessee Tech IEEE Club, and the mechanical SECON team are all stakeholders in this project. As this team represents TTU in the competition, the TTU ECE department and IEEE Club have an interest in how high the team places in the competition. The success of the mechanical portion of the robot will depend on how well the electrical/computer portion is designed, so they are also direct stakeholders in the success of this project. The 2027 IEEE Stock Car Race competition requires a fully autonomous robot to complete three laps around a track within three minutes, do a pit stop, and park within a designated location after completing the race [4]. 

Completing the race in 3 minutes or less awards 100 points, and crossing the finish line in under 2 minutes and 45 seconds awards an additional 30 points \[4\]. The bulk of the points are awarded through a variety of mid-race assignments the robot completes. For instance, the robot must be able to read an AprilTag fixed on the arena, and that reveals which of the three zones the robot needs to make a pit stop at and where it needs to park when it finishes the race for additional points \[4\]. The race begins when the referee raises a green flag, and 10 points are awarded if the robot starts on time \[4\].

At the start of the race, every robot will be holding a red spare tire and must fit, tire included, within a 12 in × 12 in × 12 in space \[3, R01\]\[4, App. G\]. Robots are allowed to expand past that area once the race starts \[3, R01\]. Between laps one and two or two and three, the robot must make a pit stop, where it drops off the red tire and picks up a different blue tire \[4, App. G\]. Doing so in the pit box assigned by the AprilTag earns 25 points for the drop-off and 40 points for the pickup, while using any other pit box earns only 12 and 20 points, and the pickup points are lost if the robot drops the blue tire before crossing the finish line \[4, App. G\]. The final major assignment the robot needs to do to earn points is raising the school flag during the final lap \[4\].

The competition is not just about finishing the race in three minutes. A myriad of assignments must be completed during the race to earn every point possible. The robot must perceive its environment, track its own progress, and manipulate game elements throughout the race. Therefore, the problem is defined by the following requirements:

1. The robot shall operate autonomously with no human input after the start command.

2. The robot shall begin the race upon detecting the referee's green flag.

3. The robot shall fit within a 12 in × 12 in × 12 in space at the start while holding a tire.

4. The robot shall complete three laps within three minutes.

5. The robot shall navigate a course whose path is known while avoiding obstacles that may be placed in various quadrants. The location of the quadrants is known, however which quadrants have an obstacle and the location within the quadrant is unknown.

6. The robot shall read the arena AprilTag to determine its assigned pit zone and parking location.

7. The robot shall track laps completed, elapsed time, and pit-stop status.

8. The robot shall make one pit stop between either laps one and two or laps two and three, remaining in the pit for at least two seconds.

9. The robot shall drop its tire in the assigned zone and pick up a different tire before leaving the pit.

10. The robot shall raise the school flag during the final lap.

11. The robot shall autonomously stop in its assigned zone at the end of the race.

While solutions exist for individual tasks, there is no known off-the-shelf solution that can complete all requirements set out by the race at once. This means a solution must be custom designed, tested, and competition-ready by April 2027. Designing such a robot requires knowledge including but not limited to: Control systems, power systems, embedded firmware and hardware, motor controls, image processing, CAD design, and soldering. A project of this size and complexity requires a full team with a diversity of skills to match these requirements and address the problem.

## Specifications and Constraints

This section defines the requirements the robot must meet. "Shall" marks a mandatory requirement, "should" marks a goal the team intends to meet, and "may" marks an optional one. Each requirement is written to be measurable, and each specification lists how it will be verified.

Specifications come from the project's stakeholders: The ECE department and Dr. Storm. Their shared goal is to place competitively in the IEEE Southeast Conference (SECON) 2027 Hardware Competition.

Constraints come from the IEEE SECON Game Design Committee, the governing body that sets the competition rules in Game Manual 1 \[3\].

Several vehicle specifications restate a competition rule with a stricter target, so the robot passes inspection with margin.

### Specifications

#### Objective Specifications

The objective specifications define the performance the stakeholders require of the system.

**TABLE I: OBJECTIVE SPECIFICATIONS BASED ON STAKEHOLDERS AND TEAM**

| ID | Requirement | Verification |
|---|---|---|
| OS-1 | The robot shall complete all game tasks autonomously, with no human input following the start command \[3, Sec. 3.3.1\]. | Full practice runs with no operator contact after start. |
| OS-2 | The robot shall complete its full task sequence within the 180 s match period \[3, Sec. 3.3.1\]. | Timed practice runs. |
| OS-3 | The robot should score no fewer than 275 points in at least 6 of 10 practice runs (PT-2). | Score log from the final round of practice runs, per the Performance Targets section. |
| OS-4 | The robot shall score no fewer than 175 points, with no Red Card, in at least 8 of 10 practice runs (PT-1). | Score log from the final round of practice runs, per the Performance Targets section. |
| OS-5 | The robot shall reach a ready-to-start state within 60 s of power-on \[3, Sec. 7.2\]. | Timed power-on to ready-indicator tests. |
| OS-6 | The robot shall operate for no less than 15 min† on a single battery charge \[3, Sec. 7.1\]. | Continuous runtime test from full charge. |
| OS-7 | The robot shall pass official inspection on the first attempt \[3, Sec. 6.1\]. | Mock inspection per the Appendix A checklist prior to travel. |
| OS-8 | Total project cost shall not exceed $1,200. | Tracked bill of materials and purchase records. |

#### Robot Specifications

The robot specifications define the physical, electrical, and interface requirements of the robot platform.

**TABLE II: ROBOT SPECIFICATIONS BASED ON STAKEHOLDERS AND TEAM**

| ID    | Requirement                                                                                                                                                                              | Verification                                                    |
|-------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|-----------------------------------------------------------------|
| RS-1  | The starting configuration shall not exceed 11.75in × 11.75in × 11.75in, providing 0.25 in of margin below the 12 in limit \[3, R01\].                                                   | Fit test in a 12 in sizing box; caliper measurement.            |
| RS-2  | The robot shall maintain a footprint of at least 10.25in × 10.25in for the first 3in above the running surface at all times \[3, R01\].                                                  | Measurement in starting and fully expanded configurations.      |
| RS-3  | The robot shall not exceed 11kg in its heaviest configuration, providing 1kg of margin below the 12 kg limit \[3, R02\].                                                                 | Calibrated scale.                                               |
| RS-4  | The start input shall be a single momentary pushbutton labeled "START" in characters no less than 0.5in in height, with an indicator LED illuminating within 1s of actuation \[3, R03\]. | Visual inspection; timed actuation test.                        |
| RS-5  | The robot shall remain physically static for no less than 5.5s following the start command \[3, R03\].                                                                                   | Frame-by-frame video timing.                                    |
| RS-6 | The emergency stop shall be a red latching switch labeled "STOP," accessible from the top of the robot, and shall remove power from all actuators within 500 ms of actuation. In accordance with ISO 13850:2015, Sec. 4.1.1.2, resetting the emergency stop shall not automatically restart the drivetrain or any actuator; a separate intentional start or arming command shall be required. | Oscilloscope measurement of actuator supply voltage during E-stop activation; repeat the test after resetting the E-stop and verify that no actuator restarts until a separate start command is issued. |
| RS-7  | Team identification shall be displayed on no fewer than two faces of the robot in characters or graphics no less than 1.5in in height \[3, R10\].                                        | Readability assessment from 6 ft by a non-team member.          |
| RS-8  | All sensing, processing, and decision-making shall be performed by computing hardware mounted on the robot \[3, R18\].                                                                   | Design review; test run with all external devices powered down. |
| RS-9  | The robot shall incorporate a designated handle and shall be removable from the Field by a single person, without tools, in less than 30 s \[3, R09\].                                   | Timed removal test.                                             |
| RS-10 | The battery shall be replaceable without tools in less than 60s \[3, Sec. 7.2\].                                                                                                         | Timed swap test.                                                |
| RS-11 | The robot may expand beyond its starting envelope after the match has begun, and Game Elements carried at start may extend beyond that envelope \[3, R01\].                              | ---                                                             |
| RS-12 | The robot may employ wireless communication between onboard components \[3, R19\].                                                                                                       | ---                                                             |

#### Board Specifications

The competition field and game elements are described and specified in Game Manual 2 \[4\]. Table III states the requirements for the team's practice board and game elements.

**TABLE III: BOARD SPECIFICATIONS BASED ON STAKEHOLDERS AND TEAM**

| ID   | Requirement                                                                                                                                       | Verification                                 |
|------|---------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------|
| BS-1 | The practice board shall be built on a 4 ft × 8 ft, 23/32 in RTD sheathing base per the GM2 field description and bill of materials, with obstacle quadrants laid out per Appendix E \[4, Sec. 3.2, App. B, App. E\]. | Dimensional inspection against GM2 drawings and Appendix E. 
| BS-2 | The practice board shall replicate the GM2 Field dimensions to within ±0.125in.                                                                   | Dimensional inspection against GM2 drawings. |
| BS-3 | Practice Game Elements shall match GM2 dimensions and materials in \[4\].                                                                         | Comparison against specifications.           |
| BS-4 | The practice board may be constructed in sections for transport. Practice boards are not permitted in the competition Pit Area \[3, Sec. 3.3.1\]. | ---                                          |

### Constraints

Constraints are defined by the IEEE SECON Game Design Committee though both Game Manual 1 \[3\] and Game Manual 2 \[4\] are not subject to negotiation with the team. Compliance is checked and verified at an official inspection using the checklist of Appendix A of the manual \[3, Sec. 6.1, App. A\]. Violations are brought to the attention of each team during the inspection and shown during competition with the use of Yellow and Red Cards at the referee’s discretion. A Red Card will set the match score to zero and constitutes an automatic loss in an Elimination Match \[3, C03\].

#### Objective Constraints

Objective constraints govern the conduct of the robot during a match and the handling of the robot at the competition.

**TABLE IV: OBJECTIVE CONSTRAINTS**

| ID    | Constraint                                                                                                                                                                               |
|-------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| OC-1  | The starting configuration shall not exceed 11.75in × 11.75in × 11.75in, providing 0.25in of margin below the 12in limit \[3, R01\].                                                     |
| OC-2  | The robot shall maintain a footprint of at least 10.25in × 10.25in for the first 3 in above the running surface at all times \[3, R01\].                                                 |
| OC-3  | The robot shall not exceed 11kg in its heaviest configuration, providing 1kg of margin below the 12kg limit \[3, R02\].                                                                  |
| OC-4  | The start input shall be a single momentary pushbutton labeled "START" in characters no less than 0.5in in height, with an indicator LED illuminating within 1s of actuation \[3, R03\]. |
| OC-5  | The robot shall remain physically static for no less than 5.5s following the start command \[3, R03\].                                                                                   |
| OC-6  | The emergency stop shall be a red latching switch labeled "STOP," accessible from the top of the robot, and shall remove power from all actuators within 500ms of actuation \[3, R04\].  |
| OC-7  | Team identification shall be displayed on no fewer than two faces of the robot in characters or graphics no less than 1.5in in height \[3, R10\].                                        |
| OC-8  | All sensing, processing, and decision-making shall be performed by computing hardware mounted on the robot \[3, R18\].                                                                   |
| OC-9  | The robot shall incorporate a designated handle and shall be removable from the Field by a single person, without tools, in less than 30s \[3, R09\].                                    |
| OC-10 | The battery shall be replaceable without tools in less than 60s \[3, Sec. 7.2\].                                                                                                         |
| OC-11 | The robot may expand beyond its starting envelope after the match has begun, and Game Elements carried at start may extend beyond that envelope \[3, R01\].                              |
| OC-12 | The robot may employ wireless communication between onboard components \[3, R19\].                                                                                                       |

#### Robot Constraints

Robot constraints are defined as bound by the physical and electrical design of the robot.

**TABLE V: ROBOT CONSTRAINTS**

| ID    | Constraint                                                                                                                                                                                                                                                                                                        |
|-------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| RC-1  | The robot shall fit within 12in × 12in × 12in (304.8mm) at match start, resting on level ground, static, and without external aid \[3, R01\].                                                                                                                                                                     |
| RC-2  | The robot shall measure at least 10in × 10in for the first 3 in above the running surface \[3, R01\].                                                                                                                                                                                                             |
| RC-3  | Robot mass shall not exceed 12kg (≈26.5lb) in the heaviest configuration \[3, R02\].                                                                                                                                                                                                                              |
| RC-4  | The start input shall be a single, clearly marked, simple electrical button or switch \[3, R03\].                                                                                                                                                                                                                 |
| RC-5  | Each robot unit shall incorporate a clearly marked emergency stop capable of halting all robot actions safely and rapidly \[3, R04\].                                                                                                                                                                             |
| RC-6  | The robot shall not incorporate sharp edges; explosive, pyrotechnic, toxic, corrosive, or biohazardous materials; flammable gases; materials that would delay the match schedule if released; devices grounding the robot to the Field; exposed abrasives; uncontained liquids or gels; or hydraulics \[3, R05\]. |
| RC-7  | Lubricants and greases shall be contained such that they present no risk of leakage onto the Field \[3, R06\].                                                                                                                                                                                                    |
| RC-8  | Pneumatic systems shall not exceed 100 psi and shall present no unresolved concerns at inspection \[3, R07\].                                                                                                                                                                                                     |
| RC-9  | Aerial devices shall not be employed unless expressly permitted by Game Manual 2 \[4, R08\].                                                                                                                                                                                                                      |
| RC-10 | The robot shall not attach to the Field or Game Elements by adhesive or any other means that would impede prompt removal by hand \[3, R09\].                                                                                                                                                                      |
| RC-11 | The robot shall bear team identification discernible from a distance of 6ft \[3, R10\].                                                                                                                                                                                                                           |
| RC-12 | Power distribution shall operate at 30 V or less, and all wire gauges shall be rated for the imposed load \[3, R16\].                                                                                                                                                                                             |
| RC-13 | Electronics may be grounded to the robot frame using proper resistive grounding practice. The robot shall not be grounded to the Field, and no structural element shall be electrically charged \[3, R15\].                                                                                                       |
| RC-14 | Light sources shall not be of sufficient intensity to impair viewing or scoring of a match. Strobe lights and visible-light lasers are prohibited \[3, R17\].                                                                                                                                                     |
| RC-15 | All computational devices shall be safely contained on the robot \[3, R18\].                                                                                                                                                                                                                                      |
| RC-16 | The team shall be prepared to demonstrate the safety of its electrical design at inspection \[3, R14\].                                                                                                                                                                                                           |

#### IEEE Constraints

The IEEE Code of Ethics [32] governs how the team works. Article I.1 requires members to hold paramount the safety, health, and welfare of the public and to disclose promptly any factor that might endanger others. Article I.5 requires honest criticism of technical work, acknowledgment and correction of errors, realistic claims based on available data, and proper credit to contributors.

ISO 13850 [33] defines the principles for the emergency stop referenced in Game Manual 1. The standard requires a red actuator on a yellow background, a direct-opening action with mechanical latching, and an emergency stop that remains available at all times and overrides every other function. It also requires that resetting the device does not restart the machine. ISO 13850:2015 [33] is applied directly to the robot's emergency-stop design. Section 4.1.1.2 requires the emergency-stop function to override normal robot operation, remain active until intentionally reset, and prevent the reset itself from restarting the machine. To satisfy these requirements, the robot will use a latching hardware emergency-stop switch that disables actuator operation independently of the normal autonomous control sequence. After the switch is reset, the master controller will remain in a non-operating state until a separate start or arming command is provided. Section 4.3.2 requires emergency-stop devices to be positioned where they are directly accessible to persons who may need to actuate them; therefore, the switch will be mounted on the upper portion of the robot where a Technician or Referee can reach it without removing covers or reaching through moving mechanisms. Section 4.3.6 specifies a red emergency-stop actuator and, where practical, a yellow background, which will also be incorporated into the physical design. Compliance with these requirements will be verified experimentally on the completed robot. While the drivetrain and at least one auxiliary actuator are operating, the emergency stop will be activated while actuator supply voltage is monitored. The measured shutdown time shall remain below the requirement defined in RS-6. After the emergency stop is reset, the robot shall remain stationary and all actuator commands shall remain disabled until a separate start command is issued. The physical location, color, labeling, and accessibility of the emergency-stop device will also be verified by inspection.

IEC 62133-2:2017 + AMD1:2021 [34] is applied to the design and operation of the robot's lithium battery system. Section 5.4 requires lithium batteries to remain within the temperature, voltage, and current limits specified by the cell or battery manufacturer. Therefore, the allowable operating and charging limits for the selected 3S LiPo battery will be taken from the battery manufacturer's specifications rather than assumed from generic lithium-polymer values. Section 5.5 requires battery terminals to be capable of carrying the maximum anticipated current while minimizing the possibility of a short circuit. This requirement influences the selection of the battery connector, conductor size, insulation, and strain relief. Section 5.6.1 also identifies current, voltage, temperature, and other safety parameters that may require protection at the battery or end-device level. These requirements support the use of overcurrent protection, battery-voltage monitoring, properly rated conductors, and controlled shutdown of high-current loads in the robot. Compliance with the applicable battery requirements will be evaluated using both documentation review and electrical testing. Before integration, the team's battery documentation will record the manufacturer's specified charging voltage, charging current, discharge limits, and temperature limits. Charger settings will be compared with these limits before use. During representative robot operation, battery voltage and current will be measured while the drivetrain and actuators operate simultaneously. Connector and conductor ratings will then be compared against the maximum measured load. The team will not claim that the completed robot itself is certified to IEC 62133-2; where certification is applicable to the selected battery, compliance will be verified using manufacturer or accredited laboratory documentation rather than destructive certification testing by the team.

ISO 12100:2010, Safety of Machinery — General Principles for Design — Risk Assessment and Risk Reduction, will be used to structure the team's design-safety analysis. Section 5 defines a risk-assessment process consisting of determining the limits of the machine, identifying hazards, estimating the associated risk, and evaluating whether additional risk reduction is required. In particular, Sec. 5.4 addresses hazard identification, Sec. 5.5 addresses risk estimation, and Sec. 5.6 addresses risk evaluation. The team will apply this process to hazards including unexpected drivetrain motion, unexpected actuator movement, mechanical pinch points, battery and wiring faults, exposed conductors, and mechanical interference between subsystems.
Risk reduction will follow the iterative process described in Sec. 6 of ISO 12100. Where practical, hazards will first be reduced through inherently safer design. Remaining hazards will then be addressed using safeguards or protective measures, followed by operating information or procedures for residual risks. For example, the flag servo and tire scoop will use mechanically limited travel to reduce the possibility of interference before relying on software limits. Electrical hazards will be reduced through insulated conductors, appropriately rated connectors, overcurrent protection, and the hardware emergency stop. The risk assessment will be updated when testing identifies new hazards or when major design changes are made.


##### Conduct and Event Safety

Below lists all of the requirements applicable to team members at the place of competition.

**TABLE VI: CONDUCT AND EVENT SAFETY CONSTRAINTS**

| ID   | Constraint                                                                                                                                                                                          |
|------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| IC-1 | All team members shall adhere to the IEEE Code of Conduct before, during, and after the competition \[3, Sec. 2.0\].                                                                                |
| IC-2 | All personnel in the Pit or Competition Area shall wear ANSI Z87.1 certified safety glasses. Prescription eyewear with ANSI Z87.1 approved side shields is permitted \[3, C06\].                    |
| IC-3 | All personnel in the Pit or Competition Area shall wear closed-toe footwear \[3, C07\].                                                                                                             |
| IC-4 | Batteries shall be handled in accordance with their chemistry and charged in an open, well-ventilated area \[3, C08\].                                                                              |
| IC-5 | Hazardous paints, sprays, glues, and aerosols shall not be applied anywhere at the competition, including the Pit Area \[3, C10\].                                                                  |
| IC-6 | The team shall comply with all government and venue-specific requirements in effect at the competition \[3, C11\].                                                                                  |
| IC-7 | All members of a Main Team shall be undergraduate students at the Region 3 university the team represents, with one Main Team permitted per university \[3, Sec. 3.2.1\].                           |
| IC-8 | The Engineering Portfolio shall not exceed five single-sided US letter pages plus a cover sheet, shall use a font of no less than 10 points, and shall contain no external links \[3, Sec. 9.2.1\]. |

##### Public Health, Safety, and Welfare

The design affects the safety of team members, referees, and spectators who handle or observe the robot. The constraints in Table VII address these hazards and shall not be traded against performance objectives.

**TABLE VII: PUBLIC HEALTH, SAFETY, AND WELFARE**

| ID    | Constraint                                                                                                                                                                                                                                      |
|-------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| IC-9  | The battery circuit shall incorporate a fuse or battery management system providing overcurrent protection sized to the rated discharge current of the battery \[3, R14, C08\].                                                                 |
| IC-10 | All power wiring shall be insulated and strain-relieved, with no exposed conductors \[3, R14–R16\].                                                                                                                                             |
| IC-11 | The emergency stop, the 30 V distribution limit, the prohibited materials list, the 100 psi pneumatic limit, and the laser prohibition constitute the safety envelope of the design and shall be treated as inviolable \[3, R04–R07, R16–R17\]. |

## Survey of Existing Solutions

### Motor Control

To finish the lap under three-minute timeframe and stop precisely at a randomized pit area, an ideal motor control solution should be self-regulating, allowing it to park accurately at a designated location. It should also be efficient enough to complete laps reliably, responsive to object detection input, and equipped with a protective system that minimizes interference effects while relaying commands with minimal delays.

DC motor speed can be controlled in four main ways: adjusting voltage, changing armature resistance, managing field flux, or using a gearbox \[9\]. Among these, Pulse Width Modulation (PWM) control is generally the most effective, as it rapidly switches voltage on and off to regulate average power delivery, offering precise and efficient control over motor speed with minimal energy loss. Armature resistance control, by contrast, is a simpler approach that uses a resistor to reduce motor speed, but it wastes significant energy as heat, making it less efficient for sustained use. Field flux control takes a different approach, increasing motor speed by weakening the magnetic field, though this method is only suitable for specific motor types and applications. Finally, a gearbox adjusts speed mechanically by using gears to reduce rotational speed while increasing torque, making it ideal for tasks that involve moving heavier loads rather than fine-tuned speed control.

Given these options, PWM stands out as the most suitable method for this application, since it combines precision, responsiveness, and energy efficiency—qualities essential for accurate pit-stop parking, consistent lap performance, and quick reaction to sensor input, all while keeping power loss and interference to a minimum. However, PWM control can introduce back EMF and switching noise, which may interfere with nearby sensors or other sensitive electronic components \[9\]. As such, proper filtering and shielding are essential to suppress this electrical noise and ensure reliable performance of the overall system.

With PWM method stands out, many control methods one can apply to improve the robot's motor including Proportional-Integral-Derivative (PID) tuning, Model Predictive Control (MPC), Feedforward Control... DC motors play a critical role in various industrial and robotic applications, where precise control of speed and torque is essential. In recent years, the demand for enhanced performance and efficiency in these systems has driven significant advancements in motor control techniques, where PID control has emerged as a dominant method due to its simplicity, robustness, and effectiveness in managing the dynamic behavior of DC motors \[10\].

Capacitors are a common noise filtration solution: a single capacitor placed across motor terminals suppresses the high-frequency switching noise generated by repeated motor starts and stops, while multiple capacitors connected between the terminals and motor casing create a diversion path for noise radiating into the surrounding environment. Ceramic disc capacitors should be used for this purpose, as electrolytic capacitors risk exploding in this application \[11\]. However, capacitor filtering only addresses noise originating from the motors themselves—environmental, or coupled, noise from external sources must be handled separately. Best practices drawn from Data Acquisition and Test Systems address this through cable shielding, twisted pair cabling, signal isolation, proper grounding, organized wiring pathways, and anti-aliasing filters \[12\]; incorporating these into the robot's electrical design supports reliable autonomous communication and protects both the equipment and its surroundings. Beyond noise suppression, Back EMF in BLDC motors serves a functional role as a built-in feedback mechanism, helping regulate speed, improve efficiency, and enable smooth sensorless control. This principle is reflected in the application schematic of the DRV10983 motor IC, which integrates power MOSFETs to drive a three-phase sensorless BLDC motor \[13\].

### Image Processing

Two Image Processing (IP) tasks are required for this project: detecting when the green starting flag is held down, and decoding AprilTags to determine which pit stop to visit. One approach to solving both problems is NVIDIA's Vision Programming Interface (VPI) \[14\], which includes a built-in AprilTag detector and pose estimator. On a compatible Jetson module with a supported camera, VPI can detect and decode multiple AprilTags in a single pass, with the option of hardware acceleration through the module's PVA (Programmable Vision Accelerator) for the early detection stages.

Additionally, an alternative approach is to use the OpenMV IDE with Python-based image processing and its AprilTags API \[15\]. OpenMV provides built-in support for AprilTag detection, allowing the camera to identify and decode tags directly on the embedded vision platform. This approach can simplify the system architecture by performing both image acquisition and AprilTag detection on the OpenMV device without requiring a separate Jetson module.

A third approach is to use the OpenCV library on a single-board computer such as a Raspberry Pi. OpenCV’s ArUco module supports predefined AprilTag dictionaries, including the tag36h11 family, so tags can be detected and decoded entirely in software [26]. The green starting flag can be detected with the same library by converting each frame to the HSV color space, thresholding the green hue range, and applying morphological filtering to remove noise. To prevent false triggers from other green objects in the scene, the system would require the detected blob to exceed a minimum area and persist across several consecutive frames before signaling the start. This approach is low-cost, well documented, and easy to prototype on a laptop before deployment. 

A fourth approach is to use a dedicated smart vision module that performs image processing on-board and sends only the results to the main controller. The Pixy2 camera performs color-based object detection and reports the position and size of detected color blocks over a serial interface such as SPI, I2C, or UART [17]. This makes it well suited to detecting the green starting flag with very little processing on the main controller. Because the Pixy2 does not decode AprilTags, pit stop identification would be handled by a second camera running an AprilTag detection library [18]. Alternatively, an all-in-one computer vision module such as the HuskyLens AI vision sensor offers both color recognition and tag recognition on a single device, with results available over UART or I2C [27]. These modules reduce development time and processing load because the vision algorithms are built in. However, they offer less control over the detection pipeline and lower resolution and frame rates than a Jetson or OpenMV platform [14], [15], and the split-camera setup adds hardware and integration complexity.

### Master Control

The robot must complete the track within a three-minute time limit while also being able to stop at designated pit stops. This requirement means the robot software must support computationally intensive processes, most likely involving machine learning and computer vision. Running these processes efficiently therefore demands a hardware controller with sufficient computing power.

Several master controller solutions exist across similar robotics competitions, each with different tradeoffs between real-time reliability and computational capability. In the FIRST Robotics Competition (FRC), which includes racing-style games, teams have commonly used the roboRIO as the master controller for robot operations \[16\]. This board combines a real-time processor with an FPGA for logic control, and its small size, light weight, and durability allow it to withstand hard hits during matches. However, the roboRIO's compute power is not designed for machine learning or computer vision workloads, making it poorly suited on its own for tasks like pit-stop detection or lane recognition.

In contrast, competitions such as F1TENTH, an autonomous racing car competition, tend to see students implement the NVIDIA Jetson for its higher computational capability \[17\]. Previous teams competing in SECON 2024 and 2025 similarly used the NVIDIA Jetson for the same reason \[5\], \[6\].

Other approaches include pairing a lower-cost single-board computer, such as a Raspberry Pi with a Coral TPU or Intel Neural Compute Stick, to offload ML inference at a fraction of the Jetson's cost, though generally with lower throughput. Some teams also adopt a hybrid architecture, using a microcontroller for low-latency, real-time motor and sensor control alongside a separate companion computer for vision and ML processing — an approach that mirrors the division of labor built into the roboRIO's combined real-time processor and FPGA, but distributes it across two dedicated boards instead of one.

Another option is to use an STM32 microcontroller board as the real-time controller. STM32 is a family of 32-bit Arm Cortex-M microcontrollers from STMicroelectronics, and its Nucleo and Discovery development boards provide hardware timers for PWM motor control, quadrature encoder interfaces, ADCs, and communication peripherals such as UART, SPI, I2C, and CAN [28]. These features suit tasks that require deterministic timing, such as speed control, steering, reading wheel encoders, and braking at a pit stop. Compared with the roboRIO, an STM32 board is smaller, lighter, and much cheaper, and it can be programmed in C/C++ with the STM32Cube tools or in MicroPython. However, a general-purpose STM32 lacks the compute power and memory for heavy computer vision workloads on its own. Higher-end devices such as the STM32H7 series can run small neural networks through ST’s X-CUBE-AI toolchain [29], and newer parts with a dedicated neural processing unit improve this further, but their throughput remains well below that of a Jetson-class module [17].

For this reason, an STM32 is best suited to the hybrid architecture described above, where it handles low-latency motor and sensor control while a companion computer, such as a Jetson or Raspberry Pi, handles AprilTag detection, flag detection, and any machine learning inference. The two boards can exchange high-level commands (for example, target speed, steering angle, or a “stop at pit” flag) over UART, USB, or CAN, so a vision delay never disrupts the motor control loop. This split also adds a safety benefit, since the STM32 can continue to enforce limits or perform an emergency stop if the companion computer stalls. The tradeoff is added integration complexity, including a defined communication protocol, two codebases, and extra wiring and power management.

### Navigation

The FRC competition centers on known-field trajectory following rather than obstacle-avoiding autonomy, since the field layout is fixed and known in advance. PathPlanner is widely used for this purpose: teams use a GUI to place waypoints and drag Bézier-curve control handles to visually shape the desired path\[18\]. Once a path is defined, PathPlannerLib provides built-in functions that allow the robot to follow the planned trajectory automatically, using feedback control to correct for drift and keep the robot on course.

F1TENTH, by contrast, does not rely on a pre-planned path in the same way. Because the track is not known in advance to the same degree, teams must localize the robot within its environment by implementing Simultaneous Localization and Mapping (SLAM)\[19\]. SLAM can be implemented using a single sensor modality or a fusion of multiple sensors to build an accurate representation of the robot's physical environment. LiDAR is the primary sensor used for this purpose, since it directly measures distances to surrounding obstacles and track boundaries, while a camera mounted on the robot can supplement this data — for example, by providing additional visual features or depth information — to improve the accuracy of the resulting SLAM map.

Since SECON involves racing along a fixed, predetermined path, Iterative Learning Control (ILC) is another approach worth considering. ILC is designed specifically for this type of scenario: a control system that performs a single, repeated task, using information from prior runs to gradually determine control inputs whose tracking performance exceeds that of traditional feedback-feedforward control \[20\].

Another option well suited to a fixed track is Pure Pursuit, a geometric path-tracking algorithm. The robot follows a pre-defined list of waypoints by repeatedly choosing a lookahead point on the path ahead of it and computing the steering curvature needed to reach that point [30]. Because the path is known in advance, localization can rely on lightweight sensing, such as wheel encoders and an IMU fused with a filter, rather than full SLAM. Drift can be corrected periodically using known landmarks, such as the AprilTags already used for pit stop identification. Pure Pursuit is simple to implement, has few parameters to tune (mainly the lookahead distance and speed), and runs easily on a microcontroller. However, it can cut corners at high speed, and its accuracy depends on the quality of the odometry.

A more advanced option is Model Predictive Control, which is widely used in autonomous racing. At each control step, MPC uses a kinematic or dynamic vehicle model to predict the robot’s motion over a short horizon and solves an optimization problem for the steering and speed commands that best track the reference path while respecting constraints such as maximum speed, steering angle, and acceleration [31]. This lets the robot slow down for tight turns and brake accurately for pit stops, which helps it finish within the three-minute limit. The cost is computation, since the optimization must be solved in real time, along with the need for an accurate vehicle model. It is therefore best suited to running on a companion computer such as a Jetson rather than a small microcontroller.

Overall, FRC and F1TENTH represent two established navigation approaches: pre-planned trajectory following for known, fixed environments, and SLAM-based localization for environments that are not known in advance. Given SECON’s fixed and repeated track layout, methods such as PathPlanner, ILC, Pure Pursuit, and MPC are the most directly applicable existing solutions to build on. Pure Pursuit offers a simple, low-compute baseline, while MPC and ILC offer higher performance at the cost of added complexity and processing demands.

### Object and Line Detection

As for this year's game board layout, we plan to design the robot to track both the gray line on the racetrack and the border of the track. Given the robot's size (12 x 12 x 12 inches) and the distance between the inner wall and the gray line, following the gray line is likely the most effective way to complete the course. In addition, the ability to detect the outer border can help prevent the robot from going out of the bounds.

To track the gray line beneath the robot, one widely used approach is IR (infrared reflectance) sensors mounted under the robot to measure surface reflectivity and distinguish a dark line from a light background \[21\]. Another possible approach is a downward-facing camera using computer vision. This method allows for real-time calculation of distance and orientation angle relative to the target line.

In both competitions, object detection serves as the critical part of the autonomous vehicle, but it targets completely different challenges tailored to their specific environments. In FRC, object detection focuses heavily on camera vision and geometric tracking; robots utilize neural networks (like YOLOv8) and specialized software (like PhotonVision) to identify dynamic, color-coded game pieces scattered across the floor. Conversely, in F1TENTH, the focus shifts to spatial perception and obstacle avoidance at high speeds, which is also what we desire at SECON 2027. Rather than relying solely on visual colors, F1TENTH cars fuse 2D LiDAR data with stereo depth cameras, using Euclidean clustering algorithms and GPU-accelerated pipelines (on Nvidia Jetson hardware) to instantly detect track boundaries and opponent vehicles so the car can recalculate its racing line or execute a high-speed overtake in milliseconds.


## Measures of Success

Success of this project is measured in two manners: compliance and performance. Compliance is whether the robot meets the requirements defined in the *Specification & Constraints* section, and performance is determined based on the number of points the robot receives during the competition. To compete, the robot must pass inspection. Failure to meet the compliance requirements set out by the game manuals will result in a failed inspection and disqualification from the competition \[3\].

### Point Breakdown

After passing inspection, the main measure of success will be earning points and avoiding penalties. Points can be earned by completing the tasks outlines, and deducted if certain violations occur.

#### Earning Points \[4\]

| **Achievement**                              | **Points Earned**           |
|----------------------------------------------|-----------------------------|
| *Robot* enters the course                    | 25                          |
| Green-flag start                             | 10                          |
| Crossing the finish line in ≤180 s           | 100                         |
| Time bonus                                   | 1 per full 10 s under 180 s |
| Pit stop after lap 1 or 2                    | 15                          |
| Stopping in the *Apriltag*-assigned pit spot | 15                          |
| Dropping the tire in the pit area            | 25                          |
| Picking up a fresh tire                      | 40                          |
| Ending the race in the assigned pit spot     | 15                          |
| No gray-wall contact                         | 10 per lap (max 30)         |
| No obstacle-vehicle contact                  | 15 per lap (max 45)         |
| Raising the school flag on the final lap     | 25                          |
| Entering the publicity contest               | 10                          |
| Maximum                                      | 355 + time bonus            |

#### Point Penalties \[4\]

| **Violation**                                                    | **Penalty**                                                                            |
|------------------------------------------------------------------|----------------------------------------------------------------------------------------|
| Early start (premature switch activation or faulty flag sensing) | 2-point deduction and a *Yellow Card*, in addition to the 10 forfeited points          |
| Leaving the pit before 2 s                                       | Described as a "point penalty" in §3.1; the table implements it as a 5-point reduction |

#### Cards & Score Reset \[3\]

| **Mechanism**                                                | **Effect**                                                                                                   |
|--------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------|
| *Yellow Card*                                                | Warning; the manuals assign no point value                                                                   |
| Second incident after a *Yellow Card*                        | *Red Card*                                                                                                   |
| *Red Card*                                                   | Current Match score set to 0; automatic loss in an Elimination Match                                         |
| Early match termination for unsafe operation or field damage | Match ends, Robot is stopped, *Yellow Card*; escalates to *Red Card* if repair is significant or delays play |

#### Card Penalties \[3\]

| **Violation**                                      | **Card**                                                         |
|----------------------------------------------------|------------------------------------------------------------------|
| Reaching outside the Field (Robot or Game Element) | *Yellow card*; *Red card* if intentional                         |
| Start switch violation                             | *Yellow card*; *Red card* if intentional                         |
| Field damage                                       | At referee discretion                                            |
| Delaying the match through complicated retrieval   | *Yellow card*                                                    |
| Intentional Technician contact with the Field      | *Red card*                                                       |
| Interference with another Team                     | *Red card*, likely disqualification                              |
| Egregious behavior                                 | *Yellow card*; *Red card* if repeated, possible disqualification |

### Performance Targets

The point breakdown above defines the possible rewards the robot can receive during the competition. This section defines specific goals for the robot and the metrics it will be rated against. The targets are divided into three tiers using the same requirement language as the *Specifications and Constraints* section: "shall" statements are the baseline goals that are mandatory for the final design, "should" statements mark targets the team intends to meet, and "may" statements are stretch objectives. Structuring goals this way lays out the robot's core function, completing the race on time and within constraints, before the design phase moves on to the high-risk pit stop and tire exchange tasks.

All score thresholds are derived from the point values in the revised Game Manual 2 \[4\]. The time bonus and the publicity contest are excluded from the thresholds so that the robot is graded purely on its performance on the course. Thresholds are set below the sum of their tasks so that a single minor contact does not cause an otherwise successful run to fail.

#### Verification Method

Performance targets will be verified during a final round of 10 practice runs on a practice board built to BS-2, using Game Elements that meet BS-3. Each run will be scored according to Game Manual 2 \[4\], with the completion time and any contact events noted for each run. The occupied obstacle quadrants and the AprilTag-assigned pit box will be randomized between runs to match competition conditions. Any run that receives a Red Card is counted as a failed run regardless of score.

#### Tiered Performance Targets

Every match begins with entering the course, starting on the green flag, and completing three laps within 180 s, which together are worth 135 points \[4\]. Each tier builds on these core tasks.

**TABLE VIII: TIERED PERFORMANCE TARGETS**

| ID   | Tier     | Requirement                                                                                                                                                  | Verification                                   | Stakeholder Need                                                |
|------|----------|--------------------------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------|-----------------------------------------------------------------|
| PT-1 | Baseline | The robot shall score no fewer than 175 points in at least 8 of 10 practice runs, earning the 135 core points and at least 40 points from contact-free laps. | Score log from the final round of practice runs. | A reliable entry that represents TTU in the competition.        |
| PT-2 | Target   | The robot should score no fewer than 275 points in at least 6 of 10 practice runs.                                                                          | Score log from the final round of practice runs. | Competitive placement for the TTU ECE department and IEEE Club. |
| PT-3 | Stretch  | The robot may complete the pit stop, full tire exchange, and school flag tasks in a single run, for a score of up to 390 points.                             | Best-scoring run in the final round.           | Maximum robot-earned score.                                     |

The "Target" tier can be reached through more than one combination of tasks. A robot that completes three contact-free laps and stops in the correct pit box for at least 2 s earns 285 points. A robot that deposits the red tire in the correct pit box but contacts an obstacle on one lap also earns 285 points. This flexibility allows the team to prioritize the tasks that are the most reliable during testing without failing the target.

#### Supporting Performance Targets

**TABLE IX: SUPPORTING PERFORMANCE TARGETS**

| ID   | Requirement                                                                                                                              | Verification                     | Stakeholder Need                                             |
|------|------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------|--------------------------------------------------------------|
| PT-4 | The robot should complete three laps in no more than 160 s, providing 20 s of margin below the 180 s limit \[4\].                        | Stopwatch timing of each run.    | Completion margin against mechanical or navigation delays.   |
| PT-5 | The robot shall receive no Red Cards across the final round of practice runs \[3, C03\].                                                 | Score log of each run.           | Rule compliance required by the SECON Game Design Committee. |
| PT-6 | The robot should receive no Yellow Cards, including those caused by a premature start, across the final round of practice runs \[3\]\[4\]. | Score log of each run.           | Rule compliance and protection against Red Card escalation.  |

In Capstone II, the "shall" targets PT-1 and PT-5 will serve as the pass/fail criteria for performance verification. The "should" and "may" targets will be reported as measured results and used to evaluate how competitive the robot is relative to the full scoring potential of the game.

## Resources

### Budget

# Expected Bill of Materials

| Item | Expected Cost Per Item | Expected Quantity | Expected Cost |
|---|---:|---:|---:|
| **Power System** | | | |
| Lithium Battery | $50.00 | 1 | $50.00 |
| Buck Converters (12V to 5V / 12V to 3.3V) | $13.00 | 2 | $26.00 |
| **Master Controller** | | | |
| Microcontroller Development Board | $80.00 | 1 | $80.00 |
| PCB (w/ connectors & standoffs) | $80.00 | 1 | $80.00 |
| **Camera / Vision Processing** | | | |
| OpenMV camera | $180.00 | 1 | $180.00 |
| **Navigation Inputs** | | | |
| Time-Of-Flight ranging sensor (for boundry detection) | $8.00 | 2 | $16.00 |
| Matrix Distance Sensor (for obstacle detection) | $30.00 | 1 | $30.00 |
| Tracking Wheel & Encoder (for odometry) | $80.00 | 2 | $160.00 |
| **Flag & Tire Actuators** | | | |
| Servo Motors | $11.67 | 5 | $58.33 |
| Stepper Motor & Driver | $15.00 | 1 | $15.00 |
| **Motor Control** | | | |
| Motor | $15.00 | 4 | $60.00 |
| Dual H Bridge Motor Driver | $13.00 | 2 | $26.00 |
| **Miscellaneous** | | | |
| Switches (emergency stop, start sutton, status LEDs) | $50.00 | 1 | $50.00 |
| Wiring & integration | $40.00 | 1 | $40.00 |
| **Expected Total** | | | **$871.33** |

Along with an estimated Bill of Materials, using a previous SECON robots’ BOM can serve as a good reference point for the cost of this project. The electrical design constraints for the Hardware Competition are largely consistent year-to-year \[3\]\[25\]. Cost drivers remain similar, so a previous team’s component costs is a reasonable benchmark. The electrical system for the Fall 2024 Capstone SECON robot cost \$1025.72 \[6\].

### Personnel

#### Team Members

- Ty Ahrens - Computer Engineering

  - Proficiency with embedded systems, PCB design, and microcontroller programming

- Tuan Kiet Le - Electrical Engineering

  - Proficiency with power systems and embedded systems, some familiarity with PCB design and control system design

- Kyle Schultz - Electrical Engineering

  - Proficiency with embedded systems and firmware development, some familiarity with power systems and soldering experience

- Austin Marcellino - Electrical Engineering

  - Proficiency with power systems, microcontroller programming, and CAD software (Fusion 360, FreeCAD, Solidworks) experience.

- Hadassah Ranghiuc - Electrical Engineering & Computer Engineering

  - Proficient in power systems, microcontroller programming, and AutoCAD; hands-on experience with soldering

- Matthew Evans - Electrical Engineering (Mechatronics)

  - Proficient with controls systems and engineering software (SolidWorks, LabVIEW, ROS)

#### Advisors

- The team has chosen Dr. Yoon to be the primary advisor for this project. His background in mechatronics and extensive research in autonomous vehicles will prove invaluable for this project.

- The team has also chosen graduate student Aiden Mullins to be an advisor for this project. His experience in the previous SECON Hardware Competition makes him a great resource.

#### Skill Gaps Present

The team is heavily weighted toward embedded systems, power electronics, and microcontroller programming. While these skills are required for the project, the overlap may create redundancy rather than coverage. No member has computer vision or image-processing experience, which is directly relevant since the Robot must detect and interpret an AprilTag to determine its pit assignment \[4\]. Microcontroller programming and firmware are listed, but higher-level autonomy logic (sensor integration, decision-making, state machines) are distinct skills not called out. While the team’s shared power and controls system experience may address this, there does exist a partial gap in experience working with motor drivers/actuator circuitry.

### Timeline

<img width="973" height="415" alt="image" src="https://github.com/user-attachments/assets/955e8fc9-9902-44e8-bfc2-344976c5fa3d" />

## Specific Implications

The main implication of that project is that the customer will receive a functional autonomous robot that demonstrates the team’s ability to apply engineering concepts to a real-world challenge. The robot is required to be able to navigate the course, avoid obstacles, complete required tasks, and be fully autonomous \[3\]\[4\]. Completing these requirements demonstrates the team’s ability to combine mechanical design, electrical systems, programming, sensors, and power management into one working system. The proposed work not only provides more than just a robot for competition but also gives the customer a clear example of the team’s design process, testing, problem-solving, and ability to work within specific requirements. The final design and documentation can also be served as a reference for future students, projects, and teams. By being able to create a safe and reliable robot, the team will demonstrate the practical skills and engineering knowledge expected from the capstone project.

## Broader Implications, Ethics, and Responsibility as Engineers

When it comes to broader implications, it is important to take into consideration what exactly is being designed and how that can either improve previously existing products or inspire new ones. With this project, the design is already focused on an autonomous robot. With that in mind, the creation of the robot, from the build to the controls and power, can all be applied in some way to autonomous vehicles. The robot creation process illustrates a critical aspect of autonomous vehicle development, which lies in creating a trajectory from the origin to the destination in streets and places full of cars \[23\]. The competition itself requires demonstrating how an autonomous vehicle can navigate \[4\]. This is a small example of what autonomous vehicles strive to do accurately in an environment: map the area, identify obstacles, recognize visual landmarks, and follow obstacle-free routes. \[23\]. Autonomous vehicles are not the only application that this project can be used for. AprilTags are an example. They are visual markers that allow camera-equipped robots to identify known markers. By using their vision system, AprilTags are able to estimate the tag’s position and orientation from an image. In other words, they are suitable for precise localization systems for either outdoor or indoor situations \[25\]. This is something that is needed for this competition. By applying AprilTags to the robot, it will show how they could be used in the field. They are currently being used for operations like inspection inside buildings for engineering, construction, and management tasks \[25\]. Another example where autonomous vehicles and AprilTags could be used together is the use of first responder and search-and-rescue robots. These robots are sent into situations that are either considered too dangerous or too difficult for humans. The same requirements needed for autonomous vehicles would be needed for these types of robots. Depending on the situation, the robot could be autonomous, reducing the need for human interaction and lowering risks. An example of this is the First Responder Robotic Operations System Test (FRROST) that Homeland Security conducted \[24\]. The purpose of FRROST was to assess commercially available sUAS (Small unmanned aircraft systems) for public safety missions. This is a real-life example of how an autonomous robot could be used outside of competitions.

Moving on from the autonomous aspect, another implication that can be drawn from this project is energy efficiency. At first glance, this wouldn’t be noticed, but when considering the competition and the fact that the robot will need to hold enough power to complete all the tasks and finish within the time limit without a recharge, the design becomes highly valuable \[3, 4\]. In the game manual, it states that the robot must use no more than 30 volts for power distribution \[3\]. At first, that may seem like a lot, but when it comes down to what needs power and how much power is being consumed, 30 volts starts to look more like a limit rather than an excess. Learning how to manage all the components without exceeding 30 volts shows innovation. This concept can be applied in numerous scenarios. All it takes is redesigning the product. In this day and age, being able to do more while using as little power as possible is considered a tremendous accomplishment. Energy efficiency is important because it means less money in the long run and more use of the product. Many may not view this as a broader impact, but when it comes to energy and power, there are places on this planet that do not have access to either. Being able to create anything that could be considered energy-efficient is one step closer to providing opportunities to those who need it. This now leads into economic and sustainable impacts. Creating any type of system, robot, or product that can be energy-efficient using common, every day, or off-the-shelf components reduces the overall cost of development. It also increases the likelihood of the concept or system being used again. Broader implications are not only about how this robot can be used in other areas of life but also how it is designed, managed, and maintained. These aspects can inspire, teach, or improve the way someone may think, address a situation, or illuminate a path for the next generation.

The design of this robot must also show consideration for safety, integrity, and reliability. It must prioritize safety, health, and welfare for all participants. The IEEE code of conduct also requires engineers to acknowledge and correct errors, give proper credit and acknowledgment to contributors, and maintain honest communication. The team has the responsibility to build, construct, and design a robot that can operate safely during testing, transportation, and the competition. This also includes using materials that are safe \[3\]\[4\]. An example of this is having an emergency stop. It must remain available for safe robot retrieval after a match \[4\]. It needs to be accessible, labeled, tested, and able to stop quickly \[4\].

Along with the IEEE code of conduct requiring engineers to acknowledge and correct errors, engineers are also responsible for identifying possible risks and either preventing them or reducing them. This is done through careful design and testing. This goes along with the competition’s requirement for inspection, which proves that the robot is safe to function \[3\]. The reason for being transparent about risks is to help future teams improve designs and make better decisions about what is appropriate.

The team is required to compete fairly and respect the work and equipment of other teams. Communication must reflect sportsmanship when conversing with other teams. This also means that teams are prohibited from intentionally interfering with one another and that external wireless communication during a match is restricted \[3\]. This is to ensure that the robot is actually fully autonomous. Integrity is also a requirement for teams. This means that teams need to correctly cite any outside sources, acknowledge borrowed code, and respect software licenses. Team members should be able to explain their own contributions without taking credit for someone else’s work. Honest documentation plays an important role in maintaining integrity. This includes keeping track of all the work, successful and unsuccessful tests, the changes and decisions made, and even disagreements. Having a timeline of all major meetings, choices, and events keeps everyone honest and accountable. Honest documentation also helps support honest communication. Communication is not only written work but also verbal. Clear diagrams, labels, instructions, documentation, and explanations are essential for effective communication. This also includes making sure everyone on the team has access to shared work and group chats. This will help bridge any gaps or misunderstandings. Respecting each other allows collaboration to run smoothly and for ideas to take form. That is why teams need to not only respect each member but also other teams.

## References

[1] “Image — Machine Vision,” Openmv.io. Accessed: Sep. 14, 2026. [Online]. Available: <https://docs.openmv.io/v5.0.0/library/omv.image.html>

[2] AprilRobotics, “AprilRobotics/apriltag,” GitHub. Accessed: Sep. 14, 2026. [Online]. Available: <https://github.com/AprilRobotics/apriltag>

[3] IEEE, “SoutheastCon 2027 Hardware Competition Stock Car Race - Game Manual 1.” IEEE, Jun. 15, 2026. [Online]. Available: <https://ieeesoutheastcon.org/wp-content/uploads/sites/755/Game-Manual-2027-1-V2.docx>

[4] IEEE, “SoutheastCon 2027 Hardware Competition Stock Car Race - Game Manual 2.” IEEE, Jun. 15, 2026. [Online]. Available: <https://ieeesoutheastcon.org/wp-content/uploads/sites/755/Game-Manual-2027-2-V2.docx>

[5] Tennessee Technological University, “F25 Team7 SECON Hardware Competition 2026,” GitHub. Accessed: Sep. 14, 2026. [Online]. Available: <https://github.com/TnTech-ECE/F25_Team7_SECONHardwareCompetition2025>

[6] Tennessee Technological University, “F24 Team1 SECON Hardware Competition 2025,” GitHub. Accessed: Sep. 14, 2026. [Online]. Available: <https://github.com/TnTech-ECE/F24_Team1_SECON>

[7] N. Gardner, “SECON2023Robot - IEEE SoutheastCon Robotics Competition,” GitHub. Accessed: Sep. 14, 2026. [Online]. Available: <https://github.com/nathan-gardner/SECON2023Robot>

[8] IEEE, “IEEE 2026 SoutheastCon Hardware Competition Ruleset,” [*https://ieeesoutheastcon.org/wp-content/uploads/sites/688/Hardware_Competition_Ruleset_2_20_26.pdf*](https://ieeesoutheastcon.org/wp-content/uploads/sites/688/Hardware_Competition_Ruleset_2_20_26.pdf), Feb. 2026.

[9] "4 Proven Methods for DC Motor Speed Control," ODG (Origin IC). [Online]. Available: <https://www.origin-ic.com/blog/4-proven-methods-for-dc-motor-dc-speed-control/49055#heading-7>.

[10] J. Chen, "The Application of PID Control in DC Motor Control Systems," *Applied and Computational Engineering*, vol. 81, no. 1, pp. 164–170, Nov. 2024, doi: 10.54254/2755-2721/81/20241083.

[11] J3, "DC Motors — Against Back-EMF. How to Prepare your DC Motor — Quick…," *Jungletronics*, Medium. [Online]. Available: <https://medium.com/jungletronics/dc-motors-against-back-emf-589d8ed174cc>.

[12] "Top 8 Ways to Deal with Noise in Data Acquisition and Test Systems," Genuen. [Online]. Available: <https://www.genuen.com/blog/top-8-ways-to-deal-with-noise-in-data-acquisition-and-test-systems/>.

[13] "Back EMF and Electric Motors: From Fundamentals to Real-World Applications," The Institution of Electronics. [Online]. Available: <https://institutionofelectronics.ac.uk/back-emf-and-electric-motors-from-fundamentals-to-real-world-applications/>.

[14] "VPI - Vision Programming Interface: AprilTag Detector and Pose Estimator," NVIDIA Docs. [Online]. Available: <https://docs.nvidia.com/vpi/algo_apriltags.html>.

[15] A. Pathare, "Color Detection Using Python and OpenCV," Medium. [Online]. Available: <https://agneya.medium.com/color-detection-using-python-and-opencv-8305c29d4a42>.

[16] "roboRIO Introduction," FIRST Robotics Competition Documentation, WPILib. [Online]. Available: <https://docs.wpilib.org/en/stable/docs/software/roborio-info/roborio-introduction.html>.

[17] "F1TENTH Autonomous Racing," University of Virginia. [Online]. Available: <https://www.f1tenth.racing/>.

[18] "PathPlanner Docs," PathPlanner. [Online]. Available: <https://pathplanner.dev/home.html>.

[19] B. D. Evans, R. Trumpp, M. Caccamo, F. Jahncke, J. Betz, H. W. Jordaan, and H. A. Engelbrecht, "Unifying F1TENTH Autonomous Racing: Survey, Methods and Benchmarks," *arXiv preprint* arXiv:2402.18558, 2024. [Online]. Available: <https://arxiv.org/html/2402.18558v2>.

[20] K. Ahmadi Dastgerdi, B. Singh, W. Naeem, and N. Athanasopoulos, "Adaptive Iterative Learning Control for Robotic Manipulators," in *Proc. 2024 UKACC 14th Int. Conf. Control (CONTROL)*, Winchester, U.K., Apr. 10–12, 2024, p. 96.

[21] M. Khaleelullah Khan, V. Rahul Naik, M. Khan, M. U. Farooq, and R. Vighnesh, "Line Following Robotic Car with Obstacle Detection and Avoidance," *TIJER – International Research Journal*, vol. 12, no. 5, pp. b544–b548, May 2025. [Online]. Available: <https://tijer.org/tijer/papers/TIJER2505195.pdf>.

[22] "Following a Line with a Camera," Pybricks. [Online]. Available: <https://pybricks.com/learn/smart-sensors/line-camera/>.

[23] H. Zhang, L. Song, Y. Li, and C. Xu, "Large language models for automated software engineering: A survey," arXiv preprint arXiv:2406.02916v1, Jun. 2024

[24] System Assessment and Validation for Emergency Responders (SAVER), "First Responder Robotic Sub-Systems (FRROST) Unmanned Aerial Systems (UAS) Focus Group Report," U.S. Dept. Homeland Security, Sci. Technol. Directorate, Washington, DC, USA, Rep. 19June2019-COD-Approved-508, Jun. 2019

[25] N. H. A. R. Ahmad, M. N. A. H. A. N. A. H. et al., "Evaluation of the effectiveness of standard operating procedures in healthcare," *PMC*, PMC6960891, 2019.

[26] OpenCV, “Detection of ArUco Markers,” OpenCV Documentation. [Online]. Available: https://docs.opencv.org/4.x/d5/dae/tutorial_aruco_detection.html.

[27] DFRobot, “HUSKYLENS: An Easy-to-use AI Machine Vision Sensor,” DFRobot Wiki. [Online]. Available: https://wiki.dfrobot.com/HUSKYLENS_V1.0_SKU_SEN0305_SEN0336.

[28] STMicroelectronics, “STM32 32-bit Arm Cortex MCUs,” STMicroelectronics. [Online]. Available: https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html.

[29] STMicroelectronics, “X-CUBE-AI: AI expansion pack for STM32CubeMX,” STMicroelectronics. [Online]. Available: https://www.st.com/en/embedded-software/x-cube-ai.html.

[30] R. C. Coulter, “Implementation of the Pure Pursuit Path Tracking Algorithm,” Carnegie Mellon University Robotics Institute, Pittsburgh, PA, USA, Tech. Rep. CMU-RI-TR-92-01, Jan. 1992.

[31] J. Kong, M. Pfeiffer, G. Schildbach, and F. Borrelli, “Kinematic and dynamic vehicle models for autonomous driving control design,” in Proc. IEEE Intelligent Vehicles Symp. (IV), Seoul, South Korea, 2015, pp. 1094-1099.

[32] IEEE, “IEEE Code of Ethics,” IEEE Policies, Sec. 7.8, rev. Jun. 2020. [Online]. Available: https://ieee-cas.org/about/ieee-code-ethics

[33] ISO, ISO 13850:2015, Safety of machinery — Emergency stop function — Principles for design. Summaries: https://machinerysafety101.com/2026/05/18/iso-13850-emergency-stop-requirements/ and https://public-library.safetyculture.io/products/emergency-stop-audit

[34] IEC, IEC 62133-2:2017 + AMD1:2021, Safety requirements for portable sealed secondary cells and batteries — Lithium systems. Example certification reports: https://cdn.sparkfun.com/assets/2/7/5/9/0/LP783450-IEC62133.pdf and https://www.htenergy.com.tw/license/IEC_62133.pdf


## Contributions

| **Assignment**                                                | **Assignee** |
|---------------------------------------------------------------|--------------|
| Introduction & Background                                     | Matthew      |
| Formulating the Problem                                       | Austin       |
| Specifications and Constraints                                | Ty           |
| Survey of Existing Solutions                                  | Tuan         |
| Measures of Success                                           | Kyle         |
| Resources                                                     | Kyle         |
| Specific Implications                                         | Hadassah     |
| Broader Implications, Ethics, and Responsibility as Engineers | Hadassah     |
| Review                                                        | All Team     |







# Conceptual Design

## Introduction

The IEEE (Institute of Electrical and Electronics Engineers) hosts an annual conference for the southeastern region known as SoutheastCon (SECON). As part of the conference, the annual Hardware Competition challenges university students to apply their engineering knowledge through the design, construction, and programming of an autonomous robotic system. For the 2027 competition, “Stock Car Race,” teams are tasked with developing a fully autonomous ground robot capable of navigating a racecourse and completing three laps within a three-minute time limit. During the race, the robot must avoid randomly placed obstacles, identify an assigned pit area using an AprilTag, perform a pit stop and tire exchange, and return to the course. Points are earned based on how well the robot can complete these tasks. Additional points can be earned by avoiding contact with obstacles and course walls, raising our university flag during the final lap, and detecting the lowering of the start flag. To meet these objectives, two Capstone teams will be responsible for the development of this autonomous robot: a mechanical team and an electrical team. The mechanical team is responsible for the chassis, drivetrain, and actuators. Because both teams build one robot under shared size, mass, and safety limits, the two teams must jointly define interface requirements.

## Restating the Fully Formulated Problem

The objective of this project is to design and build an autonomous robot capable of completing tasks required by the 2027 IEEE SoutheastCon Hardware Competition. In addition to navigating the course, the robot must perform several actions without human control. These include completing the required pit stop, exchanging a red spare tire for a different blue spare tire, and raising a university flag during the final victory lap. The robot must integrate these mechanisms with the master controller, power system, sensors, drivetrain, and mechanical chassis while remaining reliable throughout the course. The finalized rules award 25 points for raising the school flag during the final lap and up to 65 points for correctly dropping off the red tire and acquiring the blue tire in the assigned pit box.

The actuator subsystem will therefore provide the electrically controlled mechanical motion required to accomplish the flag-raising and tire-changing tasks. The subsystem must operate autonomously based on commands from the master controller and must remain inactive until the proper point in the competition sequence. The complete robot must initially fit within a 12 in. × 12 in. × 12 in. starting volume, although mechanisms may expand after the match begins. The actuator design must also safely interface with the robot's power system and emergency stop. Competition rules allow flexibility in electrical actuator selection but restrict the robot's power distribution system to 30 V or less and require wiring to be appropriately rated for its electrical load.

In the latest rules revision, the updated manual introduces several changes that affect the robot’s navigation, scoring, and mechanical design. The number of obstacles has increased from two to three, requiring the robot to detect and navigate around additional obstacles while maintaining reliable course completion. The updated rules also provide specific obstacle placement requirements, with obstacles positioned in designated course quadrants. As a result, the robot’s navigation system must accommodate additional obstacles and potential variations in their placement.

The scoring system has also been revised to reward successful performance rather than primarily penalizing errors during a round. Points are now awarded for avoiding contact with the gray course walls and obstacles, with up to 15 points per lap for avoiding the walls and 25 points per lap for avoiding obstacles. The updated rules also establish a time-based scoring incentive, awarding points for completing the course within a three-minute time limit and providing a bonus for finishing in less than two minutes and forty-five seconds. These changes increase the importance of balancing speed, obstacle avoidance, and reliable autonomous operation.

Additional revisions clarify the pit stop challenge and its scoring requirements as well. It explains that the robot must deposit and spare red tire and acquire a blue replacement tire, with the number of points being depended on whether each time is handled in the assigned pit box. The rules award 25 points for depositing the red tire in the assigned pit box and 40 points for acquiring the blue tire in that location, for a maximum of 65 points for the tire exchange. The scoring rules also specify that points for acquiring the blue are removed if the robot drops it before crossing the finish line. These requirements influence the design of the tire-handling mechanism and the robot’s ability to retain the replacement tire through the remainder of the course.

Finally, the updated manual included a revised course drawing, along with an appendix describing obstacle placement, and an appendix detailing the pit stop challenge. It also introduces an appendix for the starting-flag procedure, although the manual provided still identifies those details as a placeholder. Also, the final match is now to take place at the awards banquet. Together, these changes in the rules alter what methods and parts we use for the robot moving forward. Taking into account for the revised course layout, updated scoring priorities, and reliable tire exchange is important parts to accomplish our goal.

## Comparative Analysis of Potential Solutions

The logic dictating actions for the autonomous robot is one large control system, whose inputs are the various object / boundary detection sensors, the camera, and push buttons to trigger certain actions. Its outputs are speed & direction of motors, flag-raising actuator, and tire-changing actuators. The master controller of the robot must be capable of receiving sensor inputs, it must have the computing power to make decisions about it’s next actions, and it must send signals to the motor control & actuators to perform said actions. There are two potential high-level topologies that could be used: one uses a single-board computer (such as a Raspberry Pi or Jetson Nano) for controlling logic and a low-level controller (LLC) to interface with the sensors & motors. The master controller would receive data from the LLC, perform some calculations to dictate it’s next action for the motors / actuators, then send that data to the LLC. The second topology uses a microcontroller for both the master control and the low-level controller.

The main advantage of a single-board computer with an LLC is the computing capabilities. With a single-board computer, high-level languages can be used to program the robot, which could shorten development time. An SBC is also capable of vision processing and more complex navigation control, so the camera could be hooked up directly to the SBC and vision processing could be handled there. However, this design would require two code bases for each controller. Using an SBC would also require running a general-purpose operating system and the software setup that comes along with that, which the team lacks experience in. There’s also a concern with file-system corruption during data transfer to an SD card.

Using a single microcontroller as the master controller and low-level controller would be a much simpler solution since it wouldn’t require dealing with a general-purpose operating system. It would also only require one codebase, have a near instant boot-time, closed-loop motor control and fast sensor reads. The main drawback from this topology is the limited processing power of a microcontroller. It could not handle complex navigation control or vision processing, so a separate camera processing unit would be required for this topology.

Even with its processing drawbacks, the team has decided to move forward with the single microcontroller topology. The competition requirements are simple enough to where the processing power of an SBC will not be needed for complex navigation control, and the lack of vision processing can be addressed with a dedicated machine vision platform that can interface directly with the master controller. The team’s embedded systems experience will complement this topology. The advantages & disadvantages of these topologies will be discussed in further detail in the master controller atomic subsystem specification and the vision processing atomic subsystem specification.

## High-Level Solution

### Hardware Block Diagram

<img width="1034" height="702" alt="image" src="https://github.com/user-attachments/assets/fe4c2065-adf0-4615-82c0-2ab2c0f5c8aa" />


### Operational Flow Chart

<img width="976" height="512" alt="image" src="https://github.com/user-attachments/assets/cca70062-86b6-47cd-94a2-d2cdaae6d8e4" />

<img width="976" height="606" alt="image" src="https://github.com/user-attachments/assets/78cfb3d6-fde0-4bcc-a8a2-4992185679d2" />

<img width="977" height="591" alt="image" src="https://github.com/user-attachments/assets/6f6a6f97-0115-49e4-962c-0d0458acfc26" />

### Electrical Interconnect Design

For the competition, the implementation of a printed circuit board (PCB) is optimal for us to maintain a secure connection throughout the competition when transporting the robot and while the robot is competing. We are also able to incorporate different power and controller peripherals onto one board to ensure that there are no power limitations with any part of the robot to ensure consistent performance during the competition. These devices will either be mounted somewhere on the robot skeleton or the PCB with mounting holes so that wires can be short for reduced delay.

With the design, we will place the desired microcontroller development board in the center and have adjustable connectors to allow different peripherals on the robot to switch in and out parts if something were to break during the competition or in transport. We will also have a connector for the battery that we chose to use for our robot and mounting points for devices like 12V motor controllers and step-down buck converters to power the MCU. With this, we will need to make sure that wire gauges are proper for the load that there will be inserted into the connectors and are simple to use for consistent creation.

One type of connector to use is a screw terminal connector, which allows for simple switching of wires by clamping a single exposed wire between to pieces of metal by tightening a screw to one terminal. This connector type is good because it’s easy to switch in and out wires for different devices, but sometimes if the wire is not seated properly, the wire will fall out and that device would lose connection.

Another type of connector that we could use to connect sensors and devices are Molex KK connectors. Molex connectors have a small footprint along with are modular enough to use in our PCB design. With the variety of different pin amounts for their connectors, these connectors make a valuable addition to the PCB for different peripherals and easy cable management.

The final connector that we looked at was a JST connector, which is very similar to the Molex KK connector. This connector would also be optimal for different sensors and other components for our robot as it is easy to adjust different pin amounts, has a small footprint on the PCB, and will allow simple cable management for the robot.

<img width="320" height="246" alt="image" src="https://github.com/user-attachments/assets/57169e85-e558-4489-86ca-681cb9b704d9" />
<img width="250" height="250" alt="image" src="https://github.com/user-attachments/assets/c1ce2386-69fd-4dab-90ba-3715f5c1e059" />
<img width="250" height="250" alt="image" src="https://github.com/user-attachments/assets/b225e4af-afea-4e77-a982-378492b9c880" />

*Left: Screw Terminal Connector*
*Middle: Molex KK Connector*
*Right: JST Connector*

To connect the battery that is going to power all devices on the robot, we would need to ensure a stable and consistent connection to the motors, to supply constant power to the microcontroller development board, and to power different sensors and other peripherals that are on the robot.

A high current battery connector that is commonly used is a breakaway power connector. These are commonly used for car batteries due to the large gauge size that you can use with it, rating around 50 amps. This component allows for easy mounting; however, this may be more than is necessary given the rated current output for the robot.

Another common type of connector for batteries is XT30 power connectors, which allow for 15-30 amps of current. This would allow us to switch in and out batteries easier during competition so that we can recharge batteries between rounds for full performance each competition round.

<img width="403" height="403" alt="image" src="https://github.com/user-attachments/assets/6807c33c-0de9-421f-b14f-94000e32f041" />
<img width="402" height="402" alt="image" src="https://github.com/user-attachments/assets/5e70e9eb-5405-47d7-8b48-0811606e59db" />

Left: Breakaway Power Connector

Right: XT30 Battery Connector

Implementing a PCB to the design will allow for the robot to have consistent connections through the competition and allow for a modular system in the case that any wire or peripherals is to break while competing. Utilizing different connector types will help to keep organized and not plug a device into the wrong places on a development board. With this, it is also easier to diagnose different failure points on the robot easier with more cable management and provides a consistent connection for all devices to be used on the robot.

For the finalized design, we will be incorporating 1.25mm JST connectors for all peripherals for the board on the outside of the PCB. This will allow for easy switching in and out for devices that may break during competition and a more trackable way for debugging when testing. For the battery connection, we will be implementing the XT30 battery connector as typical 12V batteries will have this connector already attached. Utilizing both of these connectors in the design will allow for a consistent connection across the entire robot so that communication can be relayed consistently and be stable with different forces the robot may experience during competition.

## Atomic Subsystem Specifications

### Master Control

The master control system can be broken down into three major components, or two depending on how the camera subsystem is implemented. The two main core jobs will be collecting all the data from sensors for different tasks as well as sending out signals to actuators for different tasks. Additionally, based on how the camera subsystem is designed, the master controller also must do the computational of the Image Processing and AprilTags Detection. The robot shall also use a combination of sensors that will allow the robot to perceive its location on the game board and be able to identify objects on the board. The robot should utilize a camera that can perceive both color and April Tags detection to score points.

Despite its name, ROS (Robot Operating System) isn't an operating system. It's a middleware framework that runs on top of Linux, providing drivers, communication tools, and shared infrastructure that make robotics software reusable across platforms. Before ROS, every robot had its own sensors, motors, and protocols, so developers had to rewrite code for each new machine, and a navigation algorithm built for one robot rarely worked on another [13].

The idea is similar to printer drivers on Windows [13]. Word never talks to the printer hardware directly, so the same print command works with any printer that has the right driver. ROS does the same for robots: control software talks to standardized interfaces instead of hardware, so the same program can run on very different platforms as long as ROS-compatible drivers exist. This is why ROS is widely used in self-driving vehicles (integrating LiDAR, cameras, and GPS), industrial robots (pick-and-place, welding, manufacturing), and humanoid robots (navigation, manipulation, and grasping).

A real-time operating system (RTOS) is a specialized operating system built to handle time-sensitive tasks with precise timing constraints, ensuring predictability and stability. Its main roles are task scheduling, hardware resource management, and interrupt handling. Each program the system manages is treated as a task, and handling many tasks at once is called multitasking [14].

On a single-core microcontroller, true parallel execution isn't possible. Instead, the RTOS scheduler allocates short time slots to different tasks, and because the processor is fast (for example, 72MHz), the switching happens so quickly that the tasks appear to run in parallel. Tasks are assigned priorities based on how critical they are and how tight their timing requirements are, so the scheduler can make sure high-priority tasks meet their deadlines[15].

Software interrupts are a useful way to handle robot control code without making it overly complex. They simulate hardware interrupts by triggering a response whenever a specific condition is met. For example, a robot might start its boot sequence when a button is pressed, or halt a critical action when a sensor reading goes out of range.

The key difference between interrupt-driven and polling-based code is how events are detected. With polling, the processor continuously checks a peripheral’s status in a loop. With interrupts, the peripheral notifies the processor only when an event occurs, which frees the processor to do other work in the meantime.

Comparison of solutions:

Jetson Nano

<img width="453" height="341" alt="image" src="https://github.com/user-attachments/assets/18468b6a-c95b-4641-af78-c2e0db936b87" />

Jetson Nano Development Kit

The NVIDIA Jetson Nano is a compact, powerful single-board computer designed for running artificial intelligence and deep learning applications at the edge. Despite its small footprint, it features a specialized GPU optimized for efficient AI processing, paired with a multi-core CPU, ample memory, and flexible storage options. Together, these allow it to handle complex AI models and real-time inference workloads without the need for a full-sized workstation [16].

The board also supports NVIDIA's Vision Programming Interface (VPI), a software library that implements computer vision (CV) and image processing (IP) algorithms across a range of computing hardware platforms, including NVIDIA's embedded and discrete devices [18]. By leveraging VPI, the Jetson Nano can perform tasks such as AprilTag detection, color detection, and object detection, all of which are valuable for robotics, navigation, and automation projects.

In addition, the Jetson Nano can run SLAM (Simultaneous Localization and Mapping) for lightweight 2D and 3D robotics applications. This is typically achieved by combining the Robot Operating System (ROS) with suitable SLAM algorithms, allowing a robot to build a map of its surroundings while tracking its own position within it [19]. Since the board also offers native support for ROS, developers can easily integrate sensors, actuators, and software packages into a unified robotic system, making the Jetson Nano an accessible and versatile platform.

Despite its strengths, Jetson Nano comes with some drawbacks, particularly in terms of power consumption and cost. Although it is relatively efficient for an AI-capable board, it still draws considerably more power than simpler microcontrollers or basic single-board computers such as the Raspberry Pi. It typically requires a stable 5V supply, and in its higher performance 10W mode it may need a barrel jack power adapter rather than USB power alone [20]. This can be a limitation for battery-powered or portable robotics projects, where the added draw shortens runtime and may call for larger battery packs, which in turn adds weight and bulk. Cost is another concern. The Jetson Nano is more expensive than many competing hobbyist boards, and the price rises further once essential accessories are factored in, such as a quality power supply, a cooling fan or heatsink, a microSD card or other storage, and a Wi-Fi module, since the board does not include wireless connectivity by default. The board itself without modules can vary from 89$ to 199$ with the Jetson Nano Developer Kit going up to 249$.

Raspberry Pi 5 Development Board

<img width="400" height="301" alt="image" src="https://github.com/user-attachments/assets/55c9b5f0-9500-4184-893e-0b4279ecfc14" />


The Raspberry Pi 5 is a full single-board computer built around a quad-core
2.4 GHz Arm Cortex-A76 processor, with dual-band Wi-Fi, Bluetooth 5.0, a
40-pin GPIO header, and two MIPI ports for cameras or displays [25]. Like the
Jetson Nano, it runs a general-purpose Linux operating system, which gives it
access to a very large community and software ecosystem. It could run
AprilTag detection and color detection in Python or OpenCV on a connected
camera, making it a candidate for the vision layer of the robot. Compared with
the Jetson Nano, it lacks a CUDA-capable GPU, so heavier neural-network
inference would run more slowly, but it offers built-in wireless connectivity
and a simpler software setup for classical vision tasks.

Its drawbacks are similar to those of the Jetson Nano. It recommends a
5V/5A USB-C power supply, which is a substantial load for a battery-powered
robot [26]. Prices have varied considerably by retailer and memory size, and
accessories such as the power supply, cooling, and microSD card add to the
cost [25]. Because it runs Linux rather than an RTOS, it is also a poor fit
for the 5 to 10 ms motor control loop required by this robot, and it has no
analog inputs for sensors. It therefore works best as a vision layer paired
with a microcontroller, not as the main controller.

STM32 Board NUCLEO

<img width="398" height="598" alt="image" src="https://github.com/user-attachments/assets/c7b91272-feb1-4360-b65f-30404ff6b52a" />

STM32 Nucleo-H753ZI2 Development Board

STM32 Nucleo boards are a good fit for RTOS/ Interrupt-based projects: they're affordable, include an ST-LINK debugger/programmer, and offer expansion headers, which makes prototyping and debugging convenient. STM32CubeIDE also makes it easier to configure pins and create RTOS tasks, NVIC Interrupt since it can generate the FreeRTOS (CMSIS-RTOS) scaffolding automatically [21] and generate code for Interrupt task.

This development board exhibits varying power consumption depending on whether the entire board or only the microcontroller (MCU) core is measured. When the entire board is powered via USB or an external supply, typical current consumption ranges from 150 mA to over 250 mA (approximately 0.5 W to 0.8 W at 5V) due to auxiliary components like the integrated ST-LINK debugger, status LEDs, and the onboard Ethernet transceiver. For the isolated STM32H743ZI MCU core, power efficiency scales at roughly 275 µA/MHz under typical running conditions; when operating at its peak clock speed of 400 MHz to 480 MHz, the core itself draws between 110 mA and 130 mA [29].

The main drawbacks of this board are its lack of camera and USB host support and the steep learning curve it presents for the team. The board has no dedicated CSI or DCMI camera connector and no USB host port, so connecting a CSI or USB camera would require extra hardware, such as an adapter board or external module, or a switch to a different platform, which limits its suitability for vision-based features. In addition, development on this MCU demands a significant amount of low-level knowledge, including clock tree configuration (RCC) and the PLL and prescaler calculations behind it, pin assignment and alternate-function mapping, NVIC interrupt priority setup, and timer configuration for PWM, capture, and similar modes. These tasks are error-prone, and a small mistake such as a wrong clock divider or interrupt priority can cause subtle, hard-to-debug problems, which increases onboarding time and project risk, especially for team members new to embedded systems. A NUCLEO-N657X0-Q was considered as an alternative developement board due to it's built-in support for a CSI camera, however using an external camera module to process image data will allow for higher-level languages to be used for development. Camera needs could be met with a board that has a built-in camera interface or a companion module such as an OpenMV camera or Raspberry Pi.

Teensy Development Board

<img width="770" height="222" alt="image" src="https://github.com/user-attachments/assets/482dd484-c21f-410b-b55f-bd45859ad7c5" />

Teensy 4.1 Development Board

The Teensy 4.1 is attractive for this robot because of its raw microcontroller performance and low cost. It uses a single-core 600 MHz Cortex-M7 (NXP iMXRT1062) with 8MB of flash, 1MB of RAM, 55 digital I/O pins, and 18 ADC channels, at a price of about $32. Like the STM32H743ZI, its Cortex-M7 core is dual-issue and includes a hardware FPU for both 32-bit and 64-bit math, which suits the PID calculations and sensor filtering this robot needs, so the core architecture itself does not separate the two boards. Compared with the Jetson Nano, the Teensy draws only about 100mA at 600 MHz, which helps battery life, and it costs less than the Nano once accessories are included. Compared with the STM32 Nucleo, the Teensy has a higher clock speed (600 MHz versus up to 480 MHz), and it can be programmed from the Arduino IDE with the Teensyduino extension, which lowers the learning curve for a student team [22].

Teensy also has drawbacks. It is a bare board with no built-in ST-LINK-style debugger, so debugging relies mostly on serial prints, whereas the Nucleo includes a debugger and the STM32CubeIDE setup tools. It also has less official RTOS tooling than the STM32, so running FreeRTOS would depend on community ports rather than generated project scaffolding. Next to the Jetson Nano, it has no GPU or camera pipeline, and it has no built-in Wi-Fi or Bluetooth, so AprilTag detection would have to run on a separate camera module or companion computer and send results over UART or I2C. Headers may also need to be purchased and soldered separately, depending on the version. Overall, the Teensy is a strong, low-power, low-cost choice for the real-time control layer, but it works best paired with a vision module rather than replacing one [23],[24].

Raspberry Pi Pico 2 Development Board

<img width="480" height="191" alt="image" src="https://github.com/user-attachments/assets/55b65784-3e62-4707-97dc-ee9a5e1bcf16" />


Raspberry Pi Pico

The Raspberry Pi Pico 2 is a microcontroller board and competes directly with
the Teensy 4.1 and STM32 Nucleo. It uses the RP2350 chip with dual Cortex-M33
cores at 150 MHz, 520 KB of SRAM, and 4 MB of flash [27]. At about $5, it is
by far the cheapest board in this comparison. It offers 26 GPIO pins, 3 ADC
inputs, 24 PWM channels, and programmable I/O (PIO) blocks that can handle
custom interfaces such as encoder reading [28]. It can be programmed in
C/C++, MicroPython, or the Arduino IDE, and drag-and-drop programming over
USB keeps setup simple for a student team [28].

Its limitations are a lower clock speed than the Teensy 4.1 (600 MHz) or the
Nucleo-H743ZI2 (480 MHz), less memory, and only three ADC channels, which
could be tight if the robot uses many analog distance sensors. It has no
built-in debugger, so debugging relies on serial output or the separate
Raspberry Pi Debug Probe [27]. It also has no camera interface, and the
standard Pico 2 has no Wi-Fi, so vision would have to run on a separate board.
Still, 150 MHz is more than enough for a PID loop and wall following, so the
Pico 2 is a strong low-cost option for the real-time control layer and could
be paired with a Raspberry Pi 5 for vision.
Price Comparison

| Board | Processor | Clock Speed | Approximate Price | Camera Compatible |
| --- | --- | --- | --- | --- |
| NVIDIA Jetson Nano (4GB Dev Kit) | Quad-core ARM Cortex-A57 + 128-core Maxwell GPU | 1.43GHz | $99 Minimum | USB Camera, CSI Camera |
| STM32 Nucleo-H753ZI2 | Single-core ARM Cortex-M7 (STM32H753ZI) | 480MHz | $40 | Camera over UART or I2C. |
| Teensy 4.1 | Single-core ARM Cortex-M7 (NXP iMXRT1062) | 600MHz | $32 | Camera over UART or I2C. |
| Raspberry Pi 5 | Quad-core ARM Cortex-A76 (Broadcom BCM2712) + VideoCore VII GPU | 2.4GHz | $110 | USB Camera, CSI Camera |
| Raspberry Pi Pico 2 | Dual-core ARM Cortex-M33 (RP2350) | 150MHz | $18 | Camera over UART or I2C. |

#### Weighted Trade Study

The boards were evaluated against criteria derived from the robot's
specifications. Each criterion is tied to a requirement, and weights reflect
its importance to mission success. Scores use a 1 to 5 scale
(1 = poor, 3 = acceptable, 5 = excellent).

#### Criteria and Weights

| # | Criterion | Tied Specification | Weight |
| --- | --- | --- | --- |
| 1 | Real-time control | REQ-1: 5 to 10 ms motor control loop with deterministic timing | 20% |
| 2 | Vision capability | REQ-2: AprilTag and color detection from a camera | 15% |
| 3 | Power consumption | REQ-3: battery-powered operation from a 5 V supply | 15% |
| 4 | Cost | REQ-4: project budget, including required accessories | 15% |
| 5 | I/O and interfaces | REQ-5: analog distance sensors, PWM for motors, encoders, UART/I2C | 15% |
| 6 | Ease of development | REQ-6: student team with limited embedded experience | 10% |
| 7 | Debug and RTOS tooling | REQ-7: RTOS support and ability to debug | 10% |
| | **Total** | | **100%** |

#### Weighted Decision Matrix

| Criterion (Weight) | Jetson Nano | Raspberry Pi 5 | STM32 Nucleo-H743ZI2 | Teensy 4.1 | Raspberry Pi Pico 2 |
| --- | :-: | :-: | :-: | :-: | :-: |
| Real-time control (20%) | 2 | 2 | 5 | 5 | 4 |
| Vision capability (15%) | 5 | 4 | 1 | 1 | 1 |
| Power consumption (15%) | 1 | 1 | 3 | 4 | 5 |
| Cost (15%) | 2 | 2 | 4 | 4 | 5 |
| I/O and interfaces (15%) | 2 | 2 | 5 | 5 | 3 |
| Ease of development (10%) | 3 | 4 | 2 | 5 | 5 |
| Debug and RTOS tooling (10%) | 3 | 3 | 5 | 2 | 3 |
| **Weighted total (out of 5)** | **2.50** | **2.45** | **3.65** | **3.80** | **3.70** |

#### Scoring Rationale

| Criterion | Basis for Scores |
| --- | --- |
| Real-time control | The Jetson Nano and Raspberry Pi 5 run Linux, so timing has jitter. The STM32 and Teensy are bare-metal or RTOS capable. The Pico 2 is slower at 150 MHz but sufficient for a PID loop. |
| Vision capability | The Jetson Nano has a GPU, VPI, and CSI support. The Raspberry Pi 5 has CSI and OpenCV but no CUDA acceleration. The microcontrollers need an external camera module. |
| Power consumption | The Jetson Nano (5 to 10 W) and Raspberry Pi 5 (5 V/5 A supply recommended) draw the most. The STM32 board draws about 0.5 to 0.8 W. The Teensy draws about 100 mA at 600 MHz. The Pico 2 draws the least. |
| Cost | Based on the price table plus accessories noted in the text (power supply, cooling, storage). |
| I/O and interfaces | The Jetson Nano and Raspberry Pi 5 have no analog inputs. The Teensy has 18 ADC channels and 55 I/O pins. The Pico 2 has only 3 ADC channels. |
| Ease of development | The STM32 requires low-level configuration (clock tree, NVIC, timers). The Teensy and Pico 2 use Arduino or MicroPython. |
| Debug and RTOS tooling | The STM32 has ST-LINK and generated FreeRTOS scaffolding. The Teensy relies on serial prints and community RTOS ports. The Pico 2 needs a separate Debug Probe. |



The Jetson Nano and Raspberry Pi 5 score lowest because they are not suited to
the real-time control layer, but they remain the strongest options for vision.
Among the microcontrollers, the Teensy 4.1, Pico 2, and STM32 are close. The
STM32 Nucleo is selected as the master controller because of its ST-LINK
debugging, generated FreeRTOS support, and I/O capability, which become the
deciding factors when debugging and RTOS tooling are weighted more heavily.

#### Proposed Solution:

ROS 2 vs RTOS for this project

ROS 2 is designed for systems where perception, localization, and planning must be coordinated across many software components, typically in large or unstructured environments. The field is a single 4' x 8' sheet of plywood with a fixed layout, a 3-minute match limit, and a task that reduces to a short state machine: start, complete laps, make a pit stop, complete the remaining laps, and finish [2]. The environment is small and known in advance, with only three to four randomly placed obstacles and one randomly selected AprilTag, so the robot does not need a map, global localization, or long-horizon path planning. Capabilities such as SLAM, a navigation stack, and a transform tree address problems this competition does not present.

Several time-constrained tasks benefit from RTOS. A motor control loop, such as a velocity PID controller, must run at a fixed period of roughly 5 to 10 ms, since mistiming can cause drift or oscillation, and a high-priority task using vTaskDelayUntil() keeps that period deterministic. Distance sensors can take tens of milliseconds per reading, so instead of blocking everything as in a single-loop design, the sensor task can wait on a DMA transfer or semaphore while the control loop keeps running. Obstacle response also depends on low sensing and planner latency, since each lap with contact forfeits 15 points. Finally, the pit stop must last at least 2 seconds to earn the full 15 points (otherwise 10), so a fixed-delay task targeting about 2.3 seconds is a simple, verifiable way to add margin. Given this, a microcontroller board can run RTOS or basic loops with interrupts are adequate for this project.

#### Proposed Solution

The proposed solution is to use the NUCLEO-H753ZI development board. It provides the hardware timers, encoder interfaces, PWM channels, ADCs with DMA, and communication peripherals needed to interface all sensors and actuators on one board. Many team members are familar with the STM32 archtecture, and its on-board ST-LINK debugger addresses the debugging limitation noted for the Teensy 4.1 and Pico 2. The proposed firmware will use an interrupt-driven design with a polled state machine instead of an RTOS. If the number of concurrent tasks grows beyond what a single interrupt-based loop can handle, migrating to FreeRTOS via STM32CubeIDE remains possible on the same hardware. A microcontroller-based master controller was selected over the Jetson Nano and Raspberry Pi 5. As previously mentioned in the Comparative Analysis of Potential Solutions section, a single-board computer running Linux is not necessary for the requirements of this competition. A microcontroller is much more suited to deterministic control and sensor I/O. While the Teensy 4.1 has a faster clock for a lower price, it has no on-board debugger and is limited in number of pins. The Raspberry Pi Pico 2 is the cheapest option but has a 150 MHz clock, less memory, and fewer ADC channels. The Nucleo provides more computing margin, more analog inputs, and more memory for the sensor suite.

### Motor Control

#### Hardware

For the robot to move consistently and accurately during the competition, we need to design reliable way to control the speed and direction of each motor. We are looking at using 12V brushed DC gearmotors that have built-in encoder. The microcontroller will generate a pulse-width modulation (PWM) signal, and the driver will switch the 12V battery to supply to the motor at that duty cycle, which controls how fast the motor spins. The encoder reports how far the shaft shas turned, which allows for the microcontroller to loop back into the system to ensure that each motor is doing what it is commanded to do and is correct in real time. Instead of designing our own driver circuit, we will be using a pre-made motor-driver board. These boards are already built and tested, which saves design time, reduces the risk of a power circuit failure, and lets us replace a damaged driver quickly during the competition.

The simplest approach to driving a DC motor is a simple MOSFET switching the motor on and off. This approach is cheap and easy to build; however, it only lets the motor spin in one direction and cannot actively brake. Since the robot will need to have the motors move clockwise and counterclockwise to effectively use the proposed mechanisms wheels, this option is too limited for our design.

A better option is using a premade H-bridge motor driver, which lets current flow through the motor in either direction and supports braking. One option is the Cytron MDD10A, a dual channel driver that can run both motors from one board. It is rated well above the current our motors would normally draw, which gives is a margin if the robot gets pushed or stalls during a round. It is controlled by one PWM pin and one direction pin per motor, which allows for the wiring from the microcontroller to be kept simple, and it will work with the 3.3V logic, which allows for a direct connect to the microcontroller board without extra steps.

Another option is the BTS7960 driver module, which is a high-current single-channel H-bridge board that is easily available and inexpensive. It does have a far higher current capacity than our motors need, which makes it very tolerant of stalls and sudden loads. It also has current-sense pins which can be used to monitor the motor load. The tradeoff is that each module only drives one motor and is physically large, so it would take up more space on the robot and increase the number of wires.

><img width="348" height="348" alt="image" src="https://github.com/user-attachments/assets/68453c5e-5395-4831-8861-5497498b674d" />
><img width="345" height="345" alt="image" src="https://github.com/user-attachments/assets/bcf1b75b-0454-4881-9565-681b8f683f44" />
>
>*Left: Cytron MDD10A Motor Driver*
>
>*Right: BTS7960 Motor Driver Module*

When comparing these different options, other features other than functionality are also appealing when using these parts for the robot. When looking at the constraints of the competition in relation to the size constraint of 12"x12"x12", we need different devices that do not take up a lot of space on the robot. Using MOSTFETs for the design would require a lot of testing to incorporate the design from scratch and ensure that it would work consistently during the competition. The Cytron MDD101A motor driver does have this lower profile when compared to the BTS7960, which makes it more appealing for the design when looking at size constraints.

With this, a table was made in order to help distinguish the advatages, disadvantages, and the suitability of each of the three ways to control the motors below:

| Motor Driver Option | Advantages | Disadvantages | Suitability |
|---|---|---|---|
| **MOSFET Switching Circuit** | Low cost, simple design, easy to implement. | Only supports one direction of rotation and cannot actively brake the motor. | Not suitable because the robot requires bidirectional motor control. |
| **Cytron MDD10A** | Dual-channel H-bridge; drives both motors with one board; high current capacity; simple PWM and direction control; compatible with 3.3V logic. | Less current-sensing capability compared to the BTS7960. | Highly suitable due to its compact design, simple wiring, and ability to drive both motors. |
| **BTS7960** | High current capacity; supports bidirectional control and braking; includes current-sense pins; inexpensive and readily available. | Single-channel design requires two boards; physically larger; increases wiring complexity. | Suitable, but requires more space and wiring than the MDD10A. |

Overall based on the points that the table addresses, the Cytron MDD10A as it is a low profile H-bridge motor driver that will supply 10A continuously and has a motor supply voltage of 5V to 30V, which allows for a wide variety of DC motor types.

#### Software

Rather than simply turning the motors completely on or off, there are two different potential ways to control the motors: an exponential ramp that shapes how the robot speeds up and slows down, or a PID controller that makes each motor follow that ramp accurately.

With an exponential ramp that can be programmed, it is simply an open-loop control system as there are no sensors determining the speed, as the motors would be controlled solely on a time-based mathematical trajectory. The motors would change fast at first movement, then slow down asymptotically. With this following a pre-calculated curve, there can be different disturbances from other electronics or the playing field, which the motor speed would not change. This method however is simple to implement, as there is not really any tuning required, but a time-constant rate would need to be chosen.

When the robot is commanded to a new speed, if we were to jump straight to it, there would be a large current spike from the battery, put stress on the gearboxes, and could make the wheels slip or the robot move off course.
To prevent this, we will use an exponential ramp. Each time the control loop runs, the speed setpoint moves a fixed fraction of the remaining distance toward the target speed:

New Setpoint = Current Setpoint + k * (Target Speed – Current Setpoint)

Here, k is a constant value between zero and one that we can tune to adjust the speed. When the robot is far from its target speed, the setpoint will change quickly, and as it gets closer, the changes become progressively smaller, allowing for the motors to ease smoothly into the final speed. The same method applies when slowing down, so the robot decelerates gradually instead of stopping abruptly, which helps it to stop accurately without overshooting or tipping. A larger value of k makes the robot more responsive, while a smaller value makes it smoother. This lets us balance quick reactions against smooth, controlled motion during testing.

The ramp determines what speed each motor should be running at, and a PID (proportional-integral-derivative) controller makes sure each motor reaches that speed. At a fixed rate, the controller calculates the error between the ramped setpoint and the measured speed, then adjusts the PWM duty cycle using three terms:

- Proportional (P): Corrects in proportion to the current error. A larger error produces a stronger correction.

- Integral (I): Builds up over time to remove small, steady errors, such as a motor that consistently runs slightly slow because of friction or a dropping battery voltage.

- Derivative (D): Reacts to how quickly the error is changing, which reduces overshoot and oscillation.

><img width="623" height="332" alt="image" src="https://github.com/user-attachments/assets/20286d9d-f90b-4b5a-a027-546b66ad13fc" />
>
>*Example diagram of a PID controller*

#### Converting Encoder Pulses to Speed

The motor encoders don't output speed directly. Each one produces two square-wave signals (channels A and B), offset 90° from each other, with a fixed number of pulses per revolution of the motor shaft. To get the measured speed y(t) that the PID loop compares against the ramped setpoint, the controller first counts these pulses and then turns the count into a speed.

Each motor's encoder channels connect to a hardware timer on the microcontroller set to encoder mode. In this mode the timer counts both the rising and falling edges of both channels (4× decoding), so we get four counts for every encoder pulse. The timer counts up when the motor spins forward and down when it spins in reverse, which means the count tracks both how far the shaft has turned and which way. All of this happens in hardware, so it uses no processor time and no pulses are missed, even at high motor speeds. Because each motor needs its own timer, a requirement for choosing the microcontroller is that it has at least one encoder-capable hardware timer per motor, plus a separate timer to generate the fixed-rate interrupt that runs the PID loop. If the microcontroller doesn't have enough timers that support encoder mode, the encoders could be read with pin-change interrupts instead. That method uses processor time on every pulse and could miss counts at high speeds, so dedicated hardware timers are preferred.

To get speed, the controller reads each timer's count at the same fixed rate the PID loop runs at, using a sample period T_s. It subtracts the previous reading to find how many counts happened during that period, then converts the result to the output shaft's speed:

> ω[n] = (C[n] − C[n−1]) / (4 x N_PPR x G x T_s)  [rev/s]

Here C[n] is the current timer count, N_PPR is the number of encoder pulses per motor revolution, and G is the gearbox ratio. If we want the robot's linear speed, the wheel speed is v = 2πr x ω, where r is the wheel radius. Because the sample period is fixed by a timer interrupt, T_s stays constant and the speed calculation stays accurate. The hardware counters have a limited size and eventually wrap around. We handle this by doing the subtraction as a signed integer of the same width as the counter. That gives the correct result as long as the number of counts in one sample period stays under half the counter's range. We will confirm this holds once the motor and encoder are selected.

This counting method has one limitation: at low speeds, only a few counts happen during each period, so the measured speed jumps in discrete steps. The smallest speed change we can resolve is one count per sample period, or 1 / (4 x N_PPR x G x T_s) rev/s. A higher-resolution encoder, a larger gear ratio, or a longer sample period all improve this, but a longer sample period also slows down the PID loop's response. We will make this tradeoff once the motor and encoder are selected. To smooth out the steps, we pass the measured speed through a simple first-order low-pass filter before it reaches the PID controller:

> y[n] = α x ω[n] + (1 − α) x y[n−1]

Here α is between zero and one. A smaller α gives a smoother signal but adds delay. This filtering matters most for the derivative term, which would otherwise amplify the step-to-step noise in the speed measurement. We will tune α together with the PID gains during testing. If low-speed accuracy turns out to be a problem, the timers can also run in input-capture mode, which measures the time between encoder edges instead of counting edges in a fixed window. That method is more accurate at low speeds.

Each term has a gain that we will tune through testing the robot on the competition surface. We will also be limiting the integral term so that there isn't too much build up when a motor is being stalled out or the output is already at full power, which would otherwise cause the motor to overshoot once it is free to move. Since all of the motors are needing to be controlled independently, the PID loops will keep the robot driving straight even if one motor is slightly weaker than the other.

Together, the exponential ramp and PID control give the robot smooth, predictable acceleration and deceleration while keeping each motor at its intended speed. This reduces wear on the motors and gearboxes, limits current spikes on the battery, and makes the robot's movement consistent from round to round. The motor drivers will mount to the robot frame or onto mounting holes on the PCB, which will then be connected using the specified connectors defined in that section. This allows for motor wiring to be short and secure, and lets us swap out a driver quickly if one fails during the competition.

### Vision Input & Processing

#### Vision Input & Processing Requirements

To meet the vision input & processing requirements of the proposed solution, the camera system shall meet the following requirements:

* Identify 68x68 mm AprilTags from a distance 2 – 12 inches (estimate based on course dimensions [2])

* Identify the lowering of the green start flag

* Identify the location of the blue tire

#### Proposed Solutions

##### Single Board Computer (SBC) + CSI Camera

This proposed solution uses an SBC running Linux with a CSI-connected camera. The SBC could either act as the main navigation control and interface with a microcontroller to control motors and actuators; or it could act as a dedicated vision processing unit, sending results over UART to the microcontroller-based master controller. Both cases are considered in the previous section on Master Control. This section will only consider the SBC as a vision processing unit. A Raspberry Pi computer and an official CSI Raspberry Pi camera module will be considered for this proposed solution, given their popularity and extensive documentation / community support.

Precedents exist for using a Raspberry Pi 4/5 and CSI camera for AprilTag detection & color detection, as this is a common architecture for autonomous robot vision processing [7]. Raspberry Pi has many libraries for camera integration such as Raspberry Pi’s official camera library, Picamera2. Image processing can be handled with OpenCV [10], a library of programming functions for real-time computer vision. This solution also provides flexibility in the camera module used, as Raspberry Pi states there are many official Raspberry Pi camera modules that can be used [8]. A Raspberry Pi would also provide compute headroom, as it could even be capable of hosting navigation control. If a dedicated computing module was selected as the master controller, using a CSI camera hooked directly up to that would be the most viable option as opposed to a dedicated compute module.

Running a general-purpose operating system introduces risks that a dedicated vision camera avoids. Longer boot time from an SBC adds to pre-match setup. Abrupt power loss can corrupt the SD card filesystem, which would have to be accounted for in design of emergency stop button. A Raspberry Pi would also require assembling the OS, camera pipeline, libraries, and startup services. Running a general-purpose operating system on an autonomous robot can also be affected by software deployment issues, which may require a learning curve given the team’s inexperience with high-level software development. Using a Raspberry Pi can also cause a delayed response due to image processing. These shortcomings could be justified if the solution required the computing power of an SBC for navigation. Since navigation is handled elsewhere and the SBC would perform only vision tasks, the added integration risk is difficult to justify.

A Raspberry Pi 5 with 4GB of RAM would be sufficient for this approach [7]. To ensure proper lighting, a button lamp should be included in camera subsystem.

| Part | Cost | Source |
| --- | --- | --- |
| Raspberry Pi 5 (4GB RAM) Kit | $209.99 | Amazon |
| Raspberry Pi Camera Module 3 Wide | $36.00 | Amazon |
| Button Lamp | $5.99 | Amazon |
| ESTIMATED TOTAL COST | $251.90 |

##### OpenMV Camera

This proposed solution uses a dedicated smart vision module that performs image processing on-board and sends the results to the main controller. OpenMV smart camera running MicroPython. It would perform on-board AprilTag decoding and color blob detection for the three tasks. Results go over a UART link to the main controller, which handles motor and actuator control.

Unlike an SBC + CSI camera, integration for the OpenMV camera is very simple. The camera unit ships with AprilTag and color detection integrated in its firmware and IDE [11][12]. Because the camera runs a script from flash [11], it also avoids the boot time and potential SD card corruption concerns of a Linux-based SBC. While less precedent exists for the OpenMV camera in autonomous competition robots, it has been used for color detection in a similar manner to how it would be used for the SECON Hardware Competition [6]. OpenMV camera is also low power, drawing less than 0.75 Watts with 5V input [11]. While it lacks the wide camera options of using a CSI camera, OpenMV does provide swappable lens’ with their OpenMV N6 [11].

The main drawbacks for using an OpenMV camera would be the lack of precedent. An SBC and CSI camera is standard architecture for autonomous robots that require vision processing, and there exists lots of documentation and support for implementing vision processing with a Raspberry Pi. While the OpenMV camera has been used in similar competitions, it is not a standard. The OpenMV camera also does not provide the computing power of an SBC, so using it for advanced navigation control would not be an option.

The OpenMV N6 board would be most suitable for the task, given it’s more powerful processor, swappable camera module, and convenient peripheral access with jumper wire headers [11]. The OpenMV AE6 could be a viable lower-budget choice. While it isn’t as computationally powerful as and lacks swappable camera module, it does include an 8x8 time-of-flight sensor, which could aid in obstacle detection [12]. To ensure proper lighting, a button lamp should be included in camera subsystem.

| Part | Cost | Source |
| --- | --- | --- |
| OpenMV N6 | $195.00 | OpenMV |
| OpenMV AE3 | $150.00 | OpenMV |
| Button Lamp | $5.99 | Amazon |
| ESTIMATED TOTAL COST | $155.99 – $200.99 |

##### Pros & Cons
| Criterion | Raspberry Pi 5 + CSI Camera | OpenMV Camera (N6 or AE6) |
| --- | --- | --- |
| **Pros** | - Established precedent for AprilTag and color detection in autonomous robots<br>- Extensive documentation and community support<br>- Mature libraries (Picamera2, OpenCV)<br>- Flexible choice of official camera modules<br>- Compute headroom, so it could also host navigation control<br>- Direct CSI connection is the best option if a dedicated compute module is the master controller | - Simple integration, since AprilTag and color detection ship in the firmware and IDE<br>- Runs a script from flash, so there is no OS boot delay<br>- No SD card filesystem to corrupt on abrupt power loss, which simplifies emergency stop design<br>- Low power draw (under 0.75 W at 5 V)<br>- Lower software complexity, which suits the team's limited high-level software experience<br>- N6 offers a more powerful processor, swappable lenses, and convenient jumper-wire header access<br>- AE6 includes an 8x8 time-of-flight sensor that could aid obstacle detection<br>- Results are sent to the main controller over UART |
| **Cons** | - General-purpose OS increases pre-match setup time through longer boot<br>- Abrupt power loss can corrupt the SD card filesystem, which must be handled in the emergency stop design<br>- Requires assembling the OS, camera pipeline, libraries, and startup services<br>- Software deployment issues and a learning curve given the team's inexperience<br>- Image processing can cause delayed response<br>- Extra computing power is unnecessary when navigation is handled elsewhere, so the integration risk is hard to justify | - Less precedent in autonomous competition robots<br>- Less documentation and community support than Raspberry Pi<br>- Lower computing power, so it is not suited to advanced navigation control<br>- Fewer camera options than CSI modules |

#### Chosen Solution

Given that the microcontroller-based master controller toplogy has been selected over the SBC + LLC topology, the OpenMV Camera module has been selected over an SBC + CSI camera. The OpenMV camera performs the required vision tasks on-board using firmware-integrated AprilTag and color detection, then sends results to the master controller over UART. This avoids the added integration risk of an SBC, namely OS boot delay, SD card corruption on abrupt power loss, and a software deployment learning curve. The extra compute of an SBC would go unused, since navigation is not allocated to the vision subsystem.

### Flag Raising & Tire-Changing Actuators

The competition awards 25 points if the robot raises a flag displaying the team’s school logo, colors, or emblem during the final victory lap. The rules specify when the flag must be raised but do not require a specific method for deploying it, allowing the team flexibility in the mechanical design. The flag-raising subsystem must remain stored during the earlier portions of the race and deploy only after the master controller determines that the robot has entered its final lap.

Several possible methods were considered for this task. One option is a linear solenoid, which could release a spring-loaded latch and allow a spring to raise the flag. This approach would provide fast actuation and would only require the solenoid to remain energized briefly. However, the design would require additional components such as a spring, mechanical latch, solenoid driver, and protection circuitry. Another possible solution is a DC gearmotor, which would provide high torque but would require additional position control and a motor driver.

### Flag-Raising Actuator Comparison

| Option | Approx. Cost | Pros | Cons |
|---|---:|---|---|
| **Servo Motor — Selected** | **$8–$25** | Precise angular position control; compact and lightweight; integrates with the existing 5 V servo power system and PWM controller; simple coding because the controller only needs to command stored and raised positions; no separate position sensor is normally required | Must provide enough torque to raise and hold the flag; can draw high current if stalled; linkage must be designed carefully; mechanical stops may be needed |
| **Solenoid + Spring** | **$18–$30** | Fast deployment; simple ON/OFF operation; low operating time; coding is relatively simple because the controller only needs to energize the solenoid for a short timed pulse and prevent repeated activation | Requires a spring, latch, MOSFET/driver, and flyback protection; limited position control; additional mechanical components increase complexity |
| **DC Gearmotor** | **$16–$40+** | High torque; flexible range of motion; speed can be controlled with PWM | Requires a separate motor driver; more complicated coding because direction, speed, and stopping position must be controlled; likely requires an encoder or limit switch; more wiring and components |

The solution we decided on is a servo motor. The servo will directly rotate the flag arm from its stored position to its raised position when commanded by the master controller. A servo was selected because it provides controlled angular positioning in a compact package and can be driven using the PWM control hardware already planned for the robot. The team’s current power architecture includes a regulated 5 V servo supply and a PWM controller, allowing the flag mechanism to be incorporated without adding a separate high-current actuator control system. Safety considerations for the flag mechanism will follow the risk-reduction approach of ISO 12100:2010. The primary hazards identified for the mechanism are unexpected servo motion, mechanical binding, pinch points around the linkage, and interference between the raised flag and other robot components. These risks will first be reduced mechanically by limiting the servo's allowable travel and providing mechanical stops that prevent the linkage from rotating into the chassis or beyond its intended deployed position. Software position limits will provide additional protection but will not be relied upon as the only means of preventing excessive travel.

For the tire-changing mechanism, the actuators chosen will be decided by the mechanical team’s design. They presented two options for us: one is a servo-controlled claw that starts by carrying the red tire. During the pitstop maneuver, the robot would drop the red tire and use the camera to identify the location of the blue tire. The servo claw could then be used to pick up the blue tire and continue with the race. This design would be simple and would not take up much space for the robot; however it would require precise positioning based on data received from the camera subsystem.

<img width="471" height="471" alt="image" src="https://github.com/user-attachments/assets/fe73e1a5-4311-4a78-8ea4-5d53f428ddbb" />

Mecanum Robot Car with Claw Example [47]

The second proposed solution for the tire-changing mechanism is a “motorized scoop” design that uses a motor to scoop the blue tire. A separate servo or piston would be used to hold the red tire, which could drop off the red tire after it scoops the blue one. This design would allow the robot to sweep the whole pitstop area, so it would not require as precise of positioning from the camera subsystem. However, it would require bulkier components and a more complex mechanical design.

<img width="552" height="536" alt="image" src="https://github.com/user-attachments/assets/af40d1c9-693f-476a-a2bc-3912e096d00b" />

SECON Robot with Motorized Scoop Design [5]

During normal operation, the flag servo will remain in its stored position while the robot completes the first two laps and the pit-stop task. Once the master controller determines that the robot has entered the final lap, it will command the servo to rotate the flag into the raised position. The mechanism will include mechanical stops to prevent the servo from rotating beyond the intended range. The servo position and linkage geometry will be finalized during prototyping to ensure that the flag can be stored within the robot’s legal starting configuration and raised reliably during the race. Competition permits the robot to expand beyond its starting dimensions after the match begins, which provides additional flexibility for the deployed flag mechanism.

### Tire-Changing Concept Comparison

| Option | Approx. Cost | Pros | Cons |
|---|---:|---|---|
| **Servo-Controlled Claw** | **$8–$30** | Compact; relatively inexpensive; precise grip; integrates with the existing servo power and PWM system; servo-control code is simple because predefined open and closed positions can be commanded | Overall coding is more difficult because the camera and navigation system must accurately locate the blue tire and position the claw before pickup; small alignment errors may cause a failed pickup; gripping force must be sufficient |
| **Motorized Scoop + Tire Release** | **$20–$50+** | Larger pickup area; more tolerant of tire location; navigation and camera code can be simpler because the robot does not need to align as precisely with the tire; could sweep across part of the pit area to improve pickup reliability | Bulkier and heavier; requires additional motor/actuator hardware; higher power consumption; actuator code may require motor direction, timing, limit switches, or position feedback; more mechanically complex |

We selected the motorized scoop over the servo-controlled claw because it provides a larger and more forgiving pickup area for the blue tire. While the claw would require the robot and camera subsystem to position the gripper very accurately around the tire, the scoop can collect the tire even if the robot is slightly misaligned. This reduces the precision required from the vision and navigation systems and should improve the overall reliability of the pit-stop maneuver. Although the scoop requires a larger and somewhat more complex mechanical design, the team determined that the increased tolerance to positioning errors and greater likelihood of successfully collecting the tire outweighed these disadvantages. The tire-changing mechanism will be evaluated using the same ISO 12100 risk-assessment process. Potential hazards include unexpected scoop movement, pinch points between the scoop and chassis, interference with the drivetrain, and loss of the carried tire. The mechanical team and electrical team will jointly define the scoop's allowable travel before the actuator is selected. Mechanical limits will be used where practical to prevent the mechanism from entering an unsafe configuration. Activation of the robot's emergency-stop system will disable both the flag and tire-changing actuators, and resetting the emergency stop will not automatically resume an interrupted actuator movement.

Verification of these safety requirements will be performed during actuator subsystem testing. Each mechanism will be commanded through its full intended operating range while checking for binding, mechanical interference, excessive travel, and unintended motion. Emergency-stop functionality will also be tested while each actuator is moving. A successful test requires actuator motion to stop when the emergency stop is activated and requires the actuator to remain inactive after the emergency stop is reset until a new intentional command is issued. Any newly identified hazard will be documented and the design will be modified before system-level integration.

### Obstacle & Boundary Detection

The mechanical team proposes that the robot shall use mecanum wheels to drive around a 4 ft × 8 ft track that has a black floor and a white center line [2]. Along the straightaways, the center line divides the track into an inner lane and an outer lane. Three soft toy cars [38] are randomly placed in quadrants at the ends of the center rail, and each one can end up in either lane [2]. To get around an obstacle, the robot strafes sideways into the open lane, drives past it, and then moves back to the center line. A lap with no contact earns 15 points for avoiding the gray walls and another 25 points for avoiding the obstacles [2], so obstacle and wall avoidance is worth up to 120 points over three laps.

The sensors need to keep the robot on the center line and figure out which lane is blocked before the robot gets to a quadrant. They also need to keep the robot off the gray walls while it changes lanes. The center line is the main point of reference. Odometry error builds up the farther the robot travels [39], so the odometry is reset to the line sensor's reading every time the line is detected, and the side-facing ranging sensors provide a second lateral reference during the lane change. The sensors are split into three groups below: line sensing, odometry and localization, and obstacle/wall ranging. A final subsection describes how their readings are combined into one position estimate.

Each sensor decision was made in two steps. Options were first checked against pass/fail requirements, such as contactless sensing and Class 1 lasers only. The remaining options were then scored in a weighted matrix whose criteria come from the specifications of that group (LS-, OD-, and RG- numbers below). Scores use a 1 to 5 scale, and weights reflect the points at stake.

#### Line Sensing

The line sensor looks for the white center line [2] and reports how far left or right of it the robot is. As long as the line is visible, the controller knows the robot's lateral offset. This sensor is used for steering, for resetting odometry, and for confirming that the robot is back on the center line after a lane change.

###### Options Considered

Discrete reflectance sensors. A pair of infrared emitter/detector sensors can tell whether the robot is over the line or not, but not how far off it is. With only that information, the robot would have to zig-zag along the edge of the line.

Single reflectance sensor array. A row of emitter/detector pairs reads the floor at several points across the width of the robot. From those readings, the controller can tell where the line is under the robot instead of only detecting that it is there. For example, the Pololu QTR-MD-08RC fits eight sensors on a 61 mm board [40].

Front and rear reflectance arrays. A second array at the rear lets the controller measure the robot's angle relative to the line. The odometry already provides heading (see Odometry and Localization), so the rear array would duplicate that measurement.

Edge-mounted reflectance arrays. Additional arrays near each side of the chassis keep the line in view while the robot strafes around an obstacle, giving an absolute lateral reference during the lane change. The trade-offs are additional GPIO pins, mounting space near the wheels, and more sensor processing for the master controller.

Color sensor. A single-point color sensor can tell the white line apart from the black floor, but not how far the robot is from the center line.

Reusing the camera. The vision subsystem's camera points forward so it can read the AprilTag and see the start flag. Turning it toward the floor would prevent it from doing either job.

###### Line Sensing Decision Matrix

Discrete sensors and the color sensor fail LS-2 because they cannot report an offset, and the camera is already allocated to vision tasks. The remaining configurations were scored:

| Criterion (weight) | Tied spec | Front array only | Front + rear arrays | Front + edge arrays |
| --- | --- | :-: | :-: | :-: |
| Lateral reference during lane change (35%) | OD-2 | 2 | 2 | 5 |
| Offset resolution for steering (25%) | LS-2 | 5 | 5 | 5 |
| GPIO and integration load (20%) | Interfaces | 5 | 3 | 2 |
| Mounting space near wheels (10%) | LS-4 | 5 | 3 | 2 |
| Cost (10%) | Budget | 5 | 4 | 3 |
| **Weighted total** | | **3.95** | **3.25** | **3.90** |

###### Selection

The front array only and the front + edge configurations score within 2% of each other, so they are treated as a tie. The tie-breaker is integration risk: one QTR-MD-08RC array will be mounted at the front of the chassis, a few millimeters off the floor, where it tracks the robot's offset from the line with no image processing. Edge arrays, which were suggested in GTA feedback on the midterm design, will be added if testing shows lateral error exceeding OD-2 over a lane change. The rear array is rejected because heading is already measured by the odometry.

<img width="494" height="374" alt="image" src="https://github.com/user-attachments/assets/853c239a-feaf-425d-9573-6e335a918678" />

Pololu QTR-MD-08RC Reflectance Sensor Array

###### Interfaces

Line Sensor Interfaces

| Signal | Type | Direction | Protocol | Data |
| --- | --- | --- | --- | --- |
| Sensor outputs (×8) | Digital | Sensor to master controller | GPIO (RC discharge timing) | Reflectance at each sensor |
| Emitter control | Digital | Master controller to sensor | GPIO | Emitters on/off |
| Power | Power | Power subsystem to sensor | 3.3 V | Supply |

###### Specifications

The line sensor shall:

LS-1: Detect the center line at every point on the course where the line is present.

LS-2: Report the line's offset from the robot's centerline to the master controller.

LS-3: Be calibrated for the venue lighting before each match.

LS-4: Be mounted within its rated sensing height above the floor, with the mount designed together with the mechanical team.

#### Odometry and Localization

The odometry keeps track of where the robot is and which way it is facing between line references. Once the robot strafes off the line to get around an obstacle, the line is no longer under the front array, so the odometry guides the robot back to it.

###### Options Considered

Drive-wheel encoders. The drive motors already have encoders for speed control. They measure how the wheels turn and do not account for slip. Mecanum rollers slip whenever the robot strafes, so these encoders will only be used for speed control.

Two dead wheels with an IMU. Dead wheels are small unpowered wheels spring-loaded against the floor with an encoder on each axle. Because they are not driving the robot, they roll along with its actual motion. One wheel rolls forward and one rolls sideways, and an IMU provides heading. Heading depends entirely on the IMU's gyroscope, which drifts over time.

Three dead wheels. Two parallel wheels, offset to the left and right of the robot's center, roll forward, and a third rolls sideways. The difference between the two forward wheels gives heading directly, so no separate heading sensor is required. This layout was recommended by the mechanical team. It requires a third pod and encoder, and its heading accuracy depends on wheel calibration, since small differences in wheel diameter or spacing accumulate as heading error over distance [39]. An IMU can be added as a second heading source that does not depend on wheel contact.

Optical (mouse) sensors. An optical sensor takes images of the floor and works out how far the robot has moved, with no moving parts. However, it only works within a narrow height range, and accuracy depends on the floor surface.

Integrated optical odometry module. The SparkFun Optical Tracking Odometry Sensor (OTOS) puts an optical sensor and an IMU on a single 1 in × 1 in board and reports position and heading directly. SparkFun rates it at 3-5% error out of the box and under 1% after calibration [41].

SLAM (Simultaneous Localization and Mapping). SLAM builds a map of an unknown environment while tracking the robot's position within it [49]. The course layout is fixed and known in advance [2], so there is no map to build, and SLAM would require the single-board computer topology the team already rejected.

###### Odometry Decision Matrix

SLAM is rejected by the selected controller topology, and drive-wheel encoders fail OD-2 during strafing. The remaining options were scored:

| Criterion (weight) | Tied spec | Two dead wheels + IMU | Three dead wheels | Three dead wheels + IMU | OTOS |
| --- | --- | :-: | :-: | :-: | :-: |
| Slip immunity and position accuracy (30%) | OD-2 | 4 | 5 | 5 | 3 |
| Heading accuracy (20%) | OD-6 | 3 | 4 | 5 | 4 |
| Mechanical integration (20%) | OD-5 | 4 | 3 | 3 | 5 |
| Electrical and firmware integration (15%) | Interfaces | 4 | 4 | 3 | 5 |
| Cost (15%) | Budget | 4 | 4 | 4 | 3 |
| **Weighted total** | | **3.80** | **4.10** | **4.15** | **3.90** |

###### Selection

Three dead wheels will be used for odometry. Two unpowered omni wheels rolling forward will be mounted as far apart laterally as the chassis allows, and a third wheel rolling sideways will be mounted as close as possible to the robot's center of rotation, as recommended in GTA feedback. Each axle carries an AS5600 magnetic encoder, and heading is computed from the two forward wheels. Three dead wheels with and without the IMU score within 2% of each other, so they are treated as a tie, broken by integration simplicity: the robot will run on wheel heading alone, with one less device on the I2C bus. The BNO085 IMU, already procured, will be added as a second heading source if testing shows heading error exceeding OD-6. The pods will be designed together with the mechanical team. The SparkFun OTOS is the fallback if the pods do not fit within the starting volume or do not meet OD-2 in testing.

The odometry model for each update is:

- Forward travel: Δx = (ΔR + ΔL) / 2
- Heading change: Δθ = (ΔR − ΔL) / W
- Sideways travel: Δy = ΔS − d_S · Δθ

where ΔR and ΔL are the distances rolled by the right and left forward wheels, W is the spacing between them, ΔS is the distance rolled by the lateral wheel, and d_S is the lateral wheel's distance from the center of rotation. The d_S · Δθ term removes the rolling caused by rotation rather than translation, and it shrinks as the lateral wheel is mounted closer to the center of rotation. A wider spacing W reduces heading error for the same encoder resolution. The displacement is then rotated from the robot's frame into the track's frame using the current heading and added to the position estimate.

The AS5600 reports an absolute angle (4096 counts per revolution), so the change between samples is computed as ((new − old + 2048) mod 4096) − 2048. This is valid only if each wheel turns less than half a revolution between samples, which sets the minimum sample rate in OD-3. For example, a 35 mm dead wheel at 1 m/s requires at least 18 samples per second.

<img width="258" height="316" alt="image" src="https://github.com/user-attachments/assets/f47f49cd-02e4-4276-8e73-83b02437f3b0" />
<img width="546" height="320" alt="image" src="https://github.com/user-attachments/assets/3083161f-b376-49ce-97bc-3cc31c528897" />

AS5600 Magnetic Encoder and BNO085 IMU (optional)

###### Interfaces

The three AS5600 encoders share a fixed I2C address, so they are connected through an I2C multiplexer. The odometry sensors use a separate I2C bus from the ranging sensors so that ranging traffic does not delay odometry updates.

Odometry Sensor Interfaces

| Signal | Type | Direction | Protocol | Data |
| --- | --- | --- | --- | --- |
| Wheel encoders (AS5600 ×3) | Serial | Bidirectional | I2C bus 2, through a multiplexer | Wheel angle out |
| Heading (BNO085 IMU, optional) | Serial | Bidirectional | I2C bus 2 | Heading out |
| Power | Power | Power subsystem to sensors | 3.3 V | Supply |

###### Specifications

The odometry system shall:

OD-1: Measure forward travel, sideways travel, and heading.

OD-2: Estimate lateral position within ±1 cm over the length of a lane change, so that position uncertainty stays small relative to the clearance between the robot and an obstacle. Heading error is the largest contributor: a 1° heading error over a 30 cm lane change produces about 5 mm of lateral error.

OD-3: Sample each encoder at a rate f_s ≥ 2·v_max / (π·d_w), where v_max is the robot's maximum speed and d_w is the dead-wheel diameter.

OD-4: Be reset to the line sensor's reading whenever the line is detected.

OD-5: Keep all three dead wheels in contact with the floor during forward driving and strafing.

OD-6: Keep heading error within 1° between line references.

#### Obstacle and Wall Ranging

The ranging sensors look ahead at each obstacle quadrant and report which lane is blocked, if either. They also measure how far the robot is from the gray walls on each side. During a lane change, that side distance tells the master controller how far the robot has strafed and keeps it from hitting a wall. While the robot passes an obstacle, the side sensor facing the center line also sees the obstacle beside the robot, and its reading returning to open space confirms that the obstacle has been cleared.

###### Options Considered

Limit switches. A limit switch only triggers on contact. Touching obstacles or walls loses points and defeats the purpose of avoidance.

Ultrasonic sensors. An ultrasonic sensor such as the HC-SR04 sends out a sound pulse and times the echo, using a 15° beam [42]. Since the obstacles are soft toy cars [38], they likely return a weaker echo than a hard surface would. The beam is also too wide to reliably tell which lane is blocked.

Single-point laser time-of-flight (ToF) sensors. A ToF sensor times how long a pulse of infrared laser light takes to bounce back. The ST VL53L0X can measure up to 2 m with a narrow beam and uses an eye-safe Class 1 laser [43]. The narrow beam makes it a good fit for measuring the distance to a side wall. The ST VL6180X is a similar sensor with a much shorter rated range.

Multizone ToF sensors. The ST VL53L7CX breaks its view into an 8 × 8 grid and measures the distance in each zone, covering a 90° diagonal field of view out to 3.5 m [44]. The controller can see which part of the track ahead is blocked, and from that, which lane.

360° scanning LiDAR. A LiDAR like the SLAMTEC RPLIDAR C1 spins a laser sensor to measure distance all the way around the robot [45]. In theory, one sensor could handle both the walls and the obstacles. In practice, it only scans in a flat plane, which likely passes over the low obstacles. It would also need a clear view in every direction and produces far more data than the other options.

Reusing the camera. The camera could pick out obstacles by color, but it is already busy with the AprilTag and the start flag, and it cannot measure distance directly.

###### Ranging Decision Matrices

Limit switches fail the contactless requirement, the RPLIDAR fails RG-4 because its scan plane passes over the obstacles, and the camera is already allocated to vision tasks. The remaining options were scored separately for forward and side ranging, because the two answer different specifications. The forward weights reflect the 75 obstacle points at stake over three laps, which can be lost either by misidentifying the blocked lane or by missing a soft target.

Forward obstacle ranging:

| Criterion (weight) | Tied spec | VL53L7CX multizone | 2× VL53L0X, one per lane | HC-SR04 ultrasonic |
| --- | --- | :-: | :-: | :-: |
| Lane discrimination (30%) | RG-2 | 5 | 3 | 1 |
| Soft-target detection (25%) | RG-1 | 4 | 4 | 2 |
| Range margin over d_req (15%) | RG-1 | 4 | 3 | 4 |
| Integration effort (15%) | Interfaces | 3 | 4 | 4 |
| Cost (10%) | Budget | 3 | 5 | 5 |
| Size and mounting (5%) | RG-4 | 4 | 4 | 3 |
| **Weighted total** | | **4.05** | **3.65** | **2.65** |

The result depends on the weight given to lane discrimination. Reducing it to 15% and raising cost to 25% would favor the VL53L0X pair (3.95 to 3.75), so the pair is kept as the fallback.

Side wall ranging:

| Criterion (weight) | Tied spec | VL53L0X | VL6180X | HC-SR04 ultrasonic |
| --- | --- | :-: | :-: | :-: |
| Range covers wall distance during lane change (35%) | RG-3 | 5 | 2 | 5 |
| Beam width and precision (25%) | RG-3 | 4 | 4 | 2 |
| Integration effort (20%) | Interfaces | 4 | 4 | 3 |
| Cost (20%) | Budget | 4 | 4 | 5 |
| **Weighted total** | | **4.35** | **3.30** | **3.85** |

###### Selection

One VL53L7CX multizone ToF sensor will face forward to watch for obstacles, and two VL53L0X single-point ToF sensors will face sideways to watch the walls. This matches the object detection laser sensor shown in the block diagram. If the VL53L7CX cannot reliably identify the blocked lane at d_req in bench testing with the toy-car obstacles, two VL53L0X sensors angled toward each lane will replace it.

<img width="467" height="351" alt="image" src="https://github.com/user-attachments/assets/ce49134b-de81-47e4-aca6-8d27e1de6e1a" />
<img width="299" height="350" alt="image" src="https://github.com/user-attachments/assets/15341ce3-548c-4de4-b376-55d170ee576d" />

VL53L7CX (left) and VL53L0X (right) ToF Sensors

###### Interfaces

All three ranging sensors share a default I2C address, so each one's enable pin is used to assign a unique address at startup.

Ranging Sensor Interfaces

| Signal | Type | Direction | Protocol | Data |
| --- | --- | --- | --- | --- |
| Forward ranging (VL53L7CX) | Serial | Bidirectional | I2C bus 1 | Configuration in, zone distances out |
| Wall ranging (VL53L0X ×2) | Serial | Bidirectional | I2C bus 1 | Configuration in, wall distance out |
| Sensor enable (×3) | Digital | Master controller to sensors | GPIO | Sets each sensor's address at startup |
| Power | Power | Power subsystem to sensors | 3.3 V | Supply |

###### Specifications

The ranging sensors shall:

RG-1: Detect a toy-car obstacle in either lane at a distance of at least d_req = v_max · (t_lc + t_s) + d_m, where t_lc is the lane-change time, t_s is one sensor update period, and d_m is a safety margin.

RG-2: Report whether the inner lane, the outer lane, or neither is blocked.

RG-3: Measure the distance to each side wall during a lane change.

RG-4: Be mounted at a height where they can see the obstacles, the side rails, and the lower center rail.

RG-5: Use only Class 1 infrared lasers, consistent with the ban on visible-light lasers [1].

#### Position Estimation

Several sensors measure the same quantities in different ways, and their readings must be combined into one estimate of the robot's position.

| Quantity | Relative source (drifts) | Absolute sources (intermittent) |
| --- | --- | --- |
| Lateral position | Lateral dead wheel | Line array (when the line is under it); side ToF wall distance (during lane changes) |
| Forward position | Forward dead wheels | AprilTag (at the pit stop) |
| Heading | Forward dead-wheel difference; BNO085 (if added) | Line angle (when the line is visible) |

###### Options Considered

Dead reckoning with resets. The estimate is overwritten whenever an absolute reference is available. This is simple, but the estimate jumps at each reset and the side wall distance goes unused.

Complementary filter. Each update blends the odometry prediction with the absolute reference: x̂ = α·(x̂ + Δodometry) + (1 − α)·z_reference. Odometry provides smooth short-term motion, the reference removes long-term drift, and the filter has one tuning constant.

Kalman filter (EKF). Each source is weighted by its measured noise, and the filter handles a reference dropping out naturally. It gives the best accuracy but requires characterizing each sensor's noise and tuning several parameters.

###### Position Estimation Decision Matrix

| Criterion (weight) | Tied spec | Resets only | Complementary filter | EKF |
| --- | --- | :-: | :-: | :-: |
| Accuracy vs. OD-2 (35%) | OD-2 | 3 | 4 | 5 |
| Implementation risk (30%) | Team experience | 5 | 4 | 2 |
| Robustness to reference dropout (20%) | OD-2 | 2 | 4 | 5 |
| Tuning effort (15%) | Schedule | 5 | 4 | 2 |
| **Weighted total** | | **3.70** | **4.00** | **3.65** |

###### Selection

A complementary filter will combine the odometry with the line and side-wall references. If the BNO085 is added, the same filter will blend its heading with the wheel heading. Dead reckoning with resets will be used first during bring-up. If testing shows lateral error exceeding OD-2 during lane changes, the filter will be upgraded to an EKF, with guidance from faculty experienced in sensor fusion, as suggested in GTA feedback.

#### Sensor Comparison

The table below sums up the options considered for each sensor group.

Sensor Option Comparison

| Group | Option | Limitation | Decision |
| --- | --- | --- | --- |
| Line | Front reflectance array | Must sit close to the floor | Selected |
| Line | Edge-mounted reflectance arrays | More GPIO; mounting near wheels | Alternative |
| Line | Front and rear arrays | Duplicates odometry heading | Rejected |
| Line | Discrete reflectance sensors | No offset measurement | Rejected |
| Line | Color sensor | No offset measurement | Rejected |
| Line | Forward camera | Needed for AprilTags and flag | Rejected |
| Odometry | Three dead wheels | Third pod and encoder; multiplexer required; heading depends on wheel calibration | Selected |
| Odometry | Three dead wheels with IMU | Extra I2C device | Optional addition (OD-6) |
| Odometry | Optical module with IMU (OTOS) | Untested on plywood, height-sensitive | Alternative |
| Odometry | Two dead wheels with IMU | Heading depends on gyro alone | Rejected |
| Odometry | Optical mouse sensors | Narrow height band | Rejected |
| Odometry | Drive-wheel encoders | Mecanum wheels slip when strafing | Speed control only |
| Odometry | SLAM | Course layout already known; requires rejected single-board computer topology | Rejected |
| Forward ranging | Multizone ToF (VL53L7CX) | Wide field of view may include walls | Selected |
| Forward ranging | 2× single-point ToF (VL53L0X) | One point per lane | Alternative |
| Side ranging | Single-point ToF (VL53L0X) | One direction per sensor | Selected |
| Side ranging | Short-range ToF (VL6180X) | Range too short for wall distance | Rejected |
| Ranging | Ultrasonic (HC-SR04) | Soft targets, wide beam | Rejected |
| Ranging | 360° LiDAR (RPLIDAR C1) | Scan plane passes over obstacles | Rejected |
| Ranging | Limit switch | Triggers only on contact | Rejected |
| Estimation | Complementary filter | One tuning constant | Selected |
| Estimation | EKF | Noise characterization and tuning | Alternative |

#### Sensing Flowchart

<img width="958" height="685" alt="image" src="https://github.com/user-attachments/assets/b315661e-b0f3-4d35-92f9-3a0a851dbe9b" />

### Power & Battery Management

###### Purpose and Functions Overview:

The Power Subsystem stores, converts, distributes, protects, and monitors the electrical energy the autonomous robot requires. The objective is to provide supply voltages that are stable, deliver adequate system current, and remain compatible with computing, sensing, motor drive, and hardware. It also maintains predictable operation during load changes.

The selected design uses an OVONIC 3S, 11.1 V nominal, 6500 mAh lithium-polymer battery, and a Voltraize converter. These are the components that represent the team’s current selections. The exact operating limit will be finalized before system completion.

The Subsystem Functions:

* Accept battery power through the selected battery connector.

* Distribute raw battery voltage to the motor driver (such as the Cytron MDD10A).

* Produce a shared regulated 5V voltage supply rail to power control hardware, vision processors, and the servo distribution branch.

* Use available regulated outputs for compatible low-voltage peripherals. This is subject to current limits.

* Provide a defined startup and fault-response sequence.

* Include the required battery disconnect, inline fusing, and circuit protection.  This includes overcurrent safeguards.

###### Operating Modes

* Off - The battery is physically or electrically disconnected and is no longer externally supplying the power rails that are energized.

* Startup/Arming - Connecting the battery energizes the main converter and motor-driver supply lines. The controllers initiate and hold the actuator commands inactive until the startup and voltage checks are complete.

* Run - The controllers permit the motor and servo operation. It also collects available sensor and diagnostic information.

* Fault – This can be a battery low-voltage sag, overcurrent draw, or thermal limit threshold. The controller prevents the actuator commands when it detects a defined fault. The fault detection and reset behavior depends on the monitoring functions that are implemented.

* Emergency Stop - This is a selected hardware disconnect that interrupts battery power independently of normal control software. It stores downstream energy and alternative power sources.

###### Power Architecture and Voltage Rails

All control and power branches will share a common ground reference. To minimize noise and coupling, high-current motor and servo wiring will be routed separately from the low-current signal connections.  Additionally, decoupling and bypass capacitors will be placed across high-draw supply lines near driver inputs. This will suppress voltage noise and deliver immediate local current during sudden load spikes [46]. If a four-motor drivetrain is used, two motors may be connected to each channel, where the drivetrain arrangement is permitted. The final motor allocation will identify which positions will be used by which motors.

* Raw Battery Bus (VBAT): Supplies the primary motor drivers directly within a 9.0 - 12.6V operating range.

* Regulated 5V Bus: Produced by the Volrantise 12V/24V to 5V 15A converter. This delivers up to 75W of usable capacity. The shared bus feeds onboard microcontrollers, vision modules, and downstream auxiliary distribution paths. 

* Auxiliary Logic Regulation: Local linear regulators (LDOs) or secondary step-down components step down the 5V bus to supply the localized 3.3V logic and sensor demands where required. 

###### Alternatives Considered

* OVONIC 3S LiPo Battery + Volrantise Converter

  * Pros:

    * There is a high discharge rate (120C, 6500 mAh) which easily handles peak transient currents from the motor drivers and servos. This is also without severe voltage sags [29, 32]. 

    * Having high efficieny switching buck conversion minimizes the thermal waste and it maintains stable regulated power rails [25, 26].

    * Having a compact footprint with standard XT60 connectors allows for secure, and easily swappable physical integration.
    
  * Cons:
    
    * This option requires active battery voltage monitoring to prevent over-discharge [29].

    * LiPo chemistry demands strich adherence to safe charging and storage practices [1].
    
* Dual 18650 Li-Ion Packs + Linear Regulators

  * Pros:

    * This option has flexible physical packaging to fit irregular spaces within teh chassis envelope.

    * It has individual cells which are readily available off the shelf.

  * Cons:

    * There are linear voltage regulators that burn excess voltage as heat under heavy motor loads. This causes poor thermal efficiency [26].

    * There has to be custom spot-welding and cell-holder fabrication which introduces risks of loose connections under vibration.

    * The standard cells exhibit higher internal resistance and they sag heavily under high motor stall currents. 

* 12V Lead-Acid Battery + Standard Buck Converters

  * Pros:

    * This option has a high stable chemistry and inherently forgiving charging characteristics.

    * It has a low upfront cost for raw storage capacity.

  * Cons:

    * This options is extremely heavy and bulky, which penalizes the agility, payload capacity, and speed [1]. 

    * It has lower discharge current capabilities. This can trigger system brwonouts during simultaneous multi-motor activation. 

* Direct Battery Powering of All Logic (No Regulation): This will result in a wide voltage sag under motor load. This will also cause the microcontroller to reset and have unpredictable logic states.

* Separate Isolated Battery Packs for Logic and Motors: This prevent motor noise from affecting logic. It also carries multiple independent batter packs which adds unnecessary weight. It will also increase charging complexity, and complicates the emergency-stop wiring. 

Compatible sensor modules may be powered from the selected boards’ embedded regulated outputs. This allows the total connected sensor, and interface loads to be calculated before using it as the shared sensor supply. [34]

###### Power Subsystem Trade Study
| Evaluation Criteria | Weight | Option 1: OVONIC 3S LiPo + Volrantise Converter *(Selected)* | Option 2: Dual 18650 Li-Ion Packs + Linear Regulators | Option 3: 12V Lead-Acid Battery + Standard Buck Converters |
| :--- | :---: | :---: | :---: | :---: |
| **Current Delivery & Peak Headroom** | 30% | **5** (6500 mAh, 120C high discharge easily handles 15A+ peaks) | **2** (Standard 18650 packs sag heavily under high motor stall currents) | **3** (Good capacity, but excessively heavy and bulky) |
| **Efficiency & Thermal Control** | 25% | **4** (High-efficiency switching buck conversion minimizes heat) | **3** (Linear regulators burn excess voltage as heat under load) | **4** (Decent conversion, but heavy overall system weight penalty) |
| **Integration & Form Factor** | 20% | **5** (Compact, standard XT60 integration with robot frame) | **4** (Custom cell configuration required, risk of loose spot-welds) | **1** (Too heavy and large for an agile autonomous stock car) |
| **Cost & Availability** | 25% | **4** (Off-the-shelf readily available hobby RC components) | **3** (Requires building custom cell holders and safety circuits) | **4** (Inexpensive battery, but requires specialized heavy chargers) |
| **Weighted Total Score** | **100%** | **4.50 / 5.0** | **2.90 / 5.0** | **3.10 / 5.0** |

###### Hardware Interfaces and Control Signals

The subsystem will use the following interfaces:

* BAT_IN - This is the battery’s actual connector and the verified compatible mating cable.

* PWM1/DIR1 and PWM2/DIR2 - Teensy control signals for the two MDD10A channels.

* I2C_CTRL - This is for communication with the PCA9685 and is compatible with sensor modules.

* Power measurement points - These are accessible locations for checking the battery, 5V, and selected 3.3V supplies.

* Hardware disconnect - This is the emergency power-interruption device.

###### Protection, Fault Response, and Safety Verification

The protection architecture is driven by the requirements identified in ISO 13850:2015 and IEC 62133-2:2017 + AMD1:2021. The emergency-stop behavior implements the requirements of ISO 13850 Sec. 4.1.1.2 by overriding normal actuator commands and preventing automatic restart following reset. Battery protection follows the principles of IEC 62133-2 Secs. 5.4-5.6 by maintaining the selected battery within its documented voltage and current operating region and by using wiring, connectors, and protection devices appropriate for the anticipated electrical load. The main fuse will be selected after the operating and startup currents are established. Fuse sizing will consider the protected wire and connector ratings, current, motor and servo transients, temperature, and fuse time-current characteristics. Littelfuse guidance supports this application-specific method rather than having a fixed current multiplier. [35, 36]

The DuPont ribbon cables are reserved for suitable low-current signal connections, whereas battery, motor, and servo power wiring requires separate verified current-carrying capability.

The final design requires an accessible hardware disconnect, maintaining the target of no more than 50 ms from activation. This is to ensure that interruption of the designated power path remains as the project requirement.

Verification Addresses:

* Physical stopping behavior

* Residual voltage from capacitors

* USB connections that could keep controller boards powered

* Backup batteries attached to the OpenMV

* Prevention of unintended restart

The OpenMV board documents automatic power selection. This is among the supported sources and fallbacks to an attached battery. These alternative sources must be considered when defining what the E-stop disconnects [37]. Once battery monitoring is implemented, the controller hinders the motor and servo commands during a defined low-voltage fault. It will also record diagnostic information if sufficient power remains. Verification results will be recorded quantitatively. Emergency-stop testing will document the measured actuator shutdown time for each trial and whether any automatic restart occurs after reset. Power testing will record the battery voltage and current during representative simultaneous drivetrain and actuator operation. These measured results will be compared with the applicable system requirements and manufacturer limits and recorded as PASS or FAIL.

###### Inventory

* Energy Storage: OVONIC 3S 11.1V 6500 mAh 120C LiPo battery

* Conversion: Volrantise 12V/24V to 5V 15A DC-DC converter

* Protection & Distribution: This is primary fuse assembly, heavy-duty hardware disconection switch, high-current cabling, and terminal blocks. Specific motor drivers, servos, and data bus components are integrated with their respective functional subsystems.  

###### Propose Verification Requirements

Subsystem Shall:

* Accept the selected battery over a verified voltage range compatible with the power converter.

* Maintain acceptable supply voltage during the representative simultaneous motor and servo operation

* Keep microcontroller, vision, and logic signal inputs strictly within the permitted thresholds. 

* Keep external sensor loads within the supply board’s regulator’s capacity

* Provide an accessible hardware emergency disconnect

* Prevent automatic actuator restart following the emergency-stop reset

* Document and test the implemented fault-detection functions

<img width="712" height="862" alt="power_subsystem drawio" src="https://github.com/user-attachments/assets/de43eaf8-efa9-413e-bcb0-6192042fa4ed" />

## Ethical, Professional, and Standards Considerations

The conceptual design connects autonomous navigation, energy efficiency, and responsible engineering.

### Standards-Driven Risk Assessment

The team will use the risk-assessment methodology of ISO 12100:2010 throughout detailed design and system testing. Risk assessment will not be treated as a one-time safety review. Each major subsystem will be evaluated by identifying hazards in accordance with Sec. 5.4, estimating the associated risk in accordance with Sec. 5.5, and evaluating whether further risk reduction is required in accordance with Sec. 5.6.

Risk reduction will follow the three-step methodology of Sec. 6. Where practical, hazards will first be eliminated or reduced through inherently safer design. If sufficient reduction cannot be achieved through design alone, safeguards and protective measures will be applied. Information, warnings, or operating procedures will be used for residual risks that cannot reasonably be eliminated by the first two methods.

For this robot, this process directly affects design decisions. Mechanical travel limits are used to reduce actuator interference and pinch hazards before software limits are considered. The hardware emergency stop provides an independent protective measure for unexpected drivetrain or actuator motion. Electrical risks are reduced through appropriately rated wiring, insulation, strain relief, overcurrent protection, and battery monitoring. The team will document newly identified hazards during testing and reevaluate the associated risk after mitigation to determine whether additional design changes are required.

### Ethics and Sustainability

The design emphasizes efficient power management to complete tasks without recharging while remaining within the 30-volt power limit. Using available and reusable components helps control development costs, maintenance, and supports future projects. These choices are carried out through the reuse, battery-life, and disposal measures in Table 2 (M3-M7).

What guides the robot's development and team practices is safety, reliability, and integrity. To be able to reduce risks, safety materials, an accessible emergency stop, testing, and inspection are required. To have accountability and effective collaboration throughout the project, fair competition, proper acknowledgement of sources, and honest documentation are commitments the team makes.

### Stakeholder Impact: Benefits, Disadvantages, and Mitigation

The robot's path planning and AprilTag-based localization illustrate techniques used in autonomous vehicles and search-and-rescue systems, but the project itself is a single competition robot. The effects of this project are small and mostly local. To identify who is affected, the team considered every aspect of the robot's lifecycle from construction through to testing, competition, and disposal. Tables 1a and 1b summarize the groups who benefit and who are disadvantaged across economic, environmental, and societal contexts.

**Table 1a: Who benefits from this project**

| Context | Beneficiary | How they benefit |
| --- | --- | --- |
| Economic | TTU students on the team | Students build hands-on integration experience and portfolio work that applies directly to ECE and ME careers. |
| Economic | ECE and ME departments | The project produces evidence for both departments' ABET student outcomes. A competitive entry also showcases both departments to prospective students. |
| Economic | Future capstone teams | Reused parts and a published BOM reduce the cost of future builds. |
| Environmental | Future capstone teams | Reusing this project's parts lets future teams build without purchasing new hardware, avoiding the extraction and disposal impacts described in D3 and D4. |
| Societal | Future SECON teams | Published documentation, schematics, and code give teams at any school, including lower-resource ones (D1), a documented starting point. |
| Societal | Competition audience | A working autonomous robot demonstrates engineering to conference attendees and banquet guests, which can encourage interest in ECE. |
| Societal | Team members who own core subsystems | Owning a subsystem from research through testing builds in-depth, demonstrable experience in that area. |
| Societal | Employers in autonomous systems | Team members gain practice with localization, sensing, and real-time control used in the autonomous-systems industry. |

**Table 1b: Who is disadvantaged by this project**

| ID | Context | Disadvantaged | How they are disadvantaged |
| --- | --- | --- | --- |
| D1 | Economic | Teams from lower-resource schools | Spending ~$900 on a build raises the bar for schools that can't match that budget. Better-funded teams can afford better sensors and compute, and that can turn into competition results. |
| D2 | Economic | Other capstone teams that draw on the same departmental funds | Funding spent here isn't available to other teams. |
| D3 | Environmental | Sanitation workers and communities near landfills | LiPo batteries and failed PCBs become waste when thrown out. LiPo batteries can start fires in garbage trucks and landfills. Both contribute to e-waste and require specialized disposal. |
| D4 | Environmental | Communities near battery and electronics manufacturing and sourcing | The LiPo pack uses lithium and cobalt, and the motors use rare earths. Lithium extraction uses local water supplies in dry regions, and cobalt mining is associated with poor labor conditions. This project's share of that demand is small. |
| D5 | Societal | People in camera view | Attendees will be within view of the robot's camera with no choice to opt out. This only becomes an issue if camera data is stored or transmitted. |
| D6 | Societal | Team members with less embedded experience | Work on subsystems is divided based on members' existing experience, limiting the number of learning opportunities. |
| D7 | Societal | Workers in jobs autonomy displaces | Autonomous navigation contributes to automation that reduces demand for drivers and delivery workers. This project's contribution is indirect and small. |

Of these groups, teams from lower-resource schools (D1) carry the most significant cost, because it is structural and falls entirely outside the project. The environmental effects (D3, D4) can't be ignored but are considered small at this scale. D3 and D4 also share a cause with D2: buying and throwing away hardware. For that reason, reusing parts addresses all three. The camera concern (D5) depends on a design choice and is removed by M8. Two disadvantages are the counterpart of a benefit in Table 1a: the experience gained by subsystem owners comes partly at the expense of other members (D6), and the skills valued by autonomous-systems employers come from the same automation that reduces demand for other workers (D7).

**Table 2: Mitigation for each disadvantaged group**

| ID | Addresses | Mitigation | Type | Owner | Timing | Evidence |
| --- | --- | --- | --- | --- | --- | --- |
| M1 | D1 | Publish the BOM, schematics, PCB files, and code in a public repository after the competition. | Built-in | Team | After competition | Public repository link |
| M2 | D1 | Recommend that the competition consider a robot cost cap or cost reporting requirement. | Recommended to sponsor (IEEE SoutheastCon) | Team | Post-competition feedback | Submitted feedback |
| M3 | D2, D3, D4 | Set a budget ceiling, reuse parts from the previous TTU SECON robot and department inventory, and include cost as a criterion in every decision matrix. | Built-in | BOM lead | Before procurement | BOM column marking reused parts |
| M4 | D2, D3, D4 | Return working parts to department inventory for future teams. | Built-in | Team | After competition | Inventory handoff list |
| M5 | D3 | Follow a LiPo charging and storage protocol (storage voltage, fire-safe bag, no unattended charging) to extend pack life, and dispose of packs through TTU Environmental Health & Safety or a battery recycling drop-off. | Built-in | Power subsystem lead | Before first powered test | Written protocol; disposal record |
| M6 | D3, D4 | Validate circuits on development boards before ordering the PCB to limit board revisions. | Built-in | PCB lead | Before PCB order | Test log dated before fabrication |
| M7 | D4 | Size the battery from the power budget and purchase one pack rather than oversizing or buying spares. | Built-in | Power subsystem lead | Procurement | Power budget table |
| M8 | D5 | Process camera frames in memory only; no images are stored or transmitted. | Built-in | Vision subsystem lead | Firmware design | Firmware review |
| M9 | D6 | Pair each subsystem owner with a second team member and rotate integration and testing roles. | Built-in | Team | Throughout Capstone II | Task assignments in timeline |
| M10 | D7 | Limit autonomy-related claims in the documentation to what the project actually demonstrates. | Built-in | Team | This revision | Revised Broader Implications section |

Each built-in mitigation produces evidence that can be checked: the public repository, the written LiPo protocol and disposal record, the pre-fabrication test log, and the revised documentation. M2 is the only action outside the team's control; it will be submitted to IEEE SoutheastCon as a recommendation. Owner roles correspond to the subsystem assignments in the Division of Labor.

## Resources

### Budget

# Expected Bill of Materials

| Item | Expected Cost Per Item | Expected Quantity | Expected Cost | Link |
| --- | ---: | ---: | ---: | --- |
| 3S Lithium-ion Battery | $68.99 | 1 | $68.99 | [Link](<https://www.amazon.com/dp/B0CP5KYZXY/?coliid=I2F0U5KF6A0YXJ&colid=23D9XR7A5OVNN&psc=1&ref_=list_c_wl_lv_ov_lig_dp_it>) |
| DC 12V/24V to 5V 15A Step Down Converter | $10.99 | 2 | $21.98 | [Link](<https://www.amazon.com/dp/B09X1ZGR38/?coliid=I2N4TJQCC03CC4&colid=23D9XR7A5OVNN&psc=1&ref_=list_c_wl_lv_ov_lig_dp_it>) |
| **Master Controller** | | | | |
| Microcontroller Development Board | $40.81 | 1 | $40.81 | [Link](<https://www.digikey.com/en/products/detail/stmicroelectronics/NUCLEO-H753ZI/21348937?msclkid=8055c840130b15cd06a6a2ae2597b0e8&gclid=8055c840130b15cd06a6a2ae2597b0e8&gclsrc=3p.ds&gad_source=7&gad_campaignid=21987963296>) |
| PCB (w/ connectors & standoffs) | $80.00 | 1 | $80.00 |  |
| **Camera / Vision Processing** | | | | |
| OpenMV N6 camera | $225.00 | 1 | $225.00 | [Link](<https://www.amazon.com/dp/B0H8SSNBYK/?coliid=I864XICTG6T1R&colid=23D9XR7A5OVNN&psc=1&ref_=list_c_wl_lv_ov_lig_dp_it>) |
| **Navigation Inputs** | | | | |
| VL6180X TOF Distance Sensor Module | $9.99 | 2 | $19.98 | [Link](<https://www.amazon.com/dp/B0FKS84DJP/?coliid=I8K0V9OXX6862&colid=23D9XR7A5OVNN&psc=1&ref_=list_c_wl_lv_ov_lig_dp_it>) |
| DFROBOT 8x8 Matrix Sensor | $22.00 | 1 | $22.00 | [Link](<https://www.amazon.com/dp/B0FS77NZRC/?coliid=IR5ZYA6FCPMWP&colid=23D9XR7A5OVNN&psc=1&ref_=list_c_wl_lv_ov_lig_dp_it>) |
| AS5600 Magnetic Encoder | $9.99 | 1 | $9.99 | [Link](<https://www.amazon.com/dp/B0CM3C8KFT/?coliid=I194GEWTN6TZPK&colid=23D9XR7A5OVNN&psc=1&ref_=list_c_wl_lv_ov_lig_dp_it>) |
| BNO080 Nine Axis Sensor Module | $20.49 | 1 | $20.49 | [Link](<https://www.amazon.com/dp/B0CDGZMLPP/?coliid=IHFNUV2UVEAI7&colid=23D9XR7A5OVNN&psc=1&ref_=list_c_wl_lv_ov_lig_dp_it>) |
| **Flag & Tire Actuators** | | | | |
| Servo Motors | $18.99 | 4 | $75.96 | [Link](<https://www.amazon.com/dp/B07MFK266B/?coliid=I34JEY8U5JI2Z0&colid=23D9XR7A5OVNN&ref_=list_c_wl_lv_ov_lig_dp_it&th=1>) |
| DC 12V 550RPM Gear Motor High Torque | $14.99 | 1 | $14.99 | [Link](<https://www.amazon.com/dp/B072R5G5GR/?coliid=I2QVWDF9CQL7A6&colid=23D9XR7A5OVNN&ref_=list_c_wl_lv_ov_lig_dp_it&th=1>) |
| **Motor Control** | | | | |
| JGB37 520 DC12V Gear Motor With Encoder | $13.79 | 4 | $55.16 | [Link](<https://www.amazon.com/dp/B0H4FVPXDN/?coliid=I1HR7M7Y5KY96I&colid=23D9XR7A5OVNN&psc=1&ref_=list_c_wl_lv_ov_lig_dp_it>) |
| Cytron Dual Channel 10A DC Motor Driver | $23.48 | 3 | $70.44 | [Link](<https://www.amazon.com/dp/B07CW34YRB/?coliid=IWW4P5ZHRKDYM&colid=23D9XR7A5OVNN&psc=1&ref_=list_c_wl_lv_ov_lig_dp_it>) |
| **Miscellaneous** | | | | |
| Wiring & integration | $40.00 | 1 | $40.00 |  |
| Jumper Cables | $6.98 | 1 | $6.98 | [Link](<https://www.amazon.com/dp/B01EV70C78/?coliid=IYTOCWHZCEFWV&colid=23D9XR7A5OVNN&ref_=list_c_wl_lv_ov_lig_dp_it&th=1>) |
| Start Switch | $6.39 | 1 | $6.39 | [Link](<https://www.amazon.com/DaierTek-Listed-Switches-Automotive-KCD1-5Pack/dp/B07S1MV462?crid=2LSV83X8HO8IP&dib=eyJ2IjoiMSJ9.p-nxYeYUIVoEfWAP69LmQLx2KPtjR7Tjo7XlyYHnyLzo2UjyTSmfLl7Mpjwugrn274QUvaEpLEB17lsXtgFEpi0QQFOTsLEzlGrslE2f4Z9VzHjWdE24MfmRd5d6XGhbxu6Xplc6__nAFZRMSvCLGYo18hlKWzN1fBMkbCzQwJzgrvoM4v3oaTPYb9OvphfrmU76fD4e2oX67voqBVAlWDh1AgjiltiLRAym8tFSHmc.-umLKUYDH2OfiW7Xk5TNxUjEsNGrUuTblmdlm8cR-us&dib_tag=se&keywords=Switch&qid=1792005517&sprefix=switch%2Caps%2C194&sr=8-2&th=1>) |
| Emergency Stop | $11.99 | 1 | $11.99 | [Link](<https://www.amazon.com/mxuteuk-Mushroom-Emergency-Warranty-HB2-ES544/dp/B07R8PTTDX?crid=1TMFLUN683TG6&dib=eyJ2IjoiMSJ9.zJlYMxZHmYZJIkkElhAlIaFfh8fcJl-HQax35HoINBM8mxsyRX6Yzh6chrHzXHJgk0OGe1EHHLiPEezTVBiATJ5CgVOxW7LG1AIN_sjywBvA180X7eQOr3hGCOZVaXYxBS2uixKVjXHcjPayM63y5xfjbXCsAkTKD4pMrXQPBFUfjcrzD8SJzR9c2Stg7WJsPKJgRU9uk3WZg_ndRxue5p4vaWmZNXUmrNFCFhqTLtg.R9enb47Pfu3YGHnKaGykOpqFnw8_cCz8KHw2l8cY9II&dib_tag=se&keywords=Estop&qid=1792005743&sprefix=estop%2Caps%2C187&sr=8-2&th=1>) |
| **TOTAL COST** | | | **$791.15** | |

### Division of Labor

Each team member will still be responsible for managing a subsystem and its detailed design documentation. That stated, major subsystem tasks can still be broken down, prioritized, and delegated as they need to be completed by whoever is most available and whose experience matches the task. For example, a single team member may be responsible for the research and documentation of a specific subsystem, however any team member may work on the implementation of that subsystem. The mechanical engineering team will be responsible for the chassis, drivetrain, and actuator mechanisms, with electrical interfaces defined jointly between the two teams.

| Team Member | Subsystem Detailed Design |
| --- | --- |
| Kyle | Vision Input & Processing |
| Ty | PCB Design / Motor Control |
| Tuan | Master Controller |
| Hadassah | Power & Battery Management |
| Austin | Obstacle & Boundary Detection |
| Matthew | Flag Raising & Tire-Changing Actuators |

### Timeline

<img width="973" height="415" alt="image" src="https://github.com/user-attachments/assets/3ae154d7-cacb-4d33-b559-f596ad78aadf" />

## References

[1] IEEE, “SoutheastCon 2027 Hardware Competition Stock Car Race - Game Manual 1.” IEEE, Oct. 10, 2026. [Online]. Available:

[2] IEEE, “SoutheastCon 2027 Hardware Competition Stock Car Race - Game Manual 2.” IEEE, Oct. 10, 2026. [Online]. Available:

[3] Tennessee Technological University, “F25 Team7 SECON Hardware Competition 2026,” GitHub. Accessed: Sep. 14, 2026. [Online]. Available:

[4] Tennessee Technological University, “F24 Team1 SECON Hardware Competition 2025,” GitHub. Accessed: Sep. 14, 2026. [Online]. Available:

[5] N. Gardner, “SECON2023Robot - IEEE SoutheastCon Robotics Competition,” GitHub. Accessed: Sep. 14, 2026. [Online]. Available:

[6] K. Agyeman, “Robocup,” OpenMV, Oct. 08, 2024.  (accessed Oct. 19, 2026).

[7] “GitHub - ClarkeNeedles/Autonomous-PiCar” GitHub, 2026.  (accessed Oct. 19, 2026).

[8] Raspberry Pi, “Raspberry Pi Documentation - Camera,” www.raspberrypi.com.  (accessed Oct. 19, 2026).

[9] P. Schweizer, “Picamera2: Control the Raspberry Pi Camera With Python – Photos, Video, Live Stream and OpenCV,” raspberry.tips, Sept. 21, 2026.  (accessed Oct. 19, 2026).

[10] OpenCV, “OpenCV Library,” Opencv.org, 2019.  (accessed Oct. 19, 2026).

[11] “OpenMV N6,” Openmv.io, 2026.  (accessed Oct. 19, 2026).

[12] “OpenMV AE3,” Openmv.io, 2026.  (accessed Oct. 19, 2026).

[13] The Construct Robotics Institute, “What is ROS—and why it matters in robotics.” theconstruct.ai.  (accessed Oct. 18, 2026).

[14] IBM, “What is a real-time operating system (RTOS)?” IBM Think.  (accessed Oct. 18, 2026).

[15] V. A. Rokad, “Fundamentals of RTOS,” Medium.  (accessed Oct. 18, 2026).

[16] A. Tyagi, “Getting started with Jetson Nano,” Medium.  (accessed Oct. 18, 2026).

[17] NVIDIA, “Vision Programming Interface (VPI),” NVIDIA Developer.  (accessed Oct. 18, 2026).

[18] NVIDIA, “VPI - Vision Programming Interface: Main page,” NVIDIA Docs.  (accessed Oct. 18, 2026).

[19] friendlydroid, “Learning RPLIDAR with Jetson Nano: A fun and easy set-up guide to robot SLAM,” Medium.  (accessed Oct. 18, 2026).

[20] JetsonHacks, “Jetson Nano – Use more power!” JetsonHacks, Apr. 10, 2019.  (accessed Oct. 18, 2026).

[21] STMicroelectronics, “STM32 Nucleo boards.” st.com.  (accessed Oct. 18, 2026).

[22] Core Electronics, “Teensy 4.1.” core-electronics.com.au.  (accessed Oct. 18, 2026).

[23] Make:, “PJRC Teensy 4.1.” makezine.com.  (accessed Oct. 18, 2026).

[24] The Pi Hut, “Teensy 4.1 – No Ethernet.” thepihut.com.  (accessed Oct. 18, 2026).

[25] Kiwi Electronics, “Raspberry Pi 5 4GB.” kiwi-electronics.com.  (accessed Oct. 18, 2026).

[26] raspberrypi.dk, “Raspberry Pi Pico 2.” raspberrypi.dk.  (accessed Oct. 18, 2026).

[27] Olimex, “RP2350-PICO2.” olimex.com.  (accessed Oct. 18, 2026).

[28] STMicroelectronics, “STM32H743/753 Arm Cortex-M7 microcontrollers (MCUs).” st.com.  (accessed Oct. 18, 2026).

[29] Cytron Technologies, "10Amp 5V-30V DC Motor Driver (2 Channels) - MDD10A," Cytron Technologies Product Catalog, 2024. [Online]. Available: . [Accessed: Oct. 18, 2026].

[30] Cytron Technologies, "Using MDD10A with Arduino Uno," Cytron Technologies Tutorial, 2024. [Online]. Available: . [Accessed: Oct. 18, 2026].

[31] ANSI, "ISO 13850: Safety of Machinery – Emergency Stop Function – Principles for Design," ANSI Blog, Jul. 12, 2023. [Online]. Available: . [Accessed: Oct. 18, 2026].


[32] Cytron Technologies, "10Amp 5V-30V DC Motor Driver (2 Channels) - MDD10A," Cytron Technologies Product Catalog, 2024. [Online]. Available: . [Accessed: Oct. 18, 2026].

[33] L. Fried, "Adafruit 16-Channel 12-bit PWM/Servo Driver," Adafruit Learning System, Adafruit Industries, Brooklyn, NY, USA, Primary Guide ID 1126, 2024. [Online]. Available: . [Accessed: Oct. 18, 2026].

[34] PJRC, "Teensy 4.1 Development Board," PJRC Store Catalog, 2024. [Online]. Available: . [Accessed: Oct. 18, 2026].

[35] Littelfuse, Inc., "Fuseology: Fuse Facts and Fuse Selection Guide," Application Guide, Tech. Doc. be92b28c-1f63-4f48-a505-55c582b7c1ae, 2021. [Online]. Available: . [Accessed: Oct. 18, 2026].

[36] Littelfuse, Inc., "Fuses and Overcurrent Protection Products," Littelfuse Product Catalog, 2024. [Online]. Available: . [Accessed: Oct. 18, 2026].

[37] OpenMV, "OpenMV Cam N6 Quick Reference," OpenMV Documentation, 2024. [Online]. Available: . [Accessed: Oct. 18, 2026].

[38] Melissa & Doug, "K’s Kids Pull-Back Town Vehicle Set," Amazon.com.  (accessed Oct. 18, 2026).

[39] J. Borenstein and L. Feng, "Measurement and correction of systematic odometry errors in mobile robots," IEEE Trans. Robot. Autom., vol. 12, no. 6, pp. 869–880, Dec. 1996.

[40] Pololu, "QTR-MD-08RC Reflectance Sensor Array: 8-Channel, 8mm Pitch, RC Output," Pololu.  (accessed Oct. 18, 2026).

[41] SparkFun Electronics, "SparkFun Qwiic Optical Tracking Odometry Sensor - PAA5160E1," Eckstein.  (accessed Oct. 18, 2026).

[42] ElecFreaks, "Ultrasonic Ranging Module HC-SR04," datasheet.  (accessed Oct. 18, 2026).

[43] STMicroelectronics, "VL53L0X: Time-of-Flight ranging sensor," datasheet.  (accessed Oct. 18, 2026).

[44] STMicroelectronics, "VL53L7CX: Time-of-Flight 8x8 multizone ranging sensor with 90 degrees FoV," STMicroelectronics.  (accessed Oct. 18, 2026).

[45] SLAMTEC, "RPLIDAR C1 specifications," SLAMTEC.  (accessed Oct. 18, 2026).

[46] Sierra Circuits, "How to Use Decoupling Capacitors in PCB Design," Sierra Circuits Blog, Oct. 2023. [Online]. Available: . [Accessed: Oct. 21, 2026].

[47] “4WD Omnidirectional Mecanum Robot Car With Claw AI Visual Recognition Tracking for Arduino DIY Kit for UNO Programmable Robot,” Bestdealplus.com, 2026.  (accessed Oct. 23, 2026).

[48] ISO, ISO 12100:2010, *Safety of machinery — General principles for design — Risk assessment and risk reduction*. Geneva, Switzerland: International Organization for Standardization, 2010.

[49] H. Durrant-Whyte and T. Bailey, "Simultaneous localization and mapping: Part I," IEEE Robot. Autom. Mag., vol. 13, no. 2, pp. 99–110, Jun. 2006, doi: 10.1109/MRA.2006.1638022.

## Statement of Contributions

| Assignment | Assignee |
| --- | --- |
| Introduction | Matthew |
| Restating the Fully Formulated Problem | Matthew & Ty |
| Comparative Analysis of Potential Solutions | Kyle |
| High Level Solution | Tuan & Kyle |
| Electrical Interconnect Design | Ty |
| Master Control Atomic Subsystem | Tuan |
| Camera & Vision Processing Atomic Subsystem | Kyle |
| Flag Raising & Tire-Changing Actuators Atomic Subsystem | Matthew |
| Obstacle & Boundary Detection Atomic Subsystem | Austin |
| Power & Battery Management Atomic Subsystem | Hadassah |
| Ethical, Professional, and Standards Considerations | Hadassah & Austin |
| Resources | Kyle |
