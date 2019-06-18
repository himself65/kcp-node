const kcp_node = require('../src')

describe('kcp-node base unit test', () => {
	it('should have exports', () => {
		expect(typeof kcp_node.create).toBe('function')
	})

	it('should throw error when no parameter', () => {
		expect(() => kcp_node.create()).toThrowError()
		expect(() => kcp_node.create(null)).toThrowError()
		expect(() => kcp_node.create(undefined)).toThrowError()
		expect(() => kcp_node.create({})).toThrowError()
		expect(() => kcp_node.create([])).toThrowError()
		expect(() => kcp_node.create("")).toThrowError()
	})

	it('should function create returns an object', () => {
		expect(typeof kcp_node.create(3000)).toBe('object')
	})
})
