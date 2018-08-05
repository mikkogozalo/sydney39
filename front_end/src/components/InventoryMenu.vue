<template>
  <div class="wrapper">
    <div class="handle">
      <img src="/static/building-3.png" />
      <div class="name">Inventory</div>
    </div>
    <div class="body">

    </div>
  </div>
</template>

<script>
  export default {
    name: 'InventoryMenu',
    data () {
      return {

        cropType: [{id: 1, name: 'carrot'}, {id: 2, name: 'lettuce'}, {id: 3, name: 'lemon'}],
        cropState: [{id: 1, name: 'seed'}, {id: 2, name: 'grow'}, {id: 3, name: 'harvest'}]
      }
    },
    computed: {

    },
    methods: {

    }
  }
</script>

<style lang="scss" scoped>

  .wrapper {
    bottom: 20px;
    position: fixed;
    right: 10px;
  }

  .handle {
    background-color: #e8e8e8;
    border-radius: 10px;
    box-shadow: 0px 9px 0px darken(#e8e8e8, 25), 0px 9px 25px rgba(0,0,0,.7);
    cursor: pointer;
    padding: 10px 10px 25px 10px;
    transition: all linear 0.1s;

    &:active {
      box-shadow: 0px 3px 0px darken(#e8e8e8, 25), 0px 3px 6px rgba(0,0,0,.9);
      top: 6px;
      transform: translateY(5px);
    }

    img {
      height: 150px;
      width: 150px;
    }

    div {
      text-shadow: 1px 1px 10px #000000;
      color: #fff;
      font-size: 1.3em;
    }
  }

  .body {

  }
</style>
