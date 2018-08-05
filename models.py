from eosiopy.eosioparams import EosioParams
from eosiopy.nodenetwork import NodeNetwork
from eosiopy.rawinputparams import RawinputParams

keys = {
    'fadmin': '5KgUkmgSy4XGqjsL7Uc6XjeZUau1LdDqfinKsvjY8LfeftCuenM',
    'mikko': '5JXXgFJuziATxMxXC9nL4LNFwsday3mqCkhavUg56mSigx5EdPq',
    'sage': '5Ka64hLNPGy6V1RhigcLT7wiPCC6GgYERwWA37EY4XBhcC6VLbo',
    'alfred': '5JL65YSVdEgxDmZhgq4SBDQ5Wj9yHBLXbsY8MEpSoCm6YUFhuax',
    'vincent': '5KFhz3TWc8iLhoaATTEnU3cspjPZkAG3VfbhSjkNAHrEcQB2MYP'
}

U_ADMIN = 'fadmin'


class Rent(object):
    id = None
    tile = None
    seed = None
    renter = None

    @classmethod
    def deserialize(cls, text, fetch_tile=True):
        r = Rent()
        ordering = ['id', 'tile', 'seed', 'renter']
        values = text.split('|||')

        for k, v in zip(ordering, values):
            setattr(r, k, v)

        if fetch_tile:
            r.tile = Tile.get_tile(int(r.tile))
        r.seed = Seed.get_seed(int(r.seed))

        return r

    @classmethod
    def get_by_username(cls, username):
        raw = RawinputParams(
            "rentgetuser", {
                "_user": username
            }, "fadmin", "{}@active".format(username)
        )
        eosiop_arams = EosioParams(raw.params_actions_list, keys[username])
        net = NodeNetwork.push_transaction(eosiop_arams.trx_json)

        return [Rent.deserialize(_) for _ in net['processed']['action_traces'][0]['console'].split('+++') if _]


    @classmethod
    def get_by_tile(cls, tile, fetch_tile=True):
        raw = RawinputParams(
            "rentgettile", {
                "_user": U_ADMIN,
                "tile": int(tile)
            }, "fadmin", "{}@active".format(U_ADMIN)
        )
        eosiop_arams = EosioParams(raw.params_actions_list, keys[U_ADMIN])
        net = NodeNetwork.push_transaction(eosiop_arams.trx_json)
        print(net)
        return Rent.deserialize(net['processed']['action_traces'][0]['console'], fetch_tile)

    @classmethod
    def create(cls, renter, tile, seed):
        raw = RawinputParams(
            "rentcreate", {
                "_user": renter,
                "tile": int(tile),
                "seed": int(seed),
            }, "fadmin", "{}@active".format(renter)
        )
        eosiop_arams = EosioParams(raw.params_actions_list, keys[renter])
        net = NodeNetwork.push_transaction(eosiop_arams.trx_json)
        print(net)

    @property
    def statuses(self):
        print(self.id)
        raw = RawinputParams(
            "rentgets", {
                "_user": U_ADMIN,
                "rent": int(self.id),
            }, "fadmin", "{}@active".format(U_ADMIN)
        )
        eosiop_arams = EosioParams(raw.params_actions_list, keys[U_ADMIN])
        net = NodeNetwork.push_transaction(eosiop_arams.trx_json)
        _statuses = [_.split("|||") for _ in net['processed']['action_traces'][0]['console'].split('+++') if _]
        _statuses = [
            {'id': int(_[0]), 'status': _[2], 'timestamp': int(_[3])} for _ in _statuses
        ]
        return _statuses


class Tile(object):
    id = None
    owner = None
    rate = None
    x = None
    y = None
    is_occupied = None

    @classmethod
    def deserialize(cls, text):
        t = Tile()
        ordering = ['id', 'owner', 'rate', 'x', 'y', 'is_occupied']
        values = text.split('|||')

        for k, v in zip(ordering, values):
            setattr(t, k, v)

        t.is_occupied = True if t.is_occupied == 'true' else False

        return t

    @classmethod
    def get_all_tiles(cls):
        raw = RawinputParams(
            "tilegetall", {
                '_user': 'fadmin'
            }, "fadmin", "{}@active".format('fadmin')
        )
        eosiop_arams = EosioParams(raw.params_actions_list, keys['fadmin'])
        net = NodeNetwork.push_transaction(eosiop_arams.trx_json)
        return [Tile.deserialize(_) for _ in net['processed']['action_traces'][0]['console'].split('+++') if _]

    @classmethod
    def get_tile(cls, id):
        raw = RawinputParams(
            "tilegetall", {
                '_user': 'fadmin',
                'id': int(id),
            }, "fadmin", "{}@active".format('fadmin')
        )
        eosiop_arams = EosioParams(raw.params_actions_list, keys['fadmin'])
        net = NodeNetwork.push_transaction(eosiop_arams.trx_json)
        return Tile.deserialize(net['processed']['action_traces'][0]['console'])

    def to_json(self):
        json = {
            'id': int(self.id),
            'is_occupied': self.is_occupied
        }
        if self.is_occupied:
            rent = Rent.get_by_tile(self.id, fetch_tile=False)
            json['renter'] = rent.renter;
            json['crop'] = {'id': rent.seed.id, 'name': rent.seed.name}
            json['status'] = rent.statuses[-1]['status']
        return json


class Seed(object):
    id = None
    name = None

    @classmethod
    def deserialize(cls, text):
        s = Seed()
        ordering = ['id', 'name']
        values = text.split('|||')

        for k, v in zip(ordering, values):
            setattr(s, k, v)

        return s

    @classmethod
    def get_all_seeds(cls):
        raw = RawinputParams(
            "seedgetall", {
                '_user': 'fadmin'
            }, "fadmin", "{}@active".format('fadmin')
        )
        eosiop_arams = EosioParams(raw.params_actions_list, keys['fadmin'])
        net = NodeNetwork.push_transaction(eosiop_arams.trx_json)
        return [Seed.deserialize(_) for _ in net['processed']['action_traces'][0]['console'].split('+++') if _]

    @classmethod
    def get_seed(cls, id):
        raw = RawinputParams(
            "seedget", {
                '_user': 'fadmin',
                'id': id,
            }, "fadmin", "{}@active".format('fadmin')
        )
        eosiop_arams = EosioParams(raw.params_actions_list, keys['fadmin'])
        net = NodeNetwork.push_transaction(eosiop_arams.trx_json)
        return Seed.deserialize(net['processed']['action_traces'][0]['console'])
