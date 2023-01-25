import * as React from "react";
import * as ShortcutsMojo from "gen/brave/components/shortcuts/common/shortcuts.mojom.m.js";
import styled from "styled-components";

const Grid = styled.div`
  display: grid;
  grid-template-columns: 2 1fr;
`;

const Column = styled.div`
  display: flex;
  flex-direction: column;
`;

function Accelerator({
  accelerator
}: {
  accelerator: ShortcutsMojo.Accelerator;
}) {
  return (
    <div>
      {[accelerator.keycode, ...accelerator.modifiers].map((k, i) => (
        <kbd key={i}>{k}</kbd>
      ))}
    </div>
  );
}

export default function Command({
  command
}: {
  command: ShortcutsMojo.Command;
}) {
  return (
    <Grid>
      <div>{command.name}</div>
      <Column>
        {command.accelerators.map((a, i) => (
          <Accelerator key={i} accelerator={a} />
        ))}
      </Column>
    </Grid>
  );
}
