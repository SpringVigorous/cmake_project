import cv2
import numpy as np

print(cv2.__version__)

# 读取图像
image_path = r"F:/test/cmake_project/src/python_test/qr_code.png"
img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)

# 对图像进行阈值处理以实现二值化
threshold_value = 127
_, binary_img = cv2.threshold(img, threshold_value, 255, cv2.THRESH_BINARY)

# 将二值图像的像素值转换为0和1
binary_img_01 = (binary_img / 255).astype(np.uint8)

# 打印或操作0-1矩阵
#print(binary_img_01)

data_str= '\n'.join( [','.join(map(str, row))  for row in binary_img_01])

print(data_str)
# 如果需要进一步转换为二维列表以便于查看或操作
matrix_01_list = binary_img_01.tolist()

# 示例：检查前几行
# for row in matrix_01_list[:5]:
#     print(row,sep="")

input("等待")