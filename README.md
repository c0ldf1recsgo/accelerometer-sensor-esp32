# Accelerometer Sensor ESP32
## Requirements:
- Devices:
    - WEMOS LOLIN32 Lite. [MORE](https://diyprojects.io/deal-wemos-lolin32-lite-compact)
    - GY-291 ADXL345 3-AXIS ACCELEROMETER. [MORE](https://opencircuit.shop/Product/ADXL345-3-axis-Accelerometer-GY-291)

(optional) use this if you want to collect data using you board
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
### Step 4:
- Add code in check_sensor.cpp to the file *main.cpp* in folder: *your-project-name\\src\\* 
- Find the arrow button near the bottom left of Status bar in VSCode and click it, wait for it to build.
- Everything should be good for now, you can check the result in Arduino IDE
- [Here](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/) is how you can add ESP32 module to Arduino IDE.

## Data forwarder:
- This will help you to collect data from your device to EdgeImpulse to train model. Skip this step if you have other way tpo collect data.
- Input ```edge-impulse-data-forwarder``` into your Command Line.
- If it is successful, then you have to input your Registered email and Password.
- Now just follow the instruction from your Command Line.

## Input Data:
- Check this [Documentation](https://docs.edgeimpulse.com/docs/using-your-mobile-phone) if you want to use your mobile phone to collect data.
- Open EdgeImpulse and Start Sampling to add data.
- Do whatever you want and name the label for it.

## Training:
- Click on **Impulse Design** and choose how you will train it as the picture below.
![image1](https://github.com/c0ldf1recsgo/accelerometer-sensor-esp32/blob/main/Images/image1.png)
- Choose parameters for each block
- *Processing block*

![image2](https://github.com/c0ldf1recsgo/accelerometer-sensor-esp32/blob/main/Images/image2.png)
- *Learning block*

![image3](https://github.com/c0ldf1recsgo/accelerometer-sensor-esp32/blob/main/Images/image3.png)
- After running the learning block you will get the result:

![image4](https://github.com/c0ldf1recsgo/accelerometer-sensor-esp32/blob/main/Images/image4.png)
- After training your model, go to **Deployment**
- Select *Arduino Library*, disable *EON Compiler* and select *Unoptimized (float 32)* then Build

![image5](https://github.com/c0ldf1recsgo/accelerometer-sensor-esp32/blob/main/Images/image5.png)
- You will now have a .zip file, unzip it.
- We will need to file in the folder we've unzipped:
    - src\tflite-model\tflite-trained.h
    - src\model-parameters\model_metadata.h

## Deploy:
- Get back to the project in Visual Studio Code, copy the file *tflite-trained.h* to *include* folder
- Edit the *main.cpp* as in my repository
- Change the values
```NUMBER_OF_INPUTS```
```NUMBER_OF_OUTPUTS```
```TENSOR_ARENA_SIZE```
You can get these values from file *model_metadata.h*:
```EI_CLASSIFIER_NN_INPUT_FRAME_SIZE  ```
```EI_CLASSIFIER_TFLITE_ARENA_SIZE```
```NUMBER_OF_OUTPUTS``` is the number of label in ```ei_classifier_inferencing_categories[]```
- Change the PINs number to whatever you use for your Board
- Run the file
- Circuit:

![image9](https://github.com/c0ldf1recsgo/accelerometer-sensor-esp32/blob/main/Images/image9.png)
- Real image:
 
![image7](https://github.com/c0ldf1recsgo/accelerometer-sensor-esp32/blob/main/Images/image7.jpg)

![image8](https://github.com/c0ldf1recsgo/accelerometer-sensor-esp32/blob/main/Images/image8.jpg)

![image6](https://github.com/c0ldf1recsgo/accelerometer-sensor-esp32/blob/main/Images/image6.jpg)
## Finish:
### Video demo:
asfasf
### Code Explain:
