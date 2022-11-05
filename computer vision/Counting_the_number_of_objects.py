import matplotlib.pyplot as plt
import numpy as np
from skimage.measure import label
from skimage.morphology import binary_erosion, binary_dilation, binary_closing

image = np.load("D:\images\ps.npy.txt")

first_object_number = 0
second_object_number = 0

first_object_masks = np.array([[[1, 1, 1, 1], [1, 1, 1, 1], [0, 0, 1, 1], [0, 0, 1, 1], [1, 1, 1, 1], [1, 1, 1, 1]], # позиция 1 - объект из 20 пикселей повернут вправо 
                      [[1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1], [1, 1, 0, 0, 1, 1], [1, 1, 0, 0, 1, 1]], # позиция 2 - объект 20 пикселей повернут вниз 
                      [[1, 1, 0, 0, 1, 1], [1, 1, 0, 0, 1, 1], [1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1]], # позиция 3 - объект 20 пикселей повернут вверх 
                      [[1, 1, 1, 1], [1, 1, 1, 1], [1, 1, 0, 0], [1, 1, 0, 0], [1, 1, 1, 1], [1, 1, 1, 1]]], dtype=object)# позиция 4 - объект 20 пикселей повернут влево

second_object_mask = np.array([[1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1]], dtype=object) # объект прямоугольник 24 пикселя (6 * 4)

second_object_erased = binary_erosion(image, second_object_mask)
second_object_labeled = label(second_object_erased)
second_object_number += second_object_labeled.max()

for i in range(0, len(first_object_masks)):
    if i in [1,2]:
        first_object_erased = binary_erosion(image, first_object_masks[i])
        first_object_labeled = label(first_object_erased)
        print (f"Количество объектов первого вида {i+1} позиции: {first_object_labeled.max() - second_object_number}") # на вторую и третью маску первого объекта он находит и второй объект тоже поэтому отнимаю его количество
        first_object_number += first_object_labeled.max() - second_object_number
    else:
        first_object_erased = binary_erosion(image, first_object_masks[i])
        first_object_labeled = label(first_object_erased)
        print (f"Количество объектов первого вида {i+1} позиции: {first_object_labeled.max()}")
        first_object_number += first_object_labeled.max()

print (f"Общее количество объектов первого вида: {first_object_number}")
print (f"Количество объектов второго вида: {second_object_number}")
print (f"Общее количество объектов: {first_object_number + second_object_number}")

plt.imshow(image)
plt.show()

# output
# Количество объектов первого вида 1 позиции: 123
# Количество объектов первого вида 2 позиции: 96
# Количество объектов первого вида 3 позиции: 95
# Количество объектов первого вида 4 позиции: 94
# Общее количество объектов первого вида: 408
# Количество объектов второго вида: 92
# Общее количество объектов: 500