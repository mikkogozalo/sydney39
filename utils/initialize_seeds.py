#!/usr/bin/python3
import os
print('Create sample seeds')
for seed_name in ['strawberry', 'pepper', 'thyme']:
	os.system("""cleos push action fadmin seedcreate '["fadmin", "{}"]' -p fadmin""".format(seed_name))