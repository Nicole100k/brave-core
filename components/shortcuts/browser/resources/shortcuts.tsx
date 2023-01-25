import * as React from 'react'
import { render } from 'react-dom'

function App() {
  return <div>
    Hello world!
  </div>
}

document.addEventListener('DOMContentLoaded', () => render(<App/>, document.getElementById('root')))
