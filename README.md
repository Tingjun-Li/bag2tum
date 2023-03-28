# bag2tum
Convert rosbag image data to TUM format

# How to run:
1. Clone the repo into `catkin_ws/src`
2. build the repo
3. In one terminal, run `rosrun rosbag2tum bag2tum`
4. In another terminal, `rosbag play  <your_bag>.bag  -r 0.5`
5. wait for the result and check all the output
6. Create association.txt file: python3  associate.py rgb.txt  depth.txt > association.txt

Reference (In Chinese):
https://www.guyuehome.com/35920
