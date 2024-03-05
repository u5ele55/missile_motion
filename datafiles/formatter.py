
def erase(str):
    res = ""
    for line in str.split('\n'):
        res += line.split('-')[0].strip() + '\n'
    return res

toProcess = {
    "missile.txt": "parameters/missile.txt",
    "shot.txt": "parameters/launch.txt"
}

for filename in toProcess:
    outputFile = toProcess[filename]
    with open(filename, 'r', encoding='1251') as file:
        content = erase(file.read())
    with open(outputFile, 'w') as file:
        file.write(content)
