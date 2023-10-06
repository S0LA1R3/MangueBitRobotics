import cv2
import pytesseract
import numpy as np
import time
import serial

def detect_color(frame, lower_bound, upper_bound, color_name):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    
    mask = cv2.inRange(hsv, lower_bound, upper_bound)

    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    max_contour = max(contours, key=cv2.contourArea, default=None)
    
    if max_contour is not None:
    	if color_name == "Vermelho":
    		ser.write("3".encode())
    	elif color_name == "Verde":
    		ser.write("4".encode())
    	elif color_name == "Amarelo":
    		ser.write("5".encode())


ser = serial.Serial('/dev/ttyACM1', 9600)
time.sleep(2)
print('comunicação serial ativada!')
cap = cv2.VideoCapture(0)

while True:
    ret, frame = cap.read()

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    val, otsu = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY | cv2.THRESH_OTSU)

    text = pytesseract.image_to_string(otsu, config='--psm 6')

    resultado = ''
    if 'h' in text.lower():
        resultado += '0'
    
    if 's' in text.lower():
        resultado += '1'

    if 'u' in text.lower():
        resultado += '2'

    if resultado != '':
        ser.write(resultado.encode())
    lower_red = np.array([0, 100, 100])
    upper_red = np.array([10, 255, 255])
    detect_color(frame, lower_red, upper_red, "Vermelho")

    lower_green = np.array([35, 100, 100])
    upper_green = np.array([85, 255, 255])
    detect_color(frame, lower_green, upper_green, "Verde")

    lower_yellow = np.array([20, 100, 100])
    upper_yellow = np.array([40, 255, 255])
    detect_color(frame, lower_yellow, upper_yellow, "Amarelo")

cap.release()
ser.close()
