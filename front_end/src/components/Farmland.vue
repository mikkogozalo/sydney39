<template>
  <div class="background">
    <action-menu></action-menu>
    <div class="farmland">
      <div class="tile"
           v-for="tile in tiles"
           :key="tile.id"
           :class="{'active': tile.isSelected, 'others': tile.owner !== currentUser}"
           @click="selectTile(tile.id)">
        <img v-if="tile.cropType" :src="returnSpriteUrl(tile.cropType, tile.cropState)" :class="tile.cropState" />
        <i class="mdi mdi-plus" v-if="!tile.cropType"></i>
      </div>
    </div>
    <div class="tile-data" v-if="isShowInfo">
      <div class="">Owner: {{ getSelectedTile().owner }}</div>
      <div class="">Crop Type: {{ getSelectedTile().cropType }}</div>
      <div class="">Crop Status: {{ getSelectedTile().cropState }} (Projected 2 weeks to harvest)</div>
    </div>
    <marketplace-menu></marketplace-menu>
    <inventory-menu></inventory-menu>
    <confirm-rent v-if="isShowModal"></confirm-rent>
  </div>
</template>

<script>
import ActionMenu from '@/components/ActionMenu.vue'
import InventoryMenu from '@/components/InventoryMenu.vue'
import MarketplaceMenu from '@/components/MarketplaceMenu.vue'
import ConfirmRent from '@/components/ConfirmRent.vue'
import axios from 'axios'

export default {
  name: 'HelloWorld',
  components: { ActionMenu, InventoryMenu, MarketplaceMenu, ConfirmRent },
  data () {
    return {
      isShowModal: false,
      isShowInfo: false,
      currentUser: 1,
      tiles: [
      //   {
      //     id: 1,
      //     owner: 1,
      //     cropType: null,
      //     cropState: null,
      //     isSelected: false
      //   }, {
      //     id: 2,
      //     owner: 2,
      //     cropType: 'lemon',
      //     cropState: 'grow',
      //     isSelected: false
      //   }, {
      //     id: 3,
      //     owner: 2,
      //     cropType: 'lettuce',
      //     cropState: 'harvest',
      //     isSelected: false
      //   }, {
      //     id: 4,
      //     owner: 1,
      //     cropType: null,
      //     cropState: null,
      //     isSelected: false
      //   }, {
      //     id: 5,
      //     owner: 1,
      //     cropType: 'lettuce',
      //     cropState: 'harvest',
      //     isSelected: false
      //   }, {
      //     id: 6,
      //     owner: 2,
      //     cropType: 'lettuce',
      //     cropState: 'grow',
      //     isSelected: false
      //   }, {
      //     id: 7,
      //     owner: 2,
      //     cropType: 'carrot',
      //     cropState: 'harvest',
      //     isSelected: false
      //   }, {
      //     id: 8,
      //     owner: 1,
      //     cropType: 'lemon',
      //     cropState: 'harvest',
      //     isSelected: false
      //   }, {
      //     id: 9,
      //     owner: 1,
      //     cropType: 'carrot',
      //     cropState: 'grow',
      //     isSelected: false
      //   }
      ],
      tileCount: 9,
      cropType: [{id: 1, name: 'carrot'}, {id: 2, name: 'lettuce'}, {id: 3, name: 'lemon'}],
      cropState: [{id: 1, name: 'seed'}, {id: 2, name: 'grow'}, {id: 3, name: 'harvest'}]
    }
  },
  created() {
    axios.get('http://172.16.96.208:5000/tiles')
      .then(resp => {
        const data = resp.data;
        for (var i=0; i<9; i++) {
          if (data[i].is_occupied) {
            

            this.tiles.push({
              id: data[i].id,
              owner: 1,
              cropType: data[i].crop.name || null,
              cropState: data[i].status.name || null,
              isSelected: false
            });

          
          } else {
            
            this.tiles.push({
              id: data[i].id, // TODO:
              owner: 1,
              cropType: null,
              cropState: null,
              isSelected: false
            });
            
          }
        };
      });
    //   
    
  },
  methods: {
    returnSpriteUrl (cropType, cropState) {
      return `static/${cropType}_${cropState}.svg`
    },
    selectTile (tileId) {
      const tileSel = this.tiles.filter(function (obj) {
        return obj.id === tileId
      })[0];
      if (tileSel.cropType === undefined) {
        // Tile not occupied
        this.isShowModal = true
      } else {
        if (tileSel.isSelected) {
          tileSel.isSelected = false
        } else {
          tileSel.isSelected = true;
          this.isShowInfo = true;
        }
      }
    },
    getSelectedTile () {
      return this.tiles.filter(function(obj) {
        return obj.isSelected === true;
      })[0];
    }
  }
}
</script>

<style lang="scss" scoped>
  $tile-size: 15vw;
  $tile-row-count: 3;

  .background {
    background-image: url('/static/grass-s.png');
    height: 100vh;
    overflow: hidden;
    position: relative;
    width: 100vw;
  }

  .farmland {
    display: flex;
    flex-wrap: wrap;
    height: $tile-size * $tile-row-count;
    left: 50%;
    position: absolute;
    top: 50%;
    transform: translate(-50%, -50%) rotateX(60deg) rotateY(0deg) rotateZ(-45deg);
    width: $tile-size * $tile-row-count;
  }

  .tile {
    align-items: center;
    display: flex;
    /*background-color: #8b4513;*/
    background-image: url('/static/dirt.jpg');
    border: 5px solid #87c44f;
    box-sizing: border-box;
    cursor: pointer;
    height: $tile-size;
    justify-content: center;
    position: relative;
    transition: all linear 0.2s;
    width: $tile-size;

    &:after {
      background-color: rgba(255, 255, 255, 0);
      content: '';
      height: 100%;
      left: 0;
      position: absolute;
      top: 0;
      transition: background-color linear 0.2s;
      width: 100%;
      z-index: 1;
    }

    &:hover:after {
      background-color: rgba(255, 255, 255, 0.2);
    }

    &.active {
      border-color: #f2ff34;
    }

    &.others {
      opacity: 0.5;
    }

    img {
      transform: rotateX(-40deg) rotateY(0deg) rotateZ(52deg) skew(15deg) scale(1.1, 1.8);
      z-index: 3;

      &.seed {
        transform: translate(30px, -30px) rotateX(-40deg) rotateY(0deg) rotateZ(52deg) skew(15deg) scale(1.1, 1.8);
      }

      &.grow {
        transform: translate(24px, -23px) rotateX(-40deg) rotateY(0deg) rotateZ(52deg) skew(15deg) scale(1.1, 1.8);
      }
    }

    i {
      color: #ccc;
      font-size: 5em;
      transform: rotateX(-40deg) rotateY(0deg) rotateZ(52deg) skew(15deg) scale(1.0, 1.8);
    }
  }

  .tile-data {
    background-color: #e8eade;
    border: 5px solid #5d5851;
    border-radius: 10px;
    bottom: 10px;
    left: calc(50% - 250px);
    position: fixed;
    width: 500px;

    div {
      margin: 10px 0;
    }
  }

</style>
