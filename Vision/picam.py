import sys
sys.path.append('/usr/local/lib/python3.2/site-packages')

import io
import time
from picamera import PiCamera
from picamera.array import PiRGBArray
import cv2
import numpy as np


camera = PiCamera()
camera.resolution = (640, 480)
camera.framerate = 32
rawCapture = PiRGBArray(camera, size=(640, 480))

time.sleep(1)

for frame in camera.capture_continuous(rawCapture, format="bgr", use_video_port=True):

    #immediate frame from the video stream
    image = frame.array

    #actual image stuff
    blur = cv2.blur(image, (3,3))
    
    lower = np.array([76, 31, 4], dtype="uint8")
    upper = np.array([210, 90, 70], dtype="uint8")

    thresh = cv2.inRange(blur, lower, upper)
    thresh2 = thresh.copy()

    image, contours, hierarchy = cv2.findContours(thresh, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

    max_area = 0
    best_contour = 1

    for contour in contours:
        area = cv2.contourArea(contour)
        if area > max_area:
            max_area = area
            best_contour = contour

    M = cv2.moments(best_contour)
    cx, cy = int(M['m10']/M['m00']), int(M['m01']/M['m00'])

    cv2.circle(blur, (cx, cy), 10, (0, 0, 255), -1)

    
    ###########

    #cv2.imshow("Frame", blur) #displays the image
    cv2.imshow("Frame - Threshold", thresh2)
    #cv2.imshow("frame", image) #shows contours
    cv2.startWindowThread() #has to be used in order to actually close the window
    key = cv2.waitKey(1) & 0xFF #has to be used in conjunction with imshow, to close window
    
    rawCapture.seek(0) #goes to the first image in the array
    rawCapture.truncate(0) #deletes previously seen image

    #closes the program when you hit q
    if key == ord("q"):
        cv2.destroyAllWindows()
        break

    #actual image stuff
    
