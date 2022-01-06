# ELEC3662-Mini-Project
Final Assessment for ELEC3662 Embedded Systems

Components used: 

1- 4x4 Matrix Keypad 

2- HD44780U HITACHI 16x2 LCD (Blue backlight model used due to its smaller size and pinout placements)

3- TM4C123GH6PM Tiva Lauchpad 

4- Breadboard and Connecting Wires

5- 10K Potentiometer

# Hardware Schematic
1- Circuit Schematic

![Schematic_Embedded_Prj_sch_2022-01-05](https://user-images.githubusercontent.com/94575661/148176251-0d53f42f-2bd9-44a5-9620-b8541f877762.png)

2- Completed Hardware

![IMG_20220105_112005](https://user-images.githubusercontent.com/94575661/148176585-e6115a71-d990-4b59-b865-90d5372cddb0.jpg)
![IMG_20220105_112015](https://user-images.githubusercontent.com/94575661/148176591-5a25f23d-ba2d-46d3-86e9-a8cd09221c0d.jpg)


# Working Demo (Pictures and Video)
1- Boot-up Screen (Locked mode)
![IMG_20220104_192022](https://user-images.githubusercontent.com/94575661/148084143-7e045e19-62cc-42c9-a400-7d33549aa8e7.jpg)

2- Entering Correct Password

https://user-images.githubusercontent.com/94575661/148169385-3fb62ac0-75f2-49e8-accb-dda3b543b384.mp4

3- Entering Wrong Password

https://user-images.githubusercontent.com/94575661/148170346-605c5a86-5904-49d3-828e-88ed3b0f9502.mp4

4- Operations

For the 1st operation, it first calculates (5+98-44x2E1) which is -777, then 0.8/(-777) which gives -0.001 as shown on the LCD.

https://user-images.githubusercontent.com/94575661/148173682-9e4f6b12-b1bb-4ae7-a40f-2b338e1b61d6.mp4

5- Changing Password

Overwriting the existing set password with a new one which is stored inside the EEPROM

https://user-images.githubusercontent.com/94575661/148177604-8c907da5-6b90-400b-ac2d-ffc67f00d3ed.mp4

https://user-images.githubusercontent.com/94575661/148177647-10c296e4-a1d5-4ae7-82ab-821575c58e6c.mp4

# Known Bugs 

1- Unrecognizable Symbol being printed on the display right after the changed password is printed (which can be seen in the video above).

