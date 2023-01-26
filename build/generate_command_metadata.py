import re

CPP_FILENAME = 'command_utils'
COMMAND_FILES = [
  'chrome/app/chrome_command_ids.h',
  'brave/app/brave_command_ids.h'
]

IGNORE_COMMANDS = [
  "IDC_VISIT_DESKTOP_OF_LRU_USER_2",
  "IDC_VISIT_DESKTOP_OF_LRU_USER_3",
  "IDC_VISIT_DESKTOP_OF_LRU_USER_4",
  "IDC_VISIT_DESKTOP_OF_LRU_USER_5",
  "IDC_LACROS_DATA_MIGRATION",
  "IDC_MEDIA_TOOLBAR_CONTEXT_REPORT_CAST_ISSUE",
  "IDC_CONTENT_CONTEXT_QUICK_ANSWERS_INLINE_ANSWER",
  "IDC_CONTENT_CONTEXT_QUICK_ANSWERS_INLINE_QUERY",
  "IDC_BRAVE_COMMANDS_START"
]

command_regex = re.compile('^#define (IDC_([A-Z0-9]|_)+)\s+([0-9]+)$')

def generate_command_info(file):
  with open(file) as f:
    for line in f.readlines():
      m = re.match(command_regex, line)
      if not m: continue

      yield (m.group(1), m.group(3))

def get_all_commands():
  for file in COMMAND_FILES:
    for command in generate_command_info('../' + file):
      if command[0] in IGNORE_COMMANDS: continue
      yield command

def generate_cpp_header(commands, path):
  guard = "BRAVE_" + path.replace('/', '_').replace('.', '_').upper() + '_'
  return f"""
// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#ifndef BRAVE_BUILD_GENERATE_COMMAND_METADATA_H_
#define BRAVE_BUILD_GENERATE_COMMAND_METADATA_H_

#include <string>
#include <vector>

namespace commands {{

std::vector<uint16_t> GetCommands(); 
std::string GetCommandName(int command_id);
}}

#endif  // BRAVE_BUILD_GENERATE_COMMAND_METADATA_H_
  """

def generate_cpp_source(commands, path):
  command_includes = "\n".join(map(lambda x: f'#include "{x}"', COMMAND_FILES))

  def command_case_statement(command):
    text = " ".join(map(lambda x: x[0] + x[1:].lower(), command[0][4:] # Remove IDC_
      .split('_')))
    # TODO: Dump the command into a resource file so we get translations.
    return f"""
    case {command[0]}:
      return "{text}";
    """.strip()
  cases = "\n    ".join(map(command_case_statement, commands))
  return f"""
// Copyright (c) 2023 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "brave/{path[:-3]}.h"

#include "base/notreached.h"

{command_includes}

namespace commands {{
std::vector<uint16_t> GetCommands() {{
  return std::vector<uint16_t> {{{", ".join(map(lambda x: x[0], commands))}}};
}}

std::string GetCommandName(int command_id) {{
  switch (command_id) {{
    {cases}
  }}

  NOTREACHED();
  return "";
}}
}}
  """

def generate_command_utils():
  commands = list(get_all_commands())

  output_file = f'app/{CPP_FILENAME}'

  header_file = output_file + '.h'
  with open(header_file, 'w') as f:
    f.write(generate_cpp_header(commands, header_file))

  source_file = output_file + '.cc'
  with open(source_file, 'w') as f:
    f.write(generate_cpp_source(commands, source_file))

generate_command_utils()



