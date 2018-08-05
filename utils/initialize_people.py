#!/usr/bin/python3
import os
import time
print('Create sample users')
with open('accounts.keys') as f:
	for _ in f:
		if not _:
			continue
		_ = _.split('\t')
		os.system("""cleos wallet import --private-key {}""".format(_[1]))
		os.system("""cleos wallet import --private-key {}""".format(_[3]))
		os.system("""cleos create account eosio {} {} {}""".format(_[0], _[2], _[4]))
		time.sleep(0.499)