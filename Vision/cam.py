#Test script for regular USB webcam.
#Will not work with the Raspberry Pi camera
#Using python2.7 bindings, should also work with Python3.

#Installing OpenCV and running the script should open three windows
#
#The regular window with the target outlined and the centroid marked
#The contours window
#The threshold window

import sys
sys.path.append('/usr/local/lib/python2.7/site-packages')

import numpy as np
import cv2

cap = cv2.VideoCapture(0)

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    #color range in bgr or rgb, I forget
    lower = np.array([76, 31, 4], dtype="uint8")
    upper = np.array([210, 90, 70], dtype="uint8")

    blur = cv2.blur(frame, (3,3)) #blured image to make the threshold neater
    thresh = cv2.inRange(blur, lower, upper) #the thresholded image
    cntrs = thresh.copy() #copy of the threshold frame to be changed to contours

    #Finds contours for the cntrs frame
    contours, hierarchy = cv2.findContours(cntrs, cv2.RETR_LIST, cv2.CHAIN_APPROX_SIMPLE)

    max_area = 0
    best_contour = 1
    #basically finds the thing taking up the most room in the threshold
    for contour in contours:
        area = cv2.contourArea(contour) ##finds biggest area inside a contour
        if area > max_area:
            max_area = area
            best_contour = contour
            rect = cv2.boundingRect(best_contour)
            x,y,w,h = rect
            cv2.rectangle(blur,(x,y),(x+w,y+h),(0,255,0),2)

    #draws rectangle
    #print(best_contour)
    '''
    rect = cv2.boundingRect(best_contour)
    x,y,w,h = rect
    cv2.rectangle(blur,(x,y),(x+w,y+h),(0,255,0),2)
    '''

    #draws circle at center
    M = cv2.moments(best_contour)
    cx, cy = int(M['m10']/M['m00']), int(M['m01']/M['m00'])
    cv2.circle(blur, (cx, cy), 10, (0, 0, 255), -1)

    #print(str(relative)) #prints location of centroid to the console
    #cv2.putText(blur, (0, 50), (x,y), cv2.FONT_HERSHEY_SIMPLEX, 2, 255)
    #draws text, displays current x coord relative to the center of the frame
    '''
    resHeight, resWidth = frame.shape[:2]
    resCenter = int(resWidth/2)
    relative = int(cx-resCenter)
    cv2.putText(blur, str(relative), (x,y), cv2.FONT_HERSHEY_SIMPLEX, 2, 255)
    '''
    #move towards center
    #if relative > 0:
    #    #go left
    #else:
    #    #go right


    #shows all the frames/windows
    cv2.imshow('frame', blur)
    cv2.imshow('threshold', thresh)
    cv2.imshow('contours', cntrs)

    key = cv2.waitKey(1) & 0xFF

    if key == ord("q"):
        cv2.destroyAllWindows()
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
