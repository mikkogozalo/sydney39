#!/usr/bin/python3
import os
import time
print('')
for seed_name in ['lemon', 'carrot', 'lettuce']:
	os.system("""cleos push action fadmin seedcreate '["fadmin", "{}"]' -p fadmin""".format(seed_name))
	time.sleep(0.5)