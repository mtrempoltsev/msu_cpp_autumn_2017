#! /usr/bin/python3
from subprocess import Popen, PIPE, DEVNULL
tests = [
    ('1+2', '3'),
    ('2*3', '6'),
    ('1*2+3', '5'),
    ('-1+3-2', '0'),
    ('1-2-', None),
    ('1--1', '2'),
    ('-1', '-1'),
    ('20/2', '10'),
    ('-  1', '-1'),
    ('1/0', None),
    (str(2**32), None),
    ('Pi + 2', '5'),
    ('1+2*(3-1)', '5'),
    ('1+2*(3', None),
    ('fedor', None),
    ('(2 / 0)', None)
]

failed_count = 0
for i, (test, expected) in enumerate(tests):
    process = Popen(['./calc', test], stdout=PIPE, stderr=DEVNULL)
    output, error = process.communicate()
    output = output.decode().strip()
    if expected == None and error != 0 or expected != None and output == expected:
        pass
    else:
        print('Test no %d failed: %s, (%s, %s)' % (i, test, output, expected))
        failed_count += 1

if failed_count == 0:
    print('All test passed: %d' % len(tests))
else:
    exit(1)
