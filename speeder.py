import time

def log(s):
    print(s)
    L.write(s)
    L.write('\n')

CNT = 1000      # number of runs

L = open('speeder.log', 'a')

m0, m1, s = 100_000_000., -1, 0    # min, max, total

log(f'{"min":^19} | {"max":^19} | {"avg":^19} | step')

for r in range(CNT):
    t = time.time()
    a, b, c, d = 1, 0, 1.1, 1.01
    for i in range(50000):
        a = (a * 123_456_789) % 987_654_321
        if a % 2: b = b + 1
        c = c / d
        if c < 0.1: d = 0.99
        if c > 9.9: d = 1.01
    t = time.time() - t
    s = s + t
    if t < m0: m0 = t
    if t > m1: m1 = t

    log(f'{m0:19.15f} | {m1:19.15f} | {s/(r+1):19.15f} | {r+1}')

open('finetest.py', 'a').write(f'SCALE = {(s-m0-m1) / (CNT-2) * 100}\n')