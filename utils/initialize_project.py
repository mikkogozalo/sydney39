#!/usr/bin/python3
import os
from time import sleep
print('Creating farmville username')
print('Create tiles')
sleep(2)
os.system("""cleos push action fadmin tilecreate '["fadmin", 1, 0, 0]' -p fadmin""")
for i in range(1, 4):
    for j in range(1, 4):
        os.system("""cleos push action fadmin tilecreate '["fadmin", 1, {}, {}]' -p fadmin""".format(i, j))