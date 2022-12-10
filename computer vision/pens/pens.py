import os
import matplotlib.pyplot as plt
import numpy as np
import cv2

dir = "D:\images\pens"

image_names = os.listdir(dir) # Считываю названия всех изображений

allPensCount = 0

for image_name in image_names: # Считиваю каждое изображение в цикле
    pensCount = 0
    image = cv2.imread(f"{dir}\{image_name}")
    image = cv2.GaussianBlur(image, (25, 25), 0) # Делаю блюр, чтобы лучше определить контур
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY) # Убираю цвета
    tresh = cv2.threshold(gray, 130, 255, cv2.THRESH_BINARY_INV)[1] # Бинаризирую изображение
    contours = cv2.findContours(tresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0] # Нахожу все контуры
    for c in contours:   # Прохожусь по всем контурам
            perimeter = cv2.arcLength(c,True)
            if perimeter > 5000: # Подбираю подходяший периметр для карандаша
                area = cv2.contourArea(c)
                if area > 270000: # Подбираю подходяшую площадь для карандаша
                    x,y,w,h = cv2.boundingRect(c)
                    cv2.rectangle(image,(x,y), (x+w, y+h), (0,255,0),5) # Выделяю карандаш на изображении
                    pensCount += 1
                    
    print(f"Количество карандашей на изображении ({image_name}) = {pensCount}")
    allPensCount += pensCount
    
    image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
    plt.imshow(image,)
    plt.show()
    
print(f"Количество всех карандашей = {allPensCount}")