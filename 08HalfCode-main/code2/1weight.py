word = {}
with open("sg（原文）.txt", "r", encoding="utf-8") as f:
    words = f.readlines()

for i in words:
    for j in i:
        if j not in word.keys():
            word[j] = 1
        else:
            word[j] += 1
print(word)


with open("文件路径", "w", encoding="utf-8") as p:
    for key, value in word.items():
        p.write(f'{key}\t{value}\n')
