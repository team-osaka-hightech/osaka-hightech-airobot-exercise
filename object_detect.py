#!/bin/sh

cd ~/examples/lite/examples/object_detection/raspberry_pi
python3 detect.py --model efficientdet_lite0.tflite --cameraId 0
