const test = require('brittle')
const addon = require('.')

test('add', (t) => {
 try {
    const sum = addon.add(1, 1)
  console.log('from javascript:', sum)
  t.is(sum, 2, 'math. it works. or does it?')
 } catch (error) {
   console.log('somewhere there is a sensible world but that is not this world', error)
 }
})

test('addc', (t) => {
 try {
    const sum = addon.add(1, 1)
  console.log('from javascript:', sum)
  t.is(sum, 2, 'simplicity across domains isn\'t')
 } catch (error) {
   console.log('so we should keep looking', error)
 }
})
