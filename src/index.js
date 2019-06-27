const inner = require('../build/Release/kcp')

class KCP extends inner.KCP {
  constructor (conv, conf) {
    super(...arguments)
    if (typeof conf !== 'object') return
    const { address, port } = conf
    // todo
  }
}

module.exports = {
  default: KCP,
  KCP,
}
