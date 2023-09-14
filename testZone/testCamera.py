import cv2
import pytesseract
import numpy as np

def detect_color(frame, lower_bound, upper_bound, color_name):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    mask = cv2.inRange(hsv, lower_bound, upper_bound)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    max_contour = max(contours, key=cv2.contourArea, default=None)
    
    if max_contour is not None:
        x, y, w, h = cv2.boundingRect(max_contour)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        cv2.putText(frame, color_name, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)

cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    val, otsu = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV | cv2.THRESH_OTSU)
    erode = cv2.erode(otsu, np.ones((5, 5), np.uint8))

    text = pytesseract.image_to_string(erode, config='--psm 6')

    if 'r' in text.lower():
        cv2.putText(frame, 'r', (0, 30), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (255, 0, 0), 2)
    
    if 'g' in text.lower():
        cv2.putText(frame, 'g', (0, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)

    if 'b' in text.lower():
        cv2.putText(frame, 'b', (0, 90), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 2)

    lower_red = np.array([0, 100, 100])
    upper_red = np.array([10, 255, 255])
    detect_color(frame, lower_red, upper_red, "Vermelho")

    lower_green = np.array([35, 100, 100])
    upper_green = np.array([85, 255, 255])
    detect_color(frame, lower_green, upper_green, "Verde")

    lower_blue = np.array([90, 100, 100])
    upper_blue = np.array([140, 255, 255])
    detect_color(frame, lower_blue, upper_blue, "Azul")

    cv2.imshow('Camera', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
