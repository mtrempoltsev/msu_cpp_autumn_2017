import codecs
import sys

data_path = sys.argv[1]

def data():
    with codecs.open(data_path, encoding="utf-8") as data_file:
        for line in data_file:
            punct = '.,!?:;-~#$%^&*()<>/\\[]{}"'
            s = line.replace("'", " ")
            for p in punct:
                s = s.replace(p, ' ')

            lst = s.strip().split()
            for l in lst:
                yield l

with codecs.open("input1.txt", "w", encoding='utf-8') as f:
    for a in data():
        f.write(a.lower())
        f.write(' ') 
