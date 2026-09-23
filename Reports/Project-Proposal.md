# Project Proposal

## Introduction & Background

The IEEE (Institute of Electrical and Electronics Engineers) hosts an annual conference for the southeastern region known as SoutheastCon (SECON). As part of the conference, the annual Hardware Competition challenges university students to apply their engineering knowledge through the design, construction, and programming of an autonomous robotic system. For the 2027 competition, “Stock Car Race,” teams are tasked with developing a fully autonomous ground robot capable of navigating a racecourse and completing three laps within a three-minute time limit. During the race, the robot must avoid randomly placed obstacles, identify an assigned pit area using an AprilTag, perform a pit stop and tire exchange, and return to the course. Points are earned based on how well the robot can complete these tasks. Additional points can be earned by avoiding contact with obstacles and course walls and raising our university flag during the final lap. To meet these objectives, two Capstone teams will be responsible for the development of this autonomous robot: a mechanical team and an electrical team. The mechanical team is responsible for the chassis, drivetrain, and actuators. Because both teams build one robot under shared size, mass, and safety limits, the two teams must jointly define interface requirements.

### Proposal Overview

This proposal presents the planned development of the autonomous robot’s electrical systems and the approach the team will take to meet the requirements of the 2027 IEEE SoutheastCon Hardware Competition. The remaining sections of this proposal define the electrical requirements, design approach, and verification plan within the shared constraints.

## Formulating the Problem

The customers for this project are the TTU ECE department and Dr. Storm, the Fall 2026 Capstone instructor. The TTU ECE department and Tennessee Tech IEEE Club are stakeholders. As this team represents TTU in the competition, the stakeholders have a vested interest in seeing this project succeed. The 2027 IEEE Stock Car Race competition requires a fully autonomous robot to complete three laps around a track within three minutes, do a pit stop, and park within a designated location after completing the race \[4\].

Completing the race on time awards 100 points and one additional point is earned for every full 10 seconds by which the robot finishes early, up to a maximum of \[X\] points \[4\]. Additionally, 25 points are awarded just by entering the course \[4\]. The bulk of the points are awarded through a variety of mid-race assignments the robot completes. For instance, the robot must be able to read an AprilTag fixed on the arena, and that reveals which of the three zones the robot needs to make a pit stop at and where it needs to park when it finishes the race for additional points \[4\]. The race begins when the referee raises a green flag, and 10 points are awarded if the robot starts on time \[4\].

At the start of the game, every robot will be holding a tire and must fit within a 12 in x 12 in x 12 in space \[3\]. Robots are allowed to expand past that area once the game starts \[3\]. Between laps one and two or two and three, the robot must make a pit stop where points are awarded for dropping the tire in the correct zone indicated by the AprilTag \[4\]. Additional points are then awarded if the robot picks up a different tire before leaving the pit. Up to 15 points are earned by the robot for entering the pit, but the full points cannot be earned unless it stops for a minimum of two seconds in the pit \[4\]. The final major assignment the robot needs to do to earn points is raising the school flag during the final lap \[4\].

The competition is not just about finishing the race in three minutes. A myriad of assignments must be completed during the race to earn every point possible. The robot must perceive its environment, track its own progress, and manipulate game elements throughout the race. Therefore, the problem is defined by the following requirements:

1. The robot shall operate autonomously with no human input after the start command.

2. The robot shall begin the race upon detecting the referee's green flag.

3. The robot shall fit within a 12 in × 12 in × 12 in space at the start while holding a tire.

4. The robot shall complete three laps within three minutes.

5. The robot shall navigate a course whose path is known while avoiding obstacles whose positions are unknown.

6. The robot shall read the arena AprilTag to determine its assigned pit zone and parking location.

7. The robot shall track laps completed, elapsed time, and pit-stop status.

8. The robot shall make one pit stop between either laps one and two or laps two and three, remaining in the pit for at least two seconds.

9. The robot shall drop its tire in the assigned zone and pick up a different tire before leaving the pit.

10. The robot shall raise the school flag during the final lap.

11. The robot shall autonomously stop in its assigned zone at the end of the race.

While solutions exist for individual tasks, there is no known off-the-shelf solution that can complete all requirements set out by the race at once. This means a solution must be custom designed, tested, and competition-ready by April 2027. Designing such a robot requires knowledge including but not limited to: Control systems, power systems, embedded firmware and hardware, motor controls, image processing, CAD design, and soldering. A project of this size and complexity requires a full team with a diversity of skills to match these requirements and address the problem.

## Specifications and Constraints

This section defines the requirements the robot must meet. "Shall" marks a mandatory requirement and "may" marks an optional one. Each requirement is written to be measurable, and each specification lists how it will be verified.

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
| OS-3 | The robot shall score no fewer than \[X\] points per match. | Refereed practice runs scored per the GM2 \[4\] rules. |
| OS-4 | The robot shall complete a full match without failure in at least 9 of 10 consecutive practice runs. | Test log of consecutive runs. |
| OS-5 | The robot shall reach a ready-to-start state within 60 s of power-on \[3, Sec. 7.2\]. | Timed power-on to ready-indicator tests. |
| OS-6 | The robot shall operate for no less than 15 min† on a single battery charge \[3, Sec. 7.1\]. | Continuous runtime test from full charge. |
| OS-7 | The robot shall pass official inspection on the first attempt \[3, Sec. 6.1\]. | Mock inspection per the Appendix A checklist prior to travel. |
| OS-8 | Total project cost shall not exceed $\[X\]. | Tracked bill of materials and purchase records. |

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
| RS-6  | The emergency stop shall be a red latching switch labeled "STOP," accessible from the top of the robot, and shall remove power from all actuators within 500ms of actuation \[3, R04\].  | Oscilloscope measurement of actuator supply voltage.            |
| RS-7  | Team identification shall be displayed on no fewer than two faces of the robot in characters or graphics no less than 1.5in in height \[3, R10\].                                        | Readability assessment from 6 ft by a non-team member.          |
| RS-8  | All sensing, processing, and decision-making shall be performed by computing hardware mounted on the robot \[3, R18\].                                                                   | Design review; test run with all external devices powered down. |
| RS-9  | The robot shall incorporate a designated handle and shall be removable from the Field by a single person, without tools, in less than 30 s \[3, R09\].                                   | Timed removal test.                                             |
| RS-10 | The battery shall be replaceable without tools in less than 60s \[3, Sec. 7.2\].                                                                                                         | Timed swap test.                                                |
| RS-11 | The robot may expand beyond its starting envelope after the match has begun, and Game Elements carried at start may extend beyond that envelope \[3, R01\].                              | ---                                                             |
| RS-12 | The robot may employ wireless communication between onboard components \[3, R19\].                                                                                                       | ---                                                             |

