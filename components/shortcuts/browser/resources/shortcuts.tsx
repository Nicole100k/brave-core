import * as React from 'react'
import { render } from 'react-dom'
import * as ShortcutsMojo from 'gen/brave/components/shortcuts/common/shortcuts.mojom.m.js'

const api = ShortcutsMojo.ShortcutsService.getRemote()
api.getCommands().then(console.log)

function App() {
  return <div>
    Hello world!
  </div>
}

document.addEventListener('DOMContentLoaded', () => render(<App/>, document.getElementById('root')))
