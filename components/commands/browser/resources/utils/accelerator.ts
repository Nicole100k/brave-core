import { Accelerator } from "../../../../../../out/Component/gen/brave/components/commands/common/commands.mojom.m";

export const allKeys = (accelerator: Accelerator) => [...accelerator.modifiers, accelerator.keycode]