#### Board Specifications

The competition field and game elements are described and specified in Game Manual 2 \[4, Sec. 3.3.1\], which has not been fully released at this current time. Table III states the requirements are applicable at this time and remaining board specifications will be incorporated upon the finalized competition rule set.

**TABLE III: BOARD SPECIFICATIONS BASED ON STAKEHOLDERS AND TEAM**

| ID   | Requirement                                                                                                                                       | Verification                                 |
|------|---------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------|
| BS-1 | Field dimensions, surface, Game Elements, and scoring shall be incorporated from Game Manual 2 upon its release \[4, Sec. 3.3.1\].                | Document revision upon final publication.    |
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

IEEE constraints go to address the conduct, safety, eligibility, and documentation requirements imposed by the IEEE and SECON. This goes to keep the public welfare and societal considerations kept in mind while designing.

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

### Master Control

The robot must complete the track within a three-minute time limit while also being able to stop at designated pit stops. This requirement means the robot software must support computationally intensive processes, most likely involving machine learning and computer vision. Running these processes efficiently therefore demands a hardware controller with sufficient computing power.

Several master controller solutions exist across similar robotics competitions, each with different tradeoffs between real-time reliability and computational capability. In the FIRST Robotics Competition (FRC), which includes racing-style games, teams have commonly used the roboRIO as the master controller for robot operations \[16\]. This board combines a real-time processor with an FPGA for logic control, and its small size, light weight, and durability allow it to withstand hard hits during matches. However, the roboRIO's compute power is not designed for machine learning or computer vision workloads, making it poorly suited on its own for tasks like pit-stop detection or lane recognition.

In contrast, competitions such as F1TENTH, an autonomous racing car competition, tend to see students implement the NVIDIA Jetson for its higher computational capability \[17\]. Previous teams competing in SECON 2024 and 2025 similarly used the NVIDIA Jetson for the same reason \[5\], \[6\].

Other approaches include pairing a lower-cost single-board computer, such as a Raspberry Pi with a Coral TPU or Intel Neural Compute Stick, to offload ML inference at a fraction of the Jetson's cost, though generally with lower throughput. Some teams also adopt a hybrid architecture, using a microcontroller for low-latency, real-time motor and sensor control alongside a separate companion computer for vision and ML processing — an approach that mirrors the division of labor built into the roboRIO's combined real-time processor and FPGA, but distributes it across two dedicated boards instead of one.

### Navigation

The FRC competition centers on known-field trajectory following rather than obstacle-avoiding autonomy, since the field layout is fixed and known in advance. PathPlanner is widely used for this purpose: teams use a GUI to place waypoints and drag Bézier-curve control handles to visually shape the desired path\[18\]. Once a path is defined, PathPlannerLib provides built-in functions that allow the robot to follow the planned trajectory automatically, using feedback control to correct for drift and keep the robot on course.

F1TENTH, by contrast, does not rely on a pre-planned path in the same way. Because the track is not known in advance to the same degree, teams must localize the robot within its environment by implementing Simultaneous Localization and Mapping (SLAM)\[19\]. SLAM can be implemented using a single sensor modality or a fusion of multiple sensors to build an accurate representation of the robot's physical environment. LiDAR is the primary sensor used for this purpose, since it directly measures distances to surrounding obstacles and track boundaries, while a camera mounted on the robot can supplement this data — for example, by providing additional visual features or depth information — to improve the accuracy of the resulting SLAM map.

Since SECON involves racing along a fixed, predetermined path, Iterative Learning Control (ILC) is another approach worth considering. ILC is designed specifically for this type of scenario: a control system that performs a single, repeated task, using information from prior runs to gradually determine control inputs whose tracking performance exceeds that of traditional feedback-feedforward control \[20\].

Overall, FRC and F1TENTH represent two established navigation approaches: pre-planned trajectory following for known, fixed environments, and SLAM-based localization for environments that are not known in advance. Given SECON's fixed and repeated track layout, methods such as PathPlanner and ILC are the most directly applicable existing solutions to build on.

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

## Resources

### Budget

\[estimated BOM, to be completed after conceptual design\]  
Along with an estimated Bill of Materials, using the previous SECON robots’ BOM can serve as a good reference point for the cost of this project. The electrical design constraints for the Hardware Competition are largely consistent year-to-year \[3\]\[25\]. Cost drivers remain similar, so previous team’s component costs are a reasonable benchmark. The electrical systems for the Fall 2025 and Fall 2024 Capstone SECON robots’ cost \[some amount\] \[5\] and \$1025.72 \[6\], respectively.

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

<img width="1291" height="359" alt="timeline-sept-23" src="https://github.com/user-attachments/assets/158400cc-fcd5-4a62-91c6-366884b2453e" />

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
