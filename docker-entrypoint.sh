#!/bin/bash

set -m

if [ -e "/mnt/dev/data/initialized" ]
then
    nodeos -e -p eosio --plugin eosio::wallet_api_plugin --plugin eosio::wallet_plugin --plugin eosio::producer_plugin --plugin eosio::history_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --plugin eosio::http_plugin -d /mnt/dev/data --config-dir /mnt/dev/config --http-server-address=0.0.0.0:8888 --access-control-allow-origin=* --contracts-console --hard-replay --http-validate-host=false
else
    nodeos -e -p eosio --plugin eosio::wallet_api_plugin --plugin eosio::wallet_plugin --plugin eosio::producer_plugin --plugin eosio::history_plugin --plugin eosio::chain_api_plugin --plugin eosio::history_api_plugin --plugin eosio::http_plugin -d /mnt/dev/data --config-dir /mnt/dev/config --http-server-address=0.0.0.0:8888 --access-control-allow-origin=* --contracts-console --hard-replay --http-validate-host=false --delete-all-blocks &

    sleep 1s
      until curl localhost:8888/v1/chain/get_info
    do
      sleep 10s
    done
    echo "hhhhh"
    touch /mnt/dev/data/initialized
    
    cleos wallet list

    cleos wallet create -n eosiomain | tail -1 | sed -e 's/^"//' -e 's/"$//' > eosiomain_wallet_password.txt
    cleos wallet import -n eosiomain --private-key 5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3

    cleos wallet list

    ps
    fg
fi
