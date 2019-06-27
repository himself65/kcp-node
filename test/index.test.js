const kcp_node = require('../src')
const KCP = kcp_node.KCP

const ErrorMessage = {
  length: /Must have [\S]+ parameter at least./,
  function: /function expected/,
  number: /number expected/,
}

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
    expect(() => new KCP()).toThrowError(ErrorMessage.length)
    expect(() => new KCP(undefined)).toThrowError(ErrorMessage.number)
    expect(() => new KCP(null)).toThrowError(ErrorMessage.number)
    expect(() => new KCP(true)).toThrowError(ErrorMessage.number)
    expect(() => new KCP('')).toThrowError(ErrorMessage.number)
    expect(() => new KCP([])).toThrowError(ErrorMessage.number)
    expect(() => new KCP({})).toThrowError(ErrorMessage.number)
  })

  it('function KCP()', () => {
    expect(typeof kcp).toBe('object')
  })

  it('function kcp.output setter', () => {
    expect(() => kcp.output = undefined).toThrowError(ErrorMessage.function)
    expect(() => kcp.output = 1).toThrowError(ErrorMessage.function)
    expect(() => kcp.output = '').toThrowError(ErrorMessage.function)
    expect(() => kcp.output = {}).toThrowError(ErrorMessage.function)
  })

  it('function kcp.output getter/setter', () => {
    expect(typeof kcp.output).toBe('function')
    expect((() => typeof (kcp.output = () => 'output'))()).toBe('function')
    expect(kcp.output()).toBe('output')
    expect(typeof kcp.output).toBe('function')
  })

  it('function kcp.setTimestamp', () => {
    expect(typeof KCP.prototype.setTimestamp).toBe('function')
    expect(typeof kcp.setTimestamp).toBe('function')
  })

  it('function kcp.setTimestamp', () => {
    expect(() => kcp.setTimestamp()).toThrowError(ErrorMessage.length)
    expect(() => kcp.setTimestamp(1)).toThrowError(ErrorMessage.length)
    expect(() => kcp.setTimestamp(1, 2)).toThrowError(ErrorMessage.length)
    expect(() => kcp.setTimestamp(1, 2, 3)).toThrowError(ErrorMessage.length)
    expect(() => kcp.setTimestamp('','','','')).toThrowError(ErrorMessage.number)
  })

  it('function kcp.setTimestamp', () => {
    expect(() => KCP.prototype.setTimestamp.call(kcp, 1, 2, 3, 4)).not.toThrow()
    expect(() => kcp.setTimestamp(1, 2, 3, 4)).not.toThrow()
  })

  it('function kcp.setWndSize', () => {
    expect(typeof KCP.prototype.setWndSize).toBe('function')
    expect(typeof kcp.setWndSize).toBe('function')
  })

  it('function kcp.setWndSize', () => {
    expect(() => kcp.setWndSize()).toThrowError(ErrorMessage.length)
    expect(() => kcp.setWndSize(1)).toThrowError(ErrorMessage.length)
    expect(() => kcp.setWndSize('','')).toThrowError(ErrorMessage.number)
  })

  it('function kcp.setWndSize', () => {
    expect(() => KCP.prototype.setWndSize.call(kcp, 1, 1)).not.toThrow()
    expect(() => kcp.setWndSize(1, 1)).not.toThrow()
  })
})
