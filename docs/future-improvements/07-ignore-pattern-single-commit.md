# 07 - Ignore Pattern Action

Status: Planned

Source: `Nicolas01/Gittyup:IgnorePatternSingleCommit`

Key upstream commit reviewed:
- `21614904` - IgnorePatternSingleCommit

## Goal

Add an ignore-pattern workflow from file context/status UI.

## Current Behavior

Ignoring generated or unwanted files generally requires manually editing ignore files outside the immediate file context workflow.

## Desired Behavior

- User can invoke an ignore action from a file context menu.
- GitNortek proposes a useful pattern for the selected file or path.
- The chosen pattern is written to the appropriate ignore file.
- The view refreshes after the ignore operation.

## Implementation Plan

1. Inspect current `FileContextMenu` and ignore-related code.
2. Port or recreate a small ignore dialog if needed.
3. Decide whether patterns should go to `.gitignore`, `.git/info/exclude`, or be user-selectable.
4. Ask for product decision if the destination is ambiguous.
5. Update this plan with the chosen policy before implementation.

## Acceptance Criteria

- Ignore action is available for relevant untracked/generated files.
- User can confirm or edit the pattern before writing.
- Ignore file update is safe and visible in the UI after refresh.
- Build succeeds.

## Risk

Medium-high. Needs a product decision around where ignore patterns should be written.
