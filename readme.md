# KMeansDemo
An simple program to show how OpenCV's KMeans works showing its visual output. This code is part of a [post on my blog about KMeans](http://jeanvitor.com/k-means-image-segmentation-opencv/). 

# How to use
You will need a working OpenCV compilation. To learn how to install and use it with Eclipse & MinGW-w64 [take a look in a post on my blog](http://jeanvitor.com/cpp-opencv-windonws10-installing/). 

This project was developed using Eclipse. Therefore, clone using `git clone` or download and open it as a Project, configure the Linker and Compiler to match your OpenCV folder.

For compiling with G++ (Considering the OpenCV 3.4 and folders `C:\opencv\install\include` & `C:\opencv\install\x64\mingw\lib`):

* `git clone`

* `cd KMeansDemo\src`

* `g++ "-IC:\\opencv\\install\\include" -O0 -g3 -Wall -c -fmessage-length=0 -o "src\\KMeansDemo.o" "..\\src\\KMeansDemo.cpp"`

* `g++ "-LC:\\opencv\\install\\x64\\mingw\\lib" -o KMeansDemo.exe "src\\KMeansDemo.o" -lopencv_core340 -lopencv_highgui340 -lopencv_imgcodecs340 -lopencv_imgproc340`

* `.\KMeansDemo` 

* Insert the name of the image you want to see being processed by `cv::kmeans()` and choose the number of clusters using the Trackbar on top.

# Screenshot
![Screenshot](https://i.imgur.com/3HUSlc6.png)