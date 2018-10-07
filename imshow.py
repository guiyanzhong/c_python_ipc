import cv2
import numpy as np
import sysv_ipc

# Read image data from shared memory.
memory = sysv_ipc.SharedMemory(123456)
data = memory.read()

# Construct image using numpy.
frame = np.frombuffer(data, 'uint8')
width = 640
height = 424
shape = (height, width, 3)
strides = (width * 3, 3, 1)
frame = np.lib.stride_tricks.as_strided(frame, shape, strides)

# Show the image using OpenCV.
cv2.imshow('image from shared memory', frame)
cv2.waitKey()
cv2.destroyAllWindows()
