#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
using namespace eosio;
using std::string;

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

    /// @abi table seeds i64
    struct seed {
      uint64_t      id;
      string        name;

      uint64_t primary_key() const { return id; }
    };

    typedef eosio::multi_index<
            N(seeds), 
            seed
            > seeds;

    seeds _seeds;

  public:
    using contract::contract;

    farmville(account_name a):
        contract(a),
        _tiles(a, a),
        _seeds(a, a)
    {}
    
    /// @abi action
    void tilecreate(account_name _user, uint64_t _rate, uint64_t _x, uint64_t _y) {
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
    void tileupdate(account_name _user, uint64_t id, uint64_t _rate, uint64_t _x, uint64_t _y) {
      require_auth( _user );

      auto itr = _tiles.find(id);
      _tiles.modify(itr, get_self(), [&](auto& p) {
          print(p.x , ", " , p.y , ", " , p.rate);
          p.x = _x;
          p.y = _y;
          p.rate = _rate;
      });
    };

    /// @abi action
    void seedcreate(account_name _user, std::string _name) {
      require_auth(_user);

      print("wooo seeeeed");
      _seeds.emplace(get_self(), [&](auto& p) {
        p.id = _seeds.available_primary_key();
        p.name = _name;
        print("hahaha");
      });
    }

    /// @abi action
    void seedupdate(account_name _user, uint64_t id, std::string _name) {
      require_auth( _user );

      auto itr = _seeds.find(id);
      _seeds.modify(itr, get_self(), [&](auto& p) {
          print(p.name);
          p.name = _name;
      });
    };

    
    void donothing(account_name _user){

    }
};

EOSIO_ABI( farmville, (tileupdate)(tilecreate)(donothing)(seedcreate)(seedupdate) )
// EOSIO_ABI( farmville, (tileupdate)(tilecreate)(donothing) )

