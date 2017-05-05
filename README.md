# cmsisCNN

This repository contains the source code for implementing Convolutional Neural Network based Traffic sign recognition on Tiva TM4C123G LaunchPad Evaluation Kit.

The training and test data set can be downloaded from https://disq.us/url?url=https%3A%2F%2Fd17h27t6h515a5.cloudfront.net%2Ftopher%2F2017%2FFebruary%2F5898cd6f_traffic-signs-data%2Ftraffic-signs-data.zip%3AWO3Nq9Ds8s63rCvcn6CrIqXkNk0&cuid=4444009

The code cmsisCNN/python/cnn_traffic.py contains the python for training the model from the given training set.

The folder cmsisCNN/cmsis_cnn_NokiaLCD contains the complete source code for implementing on TIVA TM4C123G LaunchPad Board.

Before running the code, CMSIS-DSP Library has to be downloaded from https://github.com/ARM-software/CMSIS.
Step-by-Step instructions for setting up the CMSIS-DSP library are given in www.ti.com/lit/an/spma041g/spma041g.pdf

-------------------------------------------------------------------------------------------------------------------------------

Usage

1. Download CMSIS-DSP Library from https://github.com/ARM-software/CMSIS.
2. Follow the instructions given in www.ti.com/lit/an/spma041g/spma041g.pdf to properly set up the library.
3. For the given training data set, execute the python/cnn_traffic.py to train the model parameters. Vary the hyperparameters for the desired accuracy.
4. Extract the parameters and store them in weights.h header file in cmsisCNN/cmsis_cnn_NokiaLCD/ folder.
5. Use the main C code arm_matrix_example_f32.c to perform matrix multiplications effortlessly.


-------------------------------------------------------------------------------------------------------------------------------

Contributors
1. Desai Jagannath Vishnuteja
2. Suddpalli Krishna Chaitanya
3. Jayanth K
