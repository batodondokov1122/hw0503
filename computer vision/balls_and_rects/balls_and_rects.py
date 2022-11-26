import matplotlib.pyplot as plt
import numpy as np
from skimage.measure import label, regionprops
from skimage.morphology import binary_erosion, binary_dilation, binary_closing
from skimage.filters import threshold_otsu, sobel
from skimage import color

def recognize(im_region): # Распознавание круга и прямоугольника
    if np.mean(im_region.image) == 1.0:
        return "rect"
    else:
        return "ball"

def split_into_groups(sorted_colors): # Разбиение оттенков по группам
    groups = [[sorted_colors[0]],]
    delta = np.max(np.diff(sorted_colors))/2
    for i in range(1, len(sorted_colors)):
        previous = sorted_colors[i-1]
        current = sorted_colors[i]
        if current - previous > delta:
            groups.append([])
        groups[-1].append (current)
    return groups

def make_colors_dict(groups): # создание словаря оттенков
    result={}
    for grp in groups:
        result[np.mean(grp)] = len(grp)
    return result
    
image_name = "balls_and_rects.png"
im = plt.imread(f"D:\images\{image_name}")

hsv = color.rgb2hsv(im)

binary = hsv[ : , : , 0].copy()
binary[binary > 0] = 1
labeled = label(binary)

regions = regionprops(labeled)

balls_colors = []
rects_colors = []

for reg in regions:
    cy, cx = reg.centroid
    if recognize(reg) == "rect":
        rects_colors.append(hsv[int(cy),int(cx),0])
    else:
        balls_colors.append(hsv[int(cy),int(cx),0])

rects_colors = sorted(rects_colors)
balls_colors = sorted(balls_colors)

rects_groups = split_into_groups(rects_colors)
balls_groups = split_into_groups(balls_colors)

rects_result = make_colors_dict(rects_groups)
balls_result = make_colors_dict(balls_groups)

print(f"Общее количество фигур - {labeled.max()}")
print("\nКолличество прямоугольников по оттенкам: ")
for key in rects_result:
    print(f"Оттенок ({key}) - {rects_result[key]}")
print("\nКолличество кругов по оттенкам: ")
for key in balls_result:
    print(f"Оттенок ({key}) - {balls_result[key]}")

plt.imshow(labeled)
plt.show()