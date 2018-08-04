#!/bin/bash

set -m

if [ -e "/mnt/dev/data/initialized" ]
then
    nodeos -e -p eosio -d /mnt/dev/data --config-dir /mnt/dev/config --hard-replay --http-validate-host=false --plugin eosio::wallet_api_plugin --plugin eosio::wallet_plugin --plugin eosio::producer_plugin --plugin eosio::history_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --plugin eosio::http_plugin --http-server-address=0.0.0.0:8888 --access-control-allow-origin=* --contracts-console
else
    nodeos -e -p eosio -d /mnt/dev/data --config-dir /mnt/dev/config --http-validate-host=false --plugin eosio::wallet_api_plugin --plugin eosio::wallet_plugin --plugin eosio::producer_plugin --plugin eosio::history_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --plugin eosio::http_plugin --http-server-address=0.0.0.0:8888 --access-control-allow-origin=* --contracts-console &

    sleep 5s
      until curl localhost:8888/v1/chain/get_info
    do
      sleep 5s
    done
    touch /mnt/dev/data/initialized
    
    cleos wallet list

    cleos wallet create -n eosiomain | tail -1 | sed -e 's/^"//' -e 's/"$//' > eosiomain_wallet_password.txt
    cleos wallet import -n eosiomain --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3

    cleos wallet list
    cleos wallet list
    sleep 5s
    cleos wallet list

    cleos wallet create |  tail -1 | sed -e 's/^"//' -e 's/"$//' > default_wallet_password.txt
    cleos wallet import --private-key 5KPMYCJoskqaaniDiBA4x5ZHCMPFAggE3rLa4jytBByBhc2jYTZ
    cleos wallet import --private-key 5KgUkmgSy4XGqjsL7Uc6XjeZUau1LdDqfinKsvjY8LfeftCuenM

    cleos create account eosio fadmin EOS7dD59Df7y5S9kbMFPD4bwGNCWq9dv7GTqcBRjf83K7JkXwx2zd EOS57MDZYUBGfDTBYeCJ8qPsJ7NXQ68ur2uw22ksP7NpoAp9FTrYZ
    cd /work/farmville
    eosiocpp -o farmville.wast farmville.cpp
    eosiocpp -g farmville.abi farmville.cpp
    cd ..
    cleos set contract fadmin farmville

    fg
fi
