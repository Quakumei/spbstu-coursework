import cv2
import os
import sys

# Record video from camera to AVI file

# Prepare
if len(sys.argv) != 2:
    print("Usage: record_avi.py <filename>")
    sys.exit(1)

filename = sys.argv[1]
if os.path.exists(filename):
    print("File already exists")
    sys.exit(1)

capture = cv2.VideoCapture(0)
if not capture.isOpened():
    print("Cannot open camera")
    sys.exit(1)

# Get properties from camera
width = int(capture.get(cv2.CAP_PROP_FRAME_WIDTH))
height = int(capture.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps = capture.get(cv2.CAP_PROP_FPS)

# Define the codec and create VideoWriter object
fourcc = cv2.VideoWriter_fourcc(*"MJPG")
out = cv2.VideoWriter(filename, fourcc, fps, (width, height))

cv2.namedWindow("camera", cv2.WINDOW_AUTOSIZE)
while True:
    ret, frame = capture.read()
    if frame is None:
        print("frame is None")
        sys.exit()
    cv2.imshow("camera", frame)
    out.write(frame)
    # Wait for "ESC"
    c = cv2.waitKey(33)
    if c == 27:
        break

capture.release()
out.release()
cv2.destroyAllWindows()