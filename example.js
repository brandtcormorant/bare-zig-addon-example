const { add } = require('./index.js')

try {
  const sum = add(1, 1)
  console.log('from javascript:', sum)
} catch (error) {
  console.log(
    'even here in the middle of the shit somehow puzzles steal the show',
    error
  )
}
