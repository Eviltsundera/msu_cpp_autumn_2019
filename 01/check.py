import subprocess
def check(expr, result):
    out = subprocess.run(['./calc', expr], 
        stdout = subprocess.PIPE)

    if out.stdout.decode('ascii') != result:
        print('error {0} != {1}, got {2}'.format(expr,
         result, out.stdout))
    else:
        print('ok: {0} = {1}'.format(expr, result))

check('2 + 2', '4\n')
check('3 + 23 * 2 - -2', '51\n')
check('1 23 + 15', 'BAD EXPRESSION\n')
check('40          * 40 / 20 + 92131', '92211\n')
check('50 * 140 + 32 / 0', 'DIVISION BY ZERO\n')
check('123 * 56 + 17 / 2 + -2 * 1500', '3896\n')
check('my jopa', 'chisto')