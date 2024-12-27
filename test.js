const test = require('brittle')
const addon = require('.')

test('add', (t) => {
  t.is(addon.add(1, 1), 2)
})
