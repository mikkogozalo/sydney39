#!/usr/bin/python3
import os
print('Create sample seeds')
for seed_name in ['apple', 'carrot', 'lettuce']:
	os.system("""cleos push action fadmin seedcreate '["fadmin", "{}"]' -p fadmin""".format(seed_name))