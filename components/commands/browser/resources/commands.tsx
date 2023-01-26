import * as React from "react";
import { render } from "react-dom";
import * as CommandsMojo from "gen/brave/components/commands/common/commands.mojom.m.js";
import Command from "./components/Command";
import styled from "styled-components";

const CommandsContainer = styled.div`
  display: flex;
  flex-direction: column;
  gap: 4px;
`;

const FilterBox = styled.input`
  margin: 4px;
  padding: 4px;
  border: 1px solid lightgray;
`;

const api = CommandsMojo.CommandsService.getRemote();
api.getCommands().then(console.log);

function usePromise<T>(getPromise: () => Promise<T>, deps: any[]) {
  const [result, setResult] = React.useState<T>();
  React.useEffect(() => {
    getPromise().then(setResult);
  }, deps);

  return result;
}

function App() {
  const [filter, setFilter] = React.useState("");
  const [withAccelerator, setWithAccelerator] = React.useState(false);
  const commands = usePromise(
    () => api.getCommands().then((r) => r.commands),
    []
  );

  const filteredCommands = React.useMemo(
    () =>
      commands
        ?.filter((c) => {
          const lowerFilter = filter.toLowerCase();
          if (c.id == parseInt(filter)) return true;
          if (c.name.toLocaleLowerCase().includes(lowerFilter)) return true;
          return false;
        })
        .filter((c) => !withAccelerator || c.accelerators.length),
    [filter, withAccelerator, commands]
  );
  return (
    <CommandsContainer>
      <FilterBox value={filter} onChange={(e) => setFilter(e.target.value)} />
      <label>
        <input
          type="checkbox"
          checked={withAccelerator}
          onChange={(e) => setWithAccelerator(e.target.checked)}
        />
        Only with accelerator
      </label>
      {filteredCommands?.map((c) => (
        <Command key={c.id} command={c} />
      ))}
    </CommandsContainer>
  );
}

document.addEventListener("DOMContentLoaded", () =>
  render(<App />, document.getElementById("root"))
);
