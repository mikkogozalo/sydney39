from flask import Flask, request, jsonify
app = Flask(__name__)

from models import Seed, Tile, Rent
from flask_cors import CORS
CORS(app)

@app.route("/tiles")
def get_tiles():
    tiles = Tile.get_all_tiles()
    return jsonify([tile.to_json() for tile in tiles])

@app.route("/rent", methods=['POST'])
def create_rent():
    json = request.get_json()
    Rent.create(json['renter'], json['tile'], json['crop'])
    return jsonify({'status': 'success'})
