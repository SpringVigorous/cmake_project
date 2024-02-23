from PIL import Image

def image_to_maze(image_path):
    # 打开图像文件
    img = Image.open(image_path).convert('1')  # 转换为1位黑白图像模式

    # 获取图像尺寸
    width, height = img.size

    data=img.tobytes()
    print(len(data))
    # 将图像数据转化为二维数组
    maze = [[]] 
    #[[int(pixel) for pixel in row] for row in img.tobytes()]

    return maze

# 使用函数读取并解析迷宫图
maze_data = image_to_maze(r"F:/test/cmake_project/src/python_test/qr_code.png")

# 输出结果
