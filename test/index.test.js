const kcp_node = require('../src')

describe('kcp-node base unit test', () => {
	it('should have exports', () => {
		expect(typeof kcp_node.create).toBe('function')
	})

	it('should function create returns an object', () => {
		expect(typeof kcp_node.create(3000)).toBe('object')
	})
})
