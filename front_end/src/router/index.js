import Vue from 'vue'
import Router from 'vue-router'
import Farmland from '@/components/Farmland'

Vue.use(Router)

export default new Router({
  routes: [
    {
      path: '/',
      name: 'Farmland',
      component: Farmland
    }
  ]
})
