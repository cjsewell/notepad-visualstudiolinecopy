## Introduction

Adds two commands to Notepad\+\+ `CopyAllowLine` and `CutAllowLine`, which adds Visual Studio style copy/cutting to Notepad\+\+.

CopyAllowLine - Copies the selected text if text is selected, or copies the current line if no text is selected.

CutAllowLine - Cutsthe selected text if text is selected, or cuts the current line if no text is selected.

See below for instructions on installing the plugin. 

Inspired by: <http://stackoverflow.com/questions/619754/how-to-mimic-visual-studios-ctrl-x-ctrl-v-functionality-in-notepad>

## How to Install

1. [Download the dll][1] for your version of Notepad++:
    - `VisualStudioLineCopy.Unicode.dll` is for Unicode version of Notepad++
    - `VisualStudioLineCopy.Ansi.dll` is for Ansi version of Notepad++
    - `VisualStudioLineCopy.Unicode.Net.dll` is an older, .NET version of the addon (for Unicode only).  
2. Place the file into your Notepad++\plugins\ folder, while Notepad++ is not running
3. Start Notepad++
4. Open up the shortcut mapper (Settings > Shortcut Mapper...)
5. Remove the existing shotcuts
    1. Select the "Scintilla commands" tab
    2. Remove the Ctrl+X and Ctrl+C shortcuts
        1. Double click the Ctrl+X shortcut 
        2. Remove the Ctrl+X shortcut using delete command on the bottom left
        3. Repeat 1 & 2 for the Ctrl+C shortcut
6. Add the plugin shortcuts (use the modify button with the command selected):
    1. Select the "Plugin commands" tab
    2. Find the CopyAllowLine and CutAllowLine plugin commands (towards the bottom)
    3. Add the Ctrl+C shortcut to the CopyAllowLine command
    4. Add the Ctrl+X shortcut to the CutAllowLine command

[1]: https://bitbucket.org/zastrowm/notepad-visualstudiolinecopy/downloads