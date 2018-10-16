# LCD Monitor

Project to create a Facilities Monitor and Access Control System  for a shared space.

As our work space is shared by several people, we want to have the greatest flexibility and at the same time security and responsibility, access control is a challenge that we have long tried to solve.

We resolved to cannibalize the current alarm and create a new one whose programming is much more flexible.

---

The progress of this project can be tracked (in Portuguese) in a [blog post](https://blog.lcdporto.org/project-lcd-monitor/) at our blog.

---

## Brief description

The console will be run by a Arduino and an API running on a server, the Arduino will handle all the sensors, keypad and buzzers independently.

The API (probably using Django REST) to communicate events and receive instructions.

After receiving new programming the API will pass it to the Arduino via  ethernet. 
