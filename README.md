# Thermo-logger-Hardware-and-Software-implementation

1. What is this project supposed to do?

Answer: This project is a digital thermometer which used the PIC18F4550 microcontroller. The ambiental temperature will be registered using an external sensor.

The temperature is read and compared with the one set in the platform. If the temperature is higher than the reference, nothing happens, but if the temperature is lower, the relay closes and it turns on the hearing. 

The communication between the NodeMCU and the platform uses HTTP requests.

2. Logical diagram

![image](https://github.com/codrinalisaru/Thermo-logger-Hardware-and-Software-implementation/assets/94629883/4700d427-2e9b-4111-bb42-ff344e8fe69c)


3. Electrical wiring

![image](https://github.com/codrinalisaru/Thermo-logger-Hardware-and-Software-implementation/assets/94629883/cef01746-4766-46b9-86ab-aeae362b2b2f)

5. Proteus simulation

![image](https://github.com/codrinalisaru/Thermo-logger-Hardware-and-Software-implementation/assets/94629883/962b2c8e-3664-494b-9dde-a6fd4ed90802)

4. Used components:

- PIC18F4550 microcontroller;
- LM016L LCD display;
- LM35 temperature sensor.
