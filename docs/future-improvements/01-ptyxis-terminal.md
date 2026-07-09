# 01 - Ptyxis Terminal Support

Status: Planned

Source: `Nicolas01/Gittyup:ptyxis_terminal`

Upstream commits reviewed:
- `494e0c99` - support ptyxis as terminal search candidate
- `77abe905` - fix compilation
- `4e32d131` - Update RepoView.cpp
- `0b84d837` - cleanup

## Goal

Add Ptyxis as a supported Linux terminal for the `Open Terminal` action.

## Current Behavior

`RepoView::openTerminal()` auto-detects a terminal when `terminal/command` is unset. Linux candidates currently include `x-terminal-emulator`, `xdg-terminal`, `i3-sensible-terminal`, `gnome-terminal`, `konsole`, and `xterm`.

## Desired Behavior

When no custom terminal command is configured:
- Detect `ptyxis` on Linux.
- Launch Ptyxis in the repository working directory.
- Preserve existing behavior for other terminal candidates and for custom terminal commands.

## Implementation Plan

1. Update the Linux terminal candidate list in `src/ui/RepoView.cpp` to include `ptyxis`.
2. When `ptyxis` is the detected candidate, build a command that passes `--tab` and `--working-directory` with the repository workdir.
3. Keep the existing `sh -c` launch path to avoid cross-platform refactoring.
4. Add candidate details to the “No terminal executable found” message only if the code remains simple.

## Acceptance Criteria

- `Open Terminal` still works with existing terminals.
- If Ptyxis is installed and no custom terminal command is configured, GitNortek opens Ptyxis in the repository workdir.
- Custom configured terminal command behavior remains unchanged.
- `cmake --build build/local --target gitnortek` succeeds.

## Risk

Low. Changes are localized to terminal detection and launch command construction.
