# Accelerometer Sensor ESP32
## Requirements:
- Devices:
    - WEMOS LOLIN32 Lite. [MORE](https://diyprojects.io/deal-wemos-lolin32-lite-compact)
    - GY-291 ADXL345 3-AXIS ACCELEROMETER. [MORE](https://opencircuit.shop/Product/ADXL345-3-axis-Accelerometer-GY-291)
- Install [Node.js](https://nodejs.org/) v10 or higher on your host computer.
- Install the CLI tools via Windows Command Line:
```npm install -g edge-impulse-cli```
After that, you could meet some errors, you can search it on Googles to find the way to solve it easily.
## Coding:
- We are using Visual Studio Code with [PlatformIO](https://platformio.org) Extension for coding, you can use something else.
- After install PlatformIO IDE (PIO) in VSCode, you can see PIO icon on the Activity Bar of VSCode.
### Step 1:
- Click on PIO icon, you can see a multiple tab. Go to *PIO Home* **>** *Open*.
- Click **New Project**, name whatever you want for you project, choose Board *WEMOS LOLIN 32*, let the Framework: Arduino
- Keep Using the default location as it will save to *C:\Users\\ %your-user-name%\Documents\PlatformIO\Projects*.
- Then click Finish and wait for it to complete
### Step 2:
- In PIO Home, click on **Libraries** tab, search for *EloquentTinyML* (by Simone Salerno), click **Add to Project**
- Select the project you've created before and Add.
### Step 3:
- Do the samething with *Adafruit ADXL345* Libraries (by Adafruit)
- Download 2 libraries I've uploaded on github: **ADXL345** and **I2Cdev**
- Paste into your project with path: *your-project-name\\.pio\libdeps\lolin32\\*
### Step 4:
- Add code to the file *main.cpp* in folder: *your-project-name\\src\\* 
- Find the arrow button near the bottom left of Status bar in VSCode and click it, wait for it to build.
- Everything should be good for now, you can check the result in Arduino IDE
- [Here](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) is how you can add ESP32 module to Arduino IDE.

## Data forwarder:
- Input ```edge-impulse-data-forwarder``` into your Command Line.
- If it is successful, then you have to input your Registered email and Password.
- Now just follow the instruction from your Command Line.

## Input Data:
- Open EdgeImpulse and Start Sampling to add data.
- Do whatever you want and name the label for it.
