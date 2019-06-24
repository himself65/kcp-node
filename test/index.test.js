const kcp_node = require('../src')
const KCP = kcp_node.KCP

describe('kcp-node base unit test', () => {
  let kcp = null
  beforeEach(() => {
    kcp = new KCP(3000)
  })

  it('should have exports', () => {
    expect(typeof KCP).toBe('function')
    expect(typeof new KCP(3000)).toBe('object')
  })

  it('function KCP()', () => {
    expect(() => new KCP()).toThrowError()
    expect(() => new KCP(undefined)).toThrowError()
    expect(() => new KCP(null)).toThrowError()
    expect(() => new KCP(true)).toThrowError()
    expect(() => new KCP('')).toThrowError()
    expect(() => new KCP([])).toThrowError()
    expect(() => new KCP({})).toThrowError()
  })

  it('function KCP()', () => {
    expect(typeof kcp).toBe('object')
  })

  it('function kcp.output setter', () => {
    expect(() => kcp.output = undefined).toThrowError()
    expect(() => kcp.output = 1).toThrowError()
    expect(() => kcp.output = '').toThrowError()
    expect(() => kcp.output = {}).toThrowError()
  })

  it('function kcp.output getter/setter', () => {
    expect(typeof kcp.output).toBe('function')
    expect((() => typeof (kcp.output = () => 'output'))()).toBe('function')
    expect(kcp.output()).toBe('output')
    expect(typeof kcp.output).toBe('function')
  })
})
