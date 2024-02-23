from PIL import Image
from reportlab.pdfgen import canvas

# 打开png图像
img = Image.open(r"F:/test/cmake_project/src/python_test/qr_code.png")

# 将图像转换为PDF
c = canvas.Canvas(r"F:/test/cmake_project/src/python_test/qr_code.pdf")
c.drawInlineImage(img, 0, 0, width=img.width, height=img.height)
c.showPage()
c.save()
