import subprocess
def check(expr, result):
    out = subprocess.run(['./alloc', *expr], 
        stdout = subprocess.PIPE)

    if out.stdout.decode('ascii') != result:
        print('error {0} !-> {1}, got {2}'.format(expr,
         result, out.stdout))
    else:
        print('ok: {0} = {1}'.format(expr, result))

check(['0', 'alloc', '5'], 'Failed to allocate memory\n')
