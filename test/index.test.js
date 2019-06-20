const kcp_node = require('../src')
const KCP = kcp_node.KCP

describe('kcp-node base unit test', () => {
	it('should have exports', () => {
		expect(typeof KCP).toBe('function')
		expect(typeof new KCP(3000)).toBe('object')
	})

	it('should throw error when incorrect parameter', () => {
		expect(() => new KCP()).toThrowError()
		expect(() => new KCP(undefined)).toThrowError()
		expect(() => new KCP(null)).toThrowError()
		expect(() => new KCP(true)).toThrowError()
		expect(() => new KCP('')).toThrowError()
		expect(() => new KCP([])).toThrowError()
		expect(() => new KCP({})).toThrowError()
	})

	it('should have correct properties', () => {
		const kcp = new KCP(3000)
		expect(typeof kcp).toBe('object')
	})
})
