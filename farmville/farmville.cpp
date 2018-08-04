#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace eosio;

class farmville : public eosio::contract {
  private:
    
    /// @abi table tiles i64
    struct tile {
      uint64_t      id;
      account_name  owner;
      uint64_t      rate;
      uint64_t      x;
      uint64_t      y;

      uint64_t primary_key() const { return id; }
      account_name get_by_owner() const { return owner; }
    };

    typedef eosio::multi_index<
            N(tiles), 
            tile,
            indexed_by< N(byowner), const_mem_fun<tile, account_name, &tile::get_by_owner> >
            > tiles;

    tiles _tiles;

  public:
    using contract::contract;

    farmville(account_name a):
        contract(a),
        _tiles(a, a)
    {}
    
    /// @abi action
    void create(account_name _user, uint64_t _rate, uint64_t _x, uint64_t _y) {
      // require_auth(_user);
      print("wooo");
      _tiles.emplace(get_self(), [&](auto& p) {
        p.id = _tiles.available_primary_key();
        p.owner = _user;
        p.rate = _rate;
        p.x = _x;
        p.y = _y;
        print("hohoho");
      });
    }

    /// @abi action
    void update(account_name _user, uint64_t id, uint64_t _rate, uint64_t _x, uint64_t _y) {
      require_auth( _user );

      auto itr = _tiles.find(id);
      _tiles.modify(itr, get_self(), [&](auto& p) {
          print(p.x , ", " , p.y , ", " , p.rate);
          p.x = _x;
          p.y = _y;
          p.rate = _rate;
      });
    };

    void donothing(account_name _user){

    }
};

EOSIO_ABI( farmville, (update)(create)(donothing) )

