#! /usr/bin/python3
import sys
from subprocess import Popen, PIPE
tests = [
    ('1+2', 3),
    ('2*3', 6),
    ('1*2+3', 5),
    ('-1+3-2', 0),
    ('1-2-', None),
    ('1--1', 2),
    ('-1', -1),
    ('-  1', -1)
]

failed_count = 0
for i, (test, expected) in enumerate(tests):
    process = Popen(['./parse', test], stdout=PIPE)
    output, error = process.communicate()
    output = output.decode().strip()
    if expected == None and error != 0 or expected != None and output == str(expected):
        pass
    else:
        print('Test no %d failed: %s' % (i, test))
        failed_count += 1

if failed_count == 0:
    print('All test passed: %d' % len(tests))
else:
    exit(1)
