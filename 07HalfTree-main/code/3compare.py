import turtle as t
t.hideturtle()

def move(x, y):
    t.pu()
    t.goto(x, y)
    t.pd()


def draw_square():
    for i in range(2):
        t.fd(20)
        t.left(90)
        t.fd(40)
        t.left(90)
        t.fd(20)


def draw_line(x, y, r, angle):
    a = t.pos()[0]
    b = t.pos()[1]
    t.pu()
    t.seth(angle)
    t.fd(r)
    t.pd()
    t.fd(pow((x - a) * (x - a) + (y - b) * (y - b), 0.5) - r)
    move(a, b)
    t.seth(0)


def read_input():  # 读取输入
    f = input('输入字母及其权重(用英文逗号隔开)：\n')  # A,3,B,14,C,8,D,7,E,8
    a = f.split(',')
    return a


def begin(n, str):
    A = []
    k = 2 * n - 1
    for i in range(k):  # 初始化struct 放入循环内以便生成新的struct地址
        struct = ['', 0, -1, -1, -1, 0]  # 名称，权重，上级节点，下级节点
        struct[5] = i
        A.append(struct)
    for j in range(n):
        A[j][0] = str[2 * j]
        A[j][1] = int(str[2 * j + 1])
    return A


def compare_connect(A, n):
    for j in range(n - 1):
        compare = []
        for i in range(n + j):
            if A[i][2] == -1:
                compare.append(A[i])
        compare = sorted(compare, key=lambda x: x[1], reverse=False)  # key用lambda函数表示,排序
        A[n + j][0] = compare[0][0] + compare[1][0]  # 名称
        A[n + j][1] = compare[0][1] + compare[1][1]  # 权重
        A[n + j][3] = compare[0][5]  # 左子节点
        A[n + j][4] = compare[1][5]  # 右子节点
        A[compare[0][5]][2] = n + j  # 左子的父节点
        A[compare[1][5]][2] = n + j  # 右子的父节点
    return A


def draw_tree(A, a, x, y, n):
    move(x, y - 15)
    t.write(a[1], align='center', font=('宋体', 15, 'normal'))
    move(x, y - 30)
    if len(a[0]) == 1:
        t.circle(30)
    else:
        draw_square()
    move(x, y - 50)
    t.write(a[0], align='center', font=('宋体', 15, 'normal'))
    move(x, y)
    if n  == 0:
        n += 1
        if a[3] != -1:
            draw_line(x - 120, y - 80, 30, -150)
        if a[4] != -1:
            draw_line(x + 120, y - 80, 30, -30)

        if a[3] == -1 or a[4] == -1:
            return
        draw_tree(A, A[a[3]], x - 120, y - 80-20, n)
        draw_tree(A, A[a[4]], x + 120, y - 80-20, n)
    else:
        n += 1
        if a[3] != -1:
            draw_line(x - 80, y - 120, 30, -120+n)
        if a[4] != -1:
            draw_line(x + 80, y - 120, 30, -60-n)

        if a[3] == -1 or a[4] == -1:
            return
        draw_tree(A, A[a[3]], x - 80, y - 120-20, n)
        draw_tree(A, A[a[4]], x + 80, y - 120-20, n)


# ---------------主函数--------------
strs = read_input()
n = int(len(strs) / 2)
# print(strs, n)  # -----------检测

A = begin(n, strs)  # 初始的数列
# print(A)  # ----------检测
# -------------------------------
A = compare_connect(A, n)
# print(A)
t.tracer(0)
draw_tree(A, A[2 * n - 2], 0, 300,0)
t.tracer(1)
t.done()
