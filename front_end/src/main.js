// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import App from './App'
import router from './router'
import 'mdi/css/materialdesignicons.min.css'
import '@/assets/main.css'

import lodash from 'lodash';

Vue.config.productionTip = false

// custom plugin
// inject lodash in this Vue.$_
Vue.use({
  install(VueObj) {
    Object.defineProperties(VueObj.prototype, {
      _: {
        get() {
          return lodash;
        }
      }
    });
  }
});

/* eslint-disable no-new */
new Vue({
  el: '#app',
  router,
  components: { App },
  template: '<App/>'
})