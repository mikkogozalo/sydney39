#!/usr/bin/python3
import os
print('Creating farmville username')
print('Create tiles')
for i in range(1, 4):
    for j in range(1, 4):
        os.system("""cleos push action fadmin tilecreate '["fadmin", 1, {}, {}]' -p fadmin""".format(i, j))