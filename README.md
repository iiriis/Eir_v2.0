# Eir_v2.0

An Inexpensive Heart monitoring System which is built from scratch, without any libraries and breakout modules.


## Inspiration
One of our friends has a heart condition that requires continuous monitoring of her pulse rate. Also, during the pandemic, the rise of the number of cases of COVID positive has left many people unstable and in need of continuous monitoring of their health. This made us wonder if we could build an inexpensive alternative to the costly oximeter devices that many cannot afford. All the reasons mentioned above were the inspiration behind building Eir.

## What it does
With this very inexpensive project, we will be able to measure the essentials of heart health. Here it is performing a photoplethysmogram aka PPG with a sensor that we built. With this PPG, we optically detect the blood volume change inside the microvascular bed of tissue. By analysing the graph, the program auto-detects the systolic peaks and calculates the BPM. The user has to put the finger on the sensor. It calibrates itself and prints the BPM. Also, the results of the PPG graph are very accurate, and it can log the results to memory for further analysis. 

## How we built it
First of all, we built the sensor, for that we used an Infrared LED and a photodiode. We put both of them close to each other and covered the sides with a black cover, which we DIY-ed with black paper. Next, we needed a microcontroller for taking the readings and the calculations; for that, we used an atmega328p. The output of the sensor gets connected directly to the ADC of the microcontroller. 
Unlike the conventional pulse oximeters, which require external circuitry such as filters and smoothing capacitors and amplifiers, we have implemented digital filters to achieve the same results with accuracy. For that, we have used a recursive IIR (Infinite Impulse Response) filter that at first removes the high-frequency ADC noises and smoothes out the sensor readings. After that, we used a moving average algorithm to average 100 samples for higher accuracy. 
Till now, we were able to see the Beats. But the values had a high offset. We used a High pass recursive filter to get rid of that and finally obtained the accurate PPG graph in the monitor. 
Next, we had to detect the systolic peaks, and for that, we used a local maxima algorithm and used a millisecond timer to measure the time required from one peak to another. This is the time period of the peaks. By doing the inverse of the time period, we get the frequency. And multiplying that frequency with 60, we get the BPM. To recheck that BPM, it again runs a performance check by measuring the number of peaks detected in 10s and multiplying it with six; we get the number of peaks in the 60s. By fusing these values, we get the accurate BPM.
Finally we added a 16*2 LCD that will act as an onboard display to display the BPM, along with that it has a confidence parameter that will indicate the confidence level of the readings. Higher the confidence percentage, more accurate are the readings.

## Challenges we ran into
Making the IR sensor was a bit troublesome since not covering it properly was causing some random noises to the readings. Finding the filter coefficients for accurate readings took a lot of trial and error. The algorithm for auto-calibration was a tough one.

## Accomplishments that we're proud of
Extracting the accurate readings from the highly noisy data by Implementing the filters properly and setting their filter coefficients was a great success. Finally, when putting the fingertip on the sensor, making the PPG wave, and getting to know that our graph looks very similar to the actual PPG graphs, that was the "yaay" moment. Without the use of any external analog filters, with just a few simple laying around components, we were able to achieve such accurate results; we are proud of our accomplishment.

## What we learned
We learned about photoplethysmogram and how we can achieve that with optical sensors like photodiodes and IR LEDs. Learned about digital filters, which we can implement into our further projects, and being the most helpful. We were pretty amazed by knowing that we are surrounded by so many signals, and it contains data. Even when we saw the signal from the sensor read by the ADC, it was such a mess and very noisy reading. After filtering, we were able to get the desired reading. 

## What's next for Eir 2.0
We are targeting to attach a RED LED to measure the SP02 level. Even by modifying the algorithms for detecting the Diastolic peak and the Dicrotic notch and measuring the transit times, we can reveal many secrets of the user's health. Next, we will try to build an app that will display all the data recorded from the person using Eir, and the app will also be able to analyse and express if the user has any health condition using algorithms. Along with focusing on healthcare, this hack will also help people in general to monitor their well-being and learn about the factors that affect their health. We will try to turn this device into a commercial product that can also be used for educational purposes in institutes and hospitals. 
