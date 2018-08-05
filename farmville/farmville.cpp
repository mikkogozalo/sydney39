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
      bool          is_occupied;

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

    /// @abi table rents i64
    struct rent {
      uint64_t       id;
      uint64_t       tile;
      uint64_t       seed;
      account_name   renter;

      uint64_t primary_key() const { return id; }
      account_name get_by_renter() const { return renter; }
      uint64_t get_by_tile() const { return tile; };

    };

    typedef eosio::multi_index<
      N(rents),
      rent,
      indexed_by< N(byrenter), const_mem_fun<rent, account_name, &rent::get_by_renter> >,
      indexed_by< N(bytile), const_mem_fun<rent, account_name, &rent::get_by_tile> >
    > rents;

    rents _rents;

    /// @abi table rentstatuses
    struct rentstatus {
      uint64_t       id;
      uint64_t       rent;
      string         status;
      uint64_t       timestamp;

      uint64_t primary_key() const { return id; }
      uint64_t get_by_rent() const { return rent; }

    };

    typedef eosio::multi_index<
      N(rentstatuses),
      rentstatus,
      indexed_by< N(byrent), const_mem_fun<rentstatus, account_name, &rentstatus::get_by_rent> >
    > rentstatuses;

    rentstatuses _rentstatuses;



  public:
    using contract::contract;

    farmville(account_name a):
        contract(a),
        _tiles(a, a),
        _seeds(a, a),
        _rents(a, a),
        _rentstatuses(a, a)
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
        p.is_occupied = 0;
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
    void tilegetall(account_name _user) {
      auto itr = _tiles.begin();
      while (itr != _tiles.end()) {
        print(itr->id, "|||", name{itr->owner}, "|||", itr->rate, "|||", itr->x, "|||", itr->y, "|||", itr->is_occupied, "+++");
        itr++;
      }
    }

    /// @abi action
    void tileget(account_name _user, uint64_t id) {
      auto itr = _tiles.find(id);
      eosio_assert(itr != _tiles.end(), "Tile not in database");
      print(itr->id, "|||", name{itr->owner}, "|||", itr->rate, "|||", itr->x, "|||", itr->y, "|||", itr->is_occupied);
    }

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

    /// @abi action
    void seedgetall(account_name _user) {
      auto itr = _seeds.begin();
      while (itr != _seeds.end()) {
        print(itr->id, "|||", itr->name, "+++");
        itr++;
      }      
    }

    /// @abi action
    void seedget(account_name _user, uint64_t id) {
      auto itr = _seeds.find(id);
      eosio_assert(itr != _seeds.end(), "Seed not in database");
      print(itr->id, "|||", itr->name);

    }

    /// @abi action
    void rentcreate(account_name _user, uint64_t tile, uint64_t seed) {
      require_auth(_user);
      uint64_t blah_id;
      _rents.emplace(get_self(), [&](auto& p) {
        p.id = _rents.available_primary_key();
        blah_id = p.id;
        p.tile = tile;
        p.seed = seed;
        p.renter = _user;
        print("hahaha");
      });
      auto itr = _tiles.find(tile);
      _tiles.modify(itr, get_self(), [&](auto& p) {
        p.is_occupied = 1;
      });
      _rentstatuses.emplace(get_self(), [&](auto &q) {
        q.id = _rentstatuses.available_primary_key();
        q.status = "seed";
        q.timestamp = now();
        q.rent = blah_id;
      });
    };

    /// @abi action
    void rentupdate(account_name _user, uint64_t rent, string message) {
      require_auth(_user);

      auto rent_itr = _rents.find(rent);
      eosio_assert(rent_itr != _rents.end(), "Rent not in database");
      
      // Create new rentstatus
      _rentstatuses.emplace(get_self(), [&](auto& p) {
        p.id = _rentstatuses.available_primary_key();
        p.rent = rent;
        p.status = message;
        p.timestamp = now();

      });

      if(message == "Harvested") {
        auto tile_itr = _tiles.find(rent_itr->tile);
        _tiles.modify(tile_itr, get_self(), [&](auto& p) {
          p.is_occupied = 0;
          print("Haha this become open");
        });
      }
    }

    /// @abi action
    void rentget(account_name _user, uint64_t rent) {
      auto itr = _rents.find(rent);
      eosio_assert(itr != _rents.end(), "Rent not in database");
      print(itr->id, "|||", itr->tile, "|||", itr->seed, "|||", name{itr->renter});
    }


    void rentgets(account_name _user, uint64_t rent) {
      auto rent_idx = _rentstatuses.template get_index<N(byrent)>();
      auto itr = rent_idx.find(rent);
      while(itr != rent_idx.end() && itr->rent == rent) {
        print(itr->id, "|||", itr->rent, "|||", itr->status, "|||", itr->timestamp, "+++");
        itr++;
      }
    }

    /// @abi action
    void rentgetuser(account_name _user) {
      auto account_index = _rents.template get_index<N(byrenter)>();
      auto itr = account_index.find(_user);
      while (itr != account_index.end() && itr->renter == _user) {
        print(itr->id, "|||", itr->tile, "|||", itr->seed, "|||", name{itr->renter}, "+++");
        itr++;
      }
    }

    /// @abi action
    void rentgettile(account_name _user, uint64_t tile) {
      auto account_index = _rents.template get_index<N(bytile)>();
      auto itr = account_index.find(tile);
      string a = "";
      while (itr != account_index.end() && itr->tile == tile) {
        a = std::to_string(itr->id) + "|||" + std::to_string(itr->tile) + "|||" + std::to_string(itr->seed) +  "|||" + name{itr->renter}.to_string();
        itr++;
      }
      print(a);
      ;
    }


    void donothing(account_name _user){

    }
};

EOSIO_ABI( farmville, (tileupdate)(tilecreate)(seedcreate)(seedupdate)(rentcreate)(rentupdate)(rentget)(rentgetuser)(tilegetall)(tileget)(seedgetall)(seedget)(rentgets)(rentgettile)(donothing))
// EOSIO_ABI( farmville, (tileupdate)(tilecreate)(donothing) )

