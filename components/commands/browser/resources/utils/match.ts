import { Command } from "../../../../../../out/Component/gen/brave/components/commands/common/commands.mojom.m";
import { allKeys } from "./accelerator";

export const match = (query: string, command: Command) => {
  if (command.id === parseInt(query)) return true

  const queryUpper = query.toUpperCase()
  if (command.name.toUpperCase().includes(queryUpper)) return true

  const keys = queryUpper.split('+').map(k => k.trim()).filter(k => k)
  return command.accelerators.some(a => {
    const acceleratorKeys = new Set(allKeys(a).map(k => k.toUpperCase()))
    return keys.every(k => acceleratorKeys.has(k))
  })
}
