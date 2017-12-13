#! /usr/bin/env python3
import sys
from subprocess import call
from subprocess import Popen, PIPE, call

fn_prog_compiled = './calc'
fn_type_definer = 'type_definer.hpp'
type_definer_line = '#define CALC_TYPE {}\n'

test_types = [
    'int',
    'long',
    'double',
]
# 9223372036854775807
valid_tests = {
    'int': {
        '214748364': 214748364,
        '2 / 3': 0,
        '3 / 2': 1,

    },
    'long': {
        '922337203685477580': 922337203685477580,
        '2 / 3': 0,
        '3 / 2': 1,

    },
    'double': {
        '(3-2) - (4/2)': -1,
        'Pi + e': 5.84,
        'e + Pi': 5.84,
        'e+1': 3.7,
        '2+         Pi': 5.14,
        '2+2': 4,
        '2+ 2': 4,
        '2 +2': 4,
        '2 + 2': 4,
        '2 +   2': 4,
        '2': 2,
        '-2': -2,
        '-2 - 2': -4,
        '2 -2': 0,
        '2 - -2': 4,
        '100 + 1': 101,
        '101 + 1': 102,
        '8 - 6 * 2 / 2': 2,
        '8 - 6 / 2 * 2': 2,
        '8 - 6 / 2 * -2': 14,
        '2 + 3 * 4 - -2': 16,
        '2*-2': -4,
        '4*(-3)': -12,
        '(3)+4': 7,
        '(3)*4': 12,
        '(5 + 3 * (8 / Pi) * 4) + (1)': 36.5732,
    }
}
invalid_tests = {
    'int': [
        '2147483649',
    ],
    'long': [
        '9223372036854775800',
    ],
    'double': [
        '2 -+ 2',
        '2 ++ 2',
        '2 c 2',
        '2 2',
        '1.5 + 1.5',
        '2*+2',
        '2+*2',
        '(',
        ')',
        '()',
        '((2)',
        '(2))',
        ')(2)(',
        ')(2',
        '(-2)(3)',
        '(2)(+3)',
        '(2)-+(3)',
    ]
}

all_passed = True

for test_type in test_types:
    print('for type \'{}\''.format(test_type))
    with open(fn_type_definer, 'w') as f:
        f.write(type_definer_line.format(test_type))
    call(["make"])
    for test in valid_tests[test_type]:
        p = Popen([fn_prog_compiled, test], stdin=PIPE, stdout=PIPE, stderr=PIPE)
        output, err = p.communicate(b'input data that is passed to subprocess stdin')
        rc = p.returncode
        res = output.decode('utf-8')[:-1]
        if res == str(valid_tests[test_type][test]):
            print('OK', test)
        else:
            print('FAIL', test)
            print('got', res, 'should be', valid_tests[test_type][test])
            all_passed = False

        print('---')

    print('invalids')
    for test in invalid_tests[test_type]:
        p = Popen([fn_prog_compiled, test], stdin=PIPE, stdout=PIPE, stderr=PIPE)
        output, err = p.communicate(b'input data that is passed to subprocess stdin')
        rc = p.returncode
        res = output.decode('utf-8')[:-1]
        if rc != 0:
            print('OK', test)
        else:
            print('FAIL', test)
            print('got', res)
            all_passed = False

        print('---')

if all_passed:
    print('+ Every test passed')
else:
    print('- Tests failed')
