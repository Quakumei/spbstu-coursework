import cv2 as cv2
import sys

capture = cv2.VideoCapture(0)
if not capture.isOpened():
    print("Cannot open camera")
    sys.exit(1)

cv2.namedWindow("camera", cv2.WINDOW_AUTOSIZE)
while True:
    ret, frame = capture.read()
    if frame is None:
        print("frame is None")
        sys.exit()
    cv2.imshow("camera", frame)
    # Wait for "ESC"
    c = cv2.waitKey(33)
    if c == 27:
        break

capture.release()
cv2.destroyAllWindows()