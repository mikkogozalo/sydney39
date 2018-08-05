<template>
  <div class="wrapper">
    <div v-if="isShowQuestion">
      <h2>Rent Farm Tile</h2>
      <p>You will be renting this tile of farmland until the completion of your crop's life cycle.</p>
      <p>Are you sure to continue?</p>
      <button class="no" @click="modalNo">No</button>
      <button class="yes" @click="modalYes">Yes</button>
    </div>
    <div v-if="isShowPickFood">
      <h2>Pick a produce!</h2>
      <ul>
        <li @click="submitProduce('carrot')">
          <img src="static/carrot.svg"/>
          <div>Carrot</div>
        </li>
        <li @click="submitProduce('lettuce')">
          <img src="static/lettuce.svg"/>
          <div>Lettuce</div>
        </li>
        <li @click="submitProduce('lemon')">
          <img src="static/lemon.svg"/>
          <div>Lemon</div>
        </li>
      </ul>
    </div>
    <button class="close" @click="modalNo">X</button>
  </div>
</template>

<script>
import axios from 'axios'

  export default {
    name: 'ConfirmRent',
    data () {
      return {
        isShowQuestion: true,
        isShowPickFood: false,

        cropType: [{id: 1, name: 'carrot'}, {id: 2, name: 'lettuce'}, {id: 3, name: 'lemon'}],
        cropState: [{id: 1, name: 'seed'}, {id: 2, name: 'grow'}, {id: 3, name: 'harvest'}]
      }
    },
    methods: {
      modalNo() {
        this.$parent.isShowModal = false
      },
      modalYes() {
        // Call endpoint
        this.isShowQuestion = false
        this.isShowPickFood = true
      },
      submitProduce(produce) {
        const submitData = {crop: 2, renter: 'sage', tile: 1}

        axios.post('http://172.16.96.208:5000/rent', submitData)
          .then(() => {
            this.$parent.isShowModal = false
          });
      }
    }
  }
</script>

<style lang="scss" scoped>

  .wrapper {
    background-color: #e8eade;
    border: 5px solid #5d5851;
    border-radius: 10px;
    position: fixed;
    left: 50%;
    padding: 30px;
    top: 50%;
    transform: translate(-50%, -50%);
  }

  button.close {
    background-color: #cc4010;
    border-radius: 10px;
    box-shadow: 0px 6px 0px darken(#cc4010, 25), 0px 9px 25px rgba(0,0,0,.7);
    color: #fff;
    text-shadow: 1px 1px 10px #000000;
    cursor: pointer;
    font-family: 'Supercell-magic';
    font-size: 1em;
    margin: 15px 10px;
    padding: 10px 15px;
    position: absolute;
    right: 10px;
    top: 10px;
    transition: all linear 0.1s;

    &:active {
      box-shadow: 0px 3px 0px darken(#cc4010, 25), 0px 3px 6px rgba(0,0,0,.9);
      top: 6px;
      transform: translateY(5px);
    }
  }

  button.yes {
    background-color: #5dad10;
    border-radius: 10px;
    box-shadow: 0px 6px 0px darken(#5dad10, 25), 0px 9px 25px rgba(0,0,0,.7);
    color: #fff;
    text-shadow: 1px 1px 10px #000000;
    cursor: pointer;
    font-family: 'Supercell-magic';
    font-size: 1.3em;
    margin: 15px 10px;
    padding: 10px 25px;
    transition: all linear 0.1s;

    &:active {
      box-shadow: 0px 3px 0px darken(#5dad10, 25), 0px 3px 6px rgba(0,0,0,.9);
      top: 6px;
      transform: translateY(5px);
    }
  }

  button.no {
    background-color: #cc4010;
    border-radius: 10px;
    box-shadow: 0px 6px 0px darken(#cc4010, 25), 0px 9px 25px rgba(0,0,0,.7);
    color: #fff;
    text-shadow: 1px 1px 10px #000000;
    cursor: pointer;
    font-family: 'Supercell-magic';
    font-size: 1.3em;
    margin: 15px 10px;
    padding: 10px 25px;
    transition: all linear 0.1s;

    &:active {
      box-shadow: 0px 3px 0px darken(#cc4010, 25), 0px 3px 6px rgba(0,0,0,.9);
      top: 6px;
      transform: translateY(5px);
    }
  }

  ul {
    display: flex;
    flex-direction: row;
    list-style-type: none;
    padding: none;
  }

  li {
    cursor: pointer;
    flex: 30%;
    border-radius: 10px;
    margin: 10px;
    padding: 10px;
    border: 2px solid #ccc;
    transition: all linear 0.2s;
  }

  li:hover {
    border-color: #777;
  }

  li img {
    margin-bottom: 15px;
    height: 100px;
  }



</style>
