#!/bin/sh

sudo apt-get update
sudo apt-get install python3-sklearn

uname -a 
cat /etc/os-release
gcc -v

sudo apt install curl 
echo "deb https://packages.cloud.google.com/apt coral-edgetpu-stable main" | sudo tee /etc/apt/sources.list.d/coral-edgetpu.list
curl https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -
sudo apt update
sudo apt install python3-tflite-runtime

mkdir tmp
curl https://raw.githubusercontent.com/tensorflow/tensorflow/master/tensorflow/lite/examples/label_image/testdata/grace_hopper.bmp > ~/tmp/grace_hopper.bmp
 
curl https://storage.googleapis.com/download.tensorflow.org/models/mobilenet_v1_2018_02_22/mobilenet_v1_1.0_224.tgz | tar xzv -C ~/tmp
 
curl https://storage.googleapis.com/download.tensorflow.org/models/mobilenet_v1_1.0_224_frozen.tgz  | tar xzv -C ~/tmp  mobilenet_v1_1.0_224/labels.txt
 
mv ~/tmp/mobilenet_v1_1.0_224/labels.txt ~/tmp/

cd
wget https://raw.githubusercontent.com/team-osaka-hightech/osaka-hightech-airobot-exercise/main/label_image.py

python3 label_image.py   --model_file ~/tmp/mobilenet_v1_1.0_224.tflite   --label_file ~/tmp/labels.txt   --image ~/tmp/grace_hopper.bmp

sudo apt install python3-opencv

git clone https://github.com/tensorflow/examples --depth 1
 
cd examples/lite/examples/object_detection/raspberry_pi
 
sh setup.sh

sudo apt install libportaudio2
