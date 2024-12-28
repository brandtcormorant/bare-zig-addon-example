const test = require('brittle')
const addon = require('.')

test('add', (t) => {
  const sum = addon.add(1, 1)
  console.log('from javascript:' sum)
  t.is(addon.add(sum, 2, 'math. it works.')
})
